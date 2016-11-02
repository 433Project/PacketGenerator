#pragma once
#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>
#include "Packet_generated.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;
using namespace fb;
//#include "Protocol.h"


class SocketManager
{
public:
	SocketManager();
	~SocketManager();
	SOCKET ConnectToCS();
	SOCKET CreateUDPSocket(const DWORD flags = 0);
	SOCKET CreateTCPSocket(const DWORD flags = 0);
	DWORD Send(SOCKET s, char* buf);
	char* Receive(SOCKET s);
	void SocketManager::SendFlatBuffers(SOCKET s, Command comm, string data, int SrcCode);
	//char* HeaderToCharptr(Header *h);

private:
	WSADATA wsd;
	SOCKET hSock;
	SOCKADDR_IN addr;
	char* csIP = "10.100.10.9";
	int csPort = 12345;
	//char* csIP = "10.100.10.10";
	//int csPort = 10000;

};

