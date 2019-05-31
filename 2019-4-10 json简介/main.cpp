#include"json\json.h"
#include<iostream>
#include<string>
using namespace std;

//定义jsoncpp 支持的对象类型
enum Type
{
	nullValue = 0, ///< 'null' value
	intValue,      ///< signed integer value
	uintValue,     ///< unsigned integer value
	realValue,     ///< double value
	stringValue,   ///< UTF-8 string value
	booleanValue,  ///< bool value
	arrayValue,    ///< array value (ordered list)
	objectValue    ///< object value (collection of name/value pairs).
};

int main()
{
	Json::Value root;
	root["type"] = nullValue;
	root["name"] = "Xin Ma";
	root["pwd"] = "123456";
	

	string tmpstr = root.toStyledString();
	string tmpstr_name = root["name"].asString();//这种方法可以将json的键值对转换成字符串
	cout << tmpstr << endl;
	cout << tmpstr_name.length() << endl;
	cout << tmpstr_name + " is online " << endl;

	cout << root["name"]<<tmpstr.c_str() << endl;//.c_str()方法也可以将Json字符串转化为char* 类型，一般以后发送消息都是通过这种方式

	//string tmpstr_asString = root.asCString();//这样不行
	
	//字符串方式转化为json对象 通过reader将char转化为json对象root1
	const char* str = "{ \"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\" }";
	Json::Reader reader;
	Json::Value root1;
	reader.parse(str, root1);
	string tmpstr1 = root1.toStyledString();
	cout << tmpstr1 << endl;

	//char buff[1024] = { 0 };
	//(buff, strlen(tmpstr.c_str()) + 1, tmp.c_str());
	return 0;
}