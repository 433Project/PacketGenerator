#pragma once
#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

enum SrcDstType :int
{
	MATCHING_SERVER = 0,
	MATCHING_CLIENT,
	ROOM_MANAGER,
	PACKET_GENERATOR,
	MONITORING_SERVER
};

enum Command
{
	MATCH_REQUEST,
	MATCH_COMPLET,
	LATENCY,
	HEALTH_CHECK,
	MSLIST_REQUEST,
	PG_START,
	PG_END
};

struct Header
{
	int length;
	SrcDstType srcType;
	int srcCode;
	SrcDstType dstType;
	int dstCode;
	Header(int len, SrcDstType srcType, int srcCode, SrcDstType dstType, int dstCode) 
	{
		this->length = len;
		this->srcType = srcType;
		this->srcCode = srcCode;
		this->dstType = dstType;
		this->dstCode = dstCode;
	}
};

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

private:
	WSADATA wsd;
	SOCKET hSock;
	SOCKADDR_IN addr;
	char* csIP = "10.100.10.10";
	int csPort = 10101;

};

