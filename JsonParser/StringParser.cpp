#include <iostream>
using namespace std;
#include "JsonException.h"
#include "StringParser.h"


StringParser::StringParser()
	:beginPos(0),endPos(0),bCompleteStr(false),vType(V_END),arrayPos(0),keyState(false),commaPos(0)
{
}
StringParser::~StringParser()
{
}
/*
 * 除了判断字符串本身的格式规范，还要判断key-value是否配对
 */
void  StringParser::process(char curChar, UINT16  pos)
{
	if(curChar == '\"') {
		if(beginPos != 0) {
		   endPos = pos-1;
		   bCompleteStr = true;
		} else {
			beginPos = pos+1;

		}
	}
	/*
	 * 暂时只判断“字符串”中，字符串不包括‘，’
	 */
	if(beginPos != 0) {
		if(curChar == ',' && !bCompleteStr) {
			// 抛异常， KEY_NAME, VALUE 格式异常
			std::cout << "格式不正确，字符串中包含" << curChar << "非法字符" << std::endl;
			throw JsonException();
		}
		// 还可在此判断其他KEY_NAME, VALUE中不能包含的特殊字符
	}

	if(curChar == ':') {
		setKeyState();
		if(beginPos == 0 && endPos == 0) {
			// 抛异常， key_name 没有“”
			std::cout << "Key_name没有用\"\"引起来" << std::endl;
			throw JsonException();
		}
		keyNamePosArray[arrayPos] = beginPos;
		keyNamePosArray[arrayPos+1]=endPos;
		eventType[arrayPos] = KEYNAME;
		commaPos = pos;
		
		clear();
	}
	// 
	if(curChar == ',') {
		resetKeyState();
		if(arrayPos == 2* MaxKey) {
			// 抛异常，最多只能MaxKey个， 可以增加MaxKey来解决
		}
		if(beginPos ==0 && endPos == 0) { // value不是字符串的形式
			beginPos = commaPos + 1;
			endPos = pos - 1;
			eventType[arrayPos] = V_NUMBER; // 具体还是要判断一下，是数值，还是VALUE_TRUE, VALUE_FALSE, VALUE_NULL
		} else {
			eventType[arrayPos] = V_STRING;
		}
		valuePosArray[arrayPos] = beginPos;
		valuePosArray[arrayPos+1]=endPos;
		arrayPos += 2;
		clear();
	}
}
/*
 *  因为前面的逻辑，设置字符串起始结束位置，都是由”，“”：“触发， 最后一个字符串没有办法出发填充
 */
void  StringParser::setLastStr()
{
	if(arrayPos == 2* MaxKey) {
			// 抛异常，最多只能MaxKey个， 可以增加MaxKey来解决
	}
	if(beginPos ==0 && endPos == 0) { // value不是字符串的形式
		beginPos = commaPos + 1;
		endPos =  - 1;  // 最后的是数字形式的，再想
		eventType[arrayPos] = V_NUMBER; // 具体还是要判断一下，是数值，还是VALUE_TRUE, VALUE_FALSE, VALUE_NULL
	} else {
		eventType[arrayPos] = V_STRING;
	}

	valuePosArray[arrayPos] = beginPos;
	valuePosArray[arrayPos+1]=endPos;
	arrayPos += 2;
}

void  StringParser::clear()
{
	beginPos = 0;
	endPos = 0;
	bCompleteStr = false;
	vType = V_END;
}

void  StringParser::setKeyState()
{
	if(keyState){
		// 抛异常, 出现多个":::"的情形
	} else {
	    keyState = true;
		vType = KEYNAME;
	}
	
}

void  StringParser::resetKeyState()
{
	if(keyState == false) {
		// 抛异常， 出现了多个“，，，”的情形, 或者是没有“：”，直接一个字符串，然后就是逗号的情形
		std::cout << "格式异常，包含多个连续逗号或者key和value之间没有：" << std::endl;
		throw JsonException();
	} else {
		keyState = false;

	}
}

UINT16  StringParser::getTotalNumber()
{
	return arrayPos;
}

UINT16*  StringParser::getKeyPosArray()
{
	return keyNamePosArray;
}
UINT16*  StringParser::getValuePosArray()
{
	return valuePosArray;
}
