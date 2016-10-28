#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

LARGE_INTEGER g_frequency;
LARGE_INTEGER g_startCounter;
LARGE_INTEGER g_stopCounter;

SOCKET CreateUDPSocket(const DWORD flags = 0);
SOCKET CreateTCPSocket(const DWORD flags = 0);

void StartTiming();
void StopTiming();
void PrintTimings(const char *pDirection, long packets);

int main(int argc, char* argv[])
{
	if (argc != 6) 
	{
		cout << "USAGE: PacketGenerator <RemoteIP> <RemotePort> <Protocol> <PacketsToSend> <PacketLenght>" << endl;
		cout << "[RemoteIP] Connection Server's IP" << endl;
		cout << "[RemotePort] Connection Server's Port" << endl;
		cout << "[Protocol]TCP = 0, UDP = 1" << endl;

		exit(0);
	}

	const char* pAddress = argv[1];
	const int port = atoi(argv[2]);
	const bool proto = atoi(argv[3]);
	const long packets = atol(argv[4]);
	const long packetLenght = atol(argv[5]);

	WSADATA wsd;
	SOCKET hSock;
	SOCKADDR_IN addr;
	char *buffer = (char *)malloc(packetLenght);

	cout << "#################### Packet Generator ####################\n" << endl;

	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "[!] WSAStartup failed, code : " << nErrCode << endl;
		return 0;
	}
	
	if (proto)
		hSock = CreateUDPSocket();
	else
		hSock = CreateTCPSocket();

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(pAddress);		//Connection Server IP
	addr.sin_port = htons(port);					//Connection Server Port

	while (!proto)
	{
		cout << "===> Connecting to Connection Server..." << endl;
		if (connect(hSock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			cout << "[!]connect failed, code : " << WSAGetLastError() << endl;
			exit(0);
		}
		else
		{
			cout << "===> Connection Server connected ..." << endl;
			break;
		}
		
	}
		

	buffer = "hi";		//¸Þ¼¼Áö!!!!!!!!!!!!!!!!!!!!!!!!!!!
	WSABUF wsabuf;
	wsabuf.len = packetLenght;
	wsabuf.buf = buffer;
	DWORD sendBytes = 0;

	cout << "===> Start to Send " << packets << " Datas" << endl;
	
	StartTiming();

	for (long i = 0; i < packets; i++) 
	{
		if(SOCKET_ERROR == WSASend(hSock, &wsabuf,1, &sendBytes, 0, NULL, NULL)){
			cout << "[!]WSASend error, code : " << GetLastError() << endl;
			exit(0);
		}
	}

	StopTiming();
	cout << "===> End to Send Data" << endl;
	PrintTimings("Sent", packets);
	return 0;
}

SOCKET CreateUDPSocket(const DWORD flags)
{
	SOCKET hSock = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, flags);

	if (hSock == INVALID_SOCKET)
	{
		cout << "[!] UDP WSASocket error, code : " << GetLastError() << endl;
	}
	else
		cout << "**** UDP WSASocket Created ****" <<  endl;
	return hSock;
}

SOCKET CreateTCPSocket(const DWORD flags)
{
	SOCKET hSock = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, flags);

	if (hSock == INVALID_SOCKET)
	{
		cout << "[!] TCP WSASocket error, code : " << GetLastError() << endl;
	}
	else
		cout << "**** TCP WSASocket Created ****" << endl;

	return hSock;
}


void StartTiming()
{
	QueryPerformanceFrequency(&g_frequency);

	cout << "***** Timing started" << endl;

	if (!QueryPerformanceCounter(&g_startCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}
}

void StopTiming()
{
	if (!QueryPerformanceCounter(&g_stopCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}

	cout << "***** Timing stopped" << endl;
}

void PrintTimings(const char *pDirection, long packets)
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
