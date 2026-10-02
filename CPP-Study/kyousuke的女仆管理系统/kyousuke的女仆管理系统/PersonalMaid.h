#pragma once
#include"maid.h"

class PersonalMaid:public Maid
{
public:
	PersonalMaid(int id,string name,int PId);
	~PersonalMaid();

	void showInfo();
	string showPosi();
};

