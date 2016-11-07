#include "TimeManager.h"

static LARGE_INTEGER g_frequency;
static LARGE_INTEGER g_startCounter;
static LARGE_INTEGER g_stopCounter;

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::StartTiming()
{
	QueryPerformanceFrequency(&g_frequency);

	cout << "***** Timing started" << endl;

	if (!QueryPerformanceCounter(&g_startCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}
}

void TimeManager::StopTiming()
{
	if (!QueryPerformanceCounter(&g_stopCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}

	cout << "***** Timing stopped" << endl;
}

void TimeManager::PrintTimings(long packets)
{
	LARGE_INTEGER elapsed;

	elapsed.QuadPart = (g_stopCounter.QuadPart - g_startCounter.QuadPart) / (g_frequency.QuadPart / 1000);

	cout << "Complete in " << elapsed.QuadPart << "ms" << endl;
	cout << "Sent " << packets << " packets" << endl;

	if (elapsed.QuadPart != 0)
	{
		const double perSec = packets / elapsed.QuadPart * 1000.00;

		cout << perSec << " datagrams per second" << endl;
	}
}