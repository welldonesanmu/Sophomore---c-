// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "vector"
#include "stack"
#include "string"
#include "iostream"
using namespace std;
 
class BigInteger
{
private:
	vector<int>s;   //  ����洢
public:
	static const int BASE = 100000000; // ���÷ָ����Ĵ�С
	static const int WIDTH = 8; // ���÷ָ��λ��
	BigInteger(long long num){*this = num;}
	BigInteger operator=(long long num);
	BigInteger operator=(const string &str);
};

BigInteger BigInteger::operator=(long long num)
{	
	int temp = num;  // �տ�ʼ��ʱ��������0,��֤whileִ��
	while(temp){
		s.push_back(temp % 10);
		temp /= 10;
	}	
}

BigInteger BigInteger::operator=(const string &str)  // ������long long �ķ�Χʱ
{
	


}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

