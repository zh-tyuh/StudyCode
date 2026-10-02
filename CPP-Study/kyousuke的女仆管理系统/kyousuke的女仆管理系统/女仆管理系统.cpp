#include<iostream>
#include"manage_system.h"
#include"maid.h"
#include"HouseMaid.h"
#include"BattleMaid.h"
#include"PersonalMaid.h"
using namespace std;



int main()
{

	manageSystem ms;
	int option;
	while (1)
	{
		ms.showMenu();
		cout << "请输入您的选择:" << endl;
		cin >> option;
		switch (option)
		{
		case 0: //退出菜单
			ms.ExitSys();
			break;
		case 1: //显示女仆信息
			ms.showMaid();
			break;
		case 2://添加女仆
			ms.AddMaid();
			break;
		case 3://删除女仆
			ms.Del_Maid();
			break; 
		case 4://修改女仆信息
			ms.Modify_Maid();
			break; 
		case 5://查找女仆
			ms.Find_Maid();
			break; 
		case 6://为女仆排序
			break;
		case 7://清空女仆名录
			ms.Clean_Maid();
			break;
		default:
			break;
		}
		system("cls");
	}

	system("pause");
	return 0;

}






//选择什么样的数据结构存储信息？可以想到用数组来存储，但是是静态还是动态，因为
//存储的信息需要在不同的函数中用的到，所以选择动态存储
//但是数组要求使用同种数据类型表示，即需要用开辟Maid数组存储BattleMaid、PersonalMaid、HouseMaid不同的对象
//即Maid* md = new Maid[20],但是这里需要注意，抽象类无法实例化对象，但是可以用父类指针指向子类对象
//所以可以开辟Maid指针类数组进行存储，即new Maid*[20]=Maid**md