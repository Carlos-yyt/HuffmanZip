//                                                          _ooOoo_
//                                                         o8888888o
//                                                         88" . "88
//                                                         (| -_- |)
//                                                          O\ = /O
//                                                      ____/`---'\____
//                                                    .   ' \\| |// `.
//                                                     / \\||| : |||// \
//                                                   / _||||| -:- |||||- \
//                                                     | | \\\ - /// | |
//                                                   | \_| ''\---/'' | |
//                                                    \ .-\__ `-` ___/-. /
//                                                 ___`. .' /--.--\ `. . __
//                                              ."" '< `.___\_<|>_/___.' >'"".
//                                             | | : `- \`.;`\ _ /`;.`/ - ` : | |
//                                               \ \ `-. \_ __\ /__ _/ .-` / /
//                                       ======`-.____`-.___\_____/___.-`____.-'======
//                                                          `=---='
//
//                                       .............................................
//                                              佛祖保佑             永无BUG
//                                      佛曰:
//                                              写字楼里写字间，写字间里程序员；
//                                              程序人员写程序，又拿程序换酒钱。
//                                              酒醒只在网上坐，酒醉还来网下眠；
//                                              酒醉酒醒日复日，网上网下年复年。
//                                              但愿老死电脑间，不愿鞠躬老板前；
//                                              奔驰宝马贵者趣，公交自行程序员。
//                                              别人笑我忒疯癫，我笑自己命太贱；
//                                              不见满街漂亮妹，哪个归得程序员？


#include "Huffman.h"
#include "statistic.h"

int main()
{
	pWORD words;//对应ASCII码对0~126位
	int sumWords = 0;//文章总字符种类
	int sumArtical = 0;//文章总字节数量
	int sumArtical_huf = 0;//压缩后的 文章总字节数量
	HuffmanCode code;

	int int_choice = 0;			//记录选择
	char char_choice[30];		//记录选择
	char char_aimFileName[30];	//存用户想要的文件名

	printf("如果要压缩文件：\n\t请将您要压缩的英文文本放在.txt文件里，并将它拷贝到与源文件同级的文件夹里。【扣1】\n\t或者，可以直接调用样本文件ori_data.txt。【扣2】\n");
			printf("如果要解压文件：\n\t【扣3】\n");
			scanf("%d", &int_choice);
	
	//使用界面
	while (1)
	{	
		

		if (int_choice == 1)//压缩	用户提供的文件
		{
			printf("\n请输入您想要压缩的文件的文件名及其后缀。\n参考格式：“hello.txt”\n");
			scanf("%s", char_choice);
			sumWords = add_data(words, sumArtical, char_choice);
			Huffman_Test(words, sumWords, code);;

			//输出到屏幕
			huffmanPrint(words, sumArtical);

			//改成HUF后缀
			changeFileNameToHuf(char_choice);

			sumArtical_huf = outPutHufArtical(code, sumWords, words, char_choice, char_choice);


			printf("\n压缩率为：%f %%\n", (sumArtical_huf / (double)sumArtical) * 100);

			printf("\n===============\n%s 已经 生成 了。\n您可以在 文件夹 里查看。\n\t如果要 解压 HUF文件，请扣1。\n\t如果要结束程序，请扣-1。\n===============\n\n",char_choice);
			scanf("%d", &int_choice);
			if (int_choice==1)
			{
				decodeHufArtical(code, sumWords, words, AIM_FILE_NAME_HUFFMAN, AIM_FILE_NAME);
				printf("\n===============\n%s 文件已经被 解压 了。\n您可以在 文件夹 里查看（记事本打开的话可能会缺失空格，请使用写字板打开）。\n===============\n\n", char_choice);
			}
			else if(int_choice==-1)
			{
				break;
			}

		}
		else if (int_choice == 2)//压缩	样本文件
		{
			sumWords = add_data(words, sumArtical, ORI_FILE_NAME);
			Huffman_Test(words, sumWords, code);;

			//输出到屏幕
			huffmanPrint(words, sumArtical);

			sumArtical_huf = outPutHufArtical(code, sumWords, words, ORI_FILE_NAME, AIM_FILE_NAME_HUFFMAN);


			printf("\n压缩率为：%f %%\n", (sumArtical_huf / (double)sumArtical) * 100);

			printf("\n===============\nHUF文件已经 生成 了。\n您可以在 文件夹 里查看（记事本打开的话可能会缺失空格，请使用写字板打开）。\n===============\n");
			system("pause");

			decodeHufArtical(code, sumWords, words, AIM_FILE_NAME_HUFFMAN, AIM_FILE_NAME);
			printf("\n===============\nHUF文件已经被 解压 了。\n您可以在 文件夹 里查看（记事本打开的话可能会缺失空格，请使用写字板打开）。\n===============\n");
		}
		else if (int_choice == 3) {		//解压	用户提供的文件
			printf("\n请输入您想解压的文件的文件名。显然，它的后缀名应该是.huf。\n");
			scanf("%s", char_choice);
			changeFileNameToTxt(char_choice, char_aimFileName);
			decodeHufArtical(code, sumWords, words, char_choice, char_aimFileName);
			printf("\n===============\n%s 已经被 解压 了。\n您可以在 文件夹 里查看。（记事本打开的话可能会缺失空格，请使用写字板打开）\n===============\n", char_choice);
		}

		printf("\n退出程序-扣1\n继续使用-其他\n");
		scanf("%d", &int_choice);
		if (int_choice==1)
		{
			break;
		}

		printf("\n继续使用\n");

	}


	printf("\n\n\n程序即将退出，欢迎使用！\n\n");
	system("pause");
	return 0;
}

