#include "PGClient.h"

PGClient::PGClient()
{
	SocketManager* sm = new SocketManager();

	hConnSock = sm->ConnectToCS();
	Header* h = new Header(0, PACKET_GENERATOR, 0, MONITORING_SERVER, 0);
	char* data = reinterpret_cast<char*>(h);
	sm->Send(hConnSock, data);
	buf = sm->Receive(hConnSock);
}


PGClient::~PGClient()
{

}




