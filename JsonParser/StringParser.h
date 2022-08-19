
#pragma once
#include "global.h"
#define  MaxKey   65536
enum  ValueType
{
	KEYNAME=1, 
	V_STRING, 
	V_NUMBER, 
	V_TRUE, 
	V_FALSE,
	V_NULL,
	V_END
};
class StringParser
{
public:
	StringParser();
	~StringParser();

	void  process(char curChar, UINT16  pos);
	void  clear();

	void  setKeyState();

	void  resetKeyState();
	/*
	 * 获取最终的原始变量个数
	 */
	UINT16  getTotalNumber();


	UINT16*  getKeyPosArray();
	UINT16*  getValuePosArray();
	void  setLastStr();
private:
	UINT16  beginPos;
	UINT16  endPos;
	UINT16  commaPos;
	bool    bCompleteStr;

	bool    keyState;

	ValueType  vType;
	UINT16  keyNamePosArray[2*MaxKey];
	UINT16  valuePosArray[2*MaxKey];

	UINT8   eventType[2*MaxKey];

	UINT16  arrayPos;  // 值也是最终的具体json变量个数
};