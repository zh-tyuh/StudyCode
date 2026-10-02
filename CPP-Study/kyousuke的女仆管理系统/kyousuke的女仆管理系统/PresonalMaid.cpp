#include"PersonalMaid.h"

PersonalMaid::PersonalMaid(int id,string name,int PId)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_PId = PId;
}

PersonalMaid::~PersonalMaid(){}

void PersonalMaid::showInfo()
{
	cout << "编号: " << this->m_Id
		<< "\t名称: " << this->m_name
		<< "\t职位: " << this->showPosi()
		<< "\t贴身陪伴主人" << endl;
}

string PersonalMaid::showPosi()
{
	return "贴身女仆";
}

