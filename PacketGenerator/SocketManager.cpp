#include "SocketManager.h"

SocketManager::SocketManager()
{
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "[!] WSAStartup failed, code : " << nErrCode << endl;
		exit(0);
	}
}

SocketManager::~SocketManager()
{
	if (sockTCP != INVALID_SOCKET)
		closesocket(sockTCP);
	if (sockUDP != INVALID_SOCKET)
		closesocket(sockUDP);

	WSACleanup();
}

bool SocketManager::ConnectServer(char* ip)
{
	if (!CreateTCPSocket())
		return false;

	memset(&addrTCP, 0, sizeof(addrTCP));
	addrTCP.sin_family = AF_INET;
	addrTCP.sin_addr.s_addr = inet_addr(ip);		//Connection Server IP
	addrTCP.sin_port = htons(csPort);				//Connection Server Port

	cout << "> Connecting to Connection Server(" << ip << ")..." << endl;
	if (connect(sockTCP, (SOCKADDR*)&addrTCP, sizeof(addrTCP)) == SOCKET_ERROR)
	{
		cout << "[!]connect failed, code : " << WSAGetLastError() << endl;
		sockTCP = INVALID_SOCKET;
		return false;
	}
	else
	{
		cout << "> Connection Server(" << inet_ntoa(addrTCP.sin_addr) << ") connected ..." << endl;
		return true;
	}
}

bool SocketManager::CreateTCPSocket(const DWORD flags)
{
	sockTCP = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);

	if (sockTCP == INVALID_SOCKET)
	{
		cout << "[!] TCP WSASocket error, code : " << GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "**** TCP WSASocket Created ****" << endl;
		return true;
	}

}

bool SocketManager::CreateUDPSocket(char* ip, const DWORD flags)
{
	addrUDP.sin_family = AF_INET;
	addrUDP.sin_port = htons(csUDPPort);
	addrUDP.sin_addr.s_addr = inet_addr(ip);

	sockUDP = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, flags);

	if (sockUDP == INVALID_SOCKET)
	{
		cout << "[!] UDP WSASocket error, code : " << GetLastError() << endl;
		return false;
	}
	else
	{
		cout << "**** UDP WSASocket Created ****" << endl;
		return true;
	}
}


DWORD SocketManager::Send(char* data, int len)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = len;

	DWORD bytesSent;
	WSASend(sockTCP, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}

DWORD SocketManager::SendUDP(char* data, int len)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = len;

	DWORD bytesSent;
	WSASendTo(sockUDP, &wsabuf, 1, &bytesSent, 0, reinterpret_cast<sockaddr *>(&addrUDP), sizeof(addrUDP), NULL, NULL);
	return bytesSent;
}

int SocketManager::Receive()
{
	char* buf = new char[1];
	int bytes = recv(sockTCP, buf, 1, 0);

	if (buf != nullptr) {
		delete buf;
	}

	return bytes;
}

void SocketManager::Shutdown()
{
	if (sockTCP != INVALID_SOCKET)
		shutdown(sockTCP, SD_SEND);
}

