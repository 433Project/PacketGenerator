#pragma once
#include <iostream>
#include <WinSock2.h>

using namespace std;

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

private:
	void StartTiming();
	void StopTiming();
	void PrintTimings(const char *pDirection, long packets);

};

