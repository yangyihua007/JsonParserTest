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
			// 抛异常，JsonStr 包含超过最大数量个delimit, 可将MaxDelimitNum设置为更大的数值
			std::cout << "JsonStr超过最大" << MaxDelimitNum << std::endl;
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
 * 统计有多少个delimit出现
 */
void  Stack::count()
{
	totalSize++;
}
/*
 * 获取总共有多少个delimit出现过
 */
UINT16  Stack::getTotal()
{
	return totalSize;
}
/*
 * 递增delimit嵌套深度
 */
void  Stack::push()
{
	recursive++;
}
/*
 * 递减delimit嵌套深度
 */
void  Stack::pop()
{
	if(recursive <= 0) {
		// 抛异常， 没有配对出现
		std::cout << "字符" << oppositeDelimitChar << "没有配对出现" << std::endl;
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
