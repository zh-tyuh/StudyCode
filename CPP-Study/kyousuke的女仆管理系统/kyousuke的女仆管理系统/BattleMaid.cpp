#include "BattleMaid.h"

BattleMaid::BattleMaid(int id,string name,int PId)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_PId = PId;
}
BattleMaid::~BattleMaid() {};

void BattleMaid::showInfo()
{
	cout << "编号: " << this->m_Id
		<< "\t名称: " << this->m_name
		<< "\t职位: " << this->showPosi()
		<< "\t保证主人安全" << endl;
}

string BattleMaid::showPosi()
{
	return "战斗女仆";
}
