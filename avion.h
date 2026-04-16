#ifndef AVION_H
#define AVION_H

#include <cmath>
#include <algorithm>

struct Vector3D {
	float movementX;
	float movementY;
	float movementZ;
};

struct Vector2D {
	float movementX;
	float movementY;
	float magnitude;
};

class Avion {

	public:
		Avion();
		Avion(double speed, double altitude, double positionX, double positionY, double pitch, double yaw, double roll, double fuel);
		~Avion();

		void SetPlayerJoystickInput(Vector2D joystick);
		Vector3D GetUnitDirection() {
			return u_direction;
		}

		void SetMotorStrenght(float str) {
			inputMotorStrenght = str;
		}

		// Actions
		void setSpeed(int newSpeed) {
			currentSpeed = newSpeed;
		}
		bool upMotorStrenght(double additive) {
			if(fuel <= 0) {
				return false; // No fuel
			}

			inputMotorStrenght += additive;
			if (inputMotorStrenght > 1023) {
				inputMotorStrenght = 1023;
			}
			else if(inputMotorStrenght<0) {
				inputMotorStrenght = 0;
			}
			return true;
		}
		void downMotorStrenght(double additive) {
			if(fuel <= 0) {
				return; // No fuel
			}
			inputMotorStrenght -= additive;
			if (inputMotorStrenght > 1023) {
				inputMotorStrenght = 1023;
			}
			else if (inputMotorStrenght < 0) {
				inputMotorStrenght = 0;
			}
		}

		

		void rollRight(double additive) {
			roll += additive;
			if (roll > 180) {
				roll = 180;
			}
		}
		void rollLeft(double additive) {
			roll -= additive;
			if (roll < -180) {
				roll = -180;
			}
		}

		void upPitch(double additive) {
			pitch += additive;
			if (pitch > 90) {
				pitch = 90;
			}
		}
		void downPitch(double additive){
			pitch -= additive;
			if (pitch < -90) {
				pitch = -90;
			}
		}

		void calculateNewPosition();

		// Getters

		double getSpeed(){ return currentSpeed; }
		double getAltitude(){ return positionZ; }
		double getPositionX(){ return positionX; }
		double getPositionY(){ return positionY; }
		double getPitch(){ return pitch; }
		double getYaw(){ return (yaw * 180.0 / 3.14159265358979323846); }
		double getRoll(){ return roll; }
		double getFuel(){ return fuel; }
		double getUnitMotorStrenght() { return unitMotorStrenght; }
		double getVerticalSpeed() { return verticalMovement; }

	private:
		float motorStrenght = 100;
		float unitMotorStrenght = 0.1;
		int inputMotorStrenght = 0;

		float currentSpeed = 0;


		Vector3D u_direction;
		Vector2D joystickInputUnitVector;

		double pitch; // Nose angle
		double yaw; // compass heading
		double roll; // plane tilt for turning
		double yawChangeSpeed;

		double positionX;
		double positionY;
		double positionZ;

		float fuel;
		
		double verticalMovement;

};

#endif