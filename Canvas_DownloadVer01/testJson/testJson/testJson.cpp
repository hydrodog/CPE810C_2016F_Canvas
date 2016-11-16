// testJson.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
//添加需要的头文件
#include "include/json/json.h"

using namespace std;

//链接需要的库文件
#ifdef _DEBUG
#pragma comment(lib,"lib_json_d.lib")
#else
#pragma comment(lib,"lib_json.lib")
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"测试json写入"<<endl;
	Json::Value jsonRoot;
	Json::Value jsonItem;
	jsonItem["item1"] = "第一个条目";
	jsonItem["item2"] = "第二个条目";
	jsonItem["item3"] = 3;
	jsonRoot.append(jsonItem);
	jsonItem.clear();//清除上面已经赋值的项
	jsonItem["First"]="1";
	jsonItem["Second"]=2;
	jsonItem["Third"]=3.0F;
	jsonRoot.append(jsonItem);
	cout<<jsonRoot.toStyledString()<<endl;

	cout<<"测试json写入到文件"<<endl;

	ofstream ofs;
	ofs.open("test1.json");
	ofs<<jsonRoot.toStyledString();
	ofs.close();

	cout<<"测试json读取"<<endl;
	string sJson = jsonRoot.toStyledString();
	jsonRoot.clear();
	Json::Reader jsonReader;
	if (!jsonReader.parse(sJson,jsonRoot))
	{
		return -1;
	}
	for (auto it = jsonRoot.begin();
		it!=jsonRoot.end();
		it++)
	{
		for (auto sit = it->begin();
			sit != it->end();
			sit++)
		{
			cout<<sit.key()<<"\t"<<sit.name()<<endl;
		}
	}
	cout<<"测试读取json文件"<<endl;
	ifstream ifs;
	ifs.open("test1.json");

	jsonRoot.clear();
	if (!jsonReader.parse(ifs, jsonRoot))
	{
		return -1;
	}
	ifs.close();
	for (auto it = jsonRoot.begin();
		it!=jsonRoot.end();
		it++)
	{
		for (auto sit = it->begin();
			sit != it->end();
			sit++)
		{
			cout<<sit.key()<<"\t"<<sit.name()<<endl;
		}
	}
	return 0;
}

