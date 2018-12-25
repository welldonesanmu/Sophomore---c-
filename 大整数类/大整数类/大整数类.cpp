// 大整数类.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector"
#include "stack"
#include "string"
#include "iterator"
#include "iomanip"
#include "algorithm"
#include "iostream"

using namespace std;
 
class Doublelong
{
public:
	vector<int>s;   //  逆序存储
	static const int BASE = 100000000; // 设置分割数的大小
	static const int WIDTH = 8; // 设置分割的位数
	Doublelong(){}
	Doublelong(long long num){*this = num;}
	Doublelong operator=(long long num);
	Doublelong operator=(const string &str);
	Doublelong operator+(Doublelong x);
	Doublelong operator+=(Doublelong x);
	Doublelong operator-(Doublelong x);
	Doublelong operator-=(Doublelong x);
	bool Judge(Doublelong x);
	void Display() ;

};

Doublelong Doublelong::operator=(long long num)
{	
	s.clear();
	long long int temp = num;  // 刚开始的时候不能设置0,保证while执行
	while(temp){
		s.push_back(temp % 10);
		temp /= 10;
	}	
	return *this;   // 返回本对象
}

Doublelong Doublelong::operator=(const string &str)  // 当超出long long 的范围时
{
	s.clear();  // 清空
	int x,len = (str.length() - 1) / WIDTH + 1;  //  length()不包含字符串结束符,-1只取科学计数的幂次， +1保证当小于8个时，即len 为运行次数
	for(int i = 0;i < len;i++)
	{
		int end = str.length() - i*WIDTH;   //从后面开始取，一次取8位
		int start = max(0,end - WIDTH);  //如果最后一次循环取的数不够8个0， 那么start就从0开始
		sscanf(str.substr(start,end-start).c_str(),"%d",&x);// 一次选9位存放在x中
		s.push_back(x);
	} 
	return *this;
}

void Doublelong::Display()
{
	vector<int>::iterator ite = s.begin();
	for(;ite != s.end();++ite)
	{
		cout<<*ite;
	}
}

ostream& operator<< (ostream &out,Doublelong x)
{
	Doublelong temp(x); 
	reverse(temp.s.begin(),temp.s.end()); // 用reverse实现容器内的翻转
	temp.Display();
	return out;  // 返回一个输出流，可以实现连续输出
}



istream& operator>> (istream&in,Doublelong& x)   // 传入引用！！！
{
	string demo;
	cout<<"输入一个数字：";in>>demo;
	x = demo;
	return in;  // 实现
}

Doublelong  Doublelong::operator+(Doublelong x)
{
	Doublelong temp;
	temp.s.clear();
	for(int i = 0,flag = 0;;i++)
	{
		if(flag == 0 && i >= x.s.size() && i >= s.size()) break;
		int counter = flag;  // flag 是进位标志
		if(i < x.s.size()) counter += x.s[i];
		if(i < s.size()) counter += s[i];
		temp.s.push_back(counter % BASE);
		flag = counter / BASE;
	}
	return temp;
}

Doublelong Doublelong::operator+=(Doublelong x)
{
	*this = *this+x;
	return *this;
}

bool Doublelong::Judge(Doublelong x) // 大致判断哪个数字大
{
	if(s.size() > x.s.size()) return true; // 1表示本类的数字大
	else if(s.size() < x.s.size()) return false;
	else 
		(s[0] - x.s[0])?true:false; // 1表示本类的数据大（如果分割位数相等，直接看最高位）
}


Doublelong Doublelong::operator-(Doublelong x)
{
	Doublelong temp;
	temp.s.clear();
	int len = min(x.s.size(),s.size());
	int flag = 0;

	if(Judge(x)) // 如果被减数大于减数
	{
		for(int i = 0;;i++)	{
			if(i>=x.s.size() && i>=s.size()) break;
			int counter = flag;

			if(i < s.size()) counter += s[i];
			if(i < x.s.size()) counter -= x.s[i];
			

			if(counter >= 0){temp.s.push_back(counter);flag = 0;} //没有借位
			else{
				counter += 1e8;
				temp.s.push_back(counter%static_cast<int>(1e8));
				flag = -1;  // 借位 下一次计算-1
			}
		}
		return temp;
	}
	
	else{  //如果被减数小于减数
		for(int i = 0;;i++)	{
			if(i>=x.s.size()-1 && i>=s.size()-1) break;
			int counter = flag;
			//用减数减去被减数
			if(i < x.s.size()) counter += x.s[i];
			if(i < s.size()) counter -= s[i];
				
			if(counter >= 0){temp.s.push_back(counter);flag = 0;} //没有借位
			else{
				counter += 1e8;
				temp.s.push_back(counter%static_cast<int>(1e8));
				flag = -1;  // 借位 下一次计算-1
			}
		}
		//最后一次单独处理


		temp.s[temp.s.size()-1] = -temp.s[temp.s.size()-1]; // 最高位取反
		return temp;
	}
}



Doublelong Doublelong::operator-=(Doublelong x)
{
	*this = *this - x;
	return *this;
}


int _tmain(int argc, _TCHAR* argv[])
{
//	const string str= "1111111122222222333333334444444455555555";
//	Doublelong test,demo;
//	test = str;demo = str;
//	cout<<test<<endl<<demo;  //  返回一个输出流类，用于继续输出

//	Doublelong demo;
//	cin>>demo;
//	cout<<demo;


	Doublelong test; cin>>test;
	Doublelong demo; cin>>demo;
//	test -= demo;
//	cout<<test;
	cout<<test<<"-"<<demo<<"="<<(test-demo)<<endl;


	

	return 0;
}

