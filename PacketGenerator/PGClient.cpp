#include "PGClient.h"

PGClient::PGClient(char* ip)
{
	PrintPGMessage();
	csIP = ip;

	sm = new SocketManager();
	mm = new MessageManager(packetSize);
	timer = new TimeManager();

	if (sm == nullptr || mm == nullptr || timer == nullptr)
	{
		cout << "allocation fail" << endl;
		exit(0);
	}

	connSock = sm->CreateTCPSocket();
	sm->ConnectToCS(connSock, csIP);

	while (connSock == INVALID_SOCKET)
	{
		connSock = sm->ConnectToCS(connSock, csIP);
	}
}

PGClient::~PGClient()
{
	if (connSock != INVALID_SOCKET)
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

void PGClient::RunPacketGenerator(int total)
{
	char* data = new char[packetSize];
	
	mm->MakePacket(data, COMMAND_PG_START, to_string(total));
	sm->Send(connSock, data, packetSize);

	memset(data, 0, packetSize);
	mm->MakePacket(data, COMMAND_PG_DUMMY, "");
	
	timer->StartTiming();
	for (long i = 0; i < total; i++)
	{
		sm->Send(connSock, data, packetSize);
	}

	memset(data, 0, packetSize);
	mm->MakePacket(data, COMMAND_PG_DUMMY, "");
	sm->Send(connSock, data, packetSize);

	shutdown(connSock, SD_SEND);

	while (true)
	{
		if (!sm->Receive(connSock))
			break;
	}

	timer->StopTiming();
	timer->PrintTimings(total);

	if (data != nullptr) {
		delete data;
	}
}

void PGClient::RunDatagramGenerator(int total)
{

	sockaddr_in addr;
	SOCKET s = sm->CreateUDPSocket(csIP, addr);
	
	char* data = new char[packetSize];
	mm->MakePacket(data, COMMAND_PG_START, to_string(total));
	sm->Send(connSock, data, packetSize);

	memset(data, 0, packetSize);
	mm->MakePacket(data, COMMAND_PG_DUMMY, "");
	
	timer->StartTiming();
	for (long i = 0; i < total; ++i)
	{
		sm->SendUDP(s, addr, data, packetSize);
	}

	memset(data, 0, packetSize);
	mm->MakePacket(data, COMMAND_PG_END, "");
	sm->Send(connSock, data, packetSize);

	shutdown(connSock, SD_SEND);

	while (true)
	{
		if (!sm->Receive(connSock))
			break;
	}

	timer->StopTiming();
	timer->PrintTimings(total);
	
	if (data != nullptr) {
		delete data;
	}
}