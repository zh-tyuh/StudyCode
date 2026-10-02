#include"HouseMaid.h"

HouseMaid::HouseMaid(int id, string name, int PId)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_PId = PId;
}
HouseMaid::~HouseMaid() {}

void HouseMaid::showInfo()
{
		cout << "编号: " << this->m_Id
			<< "\t名称: " << this->m_name
			<< "\t职位: " << this->showPosi() 
			<<"\t照顾日常起居"<< endl;
}
	
string HouseMaid::showPosi()
{
	return "生活女仆";
}