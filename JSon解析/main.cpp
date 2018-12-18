#include "DwalWithJsonString.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	//��ȡjson��
	string strSourceFileName = "MyJsonSource.txt";
	std::string strSource= "";
	int iRes = ReadSourceJsonString(strSourceFileName, strSource);
	if (iRes)
	{
		std::cout << "��ȡ�ļ� ��" << strSourceFileName 
			<< " ���� �����Ƿ���ڸ��ļ���" << std::endl;
		exit(-1);
	}

	//ת��Astyle��ʽ
	std::string strTranfered = "";
	iRes = TranferredJsonString(strSource, strTranfered);
	if (iRes)
	{
		std::cout << "ת�����̳��� " << std::endl;
	}

	//д�ļ�
	iRes = WriteBackToTXT(strSourceFileName,strTranfered);
	if (iRes)
	{
		std::cout << "ת�����д���ļ��� " << strSourceFileName 
			<< " ����,�����ļ��Ƿ������򿪣�" << std::endl;
			exit(-1);
	}

	return 0;
}