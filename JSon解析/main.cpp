#include "DwalWithJsonString.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	//读取json串
	string strSourceFileName = "MyJsonSource.txt";
	std::string strSource= "";
	int iRes = ReadSourceJsonString(strSourceFileName, strSource);
	if (iRes)
	{
		std::cout << "读取文件 ：" << strSourceFileName 
			<< " 出错， 请检查是否存在该文件！" << std::endl;
		exit(-1);
	}

	//转换Astyle格式
	std::string strTranfered = "";
	iRes = TranferredJsonString(strSource, strTranfered);
	if (iRes)
	{
		std::cout << "转换过程出错 " << std::endl;
	}

	//写文件
	iRes = WriteBackToTXT(strSourceFileName,strTranfered);
	if (iRes)
	{
		std::cout << "转换结果写入文件： " << strSourceFileName 
			<< " 错误,请检查文件是否正常打开！" << std::endl;
			exit(-1);
	}

	return 0;
}