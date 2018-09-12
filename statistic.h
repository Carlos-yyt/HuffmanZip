#pragma once
#include "define.h"

typedef struct WORD
{
	char* word;//这个字符叫什么，可显字符很简单，不可显的就存它的名字。
	int frequency;//出现的次数
	char *huffmanCode;//它的Huffman编码
}*pWORD;

//初始化WORD数组。
void initializeWORD(pWORD &words);

//pWORD是放字符的数组，add_data函数不带排序功能，返回字符种类的总数(int)
int add_data(pWORD &words, int& sumArtical);

//给录入好的数据排个序列
int sort_data(pWORD &words);