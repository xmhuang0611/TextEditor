#ifndef __LINEEDITOR_H__
#define __LINEEDITOR_H__

#include<fstream>
#include "DblLinkList.h"
#include "String.h"
using namespace std;

//�ı��༭��
class LineEditor {
private:
	DblLinkList<String>textBuffer;      //�ı�����
	int curLineNo;                      //��ǰ�к�
	int allLines;                       //������
	ifstream inFile;                    //�����ļ�
	ofstream outFile;                   //����ļ�

	void NextLine();                    //ת����һ��
	void PreviousLine();                //ת��ǰһ��
	void BeginLine();                   //ת����һ��
	void EndLine();                     //ת�����һ��
	void GotoLine();                    //ת��ָ����
	void ViewFile();                    //��ʾ�ļ�����
	void InsertLine();                  //����һ��
	void DeleteLine();                  //ɾ��һ��
	void FindString();                  //���Ҵ�
	void ChangeLine();                  //�滻��ǰ�л������е�ָ���ı���
	void TotalFile();                   //ͳ���ļ��������ַ���
	void ReadFile(String fileName);     //�����ı��ļ�
	void WriteFile();                   //д�ı��ļ�
	
public:
	LineEditor(String inFName, String outFName);     //���캯��
	void Run();                                      //�����ı��༭��
};  
#endif

