// 大整数类.cpp : 定义控制台应用程序的入口点。
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
	vector<int>s;   //  逆序存储
public:
	static const int BASE = 100000000; // 设置分割数的大小
	static const int WIDTH = 8; // 设置分割的位数
	BigInteger(long long num){*this = num;}
	BigInteger operator=(long long num);
	BigInteger operator=(const string &str);
};

BigInteger BigInteger::operator=(long long num)
{	
	int temp = num;  // 刚开始的时候不能设置0,保证while执行
	while(temp){
		s.push_back(temp % 10);
		temp /= 10;
	}	
}

BigInteger BigInteger::operator=(const string &str)  // 当超出long long 的范围时
{
	


}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

