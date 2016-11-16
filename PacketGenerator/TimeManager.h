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
	void PrintTimings(long *packets);

private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCounter;
	LARGE_INTEGER stopCounter;
};

