#pragma once
#include "define.h"
#include"statistic.h"
typedef struct {
	int weight;
	int lchild, rchild, parent;
	unsigned char ch;//在解码的时候使用
}HTNode, *huffmanTree;

typedef char **HuffmanCode;

//哈夫曼算法的一部分
void select2(huffmanTree &HT, int max, int &s);

//Huffman算法的一部分
void select(huffmanTree &HT, int max, int &s);

//创建哈夫曼树+哈夫曼编码
void HuffmanTree_Build_and_Code(huffmanTree &HT, HuffmanCode &HC, int *w, int n);

//输出哈夫曼编码
void huffmanPrint(HuffmanCode code, int len);

//输出哈夫曼编码	带字符
void huffmanPrint(pWORD words, int sumWord);

//
void Huffman_Test(pWORD words, int sumWords, HuffmanCode &code);

//sumWord是种类，返回生成文件的字符总数
int outPutHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME);

void decodeHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME);

void HuffmanTree_Build(huffmanTree &HT, unsigned char* w, int n);

//解压时候创建的Huffman树
void buildEncodeHuffmanTree(huffmanTree &tree, unsigned int sumWords, unsigned int node_num);

//改名字 从TXT到HUF
void changeFileNameToHuf(char * txt, char * huf);

//改名字 从HUF到TXT
void changeFileNameToTxt(char * huf, char *txt);

//改名字 从旧TXT到压缩后生成的TXT
void chanFileNameToTxt_new(char *oldTxt, char *newTxt);
