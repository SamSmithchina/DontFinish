#include "DwalWithJsonString.h"
#include <fstream>
#include <iomanip>
#include <string>

//从 strSourceFileName 中读取 json串
// 输入 ：
//		读取的文件名strSourceFileName , 待输出的json串strSourceJsonString
// 输出 :
//		-1 -- 处理异常
//		0  --  处理正常
int ReadSourceJsonString(const string& strSourceFileName, string& strSourceJsonString)
{
	ifstream ifptrFile(strSourceFileName, ios::in);
	if (!ifptrFile)
	{
		cout << __FUNCTION__ << "  open  " << strSourceFileName << " failed!" << endl
			<< "请在执行程序的目录下建一个  " << strSourceFileName << endl;

		return -1;
	}

	//char szFileBuffer[1024] = { "\0" };		//读文件缓存；
	try
	{
		while (!ifptrFile.eof())
		{
			getline(ifptrFile, strSourceJsonString);
		}
	}
	catch (exception& e)
	{
		throw(e);
		cout << __FUNCTION__ << "  read  " << strSourceFileName << " failed!" << endl;
		return -1;
	}

	return 0;
}


/*
解析获取的json串，处理思路：
1.考虑json串 格式的特点，将json串按{}块 划分段落， 每个{解析成块的开头，，{后输出换行,与块对齐。
2.块中内容在{的下一行，且有一个tab的缩进；
3.json对象与赋值的一般格式是：< “对象名称”：对象赋值>，<“对象名称”：对象赋值>。检查双引号是否完善，冒号是否有，最后一个对象前的对象末尾的逗号是否有，最后一个对象末尾不改有逗号

json块的一般格式是：
块名:
{
< “对象名称”：对象赋值>,
<“对象名称”：对象赋值>
}

输入：
strSourceJsonString -- 原始json串
strTransferredJsonString -- 解析后的字符串
输出：
0  -- 处理正常
-1 -- 处理异常
*/
int TranferredJsonString(const string& strSourceJsonString, string &strTransferredJsonString)
{
	char szCursor;
	char szCursorNext;
	int iPos = 0;
	int iTabCursor = 0;			// 指示tab 和 { 的数量， 最小为0， 负数说明异常
	int iMaxPos = strSourceJsonString.length() - 1;
	int  iQuotParity = 0;
	string strInfor;

	strTransferredJsonString = strSourceJsonString;
	for (iPos = 0; iPos < iMaxPos; ++iPos)
	{
		szCursor = strSourceJsonString[0];
		switch (szCursor)
		{
		case '{':
			++iPos;
			strTransferredJsonString.insert(iPos, "\n");
			strTransferredJsonString.insert(iPos, iTabCursor, '\t');
			++iMaxPos;
			iTabCursor += 1 + iTabCursor;
			break;
		case '}':
			if (0 == iTabCursor)
			{
				strInfor = "\n缺少匹配的 { \n";
				strTransferredJsonString.insert(iPos + 1, strInfor);
				return -1;
			}
			//换下一行
			strTransferredJsonString.insert(iPos - 1, "\n");
			strTransferredJsonString.insert(iPos - 1, iTabCursor, '\t');
			iMaxPos += 1 + iTabCursor;
			iPos += 1 + iTabCursor;
			//为之后的字符预处理位置
			--iTabCursor;
			strTransferredJsonString.insert(iPos + 1, "\n");
			strTransferredJsonString.insert(iPos + 1, iTabCursor, '\t');
			iPos += 2 + iTabCursor;
			iMaxPos += 1 + iTabCursor;
			break;
		case '\b':
			strTransferredJsonString.replace(iPos, 1, "\\");
			++iPos;
			strTransferredJsonString.insert(iPos, "\\\b");
			iPos += 2;
			iMaxPos += 2;
			break;
		case '\"':
			++iQuotParity;
			break;
		case  ':':
			break;
		case ',':
			szCursorNext = strTransferredJsonString[iPos + 1];
			if ('\"' != szCursor || '}' != szCursor)
			{
				strInfor = "\n, 后面不匹配 \" 或者是 } ，错误 \n";
				strTransferredJsonString.insert(iPos + 1, strInfor);
				return -1;
			}
			++iPos;
			strTransferredJsonString.insert(iPos, "\n");
			strTransferredJsonString.insert(iPos, iTabCursor, '\t');
			break;
		default:
			break;
		} // end switch(szCursor)

	}
	return 0;

}

/*
将处理好的json 串输出到执行文件同目录下的"MyJsonAnalyse.txt"
输入 ;
const std::string& strResFileNmae -- 转换结果待写入的文件
strTransferredJsonString 转换好的json 串；
输出：
0  -- 写入文件成功
-1 --  写入失败
*/
int WriteBackToTXT(const std::string& strResFileNmae, const string&strTransferredJsonString)
{
	cout << "输出 json串 :" << endl << strTransferredJsonString << endl;

	ofstream ofptrFile(strResFileNmae, ios::out || ios::trunc);
	if (!ofptrFile)
	{
		cout << "open MyJsonAnalyse.txt failed !\n" << endl;
		return -1;
	}

	try
	{
		ofptrFile << strTransferredJsonString;
	}
	catch (exception& e)
	{
		throw(e);
		cout << "write MyJsonAnalyse.txt failed ! " << endl;
		return -1;
	}
	return 0;
}