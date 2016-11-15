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
	SOCKET ConnectToCS(char* ip);
	SOCKET CreateUDPSocket(char* ip, sockaddr_in &addr, const DWORD flags = 0);
	SOCKET CreateTCPSocket(const DWORD flags = 0);
	DWORD Send(SOCKET s, char* buf);
	DWORD SendUDP(SOCKET s, sockaddr_in addr, char* data);
	char* Receive(SOCKET s);
	char* MakePacket(int srcCode, Command comm, string data1, string data2);
	

private:
	WSADATA wsd;
	SOCKET hSock;
	SOCKADDR_IN addr;
	
	/*int csPort = 10444;
	int csUDPPort = 10433;
*/
	int csPort = 10433;
	int csUDPPort = 5050;

	int packetSize = 100;

};

