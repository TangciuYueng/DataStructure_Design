#include "9_2151298_������.h"

/***************************************************************************
  �������ƣ�~criticalActivity
  ��    �ܣ��ؼ����������������ͷ������ڽӱ���Ŀռ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
criticalActivity::~criticalActivity()
{
	edge* cur, * temp;
	//�ͷ�����Ŀռ�
	for (int i = 0; i < N; ++i)
	{
		if (graph1[i])//����нڵ�
		{
			cur = graph1[i];
			while (cur)
			{
				temp = cur->next;
				delete cur;
				cur = temp;
			}
		}
	}
	for (int i = 0; i < N; ++i)
	{
		if (graph2[i])//����нڵ�
		{
			cur = graph2[i];
			while (cur)
			{
				temp = cur->next;
				delete cur;
				cur = temp;
			}
		}
	}
}

/***************************************************************************
  �������ƣ�checkValid
  ��    �ܣ����ͼ�Ƿ���ͨ
  ���������
  �� �� ֵ��
  ˵    ���������ڳ��Ⱥ���Ⱦ�Ϊ��ĵ㣬���ǹ����㣬����ͨ
***************************************************************************/
bool criticalActivity::checkValid()
{
	//���񽻽ӵ�û������
	for (int i = 0; i < N; ++i)
		if (in[i] == 0 && out[i] == 0)//����Ϊ��û�л����
			return false;

	return true;
}

/***************************************************************************
  �������ƣ�init
  ��    �ܣ���ʼ���ڽӱ�����ͳ����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void criticalActivity::init()
{
	graph1.resize(N, NULL);
	graph2.resize(N, NULL);
	in.resize(N, 0);
	out.resize(N, 0);
}

/***************************************************************************
  �������ƣ�AOE
  ��    �ܣ���ؼ�·��
  ���������
  �� �� ֵ��
  ˵    ����ͨ�����������������ÿ������翪ʼ��ʱ����������ʼʱ��
			���п���ͨ����һ�������������Ƿ���ڻ�����������������ʾ
***************************************************************************/
void criticalActivity::AOE()
{
	Queue<int> q;
	//�����������翪ʼ������ʼʱ��
	Vector<int> Ve(N, 0), Vl(N, INT_MAX);
	//��¼�Ѿ��ܱ����ģ����ж���û�л�
	Vector<bool> visited(N, false);
	//���Ϊ����ӣ����翪ʼʱ���¼Ϊ��
	for (int i = 0; i < N; ++i)
		if (in[i] == 0)
			q.emplace(i);


	if (q.empty())//����û��һ��������Ϊ�㣬����������
	{
		cout << "�˷���������" << endl;
		cout << '0' << endl;
		return;
	}

	int temp = 0;
	edge* tempEdge = NULL;
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		visited[temp] = true;//��Ǳ�������

		tempEdge = graph1[temp];
		while (tempEdge)//�����ܴ�tempָ��Ķ���
		{
			//graph[temp]��¼����tempΪ���ı�
			int to = tempEdge->to;
			int val = tempEdge->val;
			//�������ֵ
			if (Ve[temp] + val > Ve[to])
				Ve[to] = Ve[temp] + val;
			//���Ϊ������
			if (--in[to] == 0)
				q.emplace(to);
			//�ƶ�����һ��ָ��Ķ���
			tempEdge = tempEdge->next;
		}
	}
	//����ѭ������Ϊ��
	for (int i = 0; i < N; ++i)
	{
		if (out[i] == 0)
		{
			q.emplace(i);
			Vl[i] = Ve[i];
		}
		if (visited[i] == false)//֮ǰ��Ȼû�б�����˵�����ڻ�
		{
			cout << "�˷���������" << endl;
			cout << '0' << endl;
			return;
		}
	}
	//��ʼ������������
	while (!q.empty())
	{
		temp = q.front();
		q.pop();

		tempEdge = graph2[temp];
		while (tempEdge)
		{
			//graph[temp]��¼����tempΪ���ı�
			int to = tempEdge->to;
			int val = tempEdge->val;
			//������С
			if (Vl[temp] - val < Vl[to])
				Vl[to] = Vl[temp] - val;
			//����Ϊ������
			if (--out[to] == 0)
				q.emplace(to);
			tempEdge = tempEdge->next;
		}
	}
	cout << "\n�����Ŀ����ʱ��: ";
	cout << Ve[N - 1] << endl;
	cout << "�ؼ��Ϊ: \n";
	//����ͼ�еıߣ�����Ҫ��ͼ�¼����
	for (int i = 0; i < N; ++i)
	{
		if (graph1[i])
		{
			edge* cur = graph1[i];
			while (cur)
			{
				int to = cur->to;
				//���翪ʼ������ʼ��ʱ����ͬ��Ϊ�ؼ��
				if (Ve[i] == Vl[i] && Ve[to] == Vl[to])
					cout << i + 1 << "->" << to + 1 << endl;
				cur = cur->next;
			}
		}
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�getNM
  ��    �ܣ��ؼ�·�����ö������ͱ����Ķ���ӿ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void criticalActivity::getNM(const int& N, const int& M)
{
	this->N = N;
	this->M = M;
}

/***************************************************************************
  �������ƣ�setEdge
  ��    �ܣ���ͼ����������
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�ж��Ƿ��ظ������ظ���ȡȨֵ��С�ı�
***************************************************************************/
void criticalActivity::setEdge(int from, int to, int val)
{
	/*
	* Ҫ�ж��Ƿ����ظ��ı�
	* �ظ��˱ߵ�Ȩֵȡ��Сֵ
	* ���ظ���ֱ�Ӳ���ͷͷ
	*/
	edge* cur1 = graph1[from], * cur2 = graph2[to];
	while (cur1)//����ж���
	{
		if (cur1->to == to)//��������ͬ�ı߾�����
			break;
		cur1 = cur1->next;//û������ͬ�ı߾ͼ���������
	}
	if (cur1)//�ҵ���ͬ�ıߣ��Ƚ�Ȩֵ��С
	{
		if (cur1->val > val)//���¸�С
		{
			//��ʱ��Ҫ���£���ȥ���·�ͼ
			cur1->val = val;

			//����ͼ����������ʱһ������
			while (cur2)
			{
				if (cur2->to == from)
					break;
				cur2 = cur2->next;
			}
			if (cur2)
				cur2->val = val;
			//�����귴ͼֱ���˳�
			return;
		}
		//���ø���Ҳֱ���˳�
		return;
	}

	//û�ҵ���ͬ�ıߣ����뵽��һ��
	edge* newNode = new edge(to, val);
	//����
	newNode->next = graph1[from];
	graph1[from] = newNode;


	//û�ҵ���ͬ�ıߣ����뵽��һ��
	newNode = new edge(from, val);
	//����
	newNode->next = graph2[to];
	graph2[to] = newNode;

	//����ӱߣ�û���ظ��ߣ��Ÿ��³��Ⱥ����
	++out[from];//��¼����
	++in[to];//��¼���
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
	criticalActivity ca;
	int tempN, tempM;

	cout << "���������񽻽ӵ����N(N <= 100), �������M: ";
	while (1)
	{
		cin >> tempN >> tempM;
		if (cin.fail() || tempN <= 0 || tempM <= 0)
		{
			cout << "��������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempN > 100)
		{
			cout << "���񽻽ӵ�������࣬ע��N<=100" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempN == 1)
		{
			cout << "����һ�����񽻽ӵ��޷����ڻ" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempM < tempN)
		{
			cout << "������٣��޷���ͨ" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
		{
			ca.getNM(tempN, tempM);//������������߸�����������
			break;
		}
	}
	//��ͼ��ʼ��
	ca.init();
	cout << "�������������񽻽ӵ��Լ���������ʱ��: " << endl;
	for (int i = 0; i < tempM;)
	{
		int from, to, val;
		cin >> from >> to >> val;
		if (cin.fail() || from <= 0 || to <= 0 || val <= 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "��������������������" << endl;
		}
		else if (from > tempN || to > tempN)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "�޴����񽻽ӵ㣬����������" << endl;
		}
		else if (from == to)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "���������������񽻽ӵ㲻Ӧ��ͬ" << endl;
		}
		else
		{
			ca.setEdge(from - 1, to - 1, val);
			++i;//��ȷ�������һ��
		}
	}
	//����Ƿ�Ϸ�
	if (ca.checkValid())
		ca.AOE();
	else
	{
		cout << "�˷���������" << endl;
		cout << '0' << endl;
	}
	to_be_continue();
}