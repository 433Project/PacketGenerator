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
	
	if (argc != 3) {
		PrintUsage();
		exit(0);
	}

	ip = argv[1];
	protocol = argv[2];
	
	PGClient* pg = new PGClient(ip);

	switch (protocol[0])
	{
		case 't': case 'T':
			pg->RunPacketGenerator();
			break;
		case 'u': case 'U':
			pg->RunDatagramGenerator();
			break;
		default:
			PrintUsage();
			exit(0);
	}

	if(pg != nullptr)
	{
		delete pg;
	}

	
}
