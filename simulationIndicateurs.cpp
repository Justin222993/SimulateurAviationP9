#include "simulationIndicateurs.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <QRandomGenerator>

// Fonctions qui on rapport a l'indicateur on ete mis dans un component pour etre utiliser par plusieurs simulations
// J'ai aussi mis les contrôles de l'avion ici

SimulationIndicateurs::SimulationIndicateurs() {}

void SimulationIndicateurs::creerAvion(double speed, double alt, double x, double y,
    double pitch, double yaw, double roll, double fuel) {
    serialManager = &SerialManager::GetInstance();
    p = Avion(speed, alt, x, y, pitch, yaw, roll, fuel);
}

void SimulationIndicateurs::setIndicateurs(QList<IndicateurComponent*> liste[], int nb) {
    listeIndicateurs = liste;
    nbInstruments = nb;
}

void SimulationIndicateurs::setAngleInstrument(int indexInstrument, int indexIndicateur, double angle) {
    if (indexInstrument >= 0 && indexInstrument < nbInstruments) {
        if (indexIndicateur >= 0 && indexIndicateur < listeIndicateurs[indexInstrument].size()) {
            listeIndicateurs[indexInstrument][indexIndicateur]->setAngleCible(angle);
        }
    }
}

void SimulationIndicateurs::setPosition(int indexInstrument, int indexIndicateur, double positionX, double positionY) {
    if (indexInstrument >= 0 && indexInstrument < nbInstruments) {
        if (indexIndicateur >= 0 && indexIndicateur < listeIndicateurs[indexInstrument].size()) {
            listeIndicateurs[indexInstrument][indexIndicateur]->setPosition(positionX, positionY);
        }
    }
}

void SimulationIndicateurs::handleAnemometre() {
    std::vector<PointValeur> pointsReference = {
        {0.0,   0.0},   {40.0,  20.0},  {60.0,  60.0},
        {80.0,  100.0}, {120.0, 180.0}, {140.0, 220.0},
        {160.0, 260.0}, {180.0, 300.0}, {200.0, 340.0}
    };

    double speed = p.getSpeed();
    double finalAngle = 0.0;

    if (speed <= pointsReference.front().valeur)
        finalAngle = pointsReference.front().angle;
    else if (speed >= pointsReference.back().valeur)
        finalAngle = pointsReference.back().angle;
    else {
        for (size_t i = 0; i < pointsReference.size() - 1; ++i) {
            if (speed >= pointsReference[i].valeur && speed <= pointsReference[i + 1].valeur) {
                double ratio = (speed - pointsReference[i].valeur) /
                    (pointsReference[i + 1].valeur - pointsReference[i].valeur);
                finalAngle = pointsReference[i].angle + ratio *
                    (pointsReference[i + 1].angle - pointsReference[i].angle);
                break;
            }
        }
    }

    setAngleInstrument(Anemometre, 0, finalAngle);
}

void SimulationIndicateurs::handleTachymetre() {
    double speed = p.getSpeed();
    if (speed < 0)   speed = 0;
    if (speed > 200) speed = 200;

    double rpm = p.getUnitMotorStrenght() * 3500.0;

    std::vector<PointValeur> pointsReference = {
        {0.0,    -225.0}, {500.0,  -186.4}, {1000.0, -147.9},
        {1500.0, -109.3}, {2000.0,  -70.7}, {2500.0,  -32.1},
        {3000.0,    6.4}, {3500.0,   45.0}
    };

    double finalAngle = 0.0;

    if (rpm <= pointsReference.front().valeur)
        finalAngle = pointsReference.front().angle;
    else if (rpm >= pointsReference.back().valeur)
        finalAngle = pointsReference.back().angle;
    else {
        for (size_t i = 0; i < pointsReference.size() - 1; ++i) {
            if (rpm >= pointsReference[i].valeur && rpm <= pointsReference[i + 1].valeur) {
                double ratio = (rpm - pointsReference[i].valeur) /
                    (pointsReference[i + 1].valeur - pointsReference[i].valeur);
                finalAngle = pointsReference[i].angle + ratio *
                    (pointsReference[i + 1].angle - pointsReference[i].angle);
                break;
            }
        }
    }

    setAngleInstrument(Tachymetre, 0, finalAngle);
}

void SimulationIndicateurs::handleBoussole() {
    double cap = p.getYaw();
    while (cap >= 360.0) cap -= 360.0;
    while (cap < 0.0)    cap += 360.0;

    double pixelsParDegre = 1820.0 / 720.0 * 0.35;

    // N est à 270° dans l'image → décalage = 270 * pixelsParDegre
    double offsetCalibration = 500.0 * pixelsParDegre;

    double offsetX = -cap * pixelsParDegre ;

    setPosition(Boussole, 1, offsetX, 0);
}

void SimulationIndicateurs::handleAltimetre() {
    double altitude = p.getAltitude();
    if (altitude < 0) altitude = 0;
    if (altitude > 10000) altitude = 10000;
    double finalAngle = (altitude / 10000.0) * 360.0;
    setAngleInstrument(Altimetre, 1, finalAngle);
	setAngleInstrument(Altimetre, 0, finalAngle * 10.0);
}

void SimulationIndicateurs::handleVariometre() {
    double verticalSpeed = p.getVerticalSpeed()/2.5;
    if (verticalSpeed < -20) verticalSpeed = -20;
    if (verticalSpeed > 20) verticalSpeed = 20;
    double finalAngle = (verticalSpeed / 20.0) * 180.0;
    finalAngle += 270;
    setAngleInstrument(Variometre, 0, finalAngle);
}
void SimulationIndicateurs::handleHorizon() {
    //200

    /*
    double horizonAngle = QRandomGenerator::global()->bounded(-50, 51);
        sim.setAngleInstrument(SimulationIndicateurs::Horizon, 0, horizonAngle);
        sim.setPosition(SimulationIndicateurs::Horizon, 0,
            QRandomGenerator::global()->bounded(-50, 51),
            QRandomGenerator::global()->bounded(-50, 51));
        sim.setAngleInstrument(SimulationIndicateurs::Horizon, 1, horizonAngle);
    
    */
	double horizonAngle = p.getRoll();
    double pitch = p.getPitch();
    double movement = pitch * 600 / 90;

    setPosition(Horizon, 0, 0, -movement);
    setAngleInstrument(SimulationIndicateurs::Horizon, 0, -horizonAngle);
    setAngleInstrument(SimulationIndicateurs::Horizon, 1, -horizonAngle);
    
}
void SimulationIndicateurs::handleCap() {

    static int previousEncoder = 0;

    int encoder = -serialManager->GetEncoder();

    int encoderDelta = encoder - previousEncoder;
    previousEncoder = encoder;

    static float previousYaw = p.getYaw();
    static float continuousYaw = p.getYaw();

    static float drift = 0.0f;

    static int driftDirection = (rand() % 2 == 0) ? 1 : -1;

    float currentYaw = p.getYaw();
    float delta = currentYaw - previousYaw;

    // unwrap (Valeur de yaw son entre 0 et 360, mais on veut garder over, genre 361 degres... 724 degr�s etc)
    if (delta > 180.0f)
        delta -= 360.0f;
    else if (delta < -180.0f)
        delta += 360.0f;

    continuousYaw += delta;
    previousYaw = currentYaw;

    drift += driftDirection * 0.01f;

    // encoder = correction one-shot
    float encoderGain = 3.0f; // +3 degr�s par tick
    continuousYaw += encoderDelta * encoderGain;

    setAngleInstrument(
        SimulationIndicateurs::Cap,
        0,
        -(continuousYaw + drift)
    );
}

void SimulationIndicateurs::handleVirage() {
    double roll = p.getRoll();
    double movement = roll * 50 / 90;
	setPosition(Virage, 1, -movement, -105);

}


void SimulationIndicateurs::inputListener(Avion& p) {
    while (true) {
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w') p.upPitch(2);
            else if (input == 's') p.downPitch(2);
            else if (input == 'a') p.rollLeft(3);
            else if (input == 'd') p.rollRight(3);
            else if (input == 'p') { if (!p.upMotorStrenght(5)) std::cout << "| NO FUEL !!!!! |"; }
            else if (input == 'l') p.downMotorStrenght(5);
            else if (input == '1') updateLight(1, 1);
            else if (input == '2') updateLight(2, 1);
            else if (input == '3') updateLight(3, 1);
            else if (input == '4') updateLight(4, 1);
            else if (input == '5') updateLight(1, 0);
            else if (input == '6') updateLight(2, 0);
            else if (input == '7') updateLight(3, 0);
            else if (input == '8') updateLight(4, 0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }
}

void SimulationIndicateurs::updateLight(int lightNumber, bool state) {

    if (lightNumber == 1) {
        SimulationIndicateurs::light1 = state;
    }
    else if(lightNumber == 2) {
        SimulationIndicateurs::light2 = state;
    }
    else if (lightNumber == 3) {
        SimulationIndicateurs::light3 = state;
    }
    else if (lightNumber == 4) {
        SimulationIndicateurs::light4 = state;
    }
}


void SimulationIndicateurs::inputArduinoHandler(Avion& p) {
    while (true) {
        if (!serialManager->ArduinoIsConnected()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
            continue;
        }

        if(SimulationIndicateurs::simulationEnCours){
            serialManager->SetReturnData(p.getSpeed(), p.getAltitude(), p.getFuel() < 500);
            serialManager->DoNetworkTick();
            p.SetMotorStrenght(serialManager->GetPotentiometer());

            JoystickInformation joyInfo = serialManager->GetJoystick();
            Vector2D vector = {joyInfo.curlX, joyInfo.curlY};

            p.SetPlayerJoystickInput(vector);
       

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        else {
            serialManager->SetReturnData(0, 0, false);
        }
    }
}