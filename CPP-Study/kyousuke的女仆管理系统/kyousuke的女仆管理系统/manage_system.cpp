#include "manage_system.h"

manageSystem::manageSystem() 
{
	//每次打开系统都要先将数据读入程序
	ifstream ifs;
	ifs.open(FILE1, ios::in);
	
	//1、文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化数据
		this->m_Num = 0;
		this->MaidArr = NULL;
		this->FileIsEmpty = true;

		//关闭构造函数
		ifs.close();
		return;
	}

	//2、文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		//初始化数据
		this->m_Num = 0;
		this->MaidArr = NULL;
		this->FileIsEmpty = true;
		
		//关闭构造函数
		ifs.close();
		return;
	}

	//3、文件存在不为空
	int num= this->Get_Num();
	this->m_Num=num;
	cout << "当前系统中共有" << num << "个女仆" << endl;
	this->MaidArr = new Maid*[num];
	this->Init();
	
}
manageSystem::~manageSystem()
{

}
void manageSystem::ExitSys() {
	cout << "玛塔 哦扣西库达赛伊马赛~" << endl;
	system("pause");
	exit(0);
};



//展示菜单
void manageSystem::showMenu()
{
	cout << "*************************************" << endl;
	cout << "*****  kyousuke的女仆管理系统  *******" << endl;
	cout << "*****    0、退出系统           *******" << endl;
	cout << "*****    1、显示女仆列表       *******" << endl;
	cout << "*****    2、添加女仆           *******" << endl;
	cout << "*****    3、删除女仆           *******" << endl;
	cout << "*****    4、修改女仆信息       *******" << endl;
	cout << "*****    5、查找女仆           *******" << endl;
	cout << "*****    6、为女仆排序         *******" << endl;
	cout << "*****    7、清空女仆名录       *******" << endl;
	cout << "*************************************" << endl;}

//添加女仆
void manageSystem::AddMaid()
{
	//1、计算系统中新的女仆数量
	int Addnum = 0;
	cout << "请输入添加女仆的数量：" << endl;
	cin >> Addnum;

	if (Addnum > 0) {
		int NewNum = this->m_Num + Addnum;

		//2、开辟新女仆数组
		Maid** NewMaidArr = new Maid * [NewNum];

		//3、将原女仆数组复制到新女仆数组
		if (this->MaidArr != NULL)
		{//判断原女仆数组是否为空
			for (int j = 0; j < this->m_Num; j++)
			{
				NewMaidArr[j] = this->MaidArr[j];
			}
		}

		int Id_arr[105] = {-1};//记录所有待添加的Id

		//4、添加新女仆
		for (int i = 0; i < Addnum; i++)
		{
			int Id;
			string name;
			int Pid;
			
			while (1) { //在这个循环中，continue表示重新输入Id，break表示Id输入完成，继续输入其他信息
				//用户输入ID
				a : cout << "请输入第" << i + 1 << "个女仆的Id:" << endl;
				cin >> Id;

				//1、记录已经添加过的Id,用于确定多次添加中ID不会重复
				bool is_AddRepeat = false;//用于标记在添加过程中是否重复
				for (int j = 0; j < i; j++)
				{
					if (Id_arr[j] == Id)
					{
						cout << "ID重复，请重新输入" << endl;
						is_AddRepeat = true;
					}
				}
				Id_arr[i] = Id;
				if (is_AddRepeat == true) continue;
				

				bool is_Repeat = false;
				//2、判断该Id是否和文件中的内容重复
				for (int i = 0; i < this->m_Num; i++)
				{
					if (this->MaidArr[i]->m_Id == Id)
					{
						cout << "ID重复，请重新输入哦~" << endl;
						is_Repeat = true;
					}
				}

				if (is_Repeat == false) break;
				else continue;
			}

			//输入其他信息
			cout << "请输入第" << i + 1 << "个女仆的名字:" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个女仆的职务:" << endl;
			cout << "1 家政女仆" << endl;
			cout << "2 战斗女仆" << endl;
			cout << "3 贴身女仆" << endl;
			cin >> Pid;

			Maid* maid = NULL;

			//判断并构造女仆对象添加到女仆数组
			switch (Pid)
			{
			case 1:
				maid = new HouseMaid(Id,name,Pid);
				break;
			case 2:
				maid = new BattleMaid(Id, name, Pid);
				break;
			case 3:
				maid = new PersonalMaid(Id, name, Pid);
				break;
			}
			NewMaidArr[this->m_Num + i] = maid;
		}
		
		//释放原空间
		Maid** TMaidArr = this->MaidArr;
		this->MaidArr = NewMaidArr;
		delete TMaidArr;

		//更新新的个数
		this->m_Num = NewNum;
		this->FileIsEmpty = false;

		//保存在文件中
		this->save();

		cout << "添加成功,按任意键继续~" << endl;
		system("pause");
	}

	else
	{
		cout << "输入错误，按任意键继续~" << endl;
		system("pause");
	}

}

//保存操作
void manageSystem::save()
{
	ofstream ofs;
	ofs.open(FILE1, ios::out);
	for (int i = 0; i < this->m_Num; i++)
	{
		ofs << this->MaidArr[i]->m_Id << " ";
		ofs << this->MaidArr[i]->m_name << " ";
		ofs<<this->MaidArr[i]->m_PId << endl;
	}

	ofs.close();
}

//获取当前系统中的女仆个数
int manageSystem::Get_Num()
{
	ifstream ifs;
	ifs.open(FILE1, ios::in);
	
	int num = 0;
	int id;
	string name;
	int pid;
	while (ifs >> id && ifs >> name && ifs >> pid)
	{
		num++;
	}
	
	ifs.close();
	return num;
}

//初始化，将文件中的女仆放在管理系统类中的女仆数组中
void manageSystem::Init()
{
	ifstream ifs;
	ifs.open(FILE1, ios::in);

	int id;
	string name;
	int pid;
	int index = 0;
	Maid* maid = NULL;//父类指针指向子类对象

	while (ifs >> id && ifs >> name && ifs >> pid)
	{	
		//创建子类对象，存放在女仆数组中
		switch (pid) {
		case 1:
			maid = new HouseMaid(id,name,pid);
			break;
		case 2:
			maid = new BattleMaid(id, name, pid);
			break;
		case 3:
			maid = new PersonalMaid(id, name, pid);
			break;
		}
		//存放在数组中
		this->MaidArr[index] = maid;
		
		index++;
	}

	ifs.close();
}


//显示女仆
void manageSystem::showMaid()
{
	
	if (this->FileIsEmpty == true)
	{
		cout << "主人，您当前没有收录任何女仆!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "主人，您一共收录了" << this->m_Num << "位女仆哦~" << endl;
		for (int i = 0; i < this->m_Num; i++)
		{
			this->MaidArr[i]->showInfo();
		}
	}
	system("pause");

}

//删除女仆
void manageSystem::Del_Maid()
{
	//判断文件是否为空
	if (this->FileIsEmpty == true)
	{
		cout << "您没有任何女仆，无法删除" << endl;
		system("pause");
		return;
	}
	else
	{
		int Del_ID;
		cout << "请输入您要删除的女仆ID:" << endl;
		cin >> Del_ID;

		//判断女仆是否存在
		if (this->isExist(Del_ID) == -1)
		{
			cout << "主人，您并没有收录该女仆哦~" << endl;
		}
		else
		{
			for (int i = isExist(Del_ID); i < this->m_Num; i++)
			{
				this->MaidArr[i] = this->MaidArr[i + 1];
			}
			this->m_Num--;
			this->save();
		}
		system("pause");
	}
}

//判断女仆是否存在，存在返回女仆数组下标，不存在返回-1
int manageSystem::isExist(int id)
{
	int temp = -1;
	for (int i = 0; i < this->m_Num; i++)
	{
		if (id == this->MaidArr[i]->m_Id)
		{
			temp = i;
		}	
	}
	return temp;
}


//修改女仆，因为修改女仆需要涉及到修改Id、name、PID，所以需要新建一个子类对象，将子类对象替换到女仆数组中
void manageSystem::Modify_Maid()
{
	//判断文件是否为空
	if (this->FileIsEmpty == true)
	{
		cout << "您当前没有任何女仆，无法修改" << endl;
		system("pause");
		return;
	}
	
	int id;
	while (1) { //continue表示重新输入，break表示继续进行修改
		cout << ":D 请输入您要修改的女仆ID :" << endl;
		cin >> id;
		//判断女仆是否存在
		if (this->isExist(id) == -1)
		{
			cout << ":c 主人您并没有收录该女仆请重新输入~" << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	
	//存在该女仆，先删除原女仆信息，然后加入新的信息
	int index = this->isExist(id);
	

	Maid *new_maid = NULL;
	int new_id;
	string new_name;
	int new_pid;
	//输入修改后的信息

	while (1) {//判断new_id是否与其他ID重复，但可以和自己id重复可以，continue是重新输入id，break是id输入完成
		cout << "请输入修改后的女仆的ID:" << endl;
		cin >> new_id;
		bool is_repeat = false;
		for (int i = 0; i < this->m_Num; i++)
		{
			if (new_id == this->MaidArr[i]->m_Id)
			{
				is_repeat = true;//new_id和其他id重复
				break;
			}
		}
		if (new_id == id) is_repeat = false;//新id与原id相同
		if (is_repeat == false) break;//没有重复，继续输入后面的信息
		else 
		{//重复
			cout << "该ID已经被其他女仆占用了o~，请重新输入uwu" << endl;
			continue; 
		}
	}

	cout << "请输入修改后的女仆的名字:" << endl;
	cin >> new_name;
	cout << "请输入修改后的女仆的PID:" << endl;
	cout << "1 家政女仆" << endl;
	cout << "2 战斗女仆" << endl;
	cout << "3 贴身女仆" << endl;
	cin >> new_pid;

	//将父类指针指向子类对象
	switch (new_pid)
	{
			case 1:
				new_maid = new HouseMaid(new_id, new_name, new_pid);
				break;
			case 2:
				new_maid = new BattleMaid(new_id, new_name, new_pid);
				break;
			case 3:
				new_maid = new PersonalMaid(new_id, new_name, new_pid);
				break;
	}
	
	//删除原女仆信息，将新对象保存在数组中和文件中
	delete this->MaidArr[index];
	this->MaidArr[index] = new_maid;
	this->save();
	system("pause");
}


//查找女仆   两种查找方式：根据id、根据姓名
void manageSystem::Find_Maid()
{
	//判断文件是否为空
	if (this->FileIsEmpty == true)
	{
		cout << "主人，您的女仆名录里没有收录任何女仆哦，无法进行查找" << endl;
		system("pause");
		return;
	}

	//进行查找
	int select;
a:	cout << "主人，请输入查找方式XD:" << endl;
	cout << "1 根据女仆ID查找" << endl;
	cout << "2 根据女仆姓名查找" << endl;
	cin >> select;

	if (select == 1)
	{//根据ID查找
		int id;
		cout << "请输入您要查找的女仆ID：" << endl;
		cin >> id;

		//遍历女仆数组
		bool is_suc1 = false;
		for (int i = 0; i < this->m_Num; i++)
		{
			if (id == this->MaidArr[i]->m_Id)
			{
				cout << "查找成功！下面是该女仆的信息:" << endl;
				this->MaidArr[i]->showInfo();
				is_suc1 = true;
			}
		}
		if (is_suc1 == false)
		{
			cout << "查找失败，主任好像没有收录该女仆哦:(" << endl;
		}
	}
	else if (select == 2)
	{//根据姓名查找
		string name;
		cout << "请输入您要查找的女仆姓名：" << endl;
		cin >> name;

		//查找
		int count = 0;//计数器，记录所有同名女仆的个数
		for (int i = 0; i < this->m_Num; i++)
		{
			if (name == this->MaidArr[i]->m_name)
			{
				cout << "查找成功，姓名为" << this->MaidArr[i]->m_name << "的女仆信息如下：" << endl;
				this->MaidArr[i]->showInfo();
				count++;
			}
		}
		if (count > 0)  cout << "共查找到" << count << "个女仆" << endl;
		else cout << "查找失败，主人好像并没有收录该女仆哦:(" << endl;
	}
	else
	{
		cout << "没有这个选项哦主人:p" << endl;
		goto a;
	}

	system("pause");
}





//清空女仆
void manageSystem::Clean_Maid()
{
	//判断文件是否为空
	if (this->FileIsEmpty == true)
	{
		cout << "主人，您的女仆名录里没有收录任何女仆哦，无法进行清空" << endl;
		system("pause");
		return;
	}

	//清空确认
	int select;
a:	cout << "主人，请在次确认您要清空女仆名录哦" << endl;
	cout << "1 我就是想要清空" << endl;
	cout << "2 我不小心点错了" << endl;
	cin >> select;

	if (select == 1)
	{//清空操作
		//删除文件重新创建
		ofstream ofs;
		ofs.open(FILE1, ios::trunc);
		

		//删除数组中所有Maid指针指向的对象 并将数组中的指针置空
		for (int i = 0; i < this->m_Num; i++)
		{
			delete this->MaidArr[i];
			this->MaidArr[i] = NULL;
		}
		
		//此时数组还占用空间，元素是几个空指针，所以要整个数组删除将数组指针置空
		delete[] this->MaidArr;
		this->MaidArr = NULL;
		
		//将其他数据初始化
		this->m_Num = 0;
		this->FileIsEmpty = true;

		ofs.close();

		cout << "好的，已为您清空完毕~" << endl;
	}
	else if (select == 2)
	{//取消清空
		return;
	}
	else
	{
		cout << "没有这个选项哦主人:p" << endl;
		goto a;
	}
	system("pause");
}


 