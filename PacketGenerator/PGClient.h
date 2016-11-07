#pragma once
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
	void RunPacketGenerator(int total, int size);
	void RunDatagramGenerator(int total, int size);

private:
	SOCKET hConnSock;
	char* csIP;
	
};

