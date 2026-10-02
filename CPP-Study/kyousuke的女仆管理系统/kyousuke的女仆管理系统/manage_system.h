#pragma once
#include<iostream>
using namespace std;
#include"maid.h"
#include"HouseMaid.h"
#include"BattleMaid.h"
#include"PersonalMaid.h"
#include<fstream>
#define FILE1 "maidfile.txt"

class manageSystem
{
public:
	manageSystem();
	~manageSystem();
	void showMenu();
	void ExitSys();
	
	int m_Num;//记录当前系统中女仆的数量
	Maid** MaidArr; //指向当前女仆系统数组的指针
	//添加女仆
	void AddMaid();

	//保存操作，将新添加的女仆存储在文件中
	void save();
	
	//读取文件
	bool FileIsEmpty;
	int Get_Num();//获取当前文件中女仆的个数
	void Init();//对女仆数组进行初始化（将文件中的女仆放在女仆数组中）

	//显示女仆
	void showMaid();

	//删除女仆
	void Del_Maid();
	//判断女仆是否存在，存在返回女仆数组下标，不存在返回-1
	int isExist(int id);
	
	//修改女仆
	void Modify_Maid();

	//查找女仆
	void Find_Maid();

	//为女仆排序

	//清空女仆
	void Clean_Maid();
	
};