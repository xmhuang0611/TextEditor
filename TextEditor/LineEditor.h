#ifndef __LINEEDITOR_H__
#define __LINEEDITOR_H__

#include<fstream>
#include "DblLinkList.h"
#include "String.h"
using namespace std;

//文本编辑类
class LineEditor {
private:
	DblLinkList<String>textBuffer;      //文本缓存
	int curLineNo;                      //当前行号
	int allLines;                       //总行数
	ifstream inFile;                    //输入文件
	ofstream outFile;                   //输出文件

	void NextLine();                    //转到下一行
	void PreviousLine();                //转到前一行
	void BeginLine();                   //转到第一行
	void EndLine();                     //转到最后一行
	void GotoLine();                    //转到指定行
	void ViewFile();                    //显示文件内容
	void InsertLine();                  //插入一行
	void DeleteLine();                  //删除一行
	void FindString();                  //查找串
	void ChangeLine();                  //替换当前行或所有行的指定文本串
	void TotalFile();                   //统计文件行数或字符数
	void ReadFile(String fileName);     //读入文本文件
	void WriteFile();                   //写文本文件
	
public:
	LineEditor(String inFName, String outFName);     //构造函数
	void Run();                                      //运行文本编辑器
};  
#endif

