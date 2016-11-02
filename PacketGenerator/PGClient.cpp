#include "PGClient.h"

LARGE_INTEGER g_frequency;
LARGE_INTEGER g_startCounter;
LARGE_INTEGER g_stopCounter;

PGClient::PGClient()
{
	cout << "#############################################################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "##################### Packet Generator ######################" << endl;
	cout << "#####################==================######################" << endl;
	cout << "#############################################################" << endl;

	SocketManager* sm = new SocketManager();

	hConnSock = sm->ConnectToCS();
	sm->SendFlatBuffers(hConnSock, Command_PG_START, "1000", 0);
	StartTiming();
	for (int i = 0; i < 1000;i++)
	{	
		sm->SendFlatBuffers(hConnSock, Command_PG_DUMMY, to_string(i), 0);
		cout << to_string(i) << endl;
	}
	StopTiming();
	
	sm->SendFlatBuffers(hConnSock, Command_PG_END, "END", 0);
	cout << "===> End to Send Data" << endl;
	PrintTimings("Sent", 1000);
}


PGClient::~PGClient()
{

}

void PGClient::StartTiming()
{
	QueryPerformanceFrequency(&g_frequency);

	cout << "***** Timing started" << endl;

	if (!QueryPerformanceCounter(&g_startCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}
}

void PGClient::StopTiming()
{
	if (!QueryPerformanceCounter(&g_stopCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}

	cout << "***** Timing stopped" << endl;
}

void PGClient::PrintTimings(const char *pDirection, long packets)
{
	LARGE_INTEGER elapsed;

	elapsed.QuadPart = (g_stopCounter.QuadPart - g_startCounter.QuadPart) / (g_frequency.QuadPart / 1000);

	cout << " Complete in " << elapsed.QuadPart << "ms" << endl;
	cout << pDirection <<" "<< packets << " datagrams" << endl;

	if (elapsed.QuadPart != 0)
	{
		const double perSec = packets / elapsed.QuadPart * 1000.00;

		cout << perSec << " datagrams per second" << endl;
	}
}

