
#pragma once
#include "global.h"
#define  MaxRecursive     128
#define  MaxDelimitNum    1024
class Stack
{
public:
	Stack(char  delimit, char oppositeDelimit);
	~Stack();

	void process(char curChar, UINT16 pos);
	/*
	 * 统计有多少个delimit出现
	 */
	void  count();
	/*
	 * 获取总共有多少个delimit出现过
	 */
	UINT16  getTotal();
	/*
	 * 递增delimit嵌套深度
	 */
	void  push();
	/*
	 * 递减delimit嵌套深度
	 */
	void  pop();

	UINT8  getRecursive();

	UINT16*  getDelimitPosArray();
	UINT16*  getOppositeDelimitArray();
private:
	char    delimitChar;
	char    oppositeDelimitChar;
	UINT16  totalSize;
	UINT8   recursive;

	UINT16  delimitArrayPos;
	UINT16  oppsiteDelimitArrayPos;

	UINT16  delimitPos[MaxDelimitNum];
	UINT16  oppositeDelimitPos[MaxDelimitNum];
};