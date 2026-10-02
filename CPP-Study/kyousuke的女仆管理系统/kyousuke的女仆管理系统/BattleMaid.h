#pragma once
#include "maid.h"

class BattleMaid :public Maid
{
public:
	BattleMaid(int id, string name, int PId);
	~BattleMaid();

	void showInfo();
	string showPosi();

};
