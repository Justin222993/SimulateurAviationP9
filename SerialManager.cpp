#include "SerialManager.h"
#include "SerialConnectionGateway.h"

SerialManager::SerialManager() : 
	joystickInfo{0, 0}, 
	potentiometerValue(0), 
	masterSwitchState(false), 
	encoderValue(0),
	cur_accel_bump(false)
{


	NetworkInit();

}
SerialManager::~SerialManager()
{
}
void SerialManager::DoNetworkTick() {

	NetworkTick();
}


void SerialManager::SetJoystick(int curlX, int curlY)
{
	joystickInfo.curlX = curlX;
	joystickInfo.curlY = curlY;
}
JoystickInformation SerialManager::GetJoystick()
{
	return joystickInfo;
}
void SerialManager::SetPotentiometer(int value)
{
	potentiometerValue = value;
}
int SerialManager::GetPotentiometer()
{
	return potentiometerValue;
}
void SerialManager::SetMasterSwitch(bool state)
{
	masterSwitchState = state;
}
bool SerialManager::GetMasterSwitch()
{
	return masterSwitchState;
}
void SerialManager::SetEncoder(int value)
{
	encoderValue = value;
}
int SerialManager::GetEncoder()
{
	return encoderValue;
}
void SerialManager::SetAccelBump(bool state)
{
	cur_accel_bump = state;
}
int SerialManager::GetAccelBump()
{
	return cur_accel_bump;
}
void SerialManager::SetReturnData(int vitesse, int altitude, bool redLed)
{
	returnData.vitesse = vitesse;
	returnData.altitude = altitude;
	redLedPreviousState = redLed;
}
ReturnData SerialManager::GetReturnData()
{
	return returnData;
}
bool SerialManager::ArduinoIsConnected() {
	return NetworkIsConnected();
}

