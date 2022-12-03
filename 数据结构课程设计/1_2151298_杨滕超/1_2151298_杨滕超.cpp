#include "1_251298_������.h"


/***************************************************************************
  �������ƣ�init
  ��    �ܣ���ʼ����������ϵͳ��
  ���������
  �� �� ֵ��
  ˵    ��������ѡ��ͨ���ֶ������ʼ����Ҳ����ѡ����ļ��ж�ȡ��ʼ��
***************************************************************************/
bool StudentSystem::ini()
{
	int cnt = 0;
	cout << "�����뽨��������Ϣϵͳ!" << endl;
	cout << "��ѡ���ʼ������" << endl;
	cout << "1.���ļ��ж�ȡ" << endl;
	cout << "2.�ֶ�����" << endl;
	int op = 0;
	while (1)
	{
		cin >> op;
		if (cin.fail() || !(op == 1 || op == 2))
		{
			cout << "������������������!" << endl;
			cin.ignore(65536, '\n');
			cin.clear();
		}
		else
			break;
	}
	//���ļ��ж�ȡ
	if (op == 1)
	{
		String fileName;
		cout << "�������ļ����ƣ���: Stu)" << endl;
		cin >> fileName;
		if (fileName.length() == 0)
		{
			fileName = "studentData.txt";
		}

		fileName += ".txt";//�����ļ�����׺
		ifstream file(fileName.c_str(), ios::in);

		if (!file.is_open())
		{
			cerr << "�ļ���ʧ��" << endl;
			//exit(1);
			return false;
		}
		Stu temp;
		while (file >> temp)
			data.emplace_back(temp);

		file.close();
		show();
		return true;//���ļ��ɹ�
	}
	cout << "�����뿼������" << endl;
	//��ȷ������˳�ѭ��
	while (1)
	{
		cin >> cnt;
		if (cin.fail() || cnt < 0)
		{
			cout << "��������������Ϊ��������!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else//��ȷ����
			break;
	}
	if (cnt == 0)//һ��ʼ������ѧ��
		return true;
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
	Stu temp;
	for (int i = 0; i < cnt; ++i)
	{
		cin >> temp;
		//�����Ѿ����ڣ�Search()�Ҳ����򷵻�NULL
		if (mySearch(temp) != NULL)
		{
			cout << "�������Ѵ��ڸÿ���!" << endl;
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
  �������ƣ�search
  ��    �ܣ�ͨ���û�����Ŀ������ţ����ҿ�����Ϣ������ӡ����
  ���������
  �� �� ֵ��
  ˵    �������в���ʧ�ܵ��ж����
***************************************************************************/
void StudentSystem::search()
{
	if (data.empty())
	{
		cout << "������Ϣϵͳ���������ݣ����ܲ���" << endl;
		return;
	}
	cout << "������Ҫ���ҵĿ����Ŀ���: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);
	//����Ҳ���
	if (tempIter == NULL)
	{
		cout << "�����ڿ���Ϊ" << num << "�Ŀ�����" << endl << endl;
	}
	else
	{
		cout << "������Ϣ����: " << endl;
		printf("����\t   ����\t\t�Ա�\t   ����\t   �������\n");
		cout << *tempIter << endl << endl;
	}
}

/***************************************************************************
  �������ƣ�remove
  ��    �ܣ�ͨ���û�����Ŀ������ţ�ɾ��ϵͳ����Ӧ�Ŀ�����Ϣ
  ���������
  �� �� ֵ��
  ˵    ����ע�⵽��ϵͳ�в��������뿼�ŵĿ�������������ش�����ʾ
***************************************************************************/
void StudentSystem::remove()
{
	if (data.empty())
	{
		cout << "������Ϣϵͳ���������ݣ�����ɾ��" << endl;
		return;
	}
	cout << "������Ҫɾ���Ŀ����Ŀ���: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);
	if (tempIter == NULL)
	{
		cout << "�����ڿ���Ϊ" << num << "�Ŀ�����" << endl << endl;
	}
	else
	{
		cout << "��ɾ���Ŀ�������Ϣ��: ";
		cout << *tempIter << endl << endl;
		data.remove(tempIter);
	}
}

/***************************************************************************
  �������ƣ�insert
  ��    �ܣ��û��������λ���뿼����Ϣ����������Ϣ���뿼��ϵͳ
  ���������
  �� �� ֵ��
  ˵    �������û�����λ�÷Ƿ�ʱ�����������������ʾ
			���뿼����Ϣ���ֿ����ظ������������Ӧ��ʾ
***************************************************************************/
void StudentSystem::insert()
{
	cout << "��������Ҫ����Ŀ�����λ��: ";
	int loc = 0;
	int Size = data.size();
	while (1)
	{
		cin >> loc;
		if (cin.fail() || loc < 0 || loc > Size)
		{
			cout << "��������ȷλ��!" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else//��ȷ����
			break;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
	Stu temp;

	cin >> temp;
	//�Ҳ����򷵻�NULL
	auto tempIter = mySearch(temp);
	//��ò���λ��
	List<Stu>::list_iterator iter = data.begin();
	for (int i = 0; i < loc; ++i)
		++iter;
	//���û�п���
	if (tempIter == NULL)
	{
		//�ڲ�����0 - Size - 1
		if (loc == Size)
			data.emplace_back(temp);
		else
			data.insert(iter, temp);
	}
	else
	{
		cout << "�������Ѵ��ڸÿ���!�����ٴβ���!" << endl << endl;
	}

}

/***************************************************************************
  �������ƣ�insertProperly
  ��    �ܣ���һ��������Ϣ���տ��Ŵ�С����ϵͳ��ʹ��ϵͳ�п��Ű���������
  ���������Stu& ѧ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void StudentSystem::insertProperly(Stu& s)
{
	int Size = data.size();
	if (Size == 0)//ϵͳ����û����Ϣ
	{
		data.emplace_back(s);
		return;
	}
	else
	{
		bool isInserted = false;
		//Stu temp;
		//�ҵ���һ����s.num��ģ�������ǰ��
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

		//�������ģ�ѭ��û�ҵ�����λ�ã��������һ��
		if (isInserted == false)
			data.emplace_back(s);
	}
}

/***************************************************************************
  �������ƣ�to_be_continue
  ��    �ܣ����������ȴ���һ���������˳�cmd����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void StudentSystem::to_be_continue()
{
	cout << endl << "�س�������" << endl;
	cin.clear();
	cin.ignore(65536, '\n');
	cin.get();
	return;
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ����б����ʽչʾϵͳ�е�ÿ�����Ϣ
  ���������
  �� �� ֵ��
  ˵    ����ע�⵽������ϵͳ����Ϣ��Ӧ��������ʾ
***************************************************************************/
void StudentSystem::show()
{
	printf("\n����\t   ����\t\t�Ա�\t   ����\t   �������\n");
	if (data.empty())
	{
		cout << "������Ϣϵͳ����������" << endl << endl;
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
  �������ƣ�change
  ��    �ܣ������û�����Ŀ��ţ��޸�ϵͳ�п�������Ϣ
  ���������
  �� �� ֵ��
  ˵    ���������뿼�Ų�������ϵͳ�У���������ʾ
			�޸ĺ�Ŀ�����Ϣ�Ŀ���Ӧ���޸�ǰ�ı���һ��
***************************************************************************/
void StudentSystem::change()
{
	if (data.empty())
	{
		cout << "������Ϣϵͳ���������ݣ������޸�" << endl;
		return;
	}
	cout << "������Ҫ�޸ĵĿ����Ŀ���: ";
	String num;
	cin >> num;

	auto tempIter = mySearch(num);

	if (tempIter == NULL)
	{
		cout << "�����ڿ���Ϊ" << num << "�Ŀ�����" << endl << endl;
	}
	else
	{
		while (1)
		{
			cout << "�������������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
			cin >> *tempIter;
			if (tempIter->num == num)
				break;
			else
			{
				cout << "���Ų��ɸ��ģ�����������" << endl;
				cin.clear();
				cin.ignore(65536, '\n');
			}
		}
	}
}

/***************************************************************************
  �������ƣ�save
  ��    �ܣ���ϵͳ�еĿ�����Ϣ�������û�������ļ���
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�ж��ļ����Ƿ�ɹ�
***************************************************************************/
void StudentSystem::save()
{
	int Size = data.size();
	if (Size == 0)
	{
		cout << "������Ϣϵͳ���������ݣ����豣��" << endl;
		return;
	}
	String fileName;
	cout << "�������ļ���: ���磺Stu)";
	cin >> fileName;
	if (cin.fail())
	{
		cout << "�Ƿ��ļ��������ݽ�������studentData.txt" << endl;
		fileName = "studentData.txt";
	}
	else if (fileName == "0")
	{
		cout << "���ݽ�������studentData.txt" << endl;
		fileName = "studentData.txt";
	}
	else
	{
		fileName += ".txt";
	}

	ofstream file(fileName.c_str(), ios::out);
	if (!file)
	{
		cerr << "�ļ���ʧ��" << endl;
		exit(0);
	}
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		file << it->num << ' ' << it->name << ' ' << it->gender
			<< ' ' << it->age << ' ' << it->type << endl;
	}

	cout << "���ݴ������!" << endl;
	file.close();
}

/***************************************************************************
  �������ƣ�statictics
  ��    �ܣ�ͳ��ϵͳ�п�����Ů������Ϣ�͸���רҵ��������Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void StudentSystem::statistics()
{
	if (data.empty())
	{
		cout << "������Ϣϵͳ���������ݣ�����ͳ��" << endl;
		return;
	}
	Map<String, int> gender;
	Map<String, int> type;
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		++gender[it->gender];
		++type[it->type];
	}
	cout << "\n�Ա�ͳ��: " << endl;
	for (auto it = gender.begin(); it != gender.end(); ++it)
	{
		cout.width(10);
		cout << it->first << it->second << endl;
	}
	cout << endl;
	cout << "רҵͳ��: " << endl;
	for (auto it = type.begin(); it != type.end(); ++it)
	{
		cout.width(10);
		cout << it->first << it->second << endl;
	}
}

/***************************************************************************
  �������ƣ�mySearch
  ��    �ܣ�����ϵͳ���Ƿ���ڸÿ���
  ���������const Stu& sѧ���������
  �� �� ֵ������ĵ�����
  ˵    ����������ʧ�ܷ��ؿ�ָ��NULL
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
  �������ƣ�mySearch
  ��    �ܣ�ͨ�����Ų��ҿ���
  ���������const String& num����������
  �� �� ֵ�����������
  ˵    ����������ʧ�ܷ��ؿ�ָ��NULL
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
	if (stuSys.ini())//����ļ��򿪳ɹ�or����ɹ�
	{
		String op;
		bool loop = true;
		bool failOp;
		while (loop)
		{
			cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊ"
				"ͳ�ƣ�6Ϊ�������ݣ�0Ϊ�˳�ϵͳ��\n";
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
					cout << "�Ƿ�����������������" << endl;
					cout << "��ܰ��ʾ��1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊ"
						"ͳ�ƣ�6Ϊ�������ݣ�0Ϊ�˳�ϵͳ" << endl;
					break;
			}
			if (stuSys.size() < 10 && failOp == false)
				stuSys.show();
			if (stuSys.size() && failOp == false)//�����ݲ���ʾ�ж�����
				cout << "������Ϣϵͳ�ֹ���" << stuSys.size() << "������" << endl;
		}//end of while
	}//end of if

	stuSys.to_be_continue();
}