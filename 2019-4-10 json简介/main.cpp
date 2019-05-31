#include"json\json.h"
#include<iostream>
#include<string>
using namespace std;

//����jsoncpp ֧�ֵĶ�������
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
	string tmpstr_name = root["name"].asString();//���ַ������Խ�json�ļ�ֵ��ת�����ַ���
	cout << tmpstr << endl;
	cout << tmpstr_name.length() << endl;
	cout << tmpstr_name + " is online " << endl;

	cout << root["name"]<<tmpstr.c_str() << endl;//.c_str()����Ҳ���Խ�Json�ַ���ת��Ϊchar* ���ͣ�һ���Ժ�����Ϣ����ͨ�����ַ�ʽ

	//string tmpstr_asString = root.asCString();//��������
	
	//�ַ�����ʽת��Ϊjson���� ͨ��reader��charת��Ϊjson����root1
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