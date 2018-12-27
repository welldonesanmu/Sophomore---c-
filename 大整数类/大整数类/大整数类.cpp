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
	vector<long long int>s;   //  逆序存储
	bool sign; //符号 1正数 0负数
	static const int BASE = 100000000; // 设置分割数的大小
	static const int WIDTH = 8; // 设置分割的位数
	Doublelong(){sign = 1;}
	Doublelong(long long num){*this = num;if(num >= 0)sign = 1;else sign = 0;}
	Doublelong operator=(long long num);
	Doublelong operator=(const string &str);
	//重载数值判断
	bool operator>(const Doublelong &) const;  // 传入的this指针是 const型的this指针
    bool operator>=(const Doublelong &) const;
    bool operator<(const Doublelong &) const;
    bool operator<=(const Doublelong &) const;
    bool operator==(const Doublelong &) const;
    bool operator!=(const Doublelong &) const;
	bool Judge(Doublelong x);
	//重载四则运算
	Doublelong operator+(Doublelong x);
	Doublelong operator+=(Doublelong x);
	Doublelong operator-(Doublelong x);
	Doublelong operator-=(Doublelong x);
	Doublelong operator*(Doublelong x);
	Doublelong operator*(int x);
	Doublelong operator*=(Doublelong x);
	Doublelong operator/(Doublelong x);
	Doublelong operator/=(Doublelong x);
	void Display();
};


bool Doublelong::operator<(const Doublelong &x) const
{
	if (sign^x.sign)  // 如果符号不同
        return x.sign; // 减数的符号就是结果
	
	if (s.size() != x.s.size())       //  如果长度不相同
		return s.size() < x.s.size(); //  比较两数的长度

	for (int i = 0; i < s.size(); i++) // 在符号相同 长度相同的情况下
        if (s[s.size()-i-1] != x.s[s.size()-i-1])
            return sign ? (s[s.size()-i-1] < x.s[s.size()-i-1]) : (!(s[s.size()-i-1] < x.s[s.size()-i-1]));
    return !sign;  // 两个数完全相同的情况下
}

bool Doublelong::operator>(const Doublelong&num) const
{
    return num < *this;
}

bool Doublelong::operator<=(const Doublelong&num)const
{
    return !(*this > num);
}

bool Doublelong::operator>=(const Doublelong&num)const
{
    return !(*this < num);
}

bool Doublelong::operator!=(const Doublelong&num)const
{
    return *this > num || *this < num;
}

bool Doublelong::operator==(const Doublelong&num)const
{
    return !(num != *this);
}


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

Doublelong Doublelong::operator=(const string &str)  // 当超出long long 的范围用string时
{
	s.clear();  // 清空

	string temp = str.substr(0,1); // 获取首字符
	if(temp == "-"){
		sign = 0; // 负数 
		string str_;
		str_ = str.substr(1,str.length()-1);  // 提取出绝对值

		long long int x,len = (str_.length() - 1) / WIDTH + 1;  //  length()不包含字符串结束符,-1只取科学计数的幂次， +1保证当小于8个时，即len 为运行次数
		for(int i = 0;i < len;i++)
		{
			int end = str_.length() - i*WIDTH;   //从后面开始取，一次取8位
			int start = max(0,end - WIDTH);  //如果最后一次循环取的数不够8个0， 那么start就从0开始
			sscanf(str_.substr(start,end-start).c_str(),"%lld",&x);// 一次选9位存放在x中
			s.push_back(x);
		} 
		return *this;
	}

	else{  // 如果不是负数
		long long int x,len = (str.length() - 1) / WIDTH + 1;  //  length()不包含字符串结束符,-1只取科学计数的幂次， +1保证当小于8个时，即len 为运行次数
		for(int i = 0;i < len;i++)
		{
			int end = str.length() - i*WIDTH;   //从后面开始取，一次取8位
			int start = max(0,end - WIDTH);  //如果最后一次循环取的数不够8个0， 那么start就从0开始
			sscanf(str.substr(start,end-start).c_str(),"%lld",&x);// 一次选9位存放在x中
			s.push_back(x);
		} 
		return *this;
	}
}

void Doublelong::Display()
{
	if(!sign)
		cout<<"-";
	vector<long long int>::iterator ite = s.begin();
	for(;ite != s.end();++ite)
	{
		cout<<*ite;
	}
}


ostream& operator<< (ostream &out,Doublelong x)  // 重载输出流
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
	if (sign^x.sign)    // 符号不同的时候
    {
        Doublelong temp = sign ? x : *this;  // 若本类正，temp取x
        temp.sign = 1;  
        return sign ? *this - x : x - temp;
    }

	Doublelong temp;
	temp.s.clear();
	if(sign == false &&x.sign == false) temp.sign = false;
	for(int i = 0,flag = 0;;i++)
	{
		if(flag == 0 && i >= x.s.size() && i >= s.size()) break;
		long long int counter = flag;  // flag 是进位标志
		if(i < x.s.size()) counter += x.s[i];
		if(i < s.size()) counter += s[i];
		temp.s.push_back(counter % BASE);
		flag = counter / BASE;  //进位数
	}
	return temp;
}

Doublelong Doublelong::operator+=(Doublelong x)
{
	*this = *this+x;
	return *this;
}


Doublelong Doublelong::operator-(Doublelong x)
{
	Doublelong b = x,a = *this;
    if (!b.sign && !sign)  // 如果同时都是负数 
    {
        b.sign = 1;
        a.sign = 1;
        return b-a;  //运算时取绝对值
    }
    if (!b.sign)  // 如果被减数是负数
    {
        b.sign = 1;
        return a+b;
    }
    if (!a.sign) // 如果减数是负数
    {
        a.sign = 1;
        b = Doublelong(0)-(a+b);
        return b;
    }
    if (a < b)  // 两个数的绝对值比较大小
    {
        Doublelong c = (b - a);
        c.sign = false;
        return c;
    }

	// 一系列操作保证了 被减数一定大于等于减数
    Doublelong result;
	result.s.clear();

	for(int i = 0,flag = 0;;i++)
	{
		if(i >= x.s.size() && i >= s.size()) break;
		int counter = flag;  // flag 是借位标志
		if(i < x.s.size()) counter -= x.s[i];
		if(i < s.size()) counter += s[i];
		result.s.push_back(counter % BASE);
		if(flag < 0)  flag = -1;
		else flag = 0;
	}
	return result;
}

Doublelong Doublelong::operator-=(Doublelong x)
{
	*this = *this - x;
	return *this;
}

Doublelong Doublelong::operator*(Doublelong x)
{
	Doublelong result;
	result.s.resize(128);// 两个64位相乘最多是128位

	for(int i = 0; i < s.size(); i++)
		for(int j = 0; j < x.s.size();j++){
			if (i >= s.size() || i < 0) { cout << "vetcor下标越界" << endl; break; }
			result.s[i + j] += s[i] * x.s[j];   //根据乘法竖式计算先计算出每个分割后的数字相乘的结果
		}
	int len = 0;
	for(int i = 0;i < result.s.size(),result.s[i];i++)
		len++;		// 找到第一个为0元素空间下标 
	result.s.erase(result.s.begin()+len,result.s.end()-1);
	for (int i = 0; i < len; i++)
    {
        result.s[i + 1] += result.s[i] / BASE;  // 加上进位
        result.s[i] %= BASE;    // 留下剩下的部分
    }
	result.sign = !(sign^x.sign);
	if(!result.s.back())   // 为0删掉（即意味着不为0保留） !!!!这个十分重要
		result.s.erase(result.s.end()-1);
	return result;
}

Doublelong Doublelong::operator*(int x)
{ 
	Doublelong temp1 = x;
    Doublelong temp2 = *this;
    return temp1*temp2;
}


Doublelong Doublelong::operator*=(Doublelong x)
{
	*this = *this * x;
	return *this;
}

Doublelong Doublelong::operator/(Doublelong x)
{
	Doublelong result;
	if(!(sign^x.sign) && !Judge(x))   // 当两个数符号相同的时候 并且被除数小于的时候
	{  
		result.sign = 1;
		result.s.push_back(0);
		return result;
	}
		 
//	if(s < x.s){result.sign = 1;result.s.push_back(0);return result;}
	int i = 1;
	while(1){
		if(sign == 1 && x*(-i) >= *this){result.s.push_back(i-1);result.sign = !(sign^x.sign);return result;}
		if(sign == 0 &&x*(-i) <= *this){result.s.push_back(i-1);result.sign = !(sign^x.sign);return result;}
		i++;
	}
}

Doublelong Doublelong::operator/=(Doublelong x)
{
	*this = *this/x;
	return *this;
}

bool Doublelong::Judge(Doublelong x) // 大致判断哪个数字大
{
	if(s.size() > x.s.size()) return true; // 1表示本类的数字大
	else if(s.size() < x.s.size()) return false;
	else 
		return (s[0] - x.s[0])?true:false; // 1表示本类的数据大（如果分割位数相等，直接看最高位）
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

	//记得写一个随机生成64位数函数
	Doublelong test;test="9999999988888888777777776666666655555555444444443333333322222222";
//	cin>>test;
	Doublelong demo;demo="-1111111122222222333333334444444455555555666666667777777788888888";
//	cin>>demo;
	Doublelong result = (test/demo);
//	cout<<result<<endl;
	cout<<(test /= demo)<<endl;


	
	return 0;
}

