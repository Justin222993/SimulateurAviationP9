#include "avionmk2.h"
#include <math.h>
#ifndef maxSpeedHorizontally
#define maxSpeedHorizontally 100
#endif // !maxSpeedHorizontally 100

#ifndef iterationsPerSecond
#define iterationsPerSecond 60.0

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
#define NormalPlaneSpeedStraight 500.0
#endif // !NormalPlaneSpeedStraight


avionmk2::avionmk2() {



}
double Lerp(double a, double b, double t)
{
	return a + (b - a) * t;
}

Vector3D CalculateMovementMultiplier() {


}

void avionmk2::SetPlayerJoystickInput(Vector2D joystick) {
	
	joystickInputUnitVector = {};
	if(joystick.movementX > joystickMiddleground) {
		float on512 = joystick.movementX - joystickMiddleground;
		joystickInputUnitVector.movementX = on512 / joystickMiddleground;

	}
	else if (joystick.movementX < joystickMiddleground) {

		joystickInputUnitVector.movementX = -(512 - joystick.movementX)/joystickMiddleground;

	}
	else
	{
		joystickInputUnitVector.movementX = 0;
	}



	if(joystick.movementY > joystickMiddleground) {
		float on512 = joystick.movementY - joystickMiddleground;
		joystickInputUnitVector.movementY = on512 / joystickMiddleground;
	}
	else if (joystick.movementY < joystickMiddleground) {
		joystickInputUnitVector.movementY = -(512 - joystick.movementY) / joystickMiddleground;
	}
	else
	{
		joystickInputUnitVector.movementY = 0;
	}

}

//double Larp(double currentValue, double finalValue, float transitionTime) {
//	double 
//
//}

float timeRoll = 0;
float rollforce = 0;
void avionmk2::MovementIteration() {

	//Calculate the new unit vector
	//100 speed ref
	double kConstraint = (2 * M_PIE) / (fullTurnTime * 100 * speedModifier);

	double dt = 1.0 / iterationsPerSecond;


	//we Get the strenght of the roll dependding on time
	rollforce = Lerp(rollforce, joystickInputUnitVector.movementX, dt);
	//Change K constarint if turns to fast
	roll += rollforce * abs(joystickInputUnitVector.movementX) * kConstraint * dt;
	// Pour que sin(30) = 1 et que plus haut que30 degree, la speed sera affecte par la rotation
	double turnSpeed = sin(roll) * 2;
	double overTurnSpeed = 1;
	if (abs(roll)>1) {
		overTurnSpeed = 1 - (abs(roll)-1) ;
	}
	
	
	//Dison que turnspeed = 1, la K constraint defini la vitesse du tour
	double turn = turnSpeed * kConstraint * currentSpeed;

	Vector2D turnVector = { u_direction.movementY, u_direction.movementX, 100};

	u_direction.movementX = u_direction.movementX * cos(turn * dt) - turnVector.movementY * sin(turn * dt);
	u_direction.movementY = u_direction.movementX * sin(turn * dt) + turnVector.movementY * cos(turn * dt);

	float factMultVert = acos(pitch);
	if (pitch < 0) {
		factMultVert += factMultVert;
	}
	factMultVert = 1 - factMultVert;

	//calculate the total speed multiplier
	//We could add altitude as a factor of speed, but we<ll see later
	

	//Now we need to calculate the speed depending on the motor strenght
	motorStrenght = Lerp(motorStrenght, inputMotorStrenght, dt);

	unitMotorStrenght = motorStrenght / 1023.0;




	double totalSpeedMultiplier = overTurnSpeed * factMultVert * unitMotorStrenght * dt;
	//FIX THIS SHIT
	currentSpeed *= 1;
	
	positionX += u_direction.movementX * currentSpeed;
	positionY += u_direction.movementY * currentSpeed;
	positionZ += static_cast<double>((sin(pitch) * currentSpeed));



	


	//Apply speed

	//Apply transformation

		
	
	

}


