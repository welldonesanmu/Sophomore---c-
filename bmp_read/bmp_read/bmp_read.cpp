// bmp_read.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
using namespace std;
/*
typedef struct
{
	BYTE b;
	BYTE g;
	BYTE r;
}RGB;
*/


int _tmain(int argc, _TCHAR* argv[])
{
//	BITMAPFILEHEADER fileHeader;
//	BITMAPINFOHEADER infoHeader;
	ofstream out("deom.txt");
	if(out.is_open()){
		out<<"this is a test demo\n";
		out.close();
	}



	
	
	return 0;
}

