#include "SocketManager.h"
#include <json/json.h>

SocketManager::SocketManager()
{
}

SocketManager::~SocketManager()
{
}

SOCKET SocketManager::ConnectToCS(char* ip) 
{
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "[!] WSAStartup failed, code : " << nErrCode << endl;
		return INVALID_SOCKET;
	}

	hSock = CreateTCPSocket();
	
	int option = TRUE;
	//setsockopt(hSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);		//Connection Server IP
	addr.sin_port = htons(csPort);					//Connection Server Port

	cout << "> Connecting to Connection Server("<<ip<<")..." << endl;
	if (connect(hSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "[!]connect failed, code : " << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	else
	{
		cout << "> Connection Server(" << inet_ntoa(addr.sin_addr) << ") connected ..." << endl;
		return hSock;
	}

}

SOCKET SocketManager::CreateUDPSocket(char* ip, sockaddr_in &addr, const DWORD flags)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(csUDPPort);
	addr.sin_addr.s_addr = inet_addr(ip);

	SOCKET hSock = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, flags);

	if (hSock == INVALID_SOCKET)
	{
		cout << "[!] UDP WSASocket error, code : " << GetLastError() << endl;
	}
	else
		cout << "**** UDP WSASocket Created ****" << endl;


	return hSock;
}

SOCKET SocketManager::CreateTCPSocket(const DWORD flags)
{
	SOCKET hSock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);

	if (hSock == INVALID_SOCKET)
	{
		cout << "[!] TCP WSASocket error, code : " << GetLastError() << endl;
	}
	else
		cout << "**** TCP WSASocket Created ****" << endl;

	return hSock;
}

DWORD SocketManager::Send(SOCKET s, char* data)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = packetSize;

	DWORD bytesSent;
	WSASend(s, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}

DWORD SocketManager::SendUDP(SOCKET s, sockaddr_in addr, char* data)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = packetSize;

	DWORD bytesSent;
	WSASendTo(s, &wsabuf, 1, &bytesSent, 0, reinterpret_cast<sockaddr *>(&addr), sizeof(addr), NULL, NULL);
	return bytesSent;
}

char* SocketManager::Receive(SOCKET s) 
{
	WSABUF wsabuf;
	WSARecv(s, &wsabuf, 1, NULL, 0, NULL, NULL);
	return wsabuf.buf;
}

char* SocketManager::MakePacket(int srcCode, Command comm, string data)
{
	flatbuffers::FlatBufferBuilder builder;
	flatbuffers::Offset<Body> body = CreateBody(builder, comm, Status_NONE, builder.CreateString(data));
	builder.Finish(body);

	uint8_t* buf = builder.GetBufferPointer();
	char* b = reinterpret_cast<char*>(buf);
	int len = builder.GetSize();
	
	Header* h = new Header(len, PACKET_GENERATOR, srcCode, MONITORING_SERVER, 0);

	char* bytes = new char[packetSize];
	memset(bytes, 0, packetSize);
	memcpy(bytes, h, sizeof(Header));
	memcpy(&bytes[sizeof(Header)], b, len);
	
	delete h;

	return bytes;
}
