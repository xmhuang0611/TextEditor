// Text Editor.cpp : �������̨Ӧ�ó������ڵ㡣
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


