#include "LineEditor.h"

LineEditor::LineEditor( String inFName, String outFName) 
{
	outFile.open(outFName.CStr(), ios::out);
	ReadFile(inFName);         //�����ı��ļ�
}

void LineEditor::NextLine()
{
	if (curLineNo == allLines)
	{
		cout << "���棺��ǰ���������һ��" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo++;
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
	}
}

void LineEditor::PreviousLine()
{
	if (curLineNo == 1)
	{
		cout << "���棺��ǰ�����ǵ�һ��" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo--;
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
	}
}

void LineEditor::BeginLine()
{
	if (textBuffer.Empty())
	{
		cout << "���棺�ı���������" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo = 1;
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
	}
}

void LineEditor::EndLine()
{
	if (textBuffer.Empty())
	{
		cout << "���棺�ı���������" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo = allLines;
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
	}
}

void LineEditor::GotoLine()
//���������ת��ָ����
{
	int tmpLineNo;
	cout << "������ָ���кţ�";
	cin >> tmpLineNo;
	if (tmpLineNo<1 || tmpLineNo>allLines)
	{
		cout << "���棺��������������" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo = tmpLineNo;                     //��ǰ�кű�Ϊָ���к�
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
		//�����ǰ�кż���ǰ������
	}
}

void LineEditor::ViewFile()
{
	if (textBuffer.Empty())
	{
		cout << "���棺�ı���������" << endl;
	}
	else
	{
		String tmpLine;
		for (int i = 1; i <= allLines; i++)
		{
			textBuffer.GetElem(i, tmpLine);
			cout << i << ":" << tmpLine.CStr() << endl;
		}
		//���ÿ���кż�ÿ������
	}
}

void LineEditor::InsertLine()
//������������뵥������
{
	int tmpLineNo;
	cout << "������Ҫ������кţ�";
	cin >> tmpLineNo;
	getchar();
	cout << "������Ҫ��������ݣ�";
	String tmpLine=tmpLine.Read(cin);
	if (textBuffer.Insert(tmpLineNo, tmpLine) ==SUCCESS)
		//����ɹ�
	{
		allLines++;                  // ��������һ
		if (tmpLineNo <= curLineNo)
		{
			curLineNo++;             //���ڵ�ǰ��֮ǰ���� ��ǰ�кż�һ
		}
		cout << tmpLineNo << ":" << tmpLine.CStr() << endl;
		//����������кż�����������
	}
	textBuffer.GetElem(curLineNo, tmpLine);
	cout << curLineNo << ":" << tmpLine.CStr() << endl;
	    //�����ǰ�кż���ǰ������
}

void LineEditor::DeleteLine()
//���������ɾ����ǰ�в��Ƶ���һ��
{
	String tmpLine;
	if (textBuffer.Delete(curLineNo, tmpLine) ==SUCCESS)
		//ɾ���ɹ�
	{
		allLines--;                   //��������һ
	}
	textBuffer.GetElem(curLineNo, tmpLine);
	cout << curLineNo << ":" << tmpLine.CStr() << endl;  
	//�����ǰ�кţ�ԭ������һ�У�����ǰ������
}

void LineEditor::ChangeLine()
//����������û�����ָ���ı������ڵ�ǰ�л�������������������ı����滻ָ���ı���
{
	char answer;                       // �û��ش��ַ�   
	bool initResponse = true;          //��ʼ�ش�

	//ѭ��ֱ���û�����ǡ���ػش�Ϊֹ
	do
	{
		if (initResponse)
		{
			cout << "�滻��ǰ��c��urrent�����滻������a��ll����";
		}
		else
		{
			cout << "��c��a�ش�";
		}

		answer = getchar();           //�������������ո��Ʊ����ȡһ�ַ�
		answer = tolower(answer);     //ת��ΪСд��ĸ
		while (cin.get() != '\n');    //�����û�����������ĸ
		initResponse = false;
	} while (answer != 'c'&&answer != 'a');

	cout << "������Ҫ���滻���ı�����";    
	String strOld=strOld.Read(cin);    //�ɴ�
	cout << "���������ı�����";        
	String strNew=strNew.Read(cin);    //�´�

	for (int row = 1; row <= allLines; row++)
	{
		if (answer == 'c'&&row != curLineNo)
		{
			continue;
		}

		String strRow;                                     //��
		textBuffer.GetElem(row, strRow);                   //ȡ����
		int index = strRow.Index(strRow, strOld);          //�ڵ�ǰ�в����ı���
		if (index != -1)
		{   //ģʽƥ��ɹ�
			String newLine;                                //����
			newLine.Copy(newLine, strRow, index);          //����ָ���ı�ǰ�Ĵ�
			newLine.Concat(newLine, strNew);               //�������ı���
			const char*oldLine = strRow.CStr();            //����
			newLine.Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
            //����һ����ʱָ�룬ָ��������ַ�������ַ����ٽ�c���ת��ΪString������newLine����
			textBuffer.SetElem(row, newLine);              //���õ�ǰ���´�
		}
	}
}


void LineEditor::FindString()
//����������ӵ�ǰ�л��һ�п�ʼ����ָ���ı�
{
	char answer;                       // �û��ش��ַ�   
	bool initResponse = true;          //��ʼ�ش�

	//ѭ��ֱ���û�����ǡ���ػش�Ϊֹ
	do
	{
		if (initResponse)
		{
			cout << "�ӵ�ǰ��c��urrent�����һ��f��irst����ʼ��";
		}
		else
		{
			cout << "��c��f�ش�";
		}

		answer = getchar();           //�������������ո��Ʊ����ȡһ�ַ�
		answer = tolower(answer);     //ת��ΪСд��ĸ
		while (cin.get() != '\n');    //�����û�����������ĸ
		initResponse = false;
	} while (answer != 'c'&&answer != 'f');
	if (answer == 'f')curLineNo = 1;   //�ӵ�һ�п�ʼ

	int index;
	cout << "���뱻���ҵ��ı���:";
	String searchString=searchString.Read(cin);  //��������ı���
	String curLine;
	textBuffer.GetElem(curLineNo, curLine);      //ȡ����ǰ��
	while ((index = curLine.Index(curLine, searchString)) == -1)
	{
		if (curLineNo<allLines)
		{   //������һ��
			curLineNo++;                               //��һ��
			textBuffer.GetElem(curLineNo, curLine);    //ȡ����һ��
		}
		else
		{  //�Ѳ�����������
			break;
		}
	}

	if (index == -1)
	{
		cout << "����ʧ��." << endl;
	}
	else
	{   //���ҳɹ�
		cout << curLineNo << "��" << curLine.CStr() << endl;
		//������ҵ��е��кż���������
	}
}

void LineEditor::TotalFile()
//���������ͳ���ļ��������ַ���
{
	char answer;                       // �û��ش��ַ�   
	bool initResponse = true;          //��ʼ�ش�

	//ѭ��ֱ���û�����ǡ���ػش�Ϊֹ
	do
	{
		if (initResponse)
		{
			cout << "������l(ines�������ַ���c(hars)";
		}
		else
		{
			cout << "��l��c�ش�";
		}

		answer = getchar();           //�������������ո��Ʊ����ȡһ�ַ�
		answer = tolower(answer);     //ת��ΪСд��ĸ
		while (cin.get() != '\n');    //�����û�����������ĸ
		initResponse = false;
	} while (answer != 'l'&&answer != 'c');

	if (answer == 'l')
		cout << "������Ϊ��" << allLines << endl;
	else
	{
		int count=0;
		String tmpLine;
		for (int i = 1; i <= allLines; i++)
		{
				textBuffer.GetElem(i, tmpLine);
				count += tmpLine.Length();
		}
		cout << "���ַ���Ϊ��" << count << endl;
	}

}

void LineEditor::ReadFile(String fileName)
//��������������ı��ļ�����ʾ�ļ�����
{
	textBuffer.Clear();           //��ջ�����
	curLineNo = 0;
	allLines = 0;
	inFile.open(fileName.CStr(), ios::in);
	String tempLine;
	while (!inFile.eof())
	{
		tempLine = tempLine.Read(inFile);
		textBuffer.Insert(++allLines, tempLine);
		cout << tempLine.CStr() << endl;
		//����ļ�����
	}
	curLineNo = 1;               //���õ�ǰ��Ϊ�ļ���һ��
	inFile.close();
}

void LineEditor::WriteFile()
//���������д�ı����浽����ļ���
{
	if (textBuffer.Empty())
	{
		cout << "���棺�ı���������" << endl;
	}
	else
	{
		String tmpLine;
		for (int i = 1; i <= allLines; i++)
		{
			textBuffer.GetElem(i, tmpLine);
			outFile << tmpLine.CStr() << endl;
		}
	}
}

 void LineEditor::Run()
//��������������ı��༭��
{
 	char userCommand;                        //�û�����
	String inFileName;                       //�����ļ���
 	do
 	{
 		
		userCommand=getchar();               //�������������ո��Ʊ����ȡһ�ַ�
		userCommand=tolower(userCommand);    //ת��ΪСд��ĸ
		while(cin.get()!='\n');              //�����û�����������ĸ
		
		switch(userCommand)

		{
			case'b':
				BeginLine();
				break; 
			case'c':
				if(textBuffer.Empty())  
				{
					cout<<"���棺�ı���������"<<endl; 
				}
				else
				{
					ChangeLine();
				}
				break;
			case'd':
				DeleteLine();
				break; 
			case'e':
				EndLine();
				break; 	
			case'f':
				if(textBuffer.Empty())  
				{
					cout<<"���棺�ı���������"<<endl; 
				}
				else
				{
					FindString();
				}
				break;
			case'g':
				GotoLine();
				break;	
			case'h':	
				cout << "��Ч���b(egin);c(hange);d(el);e(nd)" << endl
					<< "f(ind);g(o);h(elp);i(nsert);n(ext);p(rior)" << endl
					<< "q(uit);r(ead);t(otal);v(iew);w(rite)" << endl;
				break;
			case'i':
				InsertLine();
				break;	
			case'n':
				NextLine();  					
				break;
			case'p':
				PreviousLine(); 				
				break;		     
			case'q': 
				break;
			case'r':
				cout << "please input input_file name:";
				inFileName = inFileName.Read(cin);		
				ReadFile(inFileName);
				break;
			case't':
				TotalFile();
				break;
			case'v':
				ViewFile();   
				break;
			case'w':
				WriteFile();
				break;	
			default:
				cout<<"����h��ð�����������Ч�����ַ���\n";	
		}		
	}while(userCommand!='q'); 	
} 