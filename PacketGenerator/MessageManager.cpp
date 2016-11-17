#include "MessageManager.h"


MessageManager::MessageManager(int packetSize)
{
	this->packetSize = packetSize;
}


MessageManager::~MessageManager()
{
}

void MessageManager::MakePacket(char* bytes, COMMAND comm, string data1)
{
	flatbuffers::FlatBufferBuilder builder;
	flatbuffers::Offset<Body> body;

	if (data1.empty())
		body = CreateBody(builder, comm, STATUS_NONE);
	else
		body = CreateBody(builder, comm, STATUS_NONE, builder.CreateString(data1));

	builder.Finish(body);

	uint8_t* buf = builder.GetBufferPointer();
	char* b = reinterpret_cast<char*>(buf);
	int len = builder.GetSize();

	Header* h = new Header(len, PACKET_GENERATOR, 0, MONITORING_SERVER, 0);
	
	memset(bytes, 0, packetSize);
	memcpy(bytes, h, sizeof(Header));
	memcpy(&bytes[sizeof(Header)], b, len);

	delete h;
}

