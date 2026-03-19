#include "SerialConnectionGateway.h"
/* * Auteurs: Jean-Samuel Lauzon
 * Date: Fevrier 2022
 * Modif : Janvier 2023, Compatible VisualStudio, JpGouin
 * Modif : Janvier 2025, 115200 BAUDS, JpGouin
*/

/*------------------------------ Librairies ---------------------------------*/
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "SerialManager.h"

/*-------------------------- Librairies externes ----------------------------*/
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200         
#define MSG_MAX_SIZE 1024   

/*------------------------- Prototypes de fonctions -------------------------*/
bool SendToSerial(SerialPort* arduino, json j_msg);
bool RcvFromSerial(SerialPort* arduino, std::string& msg);

/*---------------------------- Variables globales ---------------------------*/
SerialPort* arduino;


// Simulation state
json j_msg_send, j_msg_rcv;

int sim_vitesse = 0;
int sim_altitude = 0;
bool etat_led_rouge = false;

//// Input state
//int cur_joy_x = 0, cur_joy_y = 0, cur_pot = 0;
//int cur_master_switch = 0, cur_encodeur = 0, cur_accel_bump = 0;

// Buffers
std::string raw_msg;
std::string trame_accumulee = "";

// Timing
std::chrono::steady_clock::time_point temps_precedent_led;
std::chrono::steady_clock::time_point temps_precedent_console;

// Connection state
bool isConnected = false;
std::string portName;
int baudRate = BAUD;

bool NetworkIsConnected()
{
    return isConnected && arduino && arduino->isConnected();
}

/*----------------------------- Fonction "Main" -----------------------------*/
bool NetworkInit(
    /*const std::string& com, int baudrate = BAUD*/
) {
    portName = "COM4";
	std::string& coms = portName;
        //com;
    baudRate = BAUD;
        //baudrate;

    if (arduino)
    {
        delete arduino;
        arduino = nullptr;
    }

    arduino = new SerialPort("COM4", baudRate);

    if (!arduino->isConnected())
    {
        std::cerr << "Impossible de se connecter." << std::endl;
        isConnected = false;
        return false;
    }

    std::cout << "Connexion reussie !" << std::endl;

    isConnected = true;

    temps_precedent_led = std::chrono::steady_clock::now();
    temps_precedent_console = std::chrono::steady_clock::now();

    return true;
}
void NetworkTick() {
    if (!isConnected || !arduino || !arduino->isConnected())
    {
        std::cerr << "Reconnexion en cours..." << std::endl;

        NetworkInit();

        // still not connected → skip everything
        if (!isConnected)
            return;
    }

    auto temps_actuel = std::chrono::steady_clock::now();

	SerialManager& serialManager = SerialManager::GetInstance();
    // 1. LED blink (every 2 sec)
    if (temps_actuel - temps_precedent_led >= std::chrono::milliseconds(2000)) {
        etat_led_rouge = !etat_led_rouge;
        temps_precedent_led = temps_actuel;
    }

    // 2. Receive data (non-blocking)
    if (RcvFromSerial(arduino, raw_msg)) {
        trame_accumulee += raw_msg;
    }

    size_t pos_fin = trame_accumulee.find('\n');
    while (pos_fin != std::string::npos) {
        std::string message_complet = trame_accumulee.substr(0, pos_fin);
        trame_accumulee.erase(0, pos_fin + 1);

        try {
            j_msg_rcv = json::parse(message_complet);

            serialManager.SetJoystick(j_msg_rcv.value("joy_x", 0), j_msg_rcv.value("joy_y", 0));
			serialManager.SetPotentiometer(j_msg_rcv.value("pot", 0));
			serialManager.SetMasterSwitch(j_msg_rcv.value("MasterSwitch", 0) == 1);
            serialManager.SetEncoder(j_msg_rcv.value("encoder", 0));
			serialManager.SetAccelBump(j_msg_rcv.value("accel_bump", 0) == 1);



        }
        catch (...) {
            // Ignore malformed JSON
        }

        pos_fin = trame_accumulee.find('\n');
    }
	ReturnData returnData = serialManager.GetReturnData();
    // 3. Send data
    j_msg_send["vitesse"] = returnData.vitesse;
    j_msg_send["altitude"] = returnData.altitude;
    j_msg_send["led_rouge"] = returnData.redLed;

    SendToSerial(arduino, j_msg_send);

    //// 4. Console output (4 Hz)
    //if (temps_actuel - temps_precedent_console >= std::chrono::milliseconds(250)) {

    //    std::cout << "\n--- Donnees du Simulateur ---" << std::endl;
    //    std::cout << "Master Switch        : " << (cur_master_switch ? "PRESSE" : "RELACHE") << std::endl;
    //    std::cout << "Joystick X / Y       : " << cur_joy_x << " / " << cur_joy_y << std::endl;
    //    std::cout << "Potentiometre        : " << cur_pot << std::endl;
    //    std::cout << "Encodeur             : " << cur_encodeur << std::endl;
    //    std::cout << "Mouvement Brusque    : " << (cur_accel_bump ? "OUI" : "NON") << std::endl;
    //    std::cout << "Vitesse Calculee     : " << sim_vitesse << " km/h" << std::endl;
    //    std::cout << "Altitude Calculee    : " << sim_altitude << " pieds" << std::endl;
    //    std::cout << "--------------------------" << std::endl;

    //    temps_precedent_console = temps_actuel;
    //}
}
void NetworkClose() {
    if (arduino) {
        delete arduino;
        arduino = nullptr;
    }
}


//int main() {
//    std::string com;
//    std::cout << "Entrer le port (ex: COM3): ";
//    std::cin >> com;
//
//    if (!NetworkInit(com)) {
//        return 1;
//    }
//
//    while (true) {
//        NetworkTick();
//
//        // Your engine/game loop timing here
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//    }
//
//    NetworkClose();
//    return 0;
//}

/*---------------------------Definition de fonctions ------------------------*/
bool SendToSerial(SerialPort* arduino, json j_msg) {
    std::string msg = j_msg.dump() + "\n";
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
}

bool RcvFromSerial(SerialPort* arduino, std::string& msg) {
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;
    msg.clear();

    buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);

    if (buffer_size > 0) {
        msg.assign(char_buffer, buffer_size);
        return true;
    }
    return false;
}