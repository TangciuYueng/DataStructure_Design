#include "6_2151298_������.h"

/***************************************************************************
  �������ƣ�familyTree
  ��    �ܣ�������������
  ���������
  �� �� ֵ��
  ˵    ����������Ĺ��캯��
***************************************************************************/
familyTree::familyTree()
{
	cout << "���Ƚ���һ������!" << endl;
	cout << "���������ȵ�����: ";
	String tempId;
	cin >> tempId;
	root = new(nothrow) familyTreeNode(tempId);
	if (root == NULL)
	{
		cerr << "����ռ�ʧ��" << endl;
		exit(1);
	}
	Size = 1;
	//����������ַ��ֵ��
	ht.insert(make_pair(tempId, root));
}

/***************************************************************************
  �������ƣ�search
  ��    �ܣ��ڼ�������������id�����õ��ó�Ա�Ľ��
  ���������String& id, familyTreeNode* cur��Ҫ�����ĵ���������ǰ�����Ľ��
  �� �� ֵ��familyTreeNode* ������Ҫ�����ĵĽ���ַ
  ˵    �����������ɹ�������Ӧ�����Ϣ�����򷵻ؿ�ָ��
***************************************************************************/
familyTreeNode* familyTree::search(String& id, familyTreeNode* cur)
{
	//�ݹ��������
	if (cur == nullptr)
		return nullptr;
	if (cur->id == id)
		return cur;
	//������Ѱ��
	familyTreeNode* temp = nullptr;
	for (int i = 0; i < cur->children.size(); ++i)
	{
		temp = search(id, cur->children[i]);
		if (temp)//temp��Ϊ��
			break;
	}
	return temp;
}

/***************************************************************************
  �������ƣ�_search
  ��    �ܣ��ڼ�������������id�����õ��ó�Ա�Ľ��
  ���������String& id��Ҫ�����ĵ�����
  �� �� ֵ��familyTreeNode* ������Ҫ�����ĵĽ���ַ
  ˵    ����ͨ����ϣ���������������ɹ�������Ӧ�����Ϣ�����򷵻ؿ�ָ��
***************************************************************************/
familyTreeNode* familyTree::_search(String& id)
{
	//ͨ����ϣ��Ѱ�ҷ��� id, ����ַ ��ֵ��
	auto res = ht.find(id);
	//����ҵ������صĵ�ַ�ǿ�
	if (res)
		return res->kv.second;
	//�Ҳ������ؿյ�ַ
	return NULL;
}

/***************************************************************************
  �������ƣ�buildfamily
  ��    �ܣ������û�����ĳ�Ա��������Ů��������Ů���������佨����ͥ
  ���������
  �� �� ֵ��
  ˵    ����������Ҫ�жϼ������Ƿ���ڸó�Ա�����ڲ��ܽ�����ͥ��
			�������������ʾ
			�ж�������Ů�����Ƿ�Ϸ�
			�ж���Ů�������Ƿ�����������г�Ա�����ظ������ظ��������ʾ��������
***************************************************************************/
void familyTree::buildFamily()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "������Ҫ������ͥ���˵�����: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "������û������ˣ�����������!" << endl;
			cin.ignore(65536, '\n');
		}
		else if (!fa->children.empty())
		{
			cout << tempId << "�Ѿ���������ͥ������������" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	int childNum = 0;
	cout << "������" << tempId << "�Ķ�Ů����: ";
	while (1)
	{
		cin >> childNum;
		if (cin.fail() || childNum <= 0)
		{
			cout << "����ȷ����һ��������!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	cout << "����������" << tempId << "�Ķ�Ů������: ";
	String childId;
	for (int i = 0; i < childNum; ++i)
	{
		cin >> childId;
		//auto temp = search(childId, root);
		auto temp = _search(childId);
		if (temp)//�ҵ���
		{
			cout << "�벻Ҫ��������г�Ա����������������" << endl;
			--i;
		}
		else//û�������ͼ��������
		{
			familyTreeNode* child = new(nothrow) familyTreeNode(childId);
			if (child == NULL)
			{
				cerr << "����ռ�ʧ��" << endl;
				exit(1);
			}
			fa->children.emplace_back(child);
			ht.insert(make_pair(childId, child));
		}
	}
	//���½������
	Size += childNum;
}

/***************************************************************************
  �������ƣ�addChild
  ��    �ܣ������û�����ĳ�Ա�����������һ����Ů
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�жϼ������Ƿ���������Ա
			�ж���ӵ���Ů�������Ƿ�����������г�Ա�����ظ������ظ��������ʾ��������
***************************************************************************/
void familyTree::addChild()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "������û������ˣ�����������!" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}

	String childId;
	cout << "������" << tempId << "����ӵĶ��ӣ���Ů����������: ";
	while (1)
	{
		cin >> childId;
		//auto temp = search(childId, root);
		auto temp = _search(childId);
		if (temp)//�ҵ���
			cout << "�벻Ҫ��������г�Ա����������������" << endl;
		else
			break;
	}

	familyTreeNode* child = new(nothrow) familyTreeNode(childId);
	if (child == NULL)
	{
		cerr << "����ռ�ʧ��" << endl;
		exit(1);
	}
	fa->children.emplace_back(child);//��ʱ�������ͷſռ䣬������ʲ���
	++Size;//���½������
	ht.insert(make_pair(childId, child));
}

/***************************************************************************
  �������ƣ�changeId
  ��    �ܣ��޸��û�����ĳ�Ա����������
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�жϼ������Ƿ���������Ա
			�ж��޸ĺ�������Ƿ�����������г�Ա�����ظ������ظ��������ʾ��������
***************************************************************************/
void familyTree::changeId()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "������Ҫ�����������˵�Ŀǰ����: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "������û������ˣ�����������!" << endl;
			cin.ignore(65536, '\n');
		}

		else
			break;
	}
	String newId;
	cout << "��������ĺ������: ";
	while (1)
	{
		cin >> newId;
		//�ж��������Ƿ�����������г�Ա����
		auto res = _search(newId);
		if (res)//������
			cout << "�벻Ҫ��������г�Ա����������������" << endl;
		else
			break;
	}
	ht.erase(fa->id);
	fa->id = newId;
	ht.insert(make_pair(fa->id, fa));
	cout << tempId << "�Ѹ���Ϊ" << newId << endl;
}

/***************************************************************************
  �������ƣ�removeChildren
  ��    �ܣ������û�����ĳ�Ա������ɾ�������к��
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�жϼ������Ƿ���������Ա
			��Ҫɾ�����к�����������ɿռ�й¶
***************************************************************************/
void familyTree::removeChildren()
{
	String tempId;
	familyTreeNode* fa;
	while (1)
	{
		cout << "������Ҫ��ɢ��ͥ���˵�����: ";
		cin >> tempId;
		//fa = search(tempId, root);
		fa = _search(tempId);

		if (fa == nullptr)
		{
			cout << "������û������ˣ�����������!" << endl;
			cin.ignore(65536, '\n');
		}
		else if (fa->children.empty())
		{
			cout << tempId << "���˼�ͥ��δ����������������" << endl;
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	cout << "Ҫ��ɢ��ͥ������: " << tempId << endl;
	_removeChildren(fa);
}

/***************************************************************************
  �������ƣ�removeChildren
  ��    �ܣ�ɾ�����к���ĸ��������ݹ鷽��
  ���������familyTreeNode* cur����ǰ��Ҫɾ���Ľ��
  �� �� ֵ��
  ˵    �������ȼ��cur�Ƿ񻹴�����Ů������������ɾ���ݹ�ɾ����Ů��û����Ů��
			�ٽ���cur��ɾ��
***************************************************************************/
void familyTree::removeChildren(familyTreeNode* cur)
{
	//���������Ů�Ƿ�û����Ů���� ���еݹ飬 ��û�о�ɾ��cur->children
	for (int i = 0; i < cur->children.size(); ++i)
	{
		if (!cur->children[i]->children.empty())
			removeChildren(cur->children[i]);
	}
	//�ݹ����֮��ɾ����ǰchildren���ͷź��ӽ��Ŀռ�
	for (int i = 0; i < cur->children.size(); ++i)
	{
		ht.erase(cur->children[i]->id);
		delete cur->children[i];
	}
	//���½������
	Size -= cur->children.size();
	//�ͷŴ��ָ��Ŀռ�
	cur->children.clear();
}

/***************************************************************************
  �������ƣ�_removeChildren
  ��    �ܣ�ɾ�����к���ĸ��������ǵݹ鷽��
  ���������familyTreeNode* cur����ǰ��Ҫɾ���Ľ��
  �� �� ֵ��
  ˵    ����ͨ������ɾ��cur�����������н��
***************************************************************************/
void familyTree::_removeChildren(familyTreeNode* cur)
{
	Queue<familyTreeNode*> q;
	//cur�ĺ��������
	for (int i = 0; i < cur->children.size(); ++i)
		q.emplace(cur->children[i]);
	familyTreeNode* temp;
	//���ö���ɾ��
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		//��ǰ���ĺ������
		for (int i = 0; i < temp->children.size(); ++i)
			q.emplace(temp->children[i]);
		//�ͷŴ�ź���ָ������
		temp->children.clear();
		//��ϣ����ɾ�����
		ht.erase(temp->id);
		//�ͷŵ�ǰ���
		delete temp;
		--Size;//��������
	}
	//�ͷ����ϵ�
	cur->children.clear();
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ������νṹ�����÷ǵݹ鷽��չʾ��������
  ���������
  �� �� ֵ��
  ˵    ��������ջʵ�ֵݹ��չ��������ע����Ҫ�ж��Ƿ�Ϊ���һ������
			���һ�����Ӷ�Ӧ������Ʊ��
***************************************************************************/
void familyTree::show()
{
	cout << endl << "��ǰ����Ϊ" << endl;
	//Queue<familyTreeNode*> q;
	//familyTreeNode* cur;
	//q.emplace(root);
	//��������������
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
	//ջ��Ҫ�������Ϣ
	//������isLast�Ƿ������һ����node�������Ľ�㣬level�ǵڼ���
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
	//���ͽṹ
	while (!stk.empty())
	{
		//ȡջ��Ԫ��
		temp = stk.getTail()->val;
		stk.pop_back();

		for (int i = 0; i < temp.level; ++i)
			cout << "��   ";
		//�Ƿ��Ǻ������е����һ��
		if (temp.isLast)
			cout << "������ ";
		else
			cout << "������ ";
		cout << temp.node->id << endl;

		//����temp�ĺ��ӣ�ע���Ƿ������һ������
		int childSize = temp.node->children.size();
		for (int i = childSize - 1; i >= 0; --i)
			stk.emplace_back(info(i == childSize - 1
				, temp.node->children[i], temp.level + 1));

	}

	cout << "����" << Size << "��" << endl;
	cout << endl;
}

/***************************************************************************
  �������ƣ�~familyTree
  ��    �ܣ��ͷż��������н��Ŀռ�
  ���������
  �� �� ֵ��
  ˵    ����_removeChildren����ɾ�����������к����Ȼ��ɾ��root���
***************************************************************************/
familyTree::~familyTree()
{
	//ɾ�������ĺ�����
	_removeChildren(root);
	//ɾ�������
	delete root;
}

/***************************************************************************
  �������ƣ�to_be_continue
  ��    �ܣ��ȴ��û�������������ٹر�cmd����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continue()
{
	cout << endl << "�س�����������" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}

int main() {
	cout << endl << "**                 ���׹���ϵͳ                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\tA --- ����    ��ͥ\t\t**" << endl;
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**" << endl;
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**" << endl;
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**" << endl;
	cout << "**\t\tE --- �˳�    ����\t\t**" << endl;
	cout << "==================================================" << endl;
	familyTree ft;
	String op;
	bool loop = true;
	while (loop)
	{
		cout << "��ѡ��Ҫִ�еĲ���: ";
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
				cout << "��������ȷ����" << endl;
				cin.ignore(65536, '\n');
				cin.clear();
				break;
		}
		ft.show();
	}
	to_be_continue();
	return 0;
}