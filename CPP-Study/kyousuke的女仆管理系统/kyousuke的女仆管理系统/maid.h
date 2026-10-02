#pragma once
#include<iostream>
#include<string>
using namespace std;

class Maid
{
public:

	//系统中女仆的两个行为：展示信息、根据编号获取职位
	virtual void showInfo() = 0;
	virtual string showPosi() = 0;

	//女仆的三个信息
	int m_Id;
	string m_name;
	int m_PId;
};




