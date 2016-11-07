#include "PGClient.h"

LARGE_INTEGER g_frequency;
LARGE_INTEGER g_startCounter;
LARGE_INTEGER g_stopCounter;

SocketManager* sm;
TimeManager* timer;

PGClient::PGClient()
{
	cout << "#############################################################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "##################### Packet Generator ######################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "#############################################################" << endl;

	sm = new SocketManager();
	timer = new TimeManager();

	hConnSock = sm->ConnectToCS();
	
}


PGClient::~PGClient()
{
	closesocket(hConnSock);
	delete sm;
	delete timer;
}

void PGClient::RunPacketGenerator(int total, int size)
{
	
	int len = 0;
	cout << total << endl;
	char* data = sm->MakePacket(&len, 0, Command_PG_START, ::to_string(total));
	cout << len + sizeof(Header) << endl;
	sm->Send(hConnSock, data, sizeof(Header) + len);
	delete data;
	
	data = sm->MakePacket(&len, 0, Command_PG_DUMMY, "안녕하세요 PACKET_GENERATOR입니다.");
	cout << len + sizeof(Header) << endl;
	
	timer->StartTiming();
	for (long i = 0; i < total; i++)
	{
		sm->Send(hConnSock, data, len + sizeof(Header));
	}
	timer->StopTiming();
		
	delete data;

	data = sm->MakePacket(&len, 0, Command_PG_END, "END");
	cout << len + sizeof(Header) << endl;
	sm->Send(hConnSock, data, len + 20);
	timer->PrintTimings(total);
	delete data;
}

void PGClient::RunDatagramGenerator(int total, int size)
{
	sockaddr_in addr;
	SOCKET s = sm->CreateUDPSocket(addr);

	int len = 0;
	cout << total << endl;
	char* data = sm->MakePacket(&len, 0, Command_PG_START, ::to_string(total));
	cout << len + 20 << endl;
	sm->Send(hConnSock, data, sizeof(Header) + len);
	delete data;

	data = sm->MakePacket(&len, 0, Command_PG_DUMMY, "안녕하세요 PACKET_GENERATOR입니다.");
	cout << len + 20 << endl;
	
	timer->StartTiming();
	for (long i = 0; i < total; ++i)
	{
		sm->SendUDP(s, addr, data, len + sizeof(Header));
	}
	timer->StopTiming();

	delete data;

	data = sm->MakePacket(&len, 0, Command_PG_END, "END");
	cout << len + 20 << endl;
	sm->Send(hConnSock, data, len + 20);
	timer->PrintTimings(total);
	delete data;
}