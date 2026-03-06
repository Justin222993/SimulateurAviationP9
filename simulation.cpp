#include "simulation.h"

Simulation::Simulation(QWidget* parent) : QWidget(parent) {
    this->setStyleSheet("background-color: black;");

    // Fond du tableau de bord ( EN CE MOMENT JE L'AI ENLEVER PARCE QUE C'ÉTAIT PAS BEAU PIS IRRELEVENT)
    fondDashboard = new QLabel(this);
    fondDashboard->setPixmap(QPixmap("ressources/simulateur/dashboard.png"));
    fondDashboard->setScaledContents(true);
    fondDashboard->lower();

    // C'est ici que je le cache
    fondDashboard->hide();

    setupIndicateurs();

    // TIMER : Fluidité visuelle
    timerAnimation = new QTimer(this);
    connect(timerAnimation, &QTimer::timeout, this, [this]() {
        for (int i = 0; i < NB_INSTRUMENTS; ++i) {
            for (IndicateurComponent* a : listeIndicateurs[i]) a->mettreAJourAnimation();
        }
    });

    // TIMER : Mise à jour des données (TEMPORAIRE, POUR TESTER LES IMAGES, DONNE DES VALEURS RANDOMS A CHAQUE SECONDES)
    timerDonnees = new QTimer(this);
    connect(timerDonnees, &QTimer::timeout, this, [this]() {
        p.calculateNewPosition();

        std::cout << "\033[H\033[J";

        std::cout << std::fixed << std::setprecision(2) << std::left
            << "Speed: " << std::setw(8) << p.getSpeed()
            << "Alt: " << std::setw(10) << p.getAltitude()
            << "X: " << std::setw(10) << p.getPositionX()
            << "Y: " << std::setw(10) << p.getPositionY()
            << "Pitch: " << std::setw(7) << p.getPitch()
            << "Yaw: " << std::setw(7) << p.getYaw()
            << "Roll: " << std::setw(7) << p.getRoll()
            << "Fuel: " << std::setw(7) << p.getFuel() << "\n";

        messagesWarning();
        messagesMorts();

        std::cout << std::flush;

        // setAngleInstrument: Demande 3 éléments, 
        // 1: Enum de l'instrument (ex: Anemometre)
        // 2: index de l'indicateurComponent dans la liste, dans le même ordre qu'ils sont rajoutées 
        // 3: Degrès de l'angle partant de en haut. 90 donnerait que indicateurComponent pointe vers la droite. -90 pointerait vers la gauche.

        // setPosition: Demande 4 éléments,
        // 1: Enum de l'instrument (ex: Anemometre)
        // 2: index de l'indicateurComponent dans la liste, dans le même ordre qu'ils sont rajoutées 
        // 3: la nouvelle position x, marche comme un setter et va lerp vers la valeur
        // 4: la nouvelle position y

        handleAnemometre();
        handleTachymetre();
        handleBoussole();

        //setAngleInstrument(Altimetre, 0, QRandomGenerator::global()->bounded(-360, 361));
        //setAngleInstrument(Altimetre, 1, QRandomGenerator::global()->bounded(-360, 361));

        //setAngleInstrument(Variometre, 0, QRandomGenerator::global()->bounded(-360, 361));

        setAngleInstrument(Cap, 0, -p.getYaw());

        setAngleInstrument(Virage, 0, p.getRoll());
        //setPosition(Virage, 1, QRandomGenerator::global()->bounded(-50, 51), -103.5);

        double horizonRandomAngle = QRandomGenerator::global()->bounded(-50, 51);

        setAngleInstrument(Horizon, 0, horizonRandomAngle);
        setPosition(Horizon, 0, QRandomGenerator::global()->bounded(-50, 51), QRandomGenerator::global()->bounded(-50, 51));
        setAngleInstrument(Horizon, 1, horizonRandomAngle);
        });
}

void Simulation::messagesWarning() {
    if (p.getAltitude() <= 1000) {
        std::cout << "| ALTITTUDE CRITICALLY LOW | -> Should be over 1000\n";
    }

    if (p.getSpeed() <= 10) {
        std::cout << "| SPEED CRITICALLY LOW | -> Should be over 10\n";
    }

    if (p.getFuel() <= 50) {
        std::cout << "| FUEL CRITICALLY LOW | -> Should be over 50\n";
    }
}

void Simulation::messagesMorts() {
    if (p.getAltitude() <= 0) {
        std::cout << "| CRASH | -> Hit the ground\n";
        timerDonnees->stop();
    }
}

void Simulation::demarrer() {
    // création de l'avion
    double initialSpeed = 40.0;
    double initialAlt = 5000.0;
    double startX = 0.0;
    double startY = 0.0;
    double initialPitch = 5.0;
    double initialYaw = 0.0;
    double initialRoll = 0.0;
    double inititalFuel = 1000;

    p = Avion(initialSpeed, initialAlt, startX, startY, initialPitch, initialYaw, initialRoll, inititalFuel);

    std::thread t(&Simulation::inputListener, this, std::ref(p));
    t.detach();

    timerAnimation->start(16); // Change la valeur du timer pour changer la fluidité
    timerDonnees->start(50); // Chaque 50 milliseconde, update console/donnees
}

struct PointValeur {
    double valeur;
    double angle;
};

void Simulation::handleAnemometre() {
    std::vector<PointValeur> pointsReference = {
        {0.0,   0.0},
        {40.0,  20.0},
        {60.0,  60.0},
        {80.0,  100.0},
        {120.0, 180.0},
        {140.0, 220.0},
        {160.0, 260.0},
        {180.0, 300.0},
        {200.0, 340.0}
    };

    double speed = p.getSpeed();
    double finalAngle = 0.0;

    // Logique pour placer l'aiguille de vitesse parfaitement ou on veux
    if (speed <= pointsReference.front().valeur) {
        finalAngle = pointsReference.front().angle;
    }
    else if (speed >= pointsReference.back().valeur) {
        finalAngle = pointsReference.back().angle;
    }
    else {
        // On cherche entre quels points on se trouve
        for (size_t i = 0; i < pointsReference.size() - 1; ++i) {
            if (speed >= pointsReference[i].valeur && speed <= pointsReference[i + 1].valeur) {
                double v1 = pointsReference[i].valeur;
                double v2 = pointsReference[i + 1].valeur;
                double a1 = pointsReference[i].angle;
                double a2 = pointsReference[i + 1].angle;

                // Interpolation linéaire entre les deux points
                double ratio = (speed - v1) / (v2 - v1);
                finalAngle = a1 + ratio * (a2 - a1);
                break;
            }
        }
    }

    setAngleInstrument(Anemometre, 0, finalAngle);
}

void Simulation::handleTachymetre() {
    double speed = p.getSpeed();
    if (speed < 0)   speed = 0;
    if (speed > 200) speed = 200;

    // Même formule que ton ancienne fonction console
    double rpm = (speed / 200.0) * 3500.0;

    // Points de référence RPM ? angle aiguille
    // Même logique que handleAnemometre()
    // START: -225° from top, SWEEP: 270°, MAX: 3500 RPM
    std::vector<PointValeur> pointsReference = {
        {0.0,    -225.0},
        {500.0,  -186.4},
        {1000.0, -147.9},
        {1500.0, -109.3},
        {2000.0,  -70.7},
        {2500.0,  -32.1},
        {3000.0,    6.4},
        {3500.0,   45.0}
    };

    double finalAngle = 0.0;

    if (rpm <= pointsReference.front().valeur) {
        finalAngle = pointsReference.front().angle;
    }
    else if (rpm >= pointsReference.back().valeur) {
        finalAngle = pointsReference.back().angle;
    }
    else {
        for (size_t i = 0; i < pointsReference.size() - 1; ++i) {
            if (rpm >= pointsReference[i].valeur && rpm <= pointsReference[i + 1].valeur) {
                double v1 = pointsReference[i].valeur;
                double v2 = pointsReference[i + 1].valeur;
                double a1 = pointsReference[i].angle;
                double a2 = pointsReference[i + 1].angle;
                double ratio = (rpm - v1) / (v2 - v1);
                finalAngle = a1 + ratio * (a2 - a1);
                break;
            }
        }
    }

    setAngleInstrument(Tachymetre, 0, finalAngle);

    std::cout << "[Tachymetre] Speed=" << std::fixed << std::setprecision(2)
        << speed << " -> RPM=" << std::setprecision(0) << rpm << "\n";
}

void Simulation::handleBoussole() {
    double cap = p.getYaw();

    // Normalise entre 0 et 360
    while (cap >= 360.0) cap -= 360.0;
    while (cap < 0.0)    cap += 360.0;

    // Le ruban fait 1800px de large pour 2 rotations complètes (720°)
    // donc 2.5px par degré. On translate négativement pour que le cap
    // courant soit centré sous la ligne de foi (lubber line).
    // On utilise modulo 900 pour rester dans la première répétition
    // et éviter que le ruban sorte de ses bornes.
    double pxParDegre = 2.5;
    double offsetX = -(cap * pxParDegre);

    // setPosition prend x et y en pixels depuis le centre de l'instrument.
    // Le ruban (echelle 1.0f, pivot 2.0f) est centré sur le widget.
    // On déplace uniquement en X.
    setPosition(Boussole, 0, offsetX, 0);

    // Debug console (optionnel, tu peux enlever)
    const char* lettre = "N";
    if (cap >= 45 && cap < 135) lettre = "E";
    else if (cap >= 135 && cap < 225) lettre = "S";
    else if (cap >= 225 && cap < 315) lettre = "W";
    std::cout << "[Boussole] Cap=" << std::fixed << std::setprecision(2)
        << cap << " deg (" << lettre << ")\n";
}

void Simulation::setAngleInstrument(int indexInstrument, int indexIndicateur, double angle) {
    if (indexInstrument >= 0 && indexInstrument < NB_INSTRUMENTS) {
        if (indexIndicateur >= 0 && indexIndicateur < listeIndicateurs[indexInstrument].size()) {
            listeIndicateurs[indexInstrument][indexIndicateur]->setAngleCible(angle);
        }
    }
}

void Simulation::setPosition(int indexInstrument, int indexIndicateur, double positionX, double positionY) {
    if (indexInstrument >= 0 && indexInstrument < NB_INSTRUMENTS) {
        if (indexIndicateur >= 0 && indexIndicateur < listeIndicateurs[indexInstrument].size()) {
            listeIndicateurs[indexInstrument][indexIndicateur]->setPosition(positionX, positionY);
        }
    }
}

void Simulation::inputListener(Avion& p) {
    while (true) {
        if (_kbhit()) { // _kbhit() checks if a key was pressed sans arrêter le loop
            char input = _getch(); // Gets the character immediately
            if (input == 'w') {
                p.upPitch(5);
            }
            else if (input == 's') {
                p.downPitch(5);
            }
            else if (input == 'a') {
                p.rollLeft(5);
            }
            else if (input == 'd') {
                p.rollRight(5);
            }
            else if (input == 'p') {
                if (!p.upSpeed(5)) {
                    std::cout << "| NO FUEL !!!!! |";
                }
            }
            else if (input == 'l') {
                p.downSpeed(5);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Simulation::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (!fondDashboard || fondDashboard->pixmap().isNull()) return;

    QSize tailleCible = fondDashboard->pixmap().size().scaled(this->size(), Qt::KeepAspectRatio);
    int dashX = (width() - tailleCible.width()) / 2;
    int dashY = (height() - tailleCible.height()) / 2;

    // Positionnement du fond (En ce moment caché)
    fondDashboard->setGeometry(dashX, dashY, tailleCible.width(), tailleCible.height());

    // Positionnement des instruments (En ce moment en grid)
    int diametre = tailleCible.width() * 0.182;
    double posX[] = { 0.185, 0.395, 0.605, 0.815 };
    double posY[] = { 0.330, 0.665 };

    for (int i = 0; i < NB_INSTRUMENTS; ++i) {
        int centreX = dashX + (tailleCible.width() * posX[i % 4]);
        int centreY = dashY + (tailleCible.height() * posY[i / 4]);
        QRect zone(centreX - diametre / 2, centreY - diametre / 2, diametre, diametre);

        instruments[i]->setGeometry(zone);
        for (IndicateurComponent* a : listeIndicateurs[i]) {
            a->setGeometry(zone);
            a->raise();
        }
    }
}

void Simulation::setupIndicateurs() {
    // Setup des 8 Instruments avec leur image de background
    for (int i = 0; i < NB_INSTRUMENTS; ++i) {
        instruments[i] = new QLabel(this);

        // On récupère le nom depuis la liste synchronisée du Header
        QString nomFichier = NOMS_IMAGES.at(i);
        QString cheminComplet = QString("ressources/simulateur/%1.png").arg(nomFichier);

        QPixmap pix(cheminComplet);
        if (pix.isNull()) {
            qDebug() << "Erreur : Impossible de charger" << cheminComplet;
        }
        else {
            instruments[i]->setPixmap(pix);
        }

        instruments[i]->setScaledContents(true);
        instruments[i]->setAttribute(Qt::WA_TranslucentBackground);
        instruments[i]->raise();
    }

    // CRÉATION DES COMPONENT DANS LES INSTTRUMENTS (EX: Aiguille, image d'avion, etc...)
    // 
    // Utilisation des noms de l'enum du header (Ex: Anemometre, Altimetre...)

    // IndicateurComponent prend 4 ou 6 arguments: 
    // 1: this 
    // 2: Image qu'on veut 
    // 3: Scale de l'image (1.0f = normale)
    // 4: Point de rotation de l'image ( 2.0f étant le milieu de l'image, 1.5f on dessend dans le bas de l'image, 2.5f on monte dans l'image)
    // (5-6) OPTIONEL: - Si on ne les définits pas, default = (0,0), ou milieu de l'instrument. Il faut le définir si on veux que l'image commence a une certaine position.
    // On veut le définir si on veut commencer a un endroit, même si la modification setPosition change la position, elle lerp, donc sa va prendre du temps pour qu'elle ce place, donc on set la position initale aussi.
    // 5: Position initiale en pixel x 
    // 6: Position initiale en pixel y

    // Anemometre
        // aiguille
    listeIndicateurs[Anemometre].append(new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    // Altimètre
        // Grande aiguille
    listeIndicateurs[Altimetre].append(new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));
    // Petite aiguille
    listeIndicateurs[Altimetre].append(new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.4f, 1.5f));

    // Variometre
        // aiguille
    listeIndicateurs[Variometre].append(new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    // Cap
        // N/W/S/E
    listeIndicateurs[Cap].append(new IndicateurComponent(this, "ressources/simulateur/valeurs-cap.png", 1.05f, 2.0f));

    // Coordonateur de virage
        // Image de l'avion
    listeIndicateurs[Virage].append(new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-aiguille.png", 1.0f, 2.0f));
    // Cercle indicateur de skidding
    listeIndicateurs[Virage].append(new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-cercle.png", 0.13f, 2.0f, 0, -103.5));

    // Horizon Artifiel
        // Ciel/sol
    listeIndicateurs[Horizon].append(new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-cieletsol.png", 2.0f, 2.0f));
    // Fléche rouge indicateur de tournant
    listeIndicateurs[Horizon].append(new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-fleche-rouge.png", 1.0f, 1.3f));
    // Couche au dessus que j'ai mis pour chacher le overdraft du ciel/sol (Vu que c'est une géante image)
    listeIndicateurs[Horizon].append(new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel.png", 1.0f, 2.0f));

    // Tachymetre
    listeIndicateurs[Tachymetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f)
    );

    instruments[Boussole]->setPixmap(QPixmap("ressources/simulateur/boussole.png"));

    // Ruban des points cardinaux - se déplace en X selon le cap
    // echelle 1.0f pour qu'il remplisse bien la fenêtre du boîtier
    // pivotRatio 2.0f = centré (point de rotation au milieu de l'image)
    listeIndicateurs[Boussole].append(
        new IndicateurComponent(
            this,
            "ressources/simulateur/ruban-points-cardinaux.png",
            1.0f,   // echelle
            2.0f,   // pivotRatio centré
            0, 0    // position initiale centrée
        )
    );

    // Boîtier par-dessus le ruban (fenêtre transparente)
    // echelle 1.05f pour couvrir les bords du clip circulaire
    listeIndicateurs[Boussole].append(
        new IndicateurComponent(
            this,
            "ressources/simulateur/boussole.png",
            1.05f,  // echelle légèrement plus grand pour couvrir le cercle
            2.0f,   // pivotRatio centré
            0, 0
        )
    );
}