#pragma once
#include "SocketManager.h"
#include "MessageManager.h"
#include "TimeManager.h"
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class PGClient
{
public:
	PGClient(char* ip);
	~PGClient();
	void PrintPGMessage();
	void RunPacketGenerator(int total);
	void RunDatagramGenerator(int total);

private:
	SocketManager* csSock;
	MessageManager* msg;
	TimeManager* timer;

	char* csIP;
	int packetSize = 100;
};

