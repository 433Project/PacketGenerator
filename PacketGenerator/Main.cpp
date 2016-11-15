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
	//long packetsToSend;

	if (argc != 3) {
		PrintUsage();
		exit(0);
	}

	ip = argv[1];
	
	protocol = argv[2];
	//packetsToSend = atol(argv[3]);

	PGClient* pg = new PGClient(ip);

	

	if (!strcmp(protocol, "t"))
		pg->RunPacketGenerator();
	else
		pg->RunDatagramGenerator();

	Sleep(10000); //delay for closesocket

	pg->~PGClient();
}
