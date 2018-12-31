// ������ͳ��.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int *keycount ; //= NULL;  //�����ּ���
	int keyfilecount; // = 0;  //ɨ������������
	int totalword ; //= 0;    //�ļ�������

	void ReadFile();
	void KeyCount();  //���������ָ��� ������������ 
	bool Compare(char * src);  //����Ƿ�Ϊ������
	void SplitLine(char * l, int * wc); //����ȡ���ַ����ָ���������ʣ�����һ���ַ������飬ͳ��ÿ�е��ʸ���
	void CreateData(int * l);  //�����������
};



void Key::KeyCount(){   //���������ָ��� ������������ 
	keyfilecount++; fstream in;  // ɨ���������
	char buf[1000];int i = 0,counter = 0;
	in.open("keywords.txt", ios_base::in | ios_base::binary);
	if (!in.is_open()) {    //�ļ���ʧ��
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
		keycount = new int[i];//���� i �� int ��С�ռ�
		for (int j = 0; j < i; j++) {  //��ʼ��
			keycount[j] = 0;
		}
	}
}
int Ifequal(char *a, char *b) //�Ƚ������ַ����Ƿ����
{
	char *p = a; char *q = b;
	if (strlen(p) != strlen(q))  //���Ȳ���
		return 0;
	else {
		while (*p != '\0' && *q != '\0'){//���ֱȽ�
			if (*p == *q){p++;q++;}
			else return 0;
		}
		return 1;
	}
}

bool Key::Compare(char * src)   //����Ƿ�Ϊ������
{
	fstream keywords;
	char keyword[20];int i = 0;
	keyfilecount++;  //ɨ���ļ���������
	keywords.open("keywords.txt", ios_base::in | ios_base::binary);
	if(!keywords.is_open())   //�ļ���ʧ��
	{cout<< "Error : File keywords can not be opened !" <<endl;exit(0);}
	else {
		while (!keywords.eof()) {
			memset(keyword, 0, sizeof(keyword));  //ÿ�ζ�ȡ����ʱ������ַ�����
			keywords.getline(keyword, sizeof(keyword));  //��keyword�������һ������
			if (Ifequal(src, keyword)) {//����Ǳ����֣��Ͷ�Ӧ�±�����++;
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

void Key::SplitLine(char * l, int * wc)  //����ȡ���ַ����ָ���������ʣ�����һ���ַ������飬ͳ��ÿ�е��ʸ���
{
	char * p = l;int count = 0;char word[20];
	while (*p != '\0' && *p != '\r') {   //����\r �� \0 ����
		int i = 0;
		memset(word, 0, sizeof(word));
		while (isalpha(*p) || *p == '_') {  //���ַ�����ĸ���»������
			word[i] = *p;  //�����ַ���
			i++;
			p++;
		}
		if (i > 1) {
			count++;
			Compare(word);
		}
		else {
		}
		while (isspace(*p)|| isdigit(*p)) {//��ָ����� space��0-9����ʱ������
			p++;
		}
		if (*p == '/' && *p++ == '/') {//����ע��
			while (*p != '\r') {
				p++;
			}
		}
		else {
			while (ispunct(*p) && !(*p == '/' && *p++ == '/')) {//��������ע��
				p++;
			}
		}
	}
	*wc = count;
}

void Key::CreateData(int * l) //�����������
{	
	fstream infile;
	char buf[N];
	int i = 0;
	int keywdcount = 0;
	keyfilecount++;
	infile.open("keywords.txt", ios_base::in | ios_base::binary);
	if (!infile.is_open()) {//�ļ���ʧ��
		cout << "Error : File keywords can not be opened" << endl;
		system("pause");
		exit(-1);
	}
	else {//�ļ��򿪳ɹ�
		fstream List1, List2;
		List1.open("output1.txt", ios_base::out | ios_base::binary);
		List2.open("output2.txt", ios_base::out | ios_base::binary);
		if (!List1.is_open()) {
			cout << "Error : List1 can not be opened" << endl;
			exit(-1);
		}
		else {
			while (!infile.eof()) {  //��keywords���ж�ȡ���� ��������������Ӧ�ؼ��ֺ󣬱�����List1 �ļ���
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
			for (int j = 0; j < i; j++) {//ͳ�Ʊ����ָ���
				keywdcount += l[j];
			}
			List2 << "KeyFileCount : " << keyfilecount << "\r\n";//��ɨ��keywords.txt �ļ��Ĵ��������������������������Ǳ����ֱ�����List2�ļ���
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
			this->SplitLine(mybuffer, &wcount);  //�ֽ������ ͳ�Ʊ�����
			this->totalword += wcount;   //ͳ�Ƶ�����
		}
		infile.close();
		this->CreateData(this->keycount);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	Key test;
	test.KeyCount(); // ��ʼ��ͳ������
	test.ReadFile();
	return 0;
}


