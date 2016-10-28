#include "SocketManager.h"

SocketManager::SocketManager()
{
}


SocketManager::~SocketManager()
{
}

SOCKET SocketManager::ConnectToCS() 
{
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "[!] WSAStartup failed, code : " << nErrCode << endl;
		return INVALID_SOCKET;
	}

	hSock = CreateTCPSocket();

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(csIP);		//Connection Server IP
	addr.sin_port = htons(csPort);					//Connection Server Port

	cout << "===> Connecting to Connection Server..." << endl;
	if (connect(hSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "[!]connect failed, code : " << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	else
	{
		cout << "===> Connection Server connected ..." << endl;
		return hSock;
	}

	return ;
}

SOCKET SocketManager::CreateUDPSocket(const DWORD flags)
{
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

DWORD SocketManager::Send(SOCKET s, char* buf) 
{
	WSABUF wsabuf;
	wsabuf.buf = buf;
	wsabuf.len = sizeof(buf);

	DWORD bytesSent;
	WSASend(s, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}

char* SocketManager::Receive(SOCKET s) 
{
	WSABUF wsabuf;
	WSARecv(s, &wsabuf, 1, NULL, 0, NULL, NULL);
	return wsabuf.buf;
}