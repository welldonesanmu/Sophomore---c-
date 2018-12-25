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
	vector<int>s;   //  ����洢
	static const int BASE = 100000000; // ���÷ָ����Ĵ�С
	static const int WIDTH = 8; // ���÷ָ��λ��
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
	long long int temp = num;  // �տ�ʼ��ʱ��������0,��֤whileִ��
	while(temp){
		s.push_back(temp % 10);
		temp /= 10;
	}	
	return *this;   // ���ر�����
}

Doublelong Doublelong::operator=(const string &str)  // ������long long �ķ�Χʱ
{
	s.clear();  // ���
	int x,len = (str.length() - 1) / WIDTH + 1;  //  length()�������ַ���������,-1ֻȡ��ѧ�������ݴΣ� +1��֤��С��8��ʱ����len Ϊ���д���
	for(int i = 0;i < len;i++)
	{
		int end = str.length() - i*WIDTH;   //�Ӻ��濪ʼȡ��һ��ȡ8λ
		int start = max(0,end - WIDTH);  //������һ��ѭ��ȡ��������8��0�� ��ôstart�ʹ�0��ʼ
		sscanf(str.substr(start,end-start).c_str(),"%d",&x);// һ��ѡ9λ�����x��
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
	Doublelong temp;
	temp.s.clear();
	for(int i = 0,flag = 0;;i++)
	{
		if(flag == 0 && i >= x.s.size() && i >= s.size()) break;
		int counter = flag;  // flag �ǽ�λ��־
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

bool Doublelong::Judge(Doublelong x) // �����ж��ĸ����ִ�
{
	if(s.size() > x.s.size()) return true; // 1��ʾ��������ִ�
	else if(s.size() < x.s.size()) return false;
	else 
		(s[0] - x.s[0])?true:false; // 1��ʾ��������ݴ�����ָ�λ����ȣ�ֱ�ӿ����λ��
}


Doublelong Doublelong::operator-(Doublelong x)
{
	Doublelong temp;
	temp.s.clear();
	int len = min(x.s.size(),s.size());
	int flag = 0;

	if(Judge(x)) // ������������ڼ���
	{
		for(int i = 0;;i++)	{
			if(i>=x.s.size() && i>=s.size()) break;
			int counter = flag;

			if(i < s.size()) counter += s[i];
			if(i < x.s.size()) counter -= x.s[i];
			

			if(counter >= 0){temp.s.push_back(counter);flag = 0;} //û�н�λ
			else{
				counter += 1e8;
				temp.s.push_back(counter%static_cast<int>(1e8));
				flag = -1;  // ��λ ��һ�μ���-1
			}
		}
		return temp;
	}
	
	else{  //���������С�ڼ���
		for(int i = 0;;i++)	{
			if(i>=x.s.size()-1 && i>=s.size()-1) break;
			int counter = flag;
			//�ü�����ȥ������
			if(i < x.s.size()) counter += x.s[i];
			if(i < s.size()) counter -= s[i];
				
			if(counter >= 0){temp.s.push_back(counter);flag = 0;} //û�н�λ
			else{
				counter += 1e8;
				temp.s.push_back(counter%static_cast<int>(1e8));
				flag = -1;  // ��λ ��һ�μ���-1
			}
		}
		//���һ�ε�������


		temp.s[temp.s.size()-1] = -temp.s[temp.s.size()-1]; // ���λȡ��
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
//	cout<<test<<endl<<demo;  //  ����һ��������࣬���ڼ������

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

