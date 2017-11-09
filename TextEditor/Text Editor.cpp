// Text Editor.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "LineEditor.h"
 

int main()
{

    cout << "please input input_file name:";
	String inFileName=inFileName.Read(cin);
	cout << "please iuput output_file name:";
	String outFileName=outFileName.Read(cin);
	LineEditor Editor(inFileName, outFileName);
	Editor.Run();
}


