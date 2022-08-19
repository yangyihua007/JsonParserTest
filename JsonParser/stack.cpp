#include <iostream>
using namespace std;
#include "JsonException.h"
#include "stack.h"

Stack::Stack(char  delimit, char oppositeDelimit)
	:delimitChar(delimit), oppositeDelimitChar(oppositeDelimit),recursive(0),totalSize(0),
	delimitArrayPos(0), oppsiteDelimitArrayPos(0)
{
}
Stack::~Stack()
{
}

void Stack::process(char curChar, UINT16 pos)
{
	if(curChar == delimitChar) {
		if(delimitArrayPos == MaxDelimitNum) {
			// ���쳣��JsonStr �����������������delimit, �ɽ�MaxDelimitNum����Ϊ�������ֵ
			std::cout << "JsonStr�������" << MaxDelimitNum << std::endl;
			throw  JsonException();
		}

		count();
		push();
		delimitPos[delimitArrayPos] = pos;
		delimitArrayPos++;
	}
	if(curChar == oppositeDelimitChar) {


		pop();
		oppositeDelimitPos[oppsiteDelimitArrayPos] = pos;
		oppsiteDelimitArrayPos++;
	}
}
/*
 * ͳ���ж��ٸ�delimit����
 */
void  Stack::count()
{
	totalSize++;
}
/*
 * ��ȡ�ܹ��ж��ٸ�delimit���ֹ�
 */
UINT16  Stack::getTotal()
{
	return totalSize;
}
/*
 * ����delimitǶ�����
 */
void  Stack::push()
{
	recursive++;
}
/*
 * �ݼ�delimitǶ�����
 */
void  Stack::pop()
{
	if(recursive <= 0) {
		// ���쳣�� û����Գ���
		std::cout << "�ַ�" << oppositeDelimitChar << "û����Գ���" << std::endl;
		throw  JsonException();
	} else {
		recursive--;
	}
}

UINT16*  Stack::getDelimitPosArray()
{
	return delimitPos;
}
	
UINT16*  Stack::getOppositeDelimitArray()
{
	return oppositeDelimitPos;
}

UINT8  Stack::getRecursive()
{
	return recursive;
}
