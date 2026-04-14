#include "simulationCockpit.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <QGraphicsDropShadowEffect>

SimulationCockpit::SimulationCockpit(QWidget* parent) : QWidget(parent)
, m_piloteActif(nullptr)
, m_altitudeMax(0.0)
, m_speedMax(0.0)
{
    this->setStyleSheet("background-color: black;");

    view3d = new QQuickWidget(this);
    view3d->setSource(QUrl::fromLocalFile("cockpit3D.qml"));
    view3d->setResizeMode(QQuickWidget::SizeRootObjectToView);
    view3d->setAttribute(Qt::WA_AlwaysStackOnTop, false);
    view3d->lower();
    view3d->show();

    ecranText = new QLabel(this);
    ecranText->setText("");
    ecranText->setStyleSheet(
        "color: #343231;"
        "background: transparent;"
        "padding: 4px;"
        "font-family: 'Courier New', monospace;"
        "font-weight: bold;"
        "letter-spacing: 1px;"
    );
    ecranText->setAlignment(Qt::AlignLeft);
    ecranText->setWordWrap(true);
    ecranText->raise();

    setupIndicateurs();

    timerAnimation = new QTimer(this);
    connect(timerAnimation, &QTimer::timeout, this, [this]() {
        for (int i = 0; i < SimulationIndicateurs::NB_INSTRUMENTS; ++i) {
            for (IndicateurComponent* a : listeIndicateurs[i]) a->mettreAJourAnimation();
        }
        });

    timerDonnees = new QTimer(this);
    connect(timerDonnees, &QTimer::timeout, this, [this]() {
        Avion& p = sim.getAvion();
        p.calculateNewPosition();

        if (p.getAltitude() > m_altitudeMax) m_altitudeMax = p.getAltitude();
        if (p.getSpeed() > m_speedMax) m_speedMax = p.getSpeed();

        std::cout << "\033[H\033[J";
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

void SimulationCockpit::setPiloteActif(Pilote* p) {
    m_piloteActif = p;
    m_typesWarnings.clear();
    m_altitudeMax = 0.0;
    m_speedMax = 0.0;
}

void SimulationCockpit::terminerVol(bool estMort, const QString& typeVol) {
    if (!m_piloteActif) return;

    DonneesVol vol;
    vol.typeVol = typeVol;
    vol.typesWarnings = m_typesWarnings;
    vol.estMort = estMort;
    vol.dateVol = QDateTime::currentDateTime();
    vol.altitudeMax = m_altitudeMax;
    vol.speedMax = m_speedMax;

    m_piloteActif->ajouterVol(vol);
}

void SimulationCockpit::messagesWarning() {
    Avion& p = sim.getAvion();
    QString warningText;

    if (p.getAltitude() <= 1000) {
        std::cout << "| ALTITUDE CRITICALLY LOW | -> Should be over 1000\n";
        warningText += "| ALTITUDE CRITICALLY LOW |\n";
        m_typesWarnings.insert("ALTITUDE CRITICALLY LOW");
    }
    if (p.getSpeed() <= 10) {
        std::cout << "| SPEED CRITICALLY LOW | -> Should be over 10\n";
        warningText += "| SPEED CRITICALLY LOW |\n";
        m_typesWarnings.insert("SPEED CRITICALLY LOW");
    }
    if (p.getFuel() <= 50) {
        std::cout << "| FUEL CRITICALLY LOW | -> Should be over 50\n";
        warningText += "| FUEL CRITICALLY LOW |\n";
        m_typesWarnings.insert("FUEL CRITICALLY LOW");
    }

    ecranText->setText(warningText);
}
void SimulationCockpit::messagesMorts() {
    if (sim.getAvion().getAltitude() <= 0) {
        std::cout << "| CRASH | -> Hit the ground\n";
        timerDonnees->stop();
        timerAnimation->stop();
        terminerVol(true, "Vol cockpit");
        emit demanderRetourMenu();
    }
}

void SimulationCockpit::demarrer() {
    m_typesWarnings.clear();
    m_altitudeMax = 0.0;
    m_speedMax = 0.0;

    sim.creerAvion(40.0, 3000.0, 0.0, 0.0, 0.0, 30.0, 0.0, 1000.0);
    sim.setIndicateurs(listeIndicateurs, SimulationIndicateurs::NB_INSTRUMENTS);

    Avion& p = sim.getAvion();
    std::thread t(&SimulationIndicateurs::inputListener, &sim, std::ref(p));
    std::thread t2(&SimulationIndicateurs::inputArduinoHandler, &sim, std::ref(p));
    t.detach();
    t2.detach();

    timerAnimation->start(16);
    timerDonnees->start(25);
}

void SimulationCockpit::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    int diametre = this->width() * 0.1;
    double posX[] = { 0.146, 0.383, 0.620, 0.857 };
    double posY[] = { 0.533, 0.820 };

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

    if (ecranText) {
        double widthFraction = 0.2;
        double heightFraction = 0.21;
        int w = static_cast<int>(widthFraction * this->width());
        int h = static_cast<int>(heightFraction * this->height());
        double posX = 0.31;
        double posY = 0.225;
        int centreX = static_cast<int>(this->width() * posX);
        int centreY = static_cast<int>(this->height() * posY);
        QRect zone(centreX - w / 2, centreY - h / 2, w, h);
        ecranText->setGeometry(zone);
        ecranText->raise();
        QFont f = ecranText->font();
        f.setPixelSize(static_cast<int>(h * 0.075));
        ecranText->setFont(f);
    }

    if (view3d)
        view3d->setGeometry(0, 0, this->width(), this->height());
}

void SimulationCockpit::setupIndicateurs() {
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

    listeIndicateurs[SimulationIndicateurs::Anemometre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    listeIndicateurs[SimulationIndicateurs::Altimetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));
    listeIndicateurs[SimulationIndicateurs::Altimetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.4f, 1.5f));

    listeIndicateurs[SimulationIndicateurs::Variometre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    listeIndicateurs[SimulationIndicateurs::Cap].append(
        new IndicateurComponent(this, "ressources/simulateur/valeurs-cap.png", 1.05f, 2.0f));

    listeIndicateurs[SimulationIndicateurs::Virage].append(
        new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-aiguille.png", 1.0f, 2.0f));
    listeIndicateurs[SimulationIndicateurs::Virage].append(
        new IndicateurComponent(this, "ressources/simulateur/coordonateur-de-virage-cercle.png", 0.13f, 2.0f, 0, -103.5));

    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-cieletsol.png", 2.0f, 2.0f));
    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel-fleche-rouge.png", 1.0f, 1.3f));
    listeIndicateurs[SimulationIndicateurs::Horizon].append(
        new IndicateurComponent(this, "ressources/simulateur/horizon-artificiel.png", 1.0f, 2.0f));

    listeIndicateurs[SimulationIndicateurs::Tachymetre].append(
        new IndicateurComponent(this, "ressources/simulateur/aiguille.png", 0.6f, 1.5f));

    listeIndicateurs[SimulationIndicateurs::Boussole].append(
        new IndicateurComponent(this, "ressources/simulateur/ruban-points-cardinaux.png", 1.0f, 2.0f, 0, 0));
    listeIndicateurs[SimulationIndicateurs::Boussole].append(
        new IndicateurComponent(this, "ressources/simulateur/boussole2.png", 1.0f, 2.0f, 0, 0));
}