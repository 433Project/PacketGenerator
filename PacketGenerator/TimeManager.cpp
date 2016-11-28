#include "TimeManager.h"



TimeManager::TimeManager()
{
	QueryPerformanceFrequency(&frequency);
}


TimeManager::~TimeManager()
{
}

void TimeManager::StartTiming()
{
	cout << "***** Timing started" << endl;

	if (!QueryPerformanceCounter(&startCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}
}

void TimeManager::StopTiming()
{
	if (!QueryPerformanceCounter(&stopCounter))
	{
		cout << "[!] QueryPerformanceCounter error, code : " << GetLastError() << endl;
	}

	cout << "***** Timing stopped" << endl;
}

void TimeManager::PrintTimings(long *packets)
{
	LARGE_INTEGER elapsed;

	elapsed.QuadPart = (stopCounter.QuadPart - startCounter.QuadPart) / (frequency.QuadPart / 1000);

	cout << "Complete in " << elapsed.QuadPart << "ms" << endl;
	cout << "Sent " << *packets << " packets" << endl;

	if (elapsed.QuadPart / 1000 != 0)
	{
		double perSec = *packets / (elapsed.QuadPart / 1000);
		cout << perSec << " datagrams per second" << endl;
	}
}