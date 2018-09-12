#include "Huffman.h"
#include "statistic.h"

int main()
{
	pWORD words;//对应ASCII码对0~126位
	int sumWords = 0;//文章总字符种类
	int sumArtical = 0;//文章总字节数量
	int sumArtical_huf = 0;//压缩后的 文章总字节数量
	HuffmanCode code;

	sumWords=add_data(words, sumArtical);
	Huffman_Test(words, sumWords, code);

	////huffmanCode是否生成成功：
	//huffmanPrint(code, sumWords);

	//输出到屏幕
	huffmanPrint(words, sumArtical);
	
	sumArtical_huf=outPutHufArtical(code, sumWords, words);


	printf("\n压缩率为：%f %%\n", (sumArtical_huf / (double)sumArtical) * 100);

	printf("\n===============\nHUF文件已经 生成 了。\n您可以在 文件夹 里查看。\n按任何键将 解压 HUF文件 。\n===============\n");
	system("pause");

	decodeHufArtical(code, sumWords, words);
	printf("\n===============\nHUF文件已经被 解压 了。\n您可以在 文件夹 里查看。\n按任何键将 结束 程序 。\n===============\n");

	system("pause");
	return 0;
}

