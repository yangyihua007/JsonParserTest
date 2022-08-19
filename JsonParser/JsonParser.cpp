#include <string.h>
#include "StringParser.h"
#include "stack.h"
#include <stdlib.h>
#include "JsonException.h"
#include "JsonParser.h"
#include <iostream>
using namespace std;

JsonParser::JsonParser(char* jsonStr)
{
	events = NULL;
	locations = NULL;
	orginalJsonStr = jsonStr;
	curPos = 0;
	UINT16  size = strlen(jsonStr);
	Stack*   stack1 = new Stack('{', '}');
	Stack*   stack2 = new Stack('[', ']');
	StringParser*  stringParser = new StringParser();
	for(UINT16 i = 0; i < size; i++) {
		stack1->process(*(jsonStr+i), i);
		stack2->process(*(jsonStr+i), i);
		stringParser->process(*(jsonStr+i), i);
	}
	stringParser->setLastStr();
	if(stack1->getRecursive() != 0) {
		// 抛异常 { 不配对
		std::cout << "异常，”{“不配对" << std::endl;
		throw JsonException();
	}
	if(stack2->getRecursive() != 0) {
		// 抛异常 [ 不配对
        std::cout << "异常，”[“不配对" << std::endl;
		throw JsonException();
	}
	nSize = stringParser->getTotalNumber() + stack1->getTotal()*2 + stack2->getTotal()*2;
	events = (UINT8*)malloc(nSize);
	locations = (JsonLocation*)malloc(nSize * sizeof(JsonLocation));
	UINT16  nSize1 = stack1->getTotal();
	UINT16  nSize2 = stack2->getTotal();
	UINT16  nKeyValue = stringParser->getTotalNumber();

    UINT16  curPos = 0;
	UINT16* delimitPosArray1 = stack1->getDelimitPosArray();
	UINT16* oppositeDelimitPosArray1 = stack1->getOppositeDelimitArray();

	UINT16* delimitPosArray2 = stack2->getDelimitPosArray();
	UINT16* oppositeDelimitPosArray2 = stack2->getOppositeDelimitArray();

	UINT16*  keyPosArray = stringParser->getKeyPosArray();
	UINT16*  valuePosArray = stringParser->getValuePosArray();

	UINT16 i = 0;
	UINT16 i1 = 0;
	UINT16 j=0;
	UINT16 j1 = 0;
	UINT16 k = 0;
	UINT16 k1 = 0;
	
	UINT16 curValue = 0;
	for(UINT16 m = 0; m < nSize; m++) {
		compare2Set(i, delimitPosArray1,i1, oppositeDelimitPosArray1, j, delimitPosArray2, j1, oppositeDelimitPosArray2, k, keyPosArray, k1, valuePosArray, events, locations, m);
	}
	delete stack1;
	delete stack2;
	delete stringParser;
}





JsonParser::~JsonParser()
{
}

/*
 * pos1~pos6 中存储的数字都是从小到大递增，从中取出当前最小的
 */
UINT16 JsonParser::compare2Set(UINT16& i1, UINT16* pos1, UINT16& i2, UINT16* pos2, UINT16& i3, UINT16* pos3, UINT16& i4, UINT16* pos4, UINT16& i5, UINT16* pos5, UINT16& i6, UINT16* pos6, UINT8* events, JsonLocation* locations, UINT16 nPos) {
	Event evtType = END;
	
	UINT16*  posChoose = pos1;
	UINT16 min = *(pos1+i1);
	UINT16 index = 1;
	evtType = START_OBJECT;
	if(min > *(pos2+i2)) {
		index = 2;
		min = *(pos2+i2);
		evtType = END_OBJECT;
		posChoose = pos2;
	}
	if(min > *(pos3+i3)) {
		index = 3;
		min = *(pos3+i3);
		evtType = START_ARRAY;
		posChoose = pos3;
	}
	if(min > *(pos4+i4)) {
		index = 4;
		min = *(pos4+i4);
		evtType = END_ARRAY;
		posChoose = pos4;
	}
	if(min > *(pos5+i5)) {
		index = 5;
		min = *(pos5+i5);
		evtType = KEY_NAME;
		posChoose = pos5;
	}
	if(min > *(pos6+i6)) {
		index = 6;
		min = *(pos6+i6);
		evtType = VALUE_STRING;
		posChoose = pos6;
	}

	*(events+nPos) = evtType;
	
	UINT16  posNum = 0;
	if(evtType == START_OBJECT || evtType == END_OBJECT || evtType == START_ARRAY || evtType == END_ARRAY) {
		
		if(index == 1) {
			posNum = *(posChoose+i1);
		    (locations+nPos)->start_ = *(posChoose+i1);
		    (locations+nPos)->end_ = *(posChoose+i1);
			i1++;
		}
	    if(index == 2) {
			posNum = *(posChoose+i2);
		    (locations+nPos)->start_ = *(posChoose+i2);
		    (locations+nPos)->end_ = *(posChoose+i2);
			i2++;
		}
		if(index == 3) {
			posNum = *(posChoose+i3);
		    (locations+nPos)->start_ = *(posChoose+i3);
		    (locations+nPos)->end_ = *(posChoose+i3);
			i3++;
		}
		if(index == 4) {
			posNum = *(posChoose+i4);
		    (locations+nPos)->start_ = *(posChoose+i4);
		    (locations+nPos)->end_ = *(posChoose+i4);
			i4++;
		}
	} else {
		
		if(index == 5) {
			posNum = *(posChoose+i5);
		    posNum = *(posChoose+i5+1);
		    (locations+nPos)->start_ = *(posChoose+i5);
		    (locations+nPos)->end_ = *(posChoose+i5+1);

            i5 += 2;
		}
		if(index == 6) {
			posNum = *(posChoose+i6);
		    posNum = *(posChoose+i6+1);
		    (locations+nPos)->start_ = *(posChoose+i6);
		    (locations+nPos)->end_ = *(posChoose+i6+1);
            i6 += 2;
		}
		
	}
	return min;
}

void JsonParser::close()
{
    if(events != NULL) {
        free(events);
	}
    if(locations != NULL) {
        free(locations);
	}
}

Event JsonParser::next()
{
	Event  evet = (Event)(*(events+curPos));
	curPos++;
	return evet;
}

bool  JsonParser::hasNext()
{
	return nSize >= (curPos+1);
}

bool   JsonParser::isIntegerNumber()
{
	return true;
}
char*  JsonParser::getString()
{
	Event  evet = END;
	char*  result;
	if(curPos >= 1) {
	   evet = (Event)(*(events+curPos-1));
	   if(!((evet == VALUE_STRING) || (evet == VALUE_NUMBER) || (evet == VALUE_TRUE) ||(evet == VALUE_FALSE) || (evet == KEY_NAME))) {
		   // 抛异常，非String类型
		   std::cout << "非String类型，不能获取字符串" << std::endl;
	   } else {
		  JsonLocation*  pLocation = (locations+curPos-1);
		  UINT16  nLength = pLocation->end_ - pLocation->start_+1;
		  result = (char*)malloc(nLength+1);
		  memset(result,0, nLength+1);
		  strncpy(result,(orginalJsonStr+pLocation->start_), nLength);
	   }
	}
	return result;
}

INT32  JsonParser::getInt()
{
	return 0;
}


INT64  JsonParser::getLong()
{
	return 0L;
}

float  JsonParser::getDecimal()
{
	return 0.0;
}