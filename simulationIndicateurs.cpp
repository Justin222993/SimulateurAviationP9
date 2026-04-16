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

    double rpm = (speed / 200.0) * 3500.0;

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

    double offsetX = -(cap * 2.5);
    setPosition(Boussole, 0, offsetX, 0);
}

void SimulationIndicateurs::inputListener(Avion& p) {
    while (true) {
        if (_kbhit()) {
            char input = _getch();
            if (input == 'w') p.upPitch(2);
            else if (input == 's') p.downPitch(2);
            else if (input == 'a') p.rollLeft(3);
            else if (input == 'd') p.rollRight(3);
            else if (input == 'p') { if (!p.upSpeed(5)) std::cout << "| NO FUEL !!!!! |"; }
            else if (input == 'l') p.downSpeed(5);
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

        serialManager->SetReturnData(p.getSpeed(), p.getAltitude(), true);
        serialManager->DoNetworkTick();
        p.SetMotorStrenght(serialManager->GetPotentiometer());

        JoystickInformation joyInfo = serialManager->GetJoystick();
        Vector2D vector = {joyInfo.curlX, joyInfo.curlY};

        p.SetPlayerJoystickInput(vector);
       

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}