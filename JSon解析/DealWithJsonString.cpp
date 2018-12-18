#include "DwalWithJsonString.h"
#include <fstream>
#include <iomanip>
#include <string>

//�� strSourceFileName �ж�ȡ json��
// ���� ��
//		��ȡ���ļ���strSourceFileName , �������json��strSourceJsonString
// ��� :
//		-1 -- �����쳣
//		0  --  ��������
int ReadSourceJsonString(const string& strSourceFileName, string& strSourceJsonString)
{
	ifstream ifptrFile(strSourceFileName, ios::in);
	if (!ifptrFile)
	{
		cout << __FUNCTION__ << "  open  " << strSourceFileName << " failed!" << endl
			<< "����ִ�г����Ŀ¼�½�һ��  " << strSourceFileName << endl;

		return -1;
	}

	//char szFileBuffer[1024] = { "\0" };		//���ļ����棻
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
������ȡ��json��������˼·��
1.����json�� ��ʽ���ص㣬��json����{}�� ���ֶ��䣬 ÿ��{�����ɿ�Ŀ�ͷ����{���������,�����롣
2.����������{����һ�У�����һ��tab��������
3.json�����븳ֵ��һ���ʽ�ǣ�< ���������ơ�������ֵ>��<���������ơ�������ֵ>�����˫�����Ƿ����ƣ�ð���Ƿ��У����һ������ǰ�Ķ���ĩβ�Ķ����Ƿ��У����һ������ĩβ�����ж���

json���һ���ʽ�ǣ�
����:
{
< ���������ơ�������ֵ>,
<���������ơ�������ֵ>
}

���룺
strSourceJsonString -- ԭʼjson��
strTransferredJsonString -- ��������ַ���
�����
0  -- ��������
-1 -- �����쳣
*/
int TranferredJsonString(const string& strSourceJsonString, string &strTransferredJsonString)
{
	char szCursor;
	char szCursorNext;
	int iPos = 0;
	int iTabCursor = 0;			// ָʾtab �� { �������� ��СΪ0�� ����˵���쳣
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
				strInfor = "\nȱ��ƥ��� { \n";
				strTransferredJsonString.insert(iPos + 1, strInfor);
				return -1;
			}
			//����һ��
			strTransferredJsonString.insert(iPos - 1, "\n");
			strTransferredJsonString.insert(iPos - 1, iTabCursor, '\t');
			iMaxPos += 1 + iTabCursor;
			iPos += 1 + iTabCursor;
			//Ϊ֮����ַ�Ԥ����λ��
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
				strInfor = "\n, ���治ƥ�� \" ������ } ������ \n";
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
������õ�json �������ִ���ļ�ͬĿ¼�µ�"MyJsonAnalyse.txt"
���� ;
const std::string& strResFileNmae -- ת�������д����ļ�
strTransferredJsonString ת���õ�json ����
�����
0  -- д���ļ��ɹ�
-1 --  д��ʧ��
*/
int WriteBackToTXT(const std::string& strResFileNmae, const string&strTransferredJsonString)
{
	cout << "��� json�� :" << endl << strTransferredJsonString << endl;

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