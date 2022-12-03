#include "1_251298_杨滕超.h"


/***************************************************************************
  函数名称：init
  功    能：初始化考生报名系统类
  输入参数：
  返 回 值：
  说    明：可以选择通过手动输入初始化，也可以选择从文件中读取初始化
***************************************************************************/
bool StudentSystem::ini()
{
	int cnt = 0;
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请选择初始化方法" << endl;
	cout << "1.从文件中读取" << endl;
	cout << "2.手动输入" << endl;
	int op = 0;
	while (1)
	{
		cin >> op;
		if (cin.fail() || !(op == 1 || op == 2))
		{
			cout << "输入有误，请重新输入!" << endl;
			cin.ignore(65536, '\n');
			cin.clear();
		}
		else
			break;
	}
	//从文件中读取
	if (op == 1)
	{
		String fileName;
		cout << "请输入文件名称（如: Stu)" << endl;
		cin >> fileName;
		if (fileName.length() == 0)
		{
			fileName = "studentData.txt";
		}

		fileName += ".txt";//加上文件名后缀
		ifstream file(fileName.c_str(), ios::in);

		if (!file.is_open())
		{
			cerr << "文件打开失败" << endl;
			//exit(1);
			return false;
		}
		Stu temp;
		while (file >> temp)
			data.emplace_back(temp);

		file.close();
		show();
		return true;//打开文件成功
	}
	cout << "请输入考生人数" << endl;
	//正确输入才退出循环
	while (1)
	{
		cin >> cnt;
		if (cin.fail() || cnt < 0)
		{
			cout << "请输入正整数作为考生人数!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else//正确输入
			break;
	}
	if (cnt == 0)//一开始不想有学生
		return true;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
	Stu temp;
	for (int i = 0; i < cnt; ++i)
	{
		cin >> temp;
		//考号已经存在，Search()找不到则返回NULL
		if (mySearch(temp) != NULL)
		{
			cout << "数据中已存在该考生!" << endl;
		}
		else
		{
			insertProperly(temp);
		}
	}
	show();
	return true;
}

/***************************************************************************
  函数名称：search
  功    能：通过用户输入的考生考号，查找考生信息，并打印出来
  输入参数：
  返 回 值：
  说    明：具有查找失败的判断输出
***************************************************************************/
void StudentSystem::search()
{
	if (data.empty())
	{
		cout << "考生信息系统中暂无数据，不能查找" << endl;
		return;
	}
	cout << "请输入要查找的考生的考号: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);
	//如果找不到
	if (tempIter == NULL)
	{
		cout << "不存在考号为" << num << "的考生！" << endl << endl;
	}
	else
	{
		cout << "查找信息如下: " << endl;
		printf("考号\t   姓名\t\t性别\t   年龄\t   报考类别\n");
		cout << *tempIter << endl << endl;
	}
}

/***************************************************************************
  函数名称：remove
  功    能：通过用户输入的考生考号，删除系统中相应的考生信息
  输入参数：
  返 回 值：
  说    明：注意到若系统中不存在输入考号的考生，则会输出相关错误提示
***************************************************************************/
void StudentSystem::remove()
{
	if (data.empty())
	{
		cout << "考生信息系统中暂无数据，不能删除" << endl;
		return;
	}
	cout << "请输入要删除的考生的考号: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);
	if (tempIter == NULL)
	{
		cout << "不存在考号为" << num << "的考生！" << endl << endl;
	}
	else
	{
		cout << "你删除的考生的信息是: ";
		cout << *tempIter << endl << endl;
		data.remove(tempIter);
	}
}

/***************************************************************************
  函数名称：insert
  功    能：用户输入插入位置与考生信息，将考生信息插入考生系统
  输入参数：
  返 回 值：
  说    明：当用户输入位置非法时候给出相关输入错误提示
			输入考生信息出现考号重复的情况给出相应提示
***************************************************************************/
void StudentSystem::insert()
{
	cout << "请输入你要插入的考生的位置: ";
	int loc = 0;
	int Size = data.size();
	while (1)
	{
		cin >> loc;
		if (cin.fail() || loc < 0 || loc > Size)
		{
			cout << "请输入正确位置!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else//正确输入
			break;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
	Stu temp;

	cin >> temp;
	//找不到则返回NULL
	auto tempIter = mySearch(temp);
	//获得插入位置
	List<Stu>::list_iterator iter = data.begin();
	for (int i = 0; i < loc; ++i)
		++iter;
	//如果没有考生
	if (tempIter == NULL)
	{
		//内部链表0 - Size - 1
		if (loc == Size)
			data.emplace_back(temp);
		else
			data.insert(iter, temp);
	}
	else
	{
		cout << "数据中已存在该考生!不能再次插入!" << endl << endl;
	}

}

/***************************************************************************
  函数名称：insertProperly
  功    能：将一个考生信息按照考号大小插入系统，使得系统中考号按升序排列
  输入参数：Stu& 学生类的引用
  返 回 值：
  说    明：
***************************************************************************/
void StudentSystem::insertProperly(Stu& s)
{
	int Size = data.size();
	if (Size == 0)//系统里面没有信息
	{
		data.emplace_back(s);
		return;
	}
	else
	{
		bool isInserted = false;
		//Stu temp;
		//找到第一个比s.num大的，插入其前面
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			//temp = *it;
			if (strCmp(s.num, it->num) < 0)
			{
				data.insert(it, s);
				isInserted = true;
				break;
			}
		}

		//考号最大的，循环没找到插入位置，插入最后一个
		if (isInserted == false)
			data.emplace_back(s);
	}
}

/***************************************************************************
  函数名称：to_be_continue
  功    能：程序结束后等待下一次输入再退出cmd窗口
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void StudentSystem::to_be_continue()
{
	cout << endl << "回车键结束" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}

/***************************************************************************
  函数名称：show
  功    能：以列表的形式展示系统中的每项考生信息
  输入参数：
  返 回 值：
  说    明：注意到若考生系统无信息，应输出相关提示
***************************************************************************/
void StudentSystem::show()
{
	printf("\n考号\t   姓名\t\t性别\t   年龄\t   报考类别\n");
	if (data.empty())
	{
		cout << "考生信息系统中暂无数据" << endl << endl;
	}
	else
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			cout << *it << endl;
		}
	}
}

/***************************************************************************
  函数名称：change
  功    能：根据用户输入的考号，修改系统中考生的信息
  输入参数：
  返 回 值：
  说    明：若输入考号不存在于系统中，输出相关提示
			修改后的考生信息的考号应与修改前的保持一致
***************************************************************************/
void StudentSystem::change()
{
	if (data.empty())
	{
		cout << "考生信息系统中暂无数据，不能修改" << endl;
		return;
	}
	cout << "请输入要修改的考生的考号: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);

	if (tempIter == NULL)
	{
		cout << "不存在考号为" << num << "的考生！" << endl << endl;
	}
	else
	{
		while (1)
		{
			cout << "请依次重新输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
			cin >> *tempIter;
			if (tempIter->num == num)
				break;
			else
			{
				cout << "考号不可更改，请重新输入" << endl;
				cin.clear();
				cin.ignore(65536, '\n');
			}
		}
	}
}

/***************************************************************************
  函数名称：save
  功    能：将系统中的考生信息保存入用户输入的文件中
  输入参数：
  返 回 值：
  说    明：需要判断文件打开是否成功
***************************************************************************/
void StudentSystem::save()
{
	int Size = data.size();
	if (Size == 0)
	{
		cout << "考生信息系统中暂无数据，无需保存" << endl;
		return;
	}
	String fileName;
	cout << "请输入文件名: （如：Stu)";
	cin >> fileName;
	if (cin.fail())
	{
		cout << "非法文件名，数据将储存入studentData.txt" << endl;
		fileName = "studentData.txt";
	}
	else if (fileName == "0")
	{
		cout << "数据将储存入studentData.txt" << endl;
		fileName = "studentData.txt";
	}
	else
	{
		fileName += ".txt";
	}

	ofstream file(fileName.c_str(), ios::out);
	if (!file)
	{
		cerr << "文件打开失败" << endl;
		exit(0);
	}
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		file << it->num << ' ' << it->name << ' ' << it->gender
			<< ' ' << it->age << ' ' << it->type << endl;
	}

	cout << "数据储存完成!" << endl;
	file.close();
}

/***************************************************************************
  函数名称：statictics
  功    能：统计系统中考生男女人数信息和各个专业的人数信息
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void StudentSystem::statistics()
{
	if (data.empty())
	{
		cout << "考生信息系统中暂无数据，无需统计" << endl;
		return;
	}
	Map<String, int> gender;
	Map<String, int> type;
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		++gender[it->gender];
		++type[it->type];
	}
	cout << "\n性别统计: " << endl;
	for (auto it = gender.begin(); it != gender.end(); ++it)
	{
		cout.width(10);
		cout << it->first << it->second << endl;
	}
	cout << endl;
	cout << "专业统计: " << endl;
	for (auto it = type.begin(); it != type.end(); ++it)
	{
		cout.width(10);
		cout << it->first << it->second << endl;
	}
}

/***************************************************************************
  函数名称：mySearch
  功    能：查找系统中是否存在该考生
  输入参数：const Stu& s学生类的引用
  返 回 值：链表的迭代器
  说    明：若查找失败返回空指针NULL
***************************************************************************/
List<Stu>::list_iterator StudentSystem::mySearch(const Stu& s)
{
	int Size = data.size();
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		if (*it == s)
			return it;
	}
	return NULL;
}

/***************************************************************************
  函数名称：mySearch
  功    能：通过考号查找考生
  输入参数：const String& num，考生考号
  返 回 值：链表迭代器
  说    明：若查找失败返回空指针NULL
***************************************************************************/
List<Stu>::list_iterator StudentSystem::mySearch(const String& num)
{
	int Size = data.size();
	for (auto it = data.begin(); it != data.end(); ++it)
		if (it->num == num)
			return it;

	return NULL;
}

int main() {
	StudentSystem stuSys;
	if (stuSys.ini())//如果文件打开成功or输入成功
	{
		String op;
		bool loop = true;
		bool failOp;
		while (loop)
		{
			cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为"
				"统计，6为保存数据，0为退出系统）\n";
			cin >> op;
			failOp = false;
			switch (op[0])
			{
				case '0':
					loop = false;
					failOp = true;
					break;
				case '1':
					stuSys.insert();
					break;
				case '2':
					stuSys.remove();
					break;
				case '3':
					stuSys.search();
					break;
				case '4':
					stuSys.change();
					break;
				case '5':
					stuSys.statistics();
					break;
				case '6':
					stuSys.save();
					break;
				default:
					failOp = true;
					cin.ignore(65536, '\n');
					cin.clear();
					cout << "非法操作，请重新输入" << endl;
					cout << "温馨提示：1为插入，2为删除，3为查找，4为修改，5为"
						"统计，6为保存数据，0为退出系统" << endl;
					break;
			}
			if (stuSys.size() < 10 && failOp == false)
				stuSys.show();
			if (stuSys.size() && failOp == false)//有数据才显示有多少条
				cout << "考生信息系统现共有" << stuSys.size() << "条数据" << endl;
		}//end of while
	}//end of if

	stuSys.to_be_continue();
} 
