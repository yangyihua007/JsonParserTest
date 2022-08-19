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
 * �����ж��ַ�������ĸ�ʽ�淶����Ҫ�ж�key-value�Ƿ����
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
	 * ��ʱֻ�жϡ��ַ������У��ַ���������������
	 */
	if(beginPos != 0) {
		if(curChar == ',' && !bCompleteStr) {
			// ���쳣�� KEY_NAME, VALUE ��ʽ�쳣
			std::cout << "��ʽ����ȷ���ַ����а���" << curChar << "�Ƿ��ַ�" << std::endl;
			throw JsonException();
		}
		// �����ڴ��ж�����KEY_NAME, VALUE�в��ܰ����������ַ�
	}

	if(curChar == ':') {
		setKeyState();
		if(beginPos == 0 && endPos == 0) {
			// ���쳣�� key_name û�С���
			std::cout << "Key_nameû����\"\"������" << std::endl;
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
			// ���쳣�����ֻ��MaxKey���� ��������MaxKey�����
		}
		if(beginPos ==0 && endPos == 0) { // value�����ַ�������ʽ
			beginPos = commaPos + 1;
			endPos = pos - 1;
			eventType[arrayPos] = V_NUMBER; // ���廹��Ҫ�ж�һ�£�����ֵ������VALUE_TRUE, VALUE_FALSE, VALUE_NULL
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
 *  ��Ϊǰ����߼��������ַ�����ʼ����λ�ã������ɡ����������������� ���һ���ַ���û�а취�������
 */
void  StringParser::setLastStr()
{
	if(arrayPos == 2* MaxKey) {
			// ���쳣�����ֻ��MaxKey���� ��������MaxKey�����
	}
	if(beginPos ==0 && endPos == 0) { // value�����ַ�������ʽ
		beginPos = commaPos + 1;
		endPos =  - 1;  // ������������ʽ�ģ�����
		eventType[arrayPos] = V_NUMBER; // ���廹��Ҫ�ж�һ�£�����ֵ������VALUE_TRUE, VALUE_FALSE, VALUE_NULL
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
		// ���쳣, ���ֶ��":::"������
	} else {
	    keyState = true;
		vType = KEYNAME;
	}
	
}

void  StringParser::resetKeyState()
{
	if(keyState == false) {
		// ���쳣�� �����˶������������������, ������û�С�������ֱ��һ���ַ�����Ȼ����Ƕ��ŵ�����
		std::cout << "��ʽ�쳣����������������Ż���key��value֮��û�У�" << std::endl;
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
