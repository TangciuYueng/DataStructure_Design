#include "6_2151298_杨滕超.h"

/***************************************************************************
  函数名称：familyTree
  功    能：建立家谱祖先
  输入参数：
  返 回 值：
  说    明：家谱类的构造函数
***************************************************************************/
familyTree::familyTree()
{
	cout << "首先建立一个家谱!" << endl;
	cout << "请输入祖先的姓名: ";
	String tempId;
	cin >> tempId;
	root = new(nothrow) familyTreeNode(tempId);
	if (root == NULL)
	{
		cerr << "申请空间失败" << endl;
		exit(1);
	}
	Size = 1;
	//插入姓名地址键值对
	ht.insert(make_pair(tempId, root));
}

/***************************************************************************
  函数名称：search
  功    能：在家谱中利用姓名id搜索得到该成员的结点
  输入参数：String& id, familyTreeNode* cur，要搜索的的姓名，当前搜索的结点
  返 回 值：familyTreeNode* 返回需要搜索的的结点地址
  说    明：若搜索成功返回相应结点信息，否则返回空指针
***************************************************************************/
familyTreeNode* familyTree::search(String& id, familyTreeNode* cur)
{
	//递归结束条件
	if (cur == nullptr)
		return nullptr;
	if (cur->id == id)
		return cur;
	//向子树寻找
	familyTreeNode* temp = nullptr;
	for (int i = 0; i < cur->children.size(); ++i)
	{
		temp = search(id, cur->children[i]);
		if (temp)//temp不为空
			break;
	}
	return temp;
}

/***************************************************************************
  函数名称：_search
  功    能：在家谱中利用姓名id搜索得到该成员的结点
  输入参数：String& id，要搜索的的姓名
  返 回 值：familyTreeNode* 返回需要搜索的的结点地址
  说    明：通过哈希表搜索，若搜索成功返回相应结点信息，否则返回空指针
***************************************************************************/
familyTreeNode* familyTree::_search(String& id)
{
	//通过哈希表寻找返回 id, 结点地址 键值对
	auto res = ht.find(id);
	//如果找到，返回的地址非空
	if (res)
		return res->kv.second;
	//找不到返回空地址
	return NULL;
}

/***************************************************************************
  函数名称：buildfamily
  功    能：根据用户输入的成员姓名，子女数量和子女姓名，对其建立家庭
  输入参数：
  返 回 值：
  说    明：这里需要判断家谱中是否存在该成员，存在才能建立家庭，
			否则输出错误提示
			判断输入子女数量是否合法
			判断子女的姓名是否与家谱中已有成员姓名重复，若重复则输出提示重新输入
***************************************************************************/
void familyTree::buildFamily()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "请输入要建立家庭的人的姓名: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "家谱中没有这个人，请重新输入!" << endl;
			cin.ignore(65536, '\n');
		}
		else if (!fa->children.empty())
		{
			cout << tempId << "已经建立过家庭，请重新输入" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	int childNum = 0;
	cout << "请输入" << tempId << "的儿女个数: ";
	while (1)
	{
		cin >> childNum;
		if (cin.fail() || childNum <= 0)
		{
			cout << "请正确输入一个正整数!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	cout << "请依次输入" << tempId << "的儿女的姓名: ";
	String childId;
	for (int i = 0; i < childNum; ++i)
	{
		cin >> childId;
		//auto temp = search(childId, root);
		auto temp = _search(childId);
		if (temp)//找到了
		{
			cout << "请不要与家谱已有成员重名！请重新输入" << endl;
			--i;
		}
		else//没有重名就加入家族树
		{
			familyTreeNode* child = new(nothrow) familyTreeNode(childId);
			if (child == NULL)
			{
				cerr << "申请空间失败" << endl;
				exit(1);
			}
			fa->children.emplace_back(child);
			ht.insert(make_pair(childId, child));
		}
	}
	//更新结点数量
	Size += childNum;
}

/***************************************************************************
  函数名称：addChild
  功    能：根据用户输入的成员姓名对其添加一个子女
  输入参数：
  返 回 值：
  说    明：需要判断家谱中是否存在输入成员
			判断添加的子女的姓名是否与家谱中已有成员姓名重复，若重复则输出提示重新输入
***************************************************************************/
void familyTree::addChild()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "请输入要添加儿子（或女儿）的人的姓名: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "家谱中没有这个人，请重新输入!" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	String childId;
	cout << "请输入" << tempId << "新添加的儿子（或女儿）的姓名: ";
	while (1)
	{
		cin >> childId;
		//auto temp = search(childId, root);
		auto temp = _search(childId);
		if (temp)//找到了
			cout << "请不要与家谱已有成员重名！请重新输入" << endl;
		else
			break;
	}

	familyTreeNode* child = new(nothrow) familyTreeNode(childId);
	if (child == NULL)
	{
		cerr << "申请空间失败" << endl;
		exit(1);
	}
	fa->children.emplace_back(child);//此时还不能释放空间，否则访问不到
	++Size;//更新结点数量
	ht.insert(make_pair(childId, child));
}

/***************************************************************************
  函数名称：changeId
  功    能：修改用户输入的成员姓名的姓名
  输入参数：
  返 回 值：
  说    明：需要判断家谱中是否存在输入成员
			判断修改后的姓名是否与家谱中已有成员姓名重复，若重复则输出提示重新输入
***************************************************************************/
void familyTree::changeId()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "请输入要更改姓名的人的目前姓名: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "家谱中没有这个人，请重新输入!" << endl;
			cin.ignore(65536, '\n');
		}

		else
			break;
	}
	String newId;
	cout << "请输入更改后的姓名: ";
	while (1)
	{
		cin >> newId;
		//判断新名字是否与家族树已有成员重名
		auto res = _search(newId);
		if (res)//有重名
			cout << "请不要与家谱已有成员重名！请重新输入" << endl;
		else
			break;
	}
	ht.erase(fa->id);
	fa->id = newId;
	ht.insert(make_pair(fa->id, fa));
	cout << tempId << "已更名为" << newId << endl;
}

/***************************************************************************
  函数名称：removeChildren
  功    能：根据用户输入的成员姓名，删除其所有后代
  输入参数：
  返 回 值：
  说    明：需要判断家谱中是否存在输入成员
			需要删除所有后代，否则会造成空间泄露
***************************************************************************/
void familyTree::removeChildren()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "请输入要解散家庭的人的姓名: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "家谱中没有这个人，请重新输入!" << endl;
			cin.ignore(65536, '\n');
		}
		else if (fa->children.empty())
		{
			cout << tempId << "该人家庭尚未建立，请重新输入" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	cout << "要解散家庭的人是: " << tempId << endl;
	_removeChildren(fa);
}

/***************************************************************************
  函数名称：removeChildren
  功    能：删除所有后代的辅助函数递归方法
  输入参数：familyTreeNode* cur，当前需要删除的结点
  返 回 值：
  说    明：首先检查cur是否还存在子女，若存在首先删除递归删除子女，没有子女后
			再进行cur的删除
***************************************************************************/
void familyTree::removeChildren(familyTreeNode* cur)
{
	//检查所有子女是否都没有子女，有 进行递归， 都没有就删除cur->children
	for (int i = 0; i < cur->children.size(); ++i)
	{
		if (!cur->children[i]->children.empty())
			removeChildren(cur->children[i]);
	}
	//递归清除之后，删除当前children，释放孩子结点的空间
	for (int i = 0; i < cur->children.size(); ++i)
	{
		ht.erase(cur->children[i]->id);
		delete cur->children[i];
	}
	//更新结点数量
	Size -= cur->children.size();
	//释放存放指针的空间
	cur->children.clear();
}

/***************************************************************************
  函数名称：_removeChildren
  功    能：删除所有后代的辅助函数非递归方法
  输入参数：familyTreeNode* cur，当前需要删除的结点
  返 回 值：
  说    明：通过队列删除cur及其后代的所有结点
***************************************************************************/
void familyTree::_removeChildren(familyTreeNode* cur)
{
	Queue<familyTreeNode*> q;
	//cur的孩子先入队
	for (int i = 0; i < cur->children.size(); ++i)
		q.emplace(cur->children[i]);
	familyTreeNode* temp;
	//利用队列删除
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		//当前结点的孩子入队
		for (int i = 0; i < temp->children.size(); ++i)
			q.emplace(temp->children[i]);
		//释放存放孩子指针数组
		temp->children.clear();
		//哈希表中删除结点
		ht.erase(temp->id);
		//释放当前结点
		delete temp;
		--Size;//更新数量
	}
	//释放最老的
	cur->children.clear();
}

/***************************************************************************
  函数名称：show
  功    能：以树形结构，利用非递归方法展示家谱内容
  输入参数：
  返 回 值：
  说    明：利用栈实现递归的展开，这里注意需要判断是否为最后一个孩子
			最后一个孩子对应特殊的制表符
***************************************************************************/
void familyTree::show()
{
	cout << endl << "当前家谱为" << endl;
	//Queue<familyTreeNode*> q;
	//familyTreeNode* cur;
	//q.emplace(root);
	//层序遍历输出家谱
	/*
	while (!q.empty())
	{
		int Size = q.size();
		for (int i = 0; i < Size; ++i)
		{
			cur = q.front();
			q.pop();
			cout << cur->id << ' ';
			for (int i = 0; i < cur->children.size(); ++i)
				q.emplace(cur->children[i]);
		}
		cout << endl;
	}*/
	//栈需要储存的信息
	//参数：isLast是否是最后一个，node家族树的结点，level是第几层
	struct info {
		info(bool isLast = false, familyTreeNode* node = nullptr, int level = 0)
			:isLast(isLast), node(node), level(level) {}
		bool isLast;
		familyTreeNode* node;
		int level;
	};
	List<info> stk;
	info temp;
	stk.emplace_back(info(Size == 1, root, 0));
	//树型结构
	while (!stk.empty())
	{
		//取栈顶元素
		temp = stk.getTail()->val;
		stk.pop_back();

		for (int i = 0; i < temp.level; ++i)
			cout << "│   ";
		//是否是孩子们中的最后一个
		if (temp.isLast)
			cout << "└── ";
		else
			cout << "├── ";
		cout << temp.node->id << endl;

		//放入temp的孩子，注意是否是最后一个孩子
		int childSize = temp.node->children.size();
		for (int i = childSize - 1; i >= 0; --i)
			stk.emplace_back(info(i == childSize - 1
				, temp.node->children[i], temp.level + 1));

	}

	cout << "共有" << Size << "人" << endl;
	cout << endl;
}

/***************************************************************************
  函数名称：~familyTree
  功    能：释放家谱中所有结点的空间
  输入参数：
  返 回 值：
  说    明：_removeChildren函数删除根结点的所有后代，然后删除root结点
***************************************************************************/
familyTree::~familyTree()
{
	//删除根结点的孩子们
	_removeChildren(root);
	//删除根结点
	delete root;
}

/***************************************************************************
  函数名称：to_be_continue
  功    能：等待用户输入任意键，再关闭cmd窗口
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continue()
{
	cout << endl << "回车键继续操作" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}

int main() {
	cout << endl << "**                 家谱管理系统                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA --- 完善    家庭\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE --- 退出    程序\t\t**" << endl;
	cout << "==================================================" << endl;
	familyTree ft;
	String op;
	bool loop = true;
	while (loop)
	{
		cout << "请选择要执行的操作: ";
		cin >> op;
		switch (op[0])
		{
			case 'a':
			case 'A':
				ft.buildFamily();
				break;
			case 'b':
			case 'B':
				ft.addChild();
				break;
			case 'c':
			case 'C':
				ft.removeChildren();
				break;
			case 'd':
			case 'D':
				ft.changeId();
				break;
			case 'e':
			case 'E':
				loop = false;
				break;
			default:
				cout << "请输入正确操作" << endl;
				cin.ignore(65536, '\n');
				cin.clear();
				break;
		}
		ft.show();
	}
	to_be_continue();
	return 0;
}