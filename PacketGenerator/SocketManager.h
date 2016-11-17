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
	SOCKET ConnectToCS(SOCKET sock, char* ip);
	SOCKET CreateUDPSocket(char* ip, sockaddr_in &addr, const DWORD flags = 0);
	SOCKET CreateTCPSocket(const DWORD flags = 0);
	DWORD Send(SOCKET s, char* buf, int len);
	DWORD SendUDP(SOCKET s, sockaddr_in addr, char* data, int len);
	int SocketManager::Receive(SOCKET s);



private:
	WSADATA wsd;
	SOCKET sock;
	SOCKADDR_IN addr;

	int csPort = 10433;
	int csUDPPort = 5050;

};

