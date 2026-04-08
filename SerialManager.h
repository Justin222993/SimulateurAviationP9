#pragma once

struct JoystickInformation
{
	int curlX;
	int curlY;
};
struct ReturnData
{
	int vitesse;
	int altitude;
	bool redLed;
};


class SerialManager
{
	public:
		static SerialManager& GetInstance()
		{
			static SerialManager instance;
			return instance;
		}

		SerialManager(const SerialManager&) = delete;
		SerialManager& operator=(const SerialManager&) = delete;


		SerialManager();
		
		~SerialManager();

		void DoNetworkTick();


		void SetJoystick(int curlX, int curlY);
		JoystickInformation GetJoystick();

		void SetPotentiometer(int value);
		int GetPotentiometer();

		void SetMasterSwitch(bool state);
		bool GetMasterSwitch();

		void SetEncoder(int value);
		int GetEncoder();

		void SetAccelBump(bool state);
		int GetAccelBump();

		void SetReturnData(int vitesse, int altitude, bool redLed);
		ReturnData GetReturnData();


		bool ArduinoIsConnected();
	private:
		JoystickInformation joystickInfo;
		int potentiometerValue;
		bool masterSwitchState;
		bool cur_accel_bump;
		int encoderValue;

		//Return data
		ReturnData returnData;
		bool redLedPreviousState;


};

