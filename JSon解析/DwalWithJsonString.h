
#ifndef __JSONINCLUDE_H__
#define __JSONINCLUDE_H__

//#include "jsoncpp-0.5.0/include/json/json.h"
//#include "jsoncpp-0.5.0/src/lib_json/json_writer.cpp"
//#include "jsoncpp-0.5.0/src/lib_json/json_value.cpp"
//#include "jsoncpp-0.5.0/src/lib_json/json_reader.cpp"

#include <iostream>
#include <string>
using namespace std;


//从 strSourceFileName 中读取 json串
// 输入 ：
//		读取的文件名strSourceFileName , 待输出的json串strSourceJsonString
// 输出 :
//		-1 -- 处理异常
//		0  --  处理正常
int ReadSourceJsonString(const string& strSourceFileName, string& strSourceJsonString);

/*
解析获取的json串，处理思路：
1.考虑json串 格式的特点，将json串按{}块 划分段落， 每个{解析成块的开头，{前换行输出到下一行，{与块对齐，{后输出换行。
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
int TranferredJsonString(const string& strSourceJsonString, string &strTransferredJsonString);

/*
将处理好的json 串输出到执行文件同目录下的"MyJsonAnalyse.txt"
输入 ;
const std::string& strResFileNmae -- 转换结果待写入的文件
strTransferredJsonString 转换好的json 串；
输出：
0  -- 写入文件成功
-1 --  写入失败
*/
int WriteBackToTXT(const std::string& strResFileNmae, const string&strTransferredJsonString);
#endif