#include "ReceivedPacketsHandler.h"	
	
void ReceivedPacket::printPacket(){
	char buffer[26];
	strftime(buffer, 26, "%Y:%m:%d %H:%M:%S", receivedTime);
	printf("\n");
	printf("--Pacchetto ricevuto il %s\n",buffer);
	printf("--Mittente arduino #%d, pacchetto #%d\n",arduinoSenderID,packetNumber);
	printf("--Sensore #%d\n",sensorID);
	printf("--Contenuto (int):  ");
	for (int a = 0; a < pl; a++) {
		printf(" %d",data[a]);
	}
	printf("\n");
	printf("--Contenuto (char):  ");
	for (int a = 0; a < pl; a++) {
		printf(" %d", (char)data[a]);
	}
	printf("\n-----------------------------------------------------------\n");
	return;
}

ReceivedPacket::ReceivedPacket(){
	
}

ReceivedPacket::ReceivedPacket(pack originalPacket,int _gw_id,bool _debug) {
	debug = _debug;
	if (debug) {
		printf("\n----------START OF A NEW PACKET----------\n");
	}
	arduinoSenderID = originalPacket.src;
	packetNumber = originalPacket.packnum;
	gw_id = _gw_id;
	//salva il timestamp dell'orario di ricezione del pacchetto in formato AAAA-MM-GG OO-MM-SS
	getTime();

	int a = 0;
	//il primo byte del pacchetto rappresenta l'id del sensore che hai fatto scattare l''invio del messaggio
	sensorID = originalPacket.data[a];
	a++;
	//gli altri byte sono i dati effettivi dei sensori
	pl = originalPacket.length;
	if (debug) {
		printf("packet lenght : %d\n", originalPacket.length);
	}
	for (; a< pl + 1 ; a++) {
		if (debug) {
			printf("inside for loop copying %d to position %d of data \n", (uint8_t)sx1272.packet_received.data[a], a - 1);
		}
		data[a - 1] = (uint8_t)originalPacket.data[a];
	}
	if (debug) {
		printf("outside for loop\n");
	}
}

ReceivedPacket::ReceivedPacket(pack originalPacket, int _gw_id) {
	ReceivedPacket(originalPacket, _gw_id, false);
}

void ReceivedPacket::getTime() {
	char buffer[30];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	receivedTime = localtime(&tv.tv_sec);
	strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", receivedTime);

}

void ReceivedPacket::issueAddToDatabaseCommand() {
	if (debug) {
		printf("ReceivedPacket : generazione del json ...");
	}

	std::string json = generateJSON();

	if (debug) {
		printf("fatto\n");
	}

	//qui viene fatto girare il comando nella shell di linux dove inserisce il messaggio appena creato nel database mongodb
	if (debug) {
		printf("ReceivedPacket :  generazione del comando ...");
	}

	std::string command = "curl -d \'";
	command.append(json);
	command.append("\' -H \"Content-Type: application/json\" http://localhost:28017/messages/test");

	if (debug) {
		printf("\nfatto\n");
		printf("ReceivedPacket: esecuzione del comando...");
	}

	system(command.c_str());

	if (debug){
		printf("fatto\n");
		printf("^$ linux command : %s \n ",command.c_str());
	}

	printf("\n");
}


std::string ReceivedPacket::generateID() {
	char buffer[50];
	std::string ID;
	sprintf(buffer, "%d",gw_id);
	ID = buffer;
	sprintf(buffer, "%d", arduinoSenderID);
	ID += buffer;
	sprintf(buffer, "%d", sensorID);
	ID += buffer;
	sprintf(buffer, "%d", packetNumber);
	ID += buffer;
	strftime(buffer,50, "%Y:%m:%dT%H:%M:%S", receivedTime);
	ID += buffer;
	return ID;
}

std::string ReceivedPacket::generateJSON(){
	char buffer[50];
	sprintf(buffer, "{ \"id\" : \"%s\",",generateID().c_str());
	if (debug) {
		printf("%s \n", buffer);
	}
	std::string json = buffer;
	sprintf(buffer," \"arduino\" : %d,",arduinoSenderID);
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;
	sprintf(buffer," \"sensore\" : %d,",sensorID);
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;
	sprintf(buffer," \"pacchetto\" : %d, ",packetNumber);
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;
	strftime(buffer,50," \"timestamp\" : \"%Y:%m:%d %H:%M:%S\", ",receivedTime);
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;
	sprintf(buffer," \"dati\" : [ ");
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;
	
	for (int a = 0; a < pl; a++) {


		if (a != pl - 1) {
			sprintf(buffer, " {\"byte\" : %d}, ", data[a]);
		}
		else {
			sprintf(buffer, " {\"byte\" : %d} ", data[a]);
		}

		if (debug) {
			printf("\t %s \n", buffer);
		}
		json += buffer;
	}
	
	sprintf(buffer," ]}");
	if (debug) {
		printf("%s \n", buffer);
	}
	json += buffer;

	return json;
}

