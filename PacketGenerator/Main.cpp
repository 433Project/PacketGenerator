#include "PGClient.h"


void PrintUsage()
{
	cout << "Useage : PacketGenerator <IP> <Protocol> <count> <length>" << endl;
	cout << "<Protocol>" << endl;
	cout << "	t : tcp, default" << endl;
	cout << "	u : udp" << endl;
	cout << "<Count>" << endl;
	cout << "	How many do you want to send?" << endl;
	cout << "<length>" << endl;
	cout << "	How long packet size" << endl;
}

int main(int argc, char* argv[])
{
	char* ip;
	char* protocol;
	long packetsToSend;
	long packetSize;

	if (argc < 2 || argc>5) {
		PrintUsage();
		exit(0);
	}

	ip = argv[1];
	protocol = argv[2];
	packetsToSend = atol(argv[3]);
	packetSize = atol(argv[4]);

	PGClient* pg = new PGClient();
	if (!strcmp(protocol, "t"))
		pg->RunPacketGenerator(packetsToSend, packetSize);
	else
		pg->RunDatagramGenerator(packetsToSend, packetSize);
	while (true) {}
}
