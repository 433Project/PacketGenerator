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
	cout << "IF YOU WANT TO STOP, PRESS ANY KEY...." << endl;

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

void PGClient::RunPacketGenerator()
{
	int total = 0;
	char* data = sm->MakePacket(0, Command_PG_START, "", "");
	sm->Send(hConnSock, data);
	delete data;
	
	data = sm->MakePacket(0, Command_PG_DUMMY, "", "");
	timer->StartTiming();
	
	while(!kbhit())
	{
		sm->Send(hConnSock, data);
		total++;
	}
	
	timer->StopTiming();
	delete data;

	data = sm->MakePacket(0, Command_PG_END, "", "");
	sm->Send(hConnSock, data);

	timer->PrintTimings(total);
	delete data;
}

void PGClient::RunDatagramGenerator()
{
	int total = 0;

	sockaddr_in addr;
	SOCKET s = sm->CreateUDPSocket(csIP, addr);
	
	char* data = sm->MakePacket(0, Command_PG_START, "", "");
	sm->Send(hConnSock, data);
	delete data;

	data = sm->MakePacket(0, Command_PG_DUMMY, "", "");
	timer->StartTiming();
	
	while (!kbhit())
	{
		sm->SendUDP(s, addr, data);
		total++;
	}
	
	timer->StopTiming();
	delete data;

	data = sm->MakePacket(0, Command_PG_END, "", "");
	sm->Send(hConnSock, data);
	timer->PrintTimings(total);
	delete data;
}
