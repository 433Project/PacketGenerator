#pragma once
#include <conio.h>
#include "SocketManager.h"
#include "TimeManager.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class PGClient
{
public:
	PGClient(char* ip);
	~PGClient();
	void PrintPGMessage();
	void RunPacketGenerator();
	void RunDatagramGenerator();
	

private:
	SOCKET connSock;
	char* csIP;
	bool isRunning = true;

	int packetSize = 100;
	
};

