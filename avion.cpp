#include "avion.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Avion::Avion()
{
    speed = 1;
    altitude = 1;
    posX = 1;
    posY = 1;
    pitch = 1;
    yaw = 1;
    roll = 1;
    fuel = 1;
}

Avion::Avion(double speed, double altitude, double positionX, double positionY, double pitch, double yaw, double roll, double fuel) : 
            speed(speed), altitude(altitude), posX(positionX), posY(positionY), pitch(pitch), yaw(yaw), roll(roll), fuel(fuel) 
{
	
}

Avion::~Avion() {

}


// Actions

bool Avion::upSpeed(double additive) {
    if (fuel != 0) {
        speed += additive;

        if (speed > 600) {
            speed = 600;
        }
        return true;
    }
    else {
        return false;
    }
}

void Avion::downSpeed(double additive) {
    speed -= additive;

    if (speed <= 0) {
        speed = 0;
    }
}

void Avion::rollRight(double additive) {
    roll += additive;
}

void Avion::rollLeft(double additive) {
    roll -= additive;
}

void Avion::upPitch(double additive) {
    pitch += additive;
}

void Avion::downPitch(double additive) {
    pitch -= additive;
}

void Avion::calculateNewPosition() {
    // Utilise plus de fuel si on va plus vite, commence a 80
    fuel -= 0.1 * std::max((speed / 80.0), 1.0);

    if (fuel <= 0) {
        fuel = 0;

        speed -= 0.5;
        if (speed <= 0) {
            speed = 0;
        }

        return;
    }

    double actualCalculationSpeed = speed / 10;

    double radYaw = yaw * (M_PI / 180.0);
    double radPitch = pitch * (M_PI / 180.0);
    double radRoll = roll * (M_PI / 180.0);

    // roll
    yaw += std::sin(radRoll) * 1.5;

    // x y position
    double horizontalSpeed = actualCalculationSpeed * std::cos(radPitch);
    posX += horizontalSpeed * std::cos(radYaw);
    posY += horizontalSpeed * std::sin(radYaw);

    // altitude
    altitude += actualCalculationSpeed * std::sin(radPitch) * std::cos(radRoll);

    // Si la vitesse est trop basse on tombe
    if (speed <= 10) {
        altitude -= (9.8 / 2);
    }

    if (altitude <= 0) {
        altitude = 0;
    }
}


// Getters

double Avion::getSpeed() {
	return speed;
}

double Avion::getAltitude() {
	return altitude;
}

double Avion::getPositionX() {
	return posX;
}

double Avion::getPositionY() {
	return posY;
}

double Avion::getPitch() {
	return pitch;
}

double Avion::getYaw() {
	return yaw;
}

double Avion::getRoll() {
	return roll;
}

double Avion::getFuel() {
    return fuel;
}