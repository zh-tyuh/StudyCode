#pragma once
#include"maid.h"

class HouseMaid:public Maid
{
public:
	HouseMaid(int id, string name,int PId);
	~HouseMaid();

	void showInfo();
	string showPosi();
};
