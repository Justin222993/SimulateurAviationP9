#pragma once
#define BAUD 115200           // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024   // Longueur maximale d'un message
#include <string>
bool NetworkIsConnected();
bool NetworkInit();
//bool NetworkInit(const std::string& com= "COM4", int baudrate = BAUD);
void NetworkTick();
void NetworkClose();
