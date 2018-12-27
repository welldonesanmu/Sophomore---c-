// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
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
	vector<long long int>s;   //  ����洢
	bool sign; //���� 1���� 0����
	static const int BASE = 100000000; // ���÷ָ����Ĵ�С
	static const int WIDTH = 8; // ���÷ָ��λ��
	Doublelong(){sign = 1;}
	Doublelong(long long num){*this = num;if(num >= 0)sign = 1;else sign = 0;}
	Doublelong operator=(long long num);
	Doublelong operator=(const string &str);
	//������ֵ�ж�
	bool operator>(const Doublelong &) const;  // �����thisָ���� const�͵�thisָ��
    bool operator>=(const Doublelong &) const;
    bool operator<(const Doublelong &) const;
    bool operator<=(const Doublelong &) const;
    bool operator==(const Doublelong &) const;
    bool operator!=(const Doublelong &) const;
	bool Judge(Doublelong x);
	//������������
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
	if (sign^x.sign)  // ������Ų�ͬ
        return x.sign; // �����ķ��ž��ǽ��
	
	if (s.size() != x.s.size())       //  ������Ȳ���ͬ
		return s.size() < x.s.size(); //  �Ƚ������ĳ���

	for (int i = 0; i < s.size(); i++) // �ڷ�����ͬ ������ͬ�������
        if (s[s.size()-i-1] != x.s[s.size()-i-1])
            return sign ? (s[s.size()-i-1] < x.s[s.size()-i-1]) : (!(s[s.size()-i-1] < x.s[s.size()-i-1]));
    return !sign;  // ��������ȫ��ͬ�������
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
	long long int temp = num;  // �տ�ʼ��ʱ��������0,��֤whileִ��
	while(temp){
		s.push_back(temp % 10);
		temp /= 10;
	}	
	return *this;   // ���ر�����
}

Doublelong Doublelong::operator=(const string &str)  // ������long long �ķ�Χ��stringʱ
{
	s.clear();  // ���

	string temp = str.substr(0,1); // ��ȡ���ַ�
	if(temp == "-"){
		sign = 0; // ���� 
		string str_;
		str_ = str.substr(1,str.length()-1);  // ��ȡ������ֵ

		long long int x,len = (str_.length() - 1) / WIDTH + 1;  //  length()�������ַ���������,-1ֻȡ��ѧ�������ݴΣ� +1��֤��С��8��ʱ����len Ϊ���д���
		for(int i = 0;i < len;i++)
		{
			int end = str_.length() - i*WIDTH;   //�Ӻ��濪ʼȡ��һ��ȡ8λ
			int start = max(0,end - WIDTH);  //������һ��ѭ��ȡ��������8��0�� ��ôstart�ʹ�0��ʼ
			sscanf(str_.substr(start,end-start).c_str(),"%lld",&x);// һ��ѡ9λ�����x��
			s.push_back(x);
		} 
		return *this;
	}

	else{  // ������Ǹ���
		long long int x,len = (str.length() - 1) / WIDTH + 1;  //  length()�������ַ���������,-1ֻȡ��ѧ�������ݴΣ� +1��֤��С��8��ʱ����len Ϊ���д���
		for(int i = 0;i < len;i++)
		{
			int end = str.length() - i*WIDTH;   //�Ӻ��濪ʼȡ��һ��ȡ8λ
			int start = max(0,end - WIDTH);  //������һ��ѭ��ȡ��������8��0�� ��ôstart�ʹ�0��ʼ
			sscanf(str.substr(start,end-start).c_str(),"%lld",&x);// һ��ѡ9λ�����x��
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


ostream& operator<< (ostream &out,Doublelong x)  // ���������
{
	Doublelong temp(x); 
	reverse(temp.s.begin(),temp.s.end()); // ��reverseʵ�������ڵķ�ת
	temp.Display();
	return out;  // ����һ�������������ʵ���������
}


istream& operator>> (istream&in,Doublelong& x)   // �������ã�����
{
	string demo;
	cout<<"����һ�����֣�";in>>demo;
	x = demo;
	return in;  // ʵ��
}

Doublelong  Doublelong::operator+(Doublelong x)
{
	if (sign^x.sign)    // ���Ų�ͬ��ʱ��
    {
        Doublelong temp = sign ? x : *this;  // ����������tempȡx
        temp.sign = 1;  
        return sign ? *this - x : x - temp;
    }

	Doublelong temp;
	temp.s.clear();
	if(sign == false &&x.sign == false) temp.sign = false;
	for(int i = 0,flag = 0;;i++)
	{
		if(flag == 0 && i >= x.s.size() && i >= s.size()) break;
		long long int counter = flag;  // flag �ǽ�λ��־
		if(i < x.s.size()) counter += x.s[i];
		if(i < s.size()) counter += s[i];
		temp.s.push_back(counter % BASE);
		flag = counter / BASE;  //��λ��
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
    if (!b.sign && !sign)  // ���ͬʱ���Ǹ��� 
    {
        b.sign = 1;
        a.sign = 1;
        return b-a;  //����ʱȡ����ֵ
    }
    if (!b.sign)  // ����������Ǹ���
    {
        b.sign = 1;
        return a+b;
    }
    if (!a.sign) // ��������Ǹ���
    {
        a.sign = 1;
        b = Doublelong(0)-(a+b);
        return b;
    }
    if (a < b)  // �������ľ���ֵ�Ƚϴ�С
    {
        Doublelong c = (b - a);
        c.sign = false;
        return c;
    }

	// һϵ�в�����֤�� ������һ�����ڵ��ڼ���
    Doublelong result;
	result.s.clear();

	for(int i = 0,flag = 0;;i++)
	{
		if(i >= x.s.size() && i >= s.size()) break;
		int counter = flag;  // flag �ǽ�λ��־
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
	result.s.resize(128);// ����64λ��������128λ

	for(int i = 0; i < s.size(); i++)
		for(int j = 0; j < x.s.size();j++){
			if (i >= s.size() || i < 0) { cout << "vetcor�±�Խ��" << endl; break; }
			result.s[i + j] += s[i] * x.s[j];   //���ݳ˷���ʽ�����ȼ����ÿ���ָ���������˵Ľ��
		}
	int len = 0;
	for(int i = 0;i < result.s.size(),result.s[i];i++)
		len++;		// �ҵ���һ��Ϊ0Ԫ�ؿռ��±� 
	result.s.erase(result.s.begin()+len,result.s.end()-1);
	for (int i = 0; i < len; i++)
    {
        result.s[i + 1] += result.s[i] / BASE;  // ���Ͻ�λ
        result.s[i] %= BASE;    // ����ʣ�µĲ���
    }
	result.sign = !(sign^x.sign);
	if(!result.s.back())   // Ϊ0ɾ��������ζ�Ų�Ϊ0������ !!!!���ʮ����Ҫ
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
	if(!(sign^x.sign) && !Judge(x))   // ��������������ͬ��ʱ�� ���ұ�����С�ڵ�ʱ��
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

bool Doublelong::Judge(Doublelong x) // �����ж��ĸ����ִ�
{
	if(s.size() > x.s.size()) return true; // 1��ʾ��������ִ�
	else if(s.size() < x.s.size()) return false;
	else 
		return (s[0] - x.s[0])?true:false; // 1��ʾ��������ݴ�����ָ�λ����ȣ�ֱ�ӿ����λ��
}

int _tmain(int argc, _TCHAR* argv[])
{
//	const string str= "1111111122222222333333334444444455555555";
//	Doublelong test,demo;
//	test = str;demo = str;
//	cout<<test<<endl<<demo;  //  ����һ��������࣬���ڼ������

//	Doublelong demo;
//	cin>>demo;
//	cout<<demo;

	//�ǵ�дһ���������64λ������
	Doublelong test;test="9999999988888888777777776666666655555555444444443333333322222222";
//	cin>>test;
	Doublelong demo;demo="-1111111122222222333333334444444455555555666666667777777788888888";
//	cin>>demo;
	Doublelong result = (test/demo);
//	cout<<result<<endl;
	cout<<(test /= demo)<<endl;


	
	return 0;
}

