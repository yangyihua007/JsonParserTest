
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
	 * ͳ���ж��ٸ�delimit����
	 */
	void  count();
	/*
	 * ��ȡ�ܹ��ж��ٸ�delimit���ֹ�
	 */
	UINT16  getTotal();
	/*
	 * ����delimitǶ�����
	 */
	void  push();
	/*
	 * �ݼ�delimitǶ�����
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