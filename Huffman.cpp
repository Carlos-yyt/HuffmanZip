// Huffman.cpp: 定义控制台应用程序的入口点。
//

#include "Huffman.h"
#include "statistic.h"

void select(huffmanTree &HT, int max, int &s) {
	//附上：int weight[] = { 1,3,5,7,9,11,13,15 };
	//printf("\n\n");
	int min = INT_MAX;
	int flag = 0;
	for (int i = 1; i <= max; i++)
	{
		if (HT[i].weight < min && HT[i].parent == 0)
		{
			min = HT[i].weight;
			flag = i;
		}
	}
	s = flag;
	if (min == INT_MAX)
	{
		printf("\n\nERROR!MAX=%d,min=%d\n\n", max, min);
		system("pause");
	}
	/*printf("No\tweight\tparent\n");
	for (int i = 1; i <= max; i++)
	{
		printf("%d:\t%d\t%d\n", i, HT[i].weight, HT[i].parent);
	}
	printf("======MAX=%d,min=%d=====\n", max, min);*/
	HT[flag].parent = 1;
}

//给使用了0号位的Tree使用
void select2(huffmanTree &HT, int max, int &s) {
	//附上：int weight[] = { 1,3,5,7,9,11,13,15 };
	//printf("\n\n");
	int min = INT_MAX;
	int flag = 0;
	for (int i = 0; i < max; i++)
	{
		if (HT[i].weight < min && HT[i].parent == 0)
		{
			min = HT[i].weight;
			flag = i;
		}
	}
	s = flag;
	if (min == INT_MAX)
	{
		printf("\n\nERROR!MAX=%d,min=%d\n\n", max, min);
		system("pause");
	}
	/*printf("No\tweight\tparent\n");
	for (int i = 1; i <= max; i++)
	{
	printf("%d:\t%d\t%d\n", i, HT[i].weight, HT[i].parent);
	}
	printf("======MAX=%d,min=%d=====\n", max, min);*/
	HT[flag].parent = 1;
}

//创建Huffman树并编码，用于压缩文件之前
void HuffmanTree_Build_and_Code(huffmanTree &HT, HuffmanCode &HC, int *w, int n) {
	//w存放权值，HT是哈夫曼树，求出n个字符的哈夫曼编码。
	//for (int j = 0; j < n; j++)
	//{
	//	printf("%d\n", w[j]);
	//}

	if (n <= 1)
	{
		return;
	}
	int m = 2 * n - 1;
	HT = (huffmanTree)malloc((m + 1) * sizeof(HTNode));//零号节点没有使用
	int i = 1;
	huffmanTree p = HT + 1;
	for (; i <= n; i++, p++, w++) {
		*p = { *w,0,0,0 };
	}
	for (; i <= m; i++, p++)
	{
		*p = { 0,0,0,0 };
	}


	//建立Huffman树
	int min1 = 0, min2 = 0;
	for (int i = n + 1; i <= m; i++)
	{
		select(HT, i - 1, min1);
		select(HT, i - 1, min2);
		HT[min1].parent = i;
		//printf("\nmin1:HT[%d].parent = %d;\n", min1, HT[min1].parent);
		HT[min2].parent = i;
		//printf("min2:HT[%d].parent = %d;\n\n\n", min2, HT[min2].parent);
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}

	//编码
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char *cd = (char*)malloc(n * sizeof(char));//可能的最长路径是n-1。
	cd[n - 1] = '\0';//最后一位,放终止符
	int start = 0;
	int child = 0;
	int father = 0;
	for (int i = 1; i <= n; i++)
	{
		//printf("\n");//for debug
		start = n - 1;//这个是“\0”位。
		child = i;
		father = HT[child].parent;
		for (; father != 0; child = father, father = HT[father].parent) {
			if (HT[father].lchild == child)//BUG!!!!!!!-done
			{
				cd[--start] = '0';
				//printf("0");//for debug
			}
			else
			{
				cd[--start] = '1';
				//printf("1");//for debug
			}
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start));
		strcpy_s(HC[i], n - start, &cd[start]);
		//strcpy_s 
	}
	//printf("\n录入结束！\n");
	free(cd);
}

//输出Huffman编码
void huffmanPrint(HuffmanCode code, int len) {
	printf("\n\n检查HuffmanCode是否生成：\n");
	for (int i = 1; i <= len; i++)
	{
		printf("%s\n", code[i]);
	}
}

//输出所有出现的字符的频率、Huffman码
void huffmanPrint(pWORD words, int sumWord)
{
	int char_type = 0;
	printf("\n\nData of %d characters:\n\nchar\tfrequency\tHuffmanCode\n\n", sumWord);
	for (int i = 0; i < 127; i++)
	{
		if (words[i].frequency > 0)
		{
			printf("%s\t%f\t%s\n", words[i].word, words[i].frequency / (double)sumWord, words[i].huffmanCode);
			char_type++;
		}
	}
	printf("\nThere are %d kinds of char in this artical.\n", char_type);
}

//测试
void Huffman_Test(pWORD words, int sumWords, HuffmanCode &code) {
	huffmanTree tree;
	int weight[127];
	int int_weight = 0;

	//权重
	for (int i = 0; i < 127; i++)
	{
		if (words[i].frequency > 0)
		{
			weight[int_weight++] = words[i].frequency;
		}
	}
	HuffmanTree_Build_and_Code(tree, code, weight, sumWords);
	//huffmanPrint(code, sumWords);

	int codeCount = 1;
	for (int i = 0; i < 127; i++)
	{
		if (words[i].frequency > 0)
		{

			words[i].huffmanCode = (char*)malloc(sizeof(char) * 20);
			//words[i].huffmanCode = NULL;
			strcpy(words[i].huffmanCode, code[codeCount++]);
			//printf("%s\n", words[i].huffmanCode);
		}
	}
	//huffmanTreePrint(code, sumWords);
}

//输出二进制的Huffman暗文
int outPutHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME) {
	unsigned int char_kinds = sumWord;		// 字符种类
	unsigned long artical_sum = 0;				//文章总字数
	int artical_sum_huf = 0;		//新生成的文件的字符数量

	char *putch;									// 暂存匹配来的的01串，超过8位就输出一波至少于8位
	putch = (char*)malloc(sizeof(char) * 100);		//编码应该不会超过100位
	putch[0] = '\0';

	char getch;
	unsigned char char_temp;						//暂存8bit的二进制内容。满了就输出到文件里面。
	char *article;									//存文章
	article = (char*)malloc(sizeof(char) * 5000);
	unsigned char code_last;						//解决 “8bit循环”之后剩下的01串

	//原文
	FILE *inFile;
	inFile = fopen(IN_FILENAME, "r");

	fseek(inFile, 3 * sizeof(char), SEEK_SET);		//不知道为什么开头有三个char的东西，先跳过去吧。——不知道为什么不跳过去也可以了。

	//输出
	FILE *outFile;
	outFile = fopen(OUT_FILENAME, "wb");

	//fread((char*)&temp_8bits, sizeof(unsigned char), 1, put);
	//fread(&article[sumArtical], 1, sizeof(char), file);

	//写头部，包括字符和对应的权重、总字符种类数量、文章总长度
	char *ch_translate;
	ch_translate = (char*)malloc(sizeof(char));//因为不可显示字符以及部分标点符号的words[i].ch存的不是ASCII码，而是名称，所以不可以直接使用，要利用下标和ASCII码的对应关系来输出

	fwrite((char *)&char_kinds, sizeof(unsigned int), 1, outFile);		// 写入字符种类
	for (int i = 0; i < 127; i++)
	{
		if (words[i].frequency > 0)
		{
			artical_sum += words[i].frequency;
			*ch_translate = (char)i;
			fwrite((char*)ch_translate, sizeof(unsigned char), 1, outFile);			//输出字符
			fwrite((char*)&words[i].frequency, sizeof(unsigned long), 1, outFile);	//输出对应的频率
		}
	}
	fwrite((char*)&artical_sum, sizeof(unsigned long), 1, outFile);//写入文章总字符数


	//一个char一个char地读入原文
	fread((char*)&getch, sizeof(char), 1, inFile);
	//写入文件
	while (!feof(inFile))
	{
		strcat(putch, words[getch].huffmanCode);	//向putch导入匹配的01串
		while (strlen(putch) >= 8)
		{
			char_temp = '\0';
			for (int i = 0; i < 8; i++)
			{
				char_temp <<= 1;					//左移一位，如果不进入下面的putch[i]=='1'，则就是零
				if (putch[i] == '1')
				{
					char_temp |= 1;					//通过 或 操作将最低位补成1
				}
			}
			fwrite((char*)&char_temp, sizeof(unsigned char), 1, outFile);//把八个bit存入文件
			artical_sum_huf++;
			strcpy(putch, putch + 8);		//删去已经写入文件的前八位bit
		}
		fread((char*)&getch, sizeof(char), 1, inFile);		//再读一个char
	}

	//处理“8bit”循环剩下的01串
	code_last = strlen(putch);
	if (code_last > 0)
	{
		char_temp = '\0';
		for (int i = 0; i < code_last; i++)
		{
			char_temp <<= 1;
			if (putch[i] == '1')
			{
				char_temp |= 1;
			}
		}
		char_temp <<= 8 - code_last;
		fwrite((char*)&char_temp, sizeof(unsigned char), 1, outFile);
	}

	//释放
	fclose(inFile);
	fclose(outFile);


	return artical_sum_huf;//返回生成文件的字节数
}

//解码
void decodeHufArtical(HuffmanCode code, int sumWord, pWORD words, char* IN_FILENAME, char* OUT_FILENAME)
{
	FILE *infile, *outfile;
	infile = fopen(IN_FILENAME, "rb");
	outfile = fopen(OUT_FILENAME, "wb");

	unsigned long writen_len = 0;		// 控制文件写入长度，达到则立即停止

	unsigned char *weight;//放权重
	weight = (unsigned char*)malloc(sizeof(unsigned char)*sumWord);

	char *getch;
	getch = (char*)malloc(sizeof(char) * 30);

	huffmanTree huf_tree;
	unsigned int node_num;					//huffman树结点个数
	unsigned int char_kinds=sumWord;		// 存储字符种类
	unsigned long artical_len;				//文章总字符数
	unsigned int root;						//根结点索引，匹配编码用
	unsigned char temp_char;				//暂时储存从文件导进来的8个bit
	char *check_char;//用来存放供比对的01串
	check_char = (char*)malloc(sizeof(char) * 30);

	fread((char*)&char_kinds, sizeof(unsigned int), 1, infile);//读取字符种类数量
	node_num = 2 * char_kinds - 1;
	huf_tree = (HTNode *)malloc(node_num * sizeof(HTNode));		// 动态分配哈夫曼树结点空间

	for (int i = 0; i < char_kinds; i++)
	{
		fread((char*)&huf_tree[i].ch, sizeof(unsigned char), 1, infile);		//获得字符
		fread((char*)&huf_tree[i].weight, sizeof(unsigned long), 1, infile);	//获得字符对应的权重
		huf_tree[i].parent = 0;
	}
	for (int i = 0; i < node_num; i++)
	{
		huf_tree[i].parent = 0;
	}
	//HuffmanTree_Build(huf_tree, weight, sumWord);//构造Huffman树
	
	buildEncodeHuffmanTree(huf_tree, char_kinds, node_num);//重建Huffman树

	fread((char*)&artical_len, sizeof(unsigned long), 1, infile);//文件长度
	root = node_num - 1;

	//输出循环
	while (1)
	{
		fread((char*)&temp_char, sizeof(unsigned char), 1, infile);
		for (int i = 0; i < 8; i++)
		{
			if (temp_char & 128)
			{
				root = huf_tree[root].rchild;
			}
			else
			{
				root = huf_tree[root].lchild;
			}
			if (root<char_kinds)
			{
				fwrite((char*)&huf_tree[root].ch, sizeof(unsigned char), 1, outfile);
				++writen_len;
				if (writen_len==artical_len)
				{
					break;
				}
				root = node_num - 1;
			}
			temp_char <<= 1;
		}
		if (writen_len == artical_len)
		{
			break;
		}
	}


	fclose(infile);
	fclose(outfile);
	free(huf_tree);

}

//构造Huffman树
void HuffmanTree_Build(huffmanTree & HT, unsigned char* w, int n)
{
	if (n <= 1)
	{
		return;
	}
	int m = 2 * n - 1;
	HT = (huffmanTree)malloc((m + 1) * sizeof(HTNode));//零号节点没有使用
	int i = 1;
	huffmanTree p = HT + 1;
	for (; i <= n; i++, p++, w++) {
		*p = { *w,0,0,0 };
	}
	for (; i <= m; i++, p++)
	{
		*p = { 0,0,0,0 };
	}


	//建立Huffman树
	int min1 = 0, min2 = 0;
	for (int i = n + 1; i <= m; i++)
	{
		select(HT, i - 1, min1);
		select(HT, i - 1, min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].weight = HT[min1].weight + HT[min2].weight;
	}
}

//解码时候创建的Huffman树
void buildEncodeHuffmanTree(huffmanTree &tree, unsigned int sumWords, unsigned int node_num)
{
	unsigned int i;
	int min1;
	int min2;
	for (int i = sumWords; i < node_num; i++)
	{
		select2(tree, i, min1);
		select2(tree, i, min2);
		tree[min1].parent = i;
		tree[min2].parent = i;
		tree[i].lchild = min1;
		tree[i].rchild = min2;
		tree[i].weight = tree[min1].weight + tree[min2].weight;
	}
}

//改名字
void changeFileNameToHuf(char * filename)
{
	int i = 0;
	while (filename[i]!='.')
	{
		i++;
	}
	filename[++i] = 'H';
	filename[++i] = 'U';
	filename[++i] = 'F';
	filename[++i] = '\0';

}

//从HUF后缀转换到txt后缀
void changeFileNameToTxt(char * huf, char * txt)
{
	int i = 0;
	while (huf[i]!='.')
	{
		txt[i] = huf[i];
		i++;
	}
	txt[i++] = '_';
	txt[i++] = 'h';
	txt[i++] = 'u';
	txt[i++] = 'f';
	txt[i++] = '.';
	txt[i++] = 't';
	txt[i++] = 'x';
	txt[i++] = 't';
	txt[i++] = '\0';
}
