// 保留字统计.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "string"
#include "algorithm"
#include "fstream"
#include "ctype.h"
#define N 1000
using namespace std;

class Key
{
public:
	Key(){keycount = NULL;keyfilecount = 0;totalword = 0;}
	int *keycount ; //= NULL;  //保留字计数
	int keyfilecount; // = 0;  //扫描程序次数计数
	int totalword ; //= 0;    //文件总字数

	void ReadFile();
	void KeyCount();  //计数保留字个数 创建计数数组 
	bool Compare(char * src);  //检查是否为保留字
	void SplitLine(char * l, int * wc); //将读取的字符串分割成正常单词，返回一个字符串数组，统计每行单词个数
	void CreateData(int * l);  //创建结果数据
};



void Key::KeyCount(){   //计数保留字个数 创建计数数组 
	keyfilecount++; fstream in;  // 扫描次数增加
	char buf[1000];int i = 0,counter = 0;
	in.open("keywords.txt", ios_base::in | ios_base::binary);
	if (!in.is_open()) {    //文件打开失败
		cout << "Error : File keywords can not be opened" << endl;
	}
	else {
		string temp;
		while(getline(in,temp)){
			strcpy(buf+counter,const_cast<char*>(temp.c_str()));
			counter += temp.length();
			i++;
		}
		in.close();
		keycount = new int[i];//申请 i 个 int 大小空间
		for (int j = 0; j < i; j++) {  //初始化
			keycount[j] = 0;
		}
	}
}
int Ifequal(char *a, char *b) //比较两个字符串是否相等
{
	char *p = a; char *q = b;
	if (strlen(p) != strlen(q))  //长度不等
		return 0;
	else {
		while (*p != '\0' && *q != '\0'){//逐字比较
			if (*p == *q){p++;q++;}
			else return 0;
		}
		return 1;
	}
}

bool Key::Compare(char * src)   //检查是否为保留字
{
	fstream keywords;
	char keyword[20];int i = 0;
	keyfilecount++;  //扫描文件次数增加
	keywords.open("keywords.txt", ios_base::in | ios_base::binary);
	if(!keywords.is_open())   //文件打开失败
	{cout<< "Error : File keywords can not be opened !" <<endl;exit(0);}
	else {
		while (!keywords.eof()) {
			memset(keyword, 0, sizeof(keyword));  //每次读取新行时，清空字符数组
			keywords.getline(keyword, sizeof(keyword));  //给keyword数组读入一行数据
			if (Ifequal(src, keyword)) {//如果是保留字，就对应下标数组++;
				keycount[i]++;
				i++;
				return true;
			}
			else {
				i++;
				continue;
			}
		}
		keywords.close();
		return false;
	}
}

void Key::SplitLine(char * l, int * wc)  //将读取的字符串分割成正常单词，返回一个字符串数组，统计每行单词个数
{
	char * p = l;int count = 0;char word[20];
	while (*p != '\0' && *p != '\r') {   //读到\r 或 \0 结束
		int i = 0;
		memset(word, 0, sizeof(word));
		while (isalpha(*p) || *p == '_') {  //当字符是字母或下划线组成
			word[i] = *p;  //拷贝字符串
			i++;
			p++;
		}
		if (i > 1) {
			count++;
			Compare(word);
		}
		else {
		}
		while (isspace(*p)|| isdigit(*p)) {//当指向的是 space，0-9数字时，跳过
			p++;
		}
		if (*p == '/' && *p++ == '/') {//跳过注释
			while (*p != '\r') {
				p++;
			}
		}
		else {
			while (ispunct(*p) && !(*p == '/' && *p++ == '/')) {//跳过标点后注释
				p++;
			}
		}
	}
	*wc = count;
}

void Key::CreateData(int * l) //创建结果数据
{	
	fstream infile;
	char buf[N];
	int i = 0;
	int keywdcount = 0;
	keyfilecount++;
	infile.open("keywords.txt", ios_base::in | ios_base::binary);
	if (!infile.is_open()) {//文件打开失败
		cout << "Error : File keywords can not be opened" << endl;
		system("pause");
		exit(-1);
	}
	else {//文件打开成功
		fstream List1, List2;
		List1.open("output1.txt", ios_base::out | ios_base::binary);
		List2.open("output2.txt", ios_base::out | ios_base::binary);
		if (!List1.is_open()) {
			cout << "Error : List1 can not be opened" << endl;
			exit(-1);
		}
		else {
			while (!infile.eof()) {  //从keywords表中读取数据 将计数结果插入对应关键字后，保存在List1 文件中
				infile.getline(buf, sizeof(buf));
				List1 << buf << "\t" << l[i] << "\r\n";
				i++;
			}
			List1.close();
			cout << "Success : File List1 saved " << endl;
		}
		infile.close();
		if (!List2.is_open()) {
			cout << "Error : File List1 can not be opened" << endl;
			system("pause");
			exit(-1);
		}
		else {
			for (int j = 0; j < i; j++) {//统计保留字个数
				keywdcount += l[j];
			}
			List2 << "KeyFileCount : " << keyfilecount << "\r\n";//将扫描keywords.txt 文件的次数，单词总数，保留字数，非保留字保存在List2文件中
			List2 << "TotalWords : " << totalword << "\r\n";
			List2 << "KeyWords : " << keywdcount << "\r\n";
			List2 << "NotKeyWords : " << totalword - keywdcount;
			List2.close();
			cout << "Success : File List2 saved" << endl;
		}
	}
}

void Key::ReadFile()
{
	fstream infile;
	int wcount = 0;char filename[20];char mybuffer[N];
	cout << "Please enter the filename : ";
	cin >> filename;
	infile.open(filename, ios_base::in | ios_base::binary);
	if (!infile.is_open()) 
		cout << "Error : File can not be opened" << endl;
	else {
		while(!infile.eof()) {
			memset(mybuffer, 0, sizeof(mybuffer));
			infile.getline(mybuffer, sizeof(mybuffer));
			this->SplitLine(mybuffer, &wcount);  //分解出单词 统计保留字
			this->totalword += wcount;   //统计单词数
		}
		infile.close();
		this->CreateData(this->keycount);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	Key test;
	test.KeyCount(); // 初始化统计数组
	test.ReadFile();
	return 0;
}


