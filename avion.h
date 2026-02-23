#include <cmath>
#include <algorithm>

class Avion {

	public:
		Avion();
		Avion(double speed, double altitude, double positionX, double positionY, double pitch, double yaw, double roll, double fuel);
		~Avion();

		// Actions
		bool upSpeed(double additive);
		void downSpeed(double additive);

		void rollRight(double additive);
		void rollLeft(double additive);

		void upPitch(double additive);
		void downPitch(double additive);

		void calculateNewPosition();

		// Getters
		double getSpeed();
		double getAltitude();
		double getPositionX();
		double getPositionY();
		double getPitch();
		double getYaw();
		double getRoll();
		double getFuel();

	private:
		double speed;
		double altitude;
		double posX;
		double posY;
		double fuel;

		double pitch; // Nose angle
		double yaw; // compass heading
		double roll; // plane tilt for turning

};
