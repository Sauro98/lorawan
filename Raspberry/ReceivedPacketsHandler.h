#ifndef RECEIVED_PACKETS_HANDLER_h
#define RECEIVED_PACKETS_HANDLER_h

#include <stdint.h>//for uint8_t and int8_t
#include <iostream>//for std::string
#include <stdio.h>//for c string formatting
#include <sys/time.h>//for formatting the timestamp
#include <time.h>//for formatting the timestamp
#include <string>//for addictional handling of strings
#include "SX1272.h"//for passing the pack struct  directly in the constructor


class ReceivedPacket{
	public:
		uint8_t data[244];
		struct tm* receivedTime;
	private:
		uint8_t arduinoSenderID;
		uint8_t sensorID;
		int packetNumber;
		//packet lenght
		int pl;
		//debug mode
		bool debug;
	public:
		//Genera un pacchetto vuoto
		ReceivedPacket();
		//Lascia che il costruttore si occupi di estrapolare i dati direttamente dal pacchetto originale ricevuto in lora
		ReceivedPacket(pack originalPacket);//debug disattivato 
		ReceivedPacket(pack originalPacket,bool _debug);//debug impostabile
		//Stampa le informazioni del pacchetto
		void printPacket();
		//esegue un comando curl sulla shell di linux per aggiungere il messaggio al database 
		void issueAddToDatabaseCommand();
		//distingue i pacchetti di comando da quelli di dati
		bool isCommandPacket();
		//ottieni il comando ricevuto
		Comando getCommand();
	private:
		std::string generateJSON();
		void getTime();
		std::string generateID();


};
#endif
