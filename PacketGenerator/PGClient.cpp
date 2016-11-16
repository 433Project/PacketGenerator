#include "PGClient.h"
#include "MessageManager.h"
#include <conio.h>

SocketManager* sm;
MessageManager* mm;
TimeManager* timer;

PGClient::PGClient(char* ip)
{
	PrintPGMessage();
	csIP = ip;
	
	try
	{
		sm = new SocketManager();
		mm = new MessageManager(packetSize);
		timer = new TimeManager();

		connSock = sm->CreateTCPSocket();
		sm->ConnectToCS(connSock, csIP);
		while (connSock == INVALID_SOCKET) {
			connSock = sm->ConnectToCS(connSock, csIP);
		}
	}
	catch (exception e) 
	{
		cout << "allocation fail, error : " << e.what() << endl;
		exit(0);
	}
}

PGClient::~PGClient()
{
	if(connSock != INVALID_SOCKET)
		closesocket(connSock);
	
	if (sm != nullptr) 
		delete sm;
	
	if (mm != nullptr)
		delete mm;
		
	if (timer != nullptr)
		delete timer;
}

void PGClient::PrintPGMessage()
{
	cout << "#############################################################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "##################### Packet Generator ######################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "#############################################################" << endl;
	cout << "IF YOU WANT TO STOP, PRESS ANY KEY...." << endl;
}

void PGClient::RunPacketGenerator()
{
	long total = 0;
	char* data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_START, "");
	sm->Send(connSock, data, packetSize);
	
	if (data != nullptr) 
	{
		delete data;
		data = nullptr;
	}

	data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_DUMMY, "");
	timer->StartTiming();
	
	while(!kbhit())
	{
		sm->Send(connSock, data, packetSize);
		total++;
	}
	cout << "stop send packets" << endl;
	data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_END, to_string(total));
	sm->Send(connSock, data, packetSize);

	shutdown(connSock, SD_SEND);

	while (true) 
	{
		if (!sm->Receive(connSock))
			break;
	}

	timer->StopTiming();

	if (data != nullptr) {
		delete data;
		data = nullptr;
	}

	timer->PrintTimings(&total);
	
	if (data != nullptr) {
		delete data;
	}
}

void PGClient::RunDatagramGenerator()
{
	long total = 0;

	sockaddr_in addr;
	SOCKET s = sm->CreateUDPSocket(csIP, addr);
	
	char* data = new char[packetSize]; 
	mm->MakePacket(data, COMMAND_PG_START, "");
	sm->Send(connSock, data, packetSize);
	
	if (data != nullptr) {
		delete data;
		data = nullptr;
	}

	data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_DUMMY, "");

	if (data != nullptr) {
		delete data;
		data = nullptr;
	}
	
	timer->StartTiming();
	
	while (!kbhit())
	{
		sm->SendUDP(s, addr, data, packetSize);
		total++;
	}

	shutdown(connSock, SD_SEND);

	while (true)
	{
		if (!sm->Receive(connSock))
			break;
	}

	timer->StopTiming();

	data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_END, to_string(total));
	sm->Send(connSock, data, packetSize);
	timer->PrintTimings(&total);
	
	if (data != nullptr) {
		delete data;
	}
}
