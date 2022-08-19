#pragma once

#include "global.h"
//#include "JsonLocation.h"



#pragma  pack (push,1)
enum Event
{
	START_OBJECT=1,
	END_OBJECT, 
	START_ARRAY, 
	END_ARRAY, 
	KEY_NAME, 
	VALUE_STRING, 
	VALUE_NUMBER, 
	VALUE_TRUE, 
	VALUE_FALSE,
	VALUE_NULL,
	END
};

struct JsonLocation
{
	UINT16 start_;
	UINT16 end_;
};

class  JsonParser
{
public:
	JsonParser(char* jsonStr);
	~JsonParser();
	void   close();
	Event  next();
	bool   hasNext();
	bool   isIntegerNumber();
	char*  getString();
	INT32  getInt();
	INT64  getLong();
	float  getDecimal();

	UINT16 JsonParser::compare2Set(UINT16& i1, UINT16* pos1, UINT16& i2, UINT16* pos2, UINT16& i3, UINT16* pos3, UINT16& i4, UINT16* pos4, UINT16& i5, UINT16* pos5, UINT16& i6, UINT16* pos6, UINT8* events, JsonLocation* locations, UINT16 nPos);
private:
	UINT16  nSize;
	UINT16  curPos;
	UINT8*  events;
	JsonLocation*   locations;

	char*  orginalJsonStr;
};

#pragma pack(pop)