#pragma once
#include "define.h"
#include"statistic.h"
typedef struct {
	int weight;
	int lchild, rchild, parent;
	unsigned char ch;//在解码的时候使用
}HTNode, *huffmanTree;

typedef char **HuffmanCode;

void select2(huffmanTree &HT, int max, int &s);

void select(huffmanTree &HT, int max, int &s);

void HuffmanTree_Build_and_Code(huffmanTree &HT, HuffmanCode &HC, int *w, int n);

void huffmanPrint(HuffmanCode code, int len);

void huffmanPrint(pWORD words, int sumWord);

void Huffman_Test(pWORD words, int sumWords, HuffmanCode &code);

//sumWord是种类，返回生成文件的字符总数
int outPutHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME);

void decodeHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME);

void HuffmanTree_Build(huffmanTree &HT, unsigned char* w, int n);

//解压时候创建的Huffman树
void buildEncodeHuffmanTree(huffmanTree &tree, unsigned int sumWords, unsigned int node_num);

//改名字
void changeFileNameToHuf(char *filename);


void changeFileNameToTxt(char * huf, char *txt);