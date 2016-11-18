#include "PGClient.h"

PGClient::PGClient(char* ip)
{
	PrintPGMessage();
	csIP = ip;

	csSock = new SocketManager();
	msg = new MessageManager(packetSize);
	timer = new TimeManager();

	if (csSock == nullptr || msg == nullptr || timer == nullptr)
	{
		cout << "allocation fail" << endl;
		exit(0);
	}

	if (!csSock->ConnectServer(csIP))
		exit(0);

}

PGClient::~PGClient()
{
	if (csSock != nullptr)
		delete csSock;

	if (msg != nullptr)
		delete msg;

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
}

void PGClient::RunPacketGenerator(int total)
{
	char* data = new char[packetSize];
	
	msg->MakePacket(data, COMMAND_PG_START, to_string(total));
	csSock->Send(data, packetSize);

	memset(data, 0, packetSize);
	msg->MakePacket(data, COMMAND_PG_DUMMY, "");
	
	timer->StartTiming();
	for (long i = 0; i < total; i++)
	{
		csSock->Send(data, packetSize);
	}

	memset(data, 0, packetSize);
	msg->MakePacket(data, COMMAND_PG_DUMMY, "");
	csSock->Send(data, packetSize);
	cout << "> sent all" << endl;
	csSock->Shutdown();

	while (true)
	{
		if (!csSock->Receive())
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
	SOCKET s = csSock->CreateUDPSocket(csIP);
	
	char* data = new char[packetSize];
	msg->MakePacket(data, COMMAND_PG_START, to_string(total));
	csSock->Send(data, packetSize);

	memset(data, 0, packetSize);
	msg->MakePacket(data, COMMAND_PG_DUMMY, "");
	
	timer->StartTiming();
	for (long i = 0; i < total; ++i)
	{
		csSock->SendUDP(data, packetSize);
	}

	memset(data, 0, packetSize);
	msg->MakePacket(data, COMMAND_PG_END, "");
	csSock->Send(data, packetSize);
	cout << "> sent all" << endl;
	csSock->Shutdown();

	while (true)
	{
		if (!csSock->Receive())
			break;
	}

	timer->StopTiming();
	timer->PrintTimings(total);
	
	if (data != nullptr) {
		delete data;
	}
}