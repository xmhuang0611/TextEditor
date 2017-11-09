#include "LineEditor.h"

LineEditor::LineEditor( String inFName, String outFName) 
{
	outFile.open(outFName.CStr(), ios::out);
	ReadFile(inFName);         //读入文本文件
}

void LineEditor::NextLine()
{
	if (curLineNo == allLines)
	{
		cout << "警告：当前行已是最后一行" << endl;
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
		cout << "警告：当前行已是第一行" << endl;
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
		cout << "警告：文本缓冲区空" << endl;
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
		cout << "警告：文本缓冲区空" << endl;
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
//操作结果：转到指定行
{
	int tmpLineNo;
	cout << "请输入指定行号：";
	cin >> tmpLineNo;
	if (tmpLineNo<1 || tmpLineNo>allLines)
	{
		cout << "警告：不存在这样的行" << endl;
	}
	else
	{
		String tmpLine;
		curLineNo = tmpLineNo;                     //当前行号变为指定行号
		textBuffer.GetElem(curLineNo, tmpLine);
		cout << curLineNo << ":" << tmpLine.CStr() << endl;
		//输出当前行号及当前行内容
	}
}

void LineEditor::ViewFile()
{
	if (textBuffer.Empty())
	{
		cout << "警告：文本缓冲区空" << endl;
	}
	else
	{
		String tmpLine;
		for (int i = 1; i <= allLines; i++)
		{
			textBuffer.GetElem(i, tmpLine);
			cout << i << ":" << tmpLine.CStr() << endl;
		}
		//输出每行行号及每行内容
	}
}

void LineEditor::InsertLine()
//操作结果：插入单个新行
{
	int tmpLineNo;
	cout << "请输入要插入的行号：";
	cin >> tmpLineNo;
	getchar();
	cout << "请输入要插入的内容：";
	String tmpLine=tmpLine.Read(cin);
	if (textBuffer.Insert(tmpLineNo, tmpLine) ==SUCCESS)
		//插入成功
	{
		allLines++;                  // 总行数加一
		if (tmpLineNo <= curLineNo)
		{
			curLineNo++;             //若在当前行之前插入 当前行号加一
		}
		cout << tmpLineNo << ":" << tmpLine.CStr() << endl;
		//输出插入行行号及插入行内容
	}
	textBuffer.GetElem(curLineNo, tmpLine);
	cout << curLineNo << ":" << tmpLine.CStr() << endl;
	    //输出当前行号及当前行内容
}

void LineEditor::DeleteLine()
//操作结果：删除当前行并移到下一行
{
	String tmpLine;
	if (textBuffer.Delete(curLineNo, tmpLine) ==SUCCESS)
		//删除成功
	{
		allLines--;                   //总行数减一
	}
	textBuffer.GetElem(curLineNo, tmpLine);
	cout << curLineNo << ":" << tmpLine.CStr() << endl;  
	//输出当前行号（原来的下一行）及当前行内容
}

void LineEditor::ChangeLine()
//操作结果：用户输入指定文本串，在当前行或所有行中用输入的新文本串替换指定文本串
{
	char answer;                       // 用户回答字符   
	bool initResponse = true;          //初始回答

	//循环直到用户输入恰当地回答为止
	do
	{
		if (initResponse)
		{
			cout << "替换当前行c（urrent）或替换所有行a（ll）：";
		}
		else
		{
			cout << "用c或a回答：";
		}

		answer = getchar();           //从输入流跳过空格及制表符获取一字符
		answer = tolower(answer);     //转换为小写字母
		while (cin.get() != '\n');    //忽略用户输入其他字母
		initResponse = false;
	} while (answer != 'c'&&answer != 'a');

	cout << "请输入要被替换的文本串：";    
	String strOld=strOld.Read(cin);    //旧串
	cout << "请输入新文本串：";        
	String strNew=strNew.Read(cin);    //新串

	for (int row = 1; row <= allLines; row++)
	{
		if (answer == 'c'&&row != curLineNo)
		{
			continue;
		}

		String strRow;                                     //行
		textBuffer.GetElem(row, strRow);                   //取出行
		int index = strRow.Index(strRow, strOld);          //在当前行查找文本串
		if (index != -1)
		{   //模式匹配成功
			String newLine;                                //新行
			newLine.Copy(newLine, strRow, index);          //复制指定文本前的串
			newLine.Concat(newLine, strNew);               //连接新文本串
			const char*oldLine = strRow.CStr();            //旧行
			newLine.Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
            //计算一个临时指针，指向紧跟在字符串后的字符，再将c风格串转换为String，连到newLine后面
			textBuffer.SetElem(row, newLine);              //设置当前行新串
		}
	}
}


void LineEditor::FindString()
//操作结果：从当前行或第一行开始查找指定文本
{
	char answer;                       // 用户回答字符   
	bool initResponse = true;          //初始回答

	//循环直到用户输入恰当地回答为止
	do
	{
		if (initResponse)
		{
			cout << "从当前行c（urrent）或第一行f（irst）开始：";
		}
		else
		{
			cout << "用c或f回答：";
		}

		answer = getchar();           //从输入流跳过空格及制表符获取一字符
		answer = tolower(answer);     //转换为小写字母
		while (cin.get() != '\n');    //忽略用户输入其他字母
		initResponse = false;
	} while (answer != 'c'&&answer != 'f');
	if (answer == 'f')curLineNo = 1;   //从第一行开始

	int index;
	cout << "输入被查找的文本串:";
	String searchString=searchString.Read(cin);  //输入查找文本串
	String curLine;
	textBuffer.GetElem(curLineNo, curLine);      //取出当前行
	while ((index = curLine.Index(curLine, searchString)) == -1)
	{
		if (curLineNo<allLines)
		{   //查找下一行
			curLineNo++;                               //下一行
			textBuffer.GetElem(curLineNo, curLine);    //取出下一行
		}
		else
		{  //已查找完所有行
			break;
		}
	}

	if (index == -1)
	{
		cout << "查找失败." << endl;
	}
	else
	{   //查找成功
		cout << curLineNo << "：" << curLine.CStr() << endl;
		//输出所找到行的行号及该行内容
	}
}

void LineEditor::TotalFile()
//操作结果：统计文件行数或字符数
{
	char answer;                       // 用户回答字符   
	bool initResponse = true;          //初始回答

	//循环直到用户输入恰当地回答为止
	do
	{
		if (initResponse)
		{
			cout << "总行数l(ines）或总字符数c(hars)";
		}
		else
		{
			cout << "用l或c回答：";
		}

		answer = getchar();           //从输入流跳过空格及制表符获取一字符
		answer = tolower(answer);     //转换为小写字母
		while (cin.get() != '\n');    //忽略用户输入其他字母
		initResponse = false;
	} while (answer != 'l'&&answer != 'c');

	if (answer == 'l')
		cout << "总行数为：" << allLines << endl;
	else
	{
		int count=0;
		String tmpLine;
		for (int i = 1; i <= allLines; i++)
		{
				textBuffer.GetElem(i, tmpLine);
				count += tmpLine.Length();
		}
		cout << "总字符数为：" << count << endl;
	}

}

void LineEditor::ReadFile(String fileName)
//操作结果：读入文本文件并显示文件内容
{
	textBuffer.Clear();           //清空缓冲区
	curLineNo = 0;
	allLines = 0;
	inFile.open(fileName.CStr(), ios::in);
	String tempLine;
	while (!inFile.eof())
	{
		tempLine = tempLine.Read(inFile);
		textBuffer.Insert(++allLines, tempLine);
		cout << tempLine.CStr() << endl;
		//输出文件内容
	}
	curLineNo = 1;               //设置当前行为文件第一行
	inFile.close();
}

void LineEditor::WriteFile()
//操作结果：写文本缓存到输出文件中
{
	if (textBuffer.Empty())
	{
		cout << "警告：文本缓冲区空" << endl;
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
//操作结果：运行文本编辑器
{
 	char userCommand;                        //用户命令
	String inFileName;                       //输入文件名
 	do
 	{
 		
		userCommand=getchar();               //从输入流跳过空格及制表符获取一字符
		userCommand=tolower(userCommand);    //转换为小写字母
		while(cin.get()!='\n');              //忽略用户输入其他字母
		
		switch(userCommand)

		{
			case'b':
				BeginLine();
				break; 
			case'c':
				if(textBuffer.Empty())  
				{
					cout<<"警告：文本缓冲区空"<<endl; 
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
					cout<<"警告：文本缓冲区空"<<endl; 
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
				cout << "有效命令：b(egin);c(hange);d(el);e(nd)" << endl
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
				cout<<"输入h获得帮助或输入有效命令字符：\n";	
		}		
	}while(userCommand!='q'); 	
} 