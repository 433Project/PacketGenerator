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
}

SOCKET SocketManager::ConnectToCS(SOCKET sock, char* ip)
{
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);		//Connection Server IP
	addr.sin_port = htons(csPort);				//Connection Server Port

	cout << "> Connecting to Connection Server(" << ip << ")..." << endl;
	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "[!]connect failed, code : " << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}
	else
	{
		cout << "> Connection Server(" << inet_ntoa(addr.sin_addr) << ") connected ..." << endl;
		return sock;
	}

}
SOCKET SocketManager::CreateUDPSocket(char* ip, sockaddr_in &addr, const DWORD flags)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(csUDPPort);
	addr.sin_addr.s_addr = inet_addr(ip);

	SOCKET sock = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, flags);

	if (sock == INVALID_SOCKET)
	{
		cout << "[!] UDP WSASocket error, code : " << GetLastError() << endl;
		exit(0);
	}
	else
		cout << "**** UDP WSASocket Created ****" << endl;

	return sock;
}

SOCKET SocketManager::CreateTCPSocket(const DWORD flags)
{
	SOCKET sock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);

	if (sock == INVALID_SOCKET)
	{
		cout << "[!] TCP WSASocket error, code : " << GetLastError() << endl;
		exit(0);
	}
	else
		cout << "**** TCP WSASocket Created ****" << endl;

	return sock;
}

DWORD SocketManager::Send(SOCKET s, char* data, int len)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = len;

	DWORD bytesSent;
	WSASend(s, &wsabuf, 1, &bytesSent, 0, NULL, NULL);
	return bytesSent;
}

DWORD SocketManager::SendUDP(SOCKET s, sockaddr_in addr, char* data, int len)
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = len;

	DWORD bytesSent;
	WSASendTo(s, &wsabuf, 1, &bytesSent, 0, reinterpret_cast<sockaddr *>(&addr), sizeof(addr), NULL, NULL);
	return bytesSent;
}

int SocketManager::Receive(SOCKET s)
{
	char* buf = new char[1];
	int bytes = recv(s, buf, 1, 0);

	if (buf != nullptr) {
		delete buf;
	}

	return bytes;
}
