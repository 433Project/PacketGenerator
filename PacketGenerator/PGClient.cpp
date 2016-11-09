#include "PGClient.h"

LARGE_INTEGER g_frequency;
LARGE_INTEGER g_startCounter;
LARGE_INTEGER g_stopCounter;

SocketManager* sm;
TimeManager* timer;

PGClient::PGClient(char* ip)
{
	cout << "#############################################################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "##################### Packet Generator ######################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "#############################################################" << endl;

	sm = new SocketManager();
	timer = new TimeManager();
	csIP = ip;
	hConnSock = sm->ConnectToCS(csIP);
}

PGClient::~PGClient()
{
	closesocket(hConnSock);
	delete sm;
	delete timer;
}

void PGClient::RunPacketGenerator(int total)
{
	char* data = sm->MakePacket(0, Command_PG_START, ::to_string(total));
	sm->Send(hConnSock, data);
	delete data;
	
	data = sm->MakePacket(0, Command_PG_DUMMY, "안녕하세요 PACKET_GENERATOR입니다.");
	timer->StartTiming();
	for (long i = 0; i < total; i++)
	{
		sm->Send(hConnSock, data);
	}
	timer->StopTiming();
	delete data;

	Sleep(total / 10);
	data = sm->MakePacket(0, Command_PG_END, "END");
	sm->Send(hConnSock, data);

	timer->PrintTimings(total);
	delete data;
}

void PGClient::RunDatagramGenerator(int total)
{
	sockaddr_in addr;
	SOCKET s = sm->CreateUDPSocket(csIP, addr);
	
	char* data = sm->MakePacket(0, Command_PG_START, ::to_string(total));
	sm->Send(hConnSock, data);
	delete data;

	data = sm->MakePacket(0, Command_PG_DUMMY, "안녕하세요 PACKET_GENERATOR입니다.");
	timer->StartTiming();
	for (long i = 0; i < total; ++i)
	{
		sm->SendUDP(s, addr, data);
	}
	timer->StopTiming();
	delete data;

	Sleep(total / 10);
	data = sm->MakePacket(0, Command_PG_END, "END");
	sm->Send(hConnSock, data);
	timer->PrintTimings(total);
	delete data;
}