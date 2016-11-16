#pragma once
#include <iostream>
#include "Packet_generated.h"
#include "flatbuffers/flatbuffers.h"
#include "Protocol.h"

using namespace fb;
using namespace std;

class MessageManager
{
public:
	MessageManager(int p);
	~MessageManager();
	void MakePacket(char* bytes, COMMAND comm, string data1);

private:
	int packetSize;
};

