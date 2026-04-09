#include "simulation.h"
#include <iostream>
#include <iomanip>
#include <thread>

// J'ai enlever beaucoup de commentaires d'explications car sa devrait etre acquis
// Sinon vous pouvez retourner dans le github ou lire le code

Simulation::Simulation(QWidget* parent) : QWidget(parent) {
    this->setStyleSheet("background-color: black;");

    // Scene 3D
    view3d = new QQuickWidget(this);
    view3d->setSource(QUrl::fromLocalFile("scene3D.qml"));
    view3d->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view3d->setAttribute(Qt::WA_AlwaysStackOnTop, false);
    view3d->lower();
    view3d->show();

    setupIndicateurs();

    // TIMER : Fluidité visuelle
    timerAnimation = new QTimer(this);
    connect(timerAnimation, &QTimer::timeout, this, [this]() {
        for (int i = 0; i < SimulationIndicateurs::NB_INSTRUMENTS; ++i) {
            for (IndicateurComponent* a : listeIndicateurs[i]) a->mettreAJourAnimation();
        }
        });

    // TIMER : Mise à jour des données
    timerDonnees = new QTimer(this);
    connect(timerDonnees, &QTimer::timeout, this, [this]() {
        Avion& p = sim.getAvion();
        p.calculateNewPosition();

        if (view3d && view3d->rootObject()) {
            QVariantMap data;
            data["x"] = (double)p.getPositionX();
            data["y"] = (double)p.getPositionY();
            data["altitude"] = (double)p.getAltitude();
            data["pitch"] = (double)p.getPitch();
            data["yaw"] = (double)p.getYaw();
            data["roll"] = (double)p.getRoll();

            QMetaObject::invokeMethod(static_cast<QObject*>(view3d->rootObject()),
                "updateCamera",
                Qt::AutoConnection,
                Q_ARG(QVariant, QVariant::fromValue(data)));
        }

        // Refresh de la console perpetuelle
        std::cout << "\033[H\033[J"; // clears terminal
        std::cout << std::fixed << std::setprecision(2) << std::left
            << "Speed: " << std::setw(8) << p.getSpeed()
            << "Alt: " << std::setw(10) << p.getAltitude()
            << "X: " << std::setw(10) << p.getPositionX()
            << "Y: " << std::setw(10) << p.getPositionY()
            << "Pitch: " << std::setw(7) << std::fmod(p.getPitch(), 360.0)
            << "Yaw: " << std::setw(7) << std::fmod(p.getYaw(), 360.0)
            << "Roll: " << std::setw(7) << std::fmod(p.getRoll(), 360.0)
            << "Fuel: " << std::setw(7) << p.getFuel()
            << "\n------------ Arduino -----------\n"
            << "Connected: " << std::setw(2) << (sim.getSerialManager()->ArduinoIsConnected() ? "True" : "False")
            << "Joystick X: " << std::setw(7) << sim.getSerialManager()->GetJoystick().curlX
            << "Joystick Y: " << std::setw(7) << sim.getSerialManager()->GetJoystick().curlY
            << "Potentiometer: " << std::setw(7) << sim.getSerialManager()->GetPotentiometer()
            << "Master Switch: " << std::setw(7) << (sim.getSerialManager()->GetMasterSwitch() ? "ON" : "OFF")
            << "Encoder: " << std::setw(7) << sim.getSerialManager()->GetEncoder()
            << "Accel Bump: " << std::setw(7) << (sim.getSerialManager()->GetAccelBump() ? "YES" : "NO")
            << "\n";

        messagesWarning();
        messagesMorts();

        sim.handleAnemometre();
        sim.handleTachymetre();
        sim.handleBoussole();

        sim.setAngleInstrument(SimulationIndicateurs::Cap, 0, -p.getYaw());
        sim.setAngleInstrument(SimulationIndicateurs::Virage, 0, p.getRoll());

        double horizonAngle = QRandomGenerator::global()->bounded(-50, 51);
        sim.setAngleInstrument(SimulationIndicateurs::Horizon, 0, horizonAngle);
        sim.setPosition(SimulationIndicateurs::Horizon, 0,
            QRandomGenerator::global()->bounded(-50, 51),
            QRandomGenerator::global()->bounded(-50, 51));
        sim.setAngleInstrument(SimulationIndicateurs::Horizon, 1, horizonAngle);
        });
}

void Simulation::messagesWarning() {
    Avion& p = sim.getAvion();
    if (p.getAltitude() <= 1000) std::cout << "| ALTITUDE CRITICALLY LOW | -> Should be over 1000\n";
    if (p.getSpeed() <= 10)   std::cout << "| SPEED CRITICALLY LOW | -> Should be over 10\n";
    if (p.getFuel() <= 50)   std::cout << "| FUEL CRITICALLY LOW | -> Should be over 50\n";
}

void Simulation::messagesMorts() {
    if (sim.getAvion().getAltitude() <= 0) {
        std::cout << "| CRASH | -> Hit the ground\n";
        timerDonnees->stop(); // arrete la simulation
    }
}

void Simulation::demarrer() {
    double initialSpeed = 40.0;
    double initialAlt = 3000.0;
    double startX = 0.0;
    double startY = 0.0;
    double initialPitch = 0.0;
    double initialYaw = 30.0;
    double initialRoll = 0.0;
    double inititalFuel = 1000;

    sim.creerAvion(initialSpeed, initialAlt, startX, startY, initialPitch, initialYaw, initialRoll, inititalFuel);
    sim.setIndicateurs(listeIndicateurs, SimulationIndicateurs::NB_INSTRUMENTS);

    Avion& p = sim.getAvion();
    std::thread t(&SimulationIndicateurs::inputListener, &sim, std::ref(p));
    std::thread t2(&SimulationIndicateurs::inputArduinoHandler, &sim, std::ref(p));
    t.detach();
    t2.detach();

    timerAnimation->start(16);
    timerDonnees->start(25);
}

void Simulation::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    int diametre = this->width() * 0.182;
    double posX[] = { 0.185, 0.395, 0.605, 0.815 };
    double posY[] = { 0.330, 0.665 };

    for (int i = 0; i < SimulationIndicateurs::NB_INSTRUMENTS; ++i) {
        int centreX = this->width() * posX[i % 4];
        int centreY = this->height() * posY[i / 4];
        QRect zone(centreX - diametre / 2, centreY - diametre / 2, diametre, diametre);

        instruments[i]->setGeometry(zone);
        for (IndicateurComponent* a : listeIndicateurs[i]) {
            a->setGeometry(zone);
            a->raise();
        }
    }

    if (view3d)
        view3d->setGeometry(0, 0, this->width(), this->height());
}

void Simulation::setupIndicateurs() {
    for (int i = 0; i < SimulationIndicateurs::NB_INSTRUMENTS; ++i) {
        instruments[i] = new QLabel(this);

        QString cheminComplet = QString("ressources/simulateur/%1.png")
            .arg(SimulationIndicateurs::NOMS_IMAGES.at(i));
        QPixmap pix(cheminComplet);
        if (pix.isNull())
            qDebug() << "Erreur : Impossible de charger" << cheminComplet;
        else
            instruments[i]->setPixmap(pix);

        instruments[i]->setScaledContents(true);
        instruments[i]->setAttribute(Qt::WA_TranslucentBackground);
        instruments[i]->raise();
    }

    // Anemometre
    listeIndicateurs[SimulationIndicateurs::Anemometre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    // Altimetre
    listeIndicateurs[SimulationIndicateurs::Altimetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));
    listeIndicateurs[SimulationIndicateurs::Altimetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.4f, 1.5f));

    // Variometre
    listeIndicateurs[SimulationIndicateurs::Variometre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    // Cap
    listeIndicateurs[SimulationIndicateurs::Cap].append(
        new IndicateurComponent(this, "ressources/simulateur/valeurs-cap.png", 1.05f, 2.0f));

    // Virage
    listeIndicateurs[SimulationIndicateurs::Virage].append(
        new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-aiguille.png", 1.0f, 2.0f));
    listeIndicateurs[SimulationIndicateurs::Virage].append(
        new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-cercle.png", 0.13f, 2.0f, 0, -103.5));

    // Horizon
    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-cieletsol.png", 2.0f, 2.0f));
    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-fleche-rouge.png", 1.0f, 1.3f));
    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel.png", 1.0f, 2.0f));

    // Tachymetre
    listeIndicateurs[SimulationIndicateurs::Tachymetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    // Boussole
    instruments[SimulationIndicateurs::Boussole]->setPixmap(
        QPixmap("ressources/simulateur/boussole.png"));
    listeIndicateurs[SimulationIndicateurs::Boussole].append(
        new IndicateurComponent(this, "ressources/simulateur/ruban-points-cardinaux.png", 1.0f, 2.0f, 0, 0));
    listeIndicateurs[SimulationIndicateurs::Boussole].append(
        new IndicateurComponent(this, "ressources/simulateur/boussole.png", 1.05f, 2.0f, 0, 0));
}