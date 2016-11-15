#pragma once
#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>
#include "Packet_generated.h"
#include "Protocol.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;
using namespace fb;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();
	SOCKET ConnectToCS();
	SOCKET CreateUDPSocket(sockaddr_in &addr, const DWORD flags = 0);
	SOCKET CreateTCPSocket(const DWORD flags = 0);
	DWORD Send(SOCKET s, char* buf, int len);
	DWORD SendUDP(SOCKET s, sockaddr_in addr, char* data, int len);
	char* Receive(SOCKET s);
	char* MakePacket(int* len, int srcCode, Command comm, string data1, string data2);
	void SetCSIP(char* ip);

private:
	WSADATA wsd;
	SOCKET hSock;
	SOCKADDR_IN addr;
	char* csIP = "10.100.10.6";
	int csPort = 10433;
	int csUDPPort = 5050;

};

