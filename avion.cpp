#include "avion.h"
#include <math.h>
#ifndef maxSpeedHorizontally
#define maxSpeedHorizontally 100
#endif // !maxSpeedHorizontally 100

#ifndef iterationsPerSecond
#define iterationsPerSecond 25

#endif

#ifndef joystickMiddleground
#define joystickMiddleground 511
#endif // !joystickMiddleground

#ifndef M_PIE
#define M_PIE 3.14159265358979323846
#endif // !M_PIE
#ifndef fullTurnTime
#define fullTurnTime 30.0
#endif // !fullTurnTime

#ifndef speedModifier
#define speedModifier 1.0
#endif // !speedModifier

#ifndef rollSpeedFullChange
#define rollSpeedFullChange 5.0
#endif // How much time for the rolling to reach its full speed

#ifndef NormalPlaneSpeedStraight
#define NormalPlaneSpeedStraight 200.0
#endif // !NormalPlaneSpeedStraight

#ifndef StartFuel
#define StartFuel 100000.0
#endif // !StartFuel

#ifndef ConsumptionMaxMotorSecond
#define ConsumptionMaxMotorSecond 10.0
#endif // !ConsumptionMaxMotorSecond

float timeRoll = 0;
float rollforce = 0;
double verticalSpeed = 0.0;
double targetPitch = 0.0;
Avion::Avion()
{
	// --- Position ---
	positionX = 0.0;
	positionY = 0.0;
	positionZ = 1000.0; // 1 km altitude (safe, avoids exp issues)

	// --- Orientation ---
	pitch = 0.0;  // level flight
	yaw = 0.0;    // not really used yet
	roll = 0.0;   // wings level

	// --- Direction (IMPORTANT) ---
	u_direction.movementX = 1.0; // facing forward (X axis)
	u_direction.movementY = 0.0;

	// --- Speed ---
	currentSpeed = 200.0; // good mid-range speed (not too slow, not too fast)

	// --- Engine ---
	motorStrenght = 512.0;        // ~50% throttle
	inputMotorStrenght = 512.0;
	unitMotorStrenght = 0.5;

	// --- Fuel ---
	fuel = StartFuel;

	// --- Input ---
	joystickInputUnitVector.movementX = 0.0;
	joystickInputUnitVector.movementY = 0.0;
	timeRoll = 0;
	rollforce = 0;
	verticalSpeed = 0.0; 
}
Avion::Avion(double speed, double altitude, double positionX, double positionY, double pitch, double yaw, double roll, double fuel) {
	// --- Position ---
	this->positionX = positionX;
	this->positionY = positionY;
	this->positionZ = altitude;

	// --- Orientation ---
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

	// --- Direction (IMPORTANT) ---
	u_direction.movementX = 1.0; // facing forward (X axis)
	u_direction.movementY = 0.0;

	// --- Speed ---
	this->currentSpeed = speed; // good mid-range speed (not too slow, not too fast)

	// --- Engine ---
	this->motorStrenght = 512.0;        // ~50% throttle
	this->inputMotorStrenght = 512.0;
	this->unitMotorStrenght = 0.5;

	// --- Fuel ---
	this->fuel = fuel;

	// --- Input ---
	joystickInputUnitVector.movementX = 0.0;
	joystickInputUnitVector.movementY = 0.0;

	timeRoll = 0;
	rollforce = 0;
	verticalSpeed = 0.0;
}
Avion::~Avion() {

}
double Clamp(double minVal, double maxVal, double v)
{
    if (v < minVal) return minVal;
    if (v > maxVal) return maxVal;
    return v;
}
double Lerp(double a, double b, double t)
{
	return a + (b - a) * t;
}


void Avion::SetPlayerJoystickInput(Vector2D joystick)
{
	float center = joystickMiddleground;
	float deadZone = 10.0f;

	float dx = joystick.movementX - center;
	float dy = joystick.movementY - center;

	// X axis (inverted)
	if (std::abs(dx) <= deadZone)
		joystickInputUnitVector.movementX = 0;
	else
		joystickInputUnitVector.movementX = -dx / center;

	// Y axis (inverted)
	if (std::abs(dy) <= deadZone)
		joystickInputUnitVector.movementY = 0;
	else
		joystickInputUnitVector.movementY = -dy / center;

	// clamp safety
	joystickInputUnitVector.movementX =
		std::clamp(joystickInputUnitVector.movementX, -1.0f, 1.0f);

	joystickInputUnitVector.movementY =
		std::clamp(joystickInputUnitVector.movementY, -1.0f, 1.0f);
}

double sCurve(double t, double L, double k, double t0)
{
	return L / (1.0 + std::exp(-k * (t - t0))) + 0.1;
}

//double Larp(double currentValue, double finalValue, float transitionTime) {
//	double
//
//}


void Avion::calculateNewPosition()
{
	double dt = 1.0 / iterationsPerSecond;

	// =========================================================
	// ROLL (input ? aircraft bank angle)
	// =========================================================
	rollforce = Lerp(rollforce, joystickInputUnitVector.movementX, dt);
	roll += rollforce * abs(joystickInputUnitVector.movementX) * dt * 2.0;
	roll = Clamp(-90.0, 90.0, roll);

	//double rollRad = roll * M_PIE / 180.0;



	

	const double g = 9.81;
	double speed = std::max(currentSpeed, 30.0f);

	double rollLimited = Clamp(-60.0, 60.0, roll);
	double rollRad = rollLimited * M_PIE / 180.0;
	
	double yawRate = (g * tan(rollRad)) / speed;

	yaw += yawRate * dt;

	// proper normalization
	yaw = fmod(yaw, 2 * M_PIE);
	if (yaw < 0)
		yaw += 2 * M_PIE;

	// direction
	u_direction.movementX = cos(yaw);
	u_direction.movementY = sin(yaw);

	positionX += u_direction.movementX * currentSpeed * dt;
	positionY += u_direction.movementY * currentSpeed * dt;

	// =========================================================
	// PITCH (kept simple + stable)
	// =========================================================

	targetPitch += joystickInputUnitVector.movementY * dt;
	targetPitch = Clamp(-90.0, 90.0, targetPitch);
	pitch = Lerp(pitch, targetPitch, dt*3);
	double pitchRad = pitch * M_PIE / 180.0;
	/*double rollCoupling = 1.0 + 0.5 * sin(rollRad);

	pitch += joystickInputUnitVector.movementY * 90.0 * dt * rollCoupling;
	pitch = Clamp(-80.0, 80.0, pitch);

	double pitchRad = pitch * M_PIE / 180.0;*/

	//pitch Rotations
	double pitchFactor = sin(pitchRad);

	double pitchX = cos(yaw) * pitchFactor;
	double pitchY = sin(yaw) * pitchFactor;
	// =========================================================
	// ENGINE / FUEL
	// =========================================================
	if(fuel <= 0) {
		inputMotorStrenght = 0;
	}
	motorStrenght = Lerp(motorStrenght, inputMotorStrenght, dt/10);

	double fuelFactor = Clamp(0.0, 2.0, motorStrenght / 1023.0);
	unitMotorStrenght = motorStrenght / 1023.0;

	fuel -= ConsumptionMaxMotorSecond * fuelFactor * dt;

	// =========================================================
	// SPEED MODEL
	// =========================================================
	double factMultVert = cos(pitchRad);

	double targetSpeed =
		NormalPlaneSpeedStraight * factMultVert * unitMotorStrenght * abs(cos(roll));

	currentSpeed += (targetSpeed - currentSpeed) * dt;

	// =========================================================
	// AIR DENSITY
	// =========================================================
	const double H = 8500.0;
	double airDensityFactor = Clamp(0.5, 1.0, exp(-positionZ / H));

	// =========================================================
	// POSITION UPDATE
	// =========================================================
	positionX += u_direction.movementX * currentSpeed * airDensityFactor * dt;
	positionY += u_direction.movementY * currentSpeed * airDensityFactor * dt;

	//double lift = sCurve(currentSpeed, 10, 0.1, -250);
	double lift = currentSpeed > 50 ? 10 : (currentSpeed / 50.0)*10;
	double gravity = g; // make it positive

	double accelerationZ = lift - gravity ;
	verticalSpeed += accelerationZ * dt ;
	verticalSpeed = Clamp(-50.0, 0.0, verticalSpeed);

	positionZ += verticalSpeed * dt;
	
	positionZ += cos(yaw)*sin(pitchRad) * currentSpeed * airDensityFactor * dt;
	//divide 60 cause 1 minute
	verticalMovement = (verticalSpeed + cos(yaw) * sin(pitchRad) * currentSpeed * airDensityFactor);
}