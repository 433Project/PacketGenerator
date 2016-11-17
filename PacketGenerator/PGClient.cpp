#include "PGClient.h"
#include <conio.h>


PGClient::PGClient(char* ip)
{
	PrintPGMessage();
	csIP = ip;
	
	csSock = new SocketManager();
	msg = new MessageManager();
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
	cout << "IF YOU WANT TO STOP, PRESS ANY KEY...." << endl;
}

void PGClient::RunPacketGenerator(bool proto)
{
	long total = 0;
	
	char* data = new char[packetSize];
	msg->MakePacketBytes(data, packetSize, COMMAND_PG_START, "");
	csSock->Send(data, packetSize);
	
	memset(data, 0, packetSize);
	msg->MakePacketBytes(data, packetSize, COMMAND_PG_DUMMY, "");
	
	if (proto)
	{
		timer->StartTiming();
		while (!_kbhit())
		{
			csSock->Send(data, packetSize);
			total++;
		}
	}
	else
	{
		timer->StartTiming();
		while (csSock->CreateUDPSocket(csIP) && !_kbhit())
		{
			csSock->SendUDP(data, packetSize);
			total++;
		}
	}
	cout << "> stop sending packets" << endl;
	
	memset(data, 0, packetSize);
	msg->MakePacketBytes(data, packetSize, COMMAND_PG_END, to_string(total));
	csSock->Send(data, packetSize);

	csSock->Shutdown();

	while (true) 
	{
		if (!csSock->Receive())
			break;
	}

	timer->StopTiming();
	timer->PrintTimings(&total);
	
	if (data != nullptr) {
		delete data;
	}
}
