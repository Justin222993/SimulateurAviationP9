#pragma once
class avionmk2
{

public:
	avionmk2();
	void SetPlayerJoystickInput(Vector2D joystick);
	~avionmk2();
	void SetPlayerJoystickInput(Vector2D joystick);
	void MovementIteration();
	Vector3D CalculateMovementMultiplier();


	Vector3D GetUnitDirection() {
		return u_direction;
	}


	void SetMotorStrenght(float str);
	void SetMovementVector();

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
	
};
/// <summary>
/// X and Y are horizontale while Z is verticale
/// </summary>
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
	