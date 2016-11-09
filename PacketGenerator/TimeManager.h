#pragma once
#include <iostream>
#include <WinSock2.h>

using namespace std;

class TimeManager
{
public:
	TimeManager();
	~TimeManager();
	void StartTiming();
	void StopTiming();
	void PrintTimings(long packets);

private:
	LARGE_INTEGER g_frequency;
	LARGE_INTEGER g_startCounter;
	LARGE_INTEGER g_stopCounter;
};

