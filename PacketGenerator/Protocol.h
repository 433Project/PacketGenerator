#pragma once
enum TERMINALTYPE :int
{
	MATCHING_SERVER = 0,
	MATCHING_CLIENT,
	ROOM_SERVER,
	PACKET_GENERATOR,
	MONITORING_SERVER,
	CONFIG_SERVER,
	CONNECTION_SERVER
};

struct Header
{
	int length;
	TERMINALTYPE srcType;
	int srcCode;
	TERMINALTYPE dstType;
	int dstCode;
	Header() {};

	Header(int len, TERMINALTYPE srcType, int srcCode, TERMINALTYPE dstType, int dstCode)
	{
		this->length = len;
		this->srcType = srcType;
		this->srcCode = srcCode;
		this->dstType = dstType;
		this->dstCode = dstCode;
	}
};

struct UserInfo
{
	int	ID;
	int	metric;
};