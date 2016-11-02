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
	PGClient();
	~PGClient();
private:
	void StartTiming();
	void StopTiming();
	void PrintTimings(const char *pDirection, long packets);

private:
	SOCKET hConnSock;
	
};

