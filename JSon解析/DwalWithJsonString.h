
#ifndef __JSONINCLUDE_H__
#define __JSONINCLUDE_H__

//#include "jsoncpp-0.5.0/include/json/json.h"
//#include "jsoncpp-0.5.0/src/lib_json/json_writer.cpp"
//#include "jsoncpp-0.5.0/src/lib_json/json_value.cpp"
//#include "jsoncpp-0.5.0/src/lib_json/json_reader.cpp"

#include <iostream>
#include <string>
using namespace std;


//�� strSourceFileName �ж�ȡ json��
// ���� ��
//		��ȡ���ļ���strSourceFileName , �������json��strSourceJsonString
// ��� :
//		-1 -- �����쳣
//		0  --  ��������
int ReadSourceJsonString(const string& strSourceFileName, string& strSourceJsonString);

/*
������ȡ��json��������˼·��
1.����json�� ��ʽ���ص㣬��json����{}�� ���ֶ��䣬 ÿ��{�����ɿ�Ŀ�ͷ��{ǰ�����������һ�У�{�����룬{��������С�
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
int TranferredJsonString(const string& strSourceJsonString, string &strTransferredJsonString);

/*
������õ�json �������ִ���ļ�ͬĿ¼�µ�"MyJsonAnalyse.txt"
���� ;
const std::string& strResFileNmae -- ת�������д����ļ�
strTransferredJsonString ת���õ�json ����
�����
0  -- д���ļ��ɹ�
-1 --  д��ʧ��
*/
int WriteBackToTXT(const std::string& strResFileNmae, const string&strTransferredJsonString);
#endif