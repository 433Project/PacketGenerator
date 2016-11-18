#pragma once
#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

class SocketManager
{
public:
	SocketManager();
	~SocketManager();

	bool ConnectServer(char* ip);
	bool CreateUDPSocket(char* ip, const DWORD flags = 0);
	bool CreateTCPSocket(const DWORD flags = 0);

	DWORD Send(char* buf, int len);
	DWORD SendUDP(char* data, int len);

	int Receive();
	void Shutdown();

private:
	WSADATA wsd;

	SOCKET sockTCP;
	SOCKET sockUDP;

	SOCKADDR_IN addrTCP;
	SOCKADDR_IN addrUDP;

	int csPort = 10433;
	int csUDPPort = 5050;

};

