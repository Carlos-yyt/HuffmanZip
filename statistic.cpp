//统计字符

#include "statistic.h"

//加入一个word。（frequency+1）


void initializeWORD(pWORD & words)
{
	for (char i = 0; i < 127; i++)
	{
		words[i].frequency = 0;
		words[i].word = (char*)malloc(sizeof(char)*16);
		//strcpy(words[i].word, &(char)i);//ASCII不显示字符还要再区分一下
		words[i].word[0] = (char)i;//ASCII不显示字符还要再区分一下
		words[i].word[1] = '\0';
		words[i].huffmanCode = NULL;
	}
	for (int i = 0; i < 127; i++)
	{
		switch (i)
		{
		case 0:strcpy(words[i].word, "空字符"); break;
		case 1:strcpy(words[i].word, "标题开始"); break;
		case 2:strcpy(words[i].word, "文本开始"); break;
		case 3:strcpy(words[i].word, "文本结束"); break;
		case 4:strcpy(words[i].word, "传输结束"); break;
		case 5:strcpy(words[i].word, "请求"); break;
		case 6:strcpy(words[i].word, "确认回应"); break;
		case 7:strcpy(words[i].word, "响铃"); break;
		case 8:strcpy(words[i].word, "退格"); break;
		case 9:strcpy(words[i].word, "水平定位符号"); break;
		case 10:strcpy(words[i].word, "换行键"); break;
		case 11:strcpy(words[i].word, "垂直定位符号"); break;
		case 12:strcpy(words[i].word, "换页键"); break;
		case 13:strcpy(words[i].word, "归为键"); break;
		case 14:strcpy(words[i].word, "取消变换"); break;
		case 15:strcpy(words[i].word, "启用变换"); break;
		case 16:strcpy(words[i].word, "跳出通讯数据"); break;
		case 17:strcpy(words[i].word, "设备控制一"); break;
		case 18:strcpy(words[i].word, "设备控制二"); break;
		case 19:strcpy(words[i].word, "设备控制三"); break;
		case 20:strcpy(words[i].word, "设备控制四"); break;
		case 32:strcpy(words[i].word, "空格"); break;
		default:
			break;
		}
	}
	
}

//fileName是文件名，pWORD是放字符的数组，add_data函数不带排序功能，返回字符种类的总数(int)
int add_data(pWORD & words, int& sumArtical, char* FILENAME)
{
	words=(pWORD)malloc(127 * sizeof(WORD));
	initializeWORD(words);
	char *article;//存文章
	article = (char*)malloc(sizeof(char)*10000);

	sumArtical=0;//总字数
	int typeSum = 0;//总类型个数（重复算一个）

	char word;//当前读入的word
	FILE *file;
	file = fopen(FILENAME, "r");
	//fseek(file, sizeof(char) * 3, SEEK_SET);//不知道为什么开头有三个char的东西，先跳过去吧。
	fseek(file, sizeof(char) * 3, SEEK_SET);//不知道为什么开头有三个char的东西，先跳过去吧。
	while (!feof(file))
	{
		fread(&article[sumArtical], 1, sizeof(char), file);
		words[article[sumArtical]].frequency++;//ASCII码和数组下标一一对应。
		if (words[article[sumArtical]].frequency==1)
		{
			typeSum++;
		}
		sumArtical++;//产生了巨大的数字 BUG
	}

	//错误，不应该在Huffman编码前做这件事情。
	//把frequency从次数变成频率
	//for (int i = 0; i < 127; i++)
	//{
	//	if (words[i].frequency!=0)
	//	{
	//		words[i].frequency = words[i].frequency / pArticle;
	//	}
	//}
	free(article);
	return typeSum;
}

//给录入好的数据排个序列
int sort_data(pWORD & words)
{
	return 0;
}
