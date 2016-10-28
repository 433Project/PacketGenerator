#pragma once
#include "SocketManager.h"
#include "TimeManager.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

class PGClient
{
public:
	PGClient();
	~PGClient();
private:
	SOCKET hConnSock;
};

