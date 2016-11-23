#include "PGClient.h"


void PrintUsage()
{
	cout << "Useage : PacketGenerator <IP> <Protocol> <count>" << endl;
	cout << "<Protocol>" << endl;
	cout << "	t : tcp, default" << endl;
	cout << "	u : udp" << endl;
	cout << "<Count>" << endl;
	cout << "	How many do you want to send?" << endl;
}

int main(int argc, char* argv[])
{
	char* ip;
	char* protocol;
	long packetsToSend;

	if (argc != 4) {
		PrintUsage();
		exit(0);
	}

	ip = argv[1];
	
	protocol = argv[2];
	packetsToSend = atol(argv[3]);

	//while (true)
	//{
	PGClient* pg = new PGClient(ip);

	if (pg == nullptr)
		exit(0);

	switch (protocol[0])
	{
	case 't': case 'T':
		pg->RunPacketGenerator(packetsToSend);
		break;
	case 'u': case 'U':
		pg->RunDatagramGenerator(packetsToSend);
		break;
	default:
		PrintUsage();
		exit(0);
	}

	if (pg != nullptr)
	{
		delete pg;
	}
	//}
}
