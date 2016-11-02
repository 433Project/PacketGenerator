#include "SocketManager.h"
#include <json/json.h>

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
		cout << "===> Connection Server(" << inet_ntoa(addr.sin_addr) << ") connected ..." << endl;
		return hSock;
	}

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

DWORD SocketManager::Send(SOCKET s, char* data) 
{
	WSABUF wsabuf;
	wsabuf.buf = data;
	wsabuf.len = sizeof(Packet);

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

void SocketManager::SendFlatBuffers(SOCKET s, Command comm, string data, int SrcCode)
{
	flatbuffers::FlatBufferBuilder builder;
	//MakeBody(builder, comm, data);
	flatbuffers::Offset<Body> body = CreateBody(builder, comm, builder.CreateString(data));
	flatbuffers::Offset<Header> header = CreateHeader(builder, sizeof(body), SrcDstType_PACKET_GENERATOR, SrcCode, SrcDstType_MONITORING_SERVER, 0);
	builder.Finish(CreatePacket(builder, header, body));

	uint8_t* buf = builder.GetBufferPointer();
		
	send(s, reinterpret_cast<char*>(buf), builder.GetSize(), 0);

	//cout << "===> Send !!!!!" << endl;
	/*
	cout << reinterpret_cast<char*>(builder.GetBufferPointer()) <<endl;
	const Packet *p = GetPacket(buf);
	const Header *h = p->header();
	cout << sizeof(Header) << endl;
	auto b = p->body();
	cout <<"h->length() : "<< h->length() << endl;
	cout << "h->srcType() : " << h->srcType() << endl;
	cout << "h->srcCode() : " << h->srcCode() << endl;
	cout << "h->dstType() : " << h->dstType() << endl;
	cout << "h->dstCode() : " << h->dstCode() << endl;
	cout << "b->cmd() : " << b->cmd() << endl;
	cout << "b->data() : " << b->data() << endl;
	*/
}