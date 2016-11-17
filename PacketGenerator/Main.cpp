#include "PGClient.h"
#include "MessageManager.h"

void PrintUsage()
{
	cout << "Useage : PacketGenerator <IP> <Protocol>" << endl;
	cout << "<Protocol>" << endl;
	cout << "	t : tcp, default" << endl;
	cout << "	u : udp" << endl;
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

	if (pg == nullptr) 
		exit(0);

	switch (protocol[0])
	{
		case 't': case 'T':
			pg->RunPacketGenerator(true);
			break;
		case 'u': case 'U':
			pg->RunPacketGenerator(false);
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
