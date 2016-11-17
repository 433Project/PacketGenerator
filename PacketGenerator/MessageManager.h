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
	MessageManager();
	~MessageManager();
	void MakePacketBytes(char* bytes, int len, COMMAND comm, string data);

};

