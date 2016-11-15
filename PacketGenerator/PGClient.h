#pragma once
#include <conio.h>
#include "SocketManager.h"
#include "TimeManager.h"
#include "flatbuffers/flatbuffers.h"
#pragma comment(lib, "ws2_32.lib")
using namespace std;
using namespace fb;

class PGClient
{
public:
	PGClient(char* ip);
	~PGClient();
	void RunPacketGenerator();
	void RunDatagramGenerator();


private:
	SOCKET hConnSock;
	char* csIP;
	bool isRunning = true;

	
};

