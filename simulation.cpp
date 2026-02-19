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

    // TIMER : Fluidité visuelle
    QTimer* timerAnimation = new QTimer(this);
    connect(timerAnimation, &QTimer::timeout, this, [this]() {
        for (int i = 0; i < NB_INSTRUMENTS; ++i) {
            for (IndicateurComponent* a : listeIndicateurs[i]) a->mettreAJourAnimation();
        }
        });
    timerAnimation->start(16); // Change la valeur du timer pour changer la fluidité

    // TIMER : Mise à jour des données (TEMPORAIRE, POUR TESTER LES IMAGES, DONNE DES VALEURS RANDOMS A CHAQUE SECONDES)
    QTimer* timerDonnees = new QTimer(this);
    connect(timerDonnees, &QTimer::timeout, this, [this]() {

        // setAngleInstrument: Demande 3 éléments, 
        // 1: Enum de l'instrument (ex: Anemometre)
        // 2: index de l'indicateurComponent dans la liste, dans le même ordre qu'ils sont rajoutées 
        // 3: Degrès de l'angle partant de en haut. 90 donnerait que indicateurComponent pointe vers la droite. -90 pointerait vers la gauche.

        // setPosition: Demande 4 éléments,
        // 1: Enum de l'instrument (ex: Anemometre)
        // 2: index de l'indicateurComponent dans la liste, dans le même ordre qu'ils sont rajoutées 
        // 3: la nouvelle position x, marche comme un setter et va lerp vers la valeur
        // 4: la nouvelle position y

        setAngleInstrument(Anemometre, 0, 60 + QRandomGenerator::global()->bounded(140));

        setAngleInstrument(Altimetre, 0, QRandomGenerator::global()->bounded(-360, 361));
        setAngleInstrument(Altimetre, 1, QRandomGenerator::global()->bounded(-360, 361));

        setAngleInstrument(Variometre, 0, QRandomGenerator::global()->bounded(-360, 361));

        setAngleInstrument(Cap, 0, QRandomGenerator::global()->bounded(-360, 361));

        setAngleInstrument(Virage, 0, QRandomGenerator::global()->bounded(-50, 51));
        setPosition(Virage, 1, QRandomGenerator::global()->bounded(-50, 51), -103.5);

        double horizonRandomAngle = QRandomGenerator::global()->bounded(-50, 51);

        setAngleInstrument(Horizon, 0, horizonRandomAngle);
        setPosition(Horizon, 0, QRandomGenerator::global()->bounded(-50, 51), QRandomGenerator::global()->bounded(-50, 51));
        setAngleInstrument(Horizon, 1, horizonRandomAngle);
        });
    timerDonnees->start(1000);
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