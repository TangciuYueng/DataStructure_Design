#include "9_2151298_杨滕超.h"

/***************************************************************************
  函数名称：~criticalActivity
  功    能：关键活动类的析构函数，释放申请邻接表结点的空间
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
criticalActivity::~criticalActivity()
{
	edge* cur, * temp;
	//释放申请的空间
	for (int i = 0; i < N; ++i)
	{
		if (graph1[i])//如果有节点
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
		if (graph2[i])//如果有节点
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
  函数名称：checkValid
  功    能：检查图是否连通
  输入参数：
  返 回 值：
  说    明：若存在出度和入度均为零的点，则是孤立点，不连通
***************************************************************************/
bool criticalActivity::checkValid()
{
	//任务交接点没有连接
	for (int i = 0; i < N; ++i)
		if (in[i] == 0 && out[i] == 0)//度数为零没有活动连接
			return false;

	return true;
}

/***************************************************************************
  函数名称：init
  功    能：初始化邻接表数组和出度入度数组
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void criticalActivity::init()
{
	graph1.resize(N, NULL);
	graph2.resize(N, NULL);
	in.resize(N, 0);
	out.resize(N, 0);
}

/***************************************************************************
  函数名称：AOE
  功    能：求关键路径
  输入参数：
  返 回 值：
  说    明：通过两次拓扑排序求得每个活动最早开始的时间和最迟允许开始时间
			其中可以通过第一次拓扑排序检查是否存在环，存在则输出相关提示
***************************************************************************/
void criticalActivity::AOE()
{
	Queue<int> q;
	//各个顶点最早开始和最晚开始时间
	Vector<int> Ve(N, 0), Vl(N, INT_MAX);
	//记录已经能遍历的，来判断有没有环
	Vector<bool> visited(N, false);
	//入度为零入队，最早开始时间记录为零
	for (int i = 0; i < N; ++i)
		if (in[i] == 0)
			q.emplace(i);


	if (q.empty())//甚至没有一个顶点有为零，方案不可行
	{
		cout << "此方案不可行" << endl;
		cout << '0' << endl;
		return;
	}

	int temp = 0;
	edge* tempEdge = NULL;
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		visited[temp] = true;//标记遍历过了

		tempEdge = graph1[temp];
		while (tempEdge)//遍历能从temp指向的顶点
		{
			//graph[temp]记录了以temp为起点的边
			int to = tempEdge->to;
			int val = tempEdge->val;
			//更新最大值
			if (Ve[temp] + val > Ve[to])
				Ve[to] = Ve[temp] + val;
			//入度为零就入队
			if (--in[to] == 0)
				q.emplace(to);
			//移动到下一个指向的顶点
			tempEdge = tempEdge->next;
		}
	}
	//跳出循环队列为空
	for (int i = 0; i < N; ++i)
	{
		if (out[i] == 0)
		{
			q.emplace(i);
			Vl[i] = Ve[i];
		}
		if (visited[i] == false)//之前居然没有遍历，说明存在环
		{
			cout << "此方案不可行" << endl;
			cout << '0' << endl;
			return;
		}
	}
	//开始逆向拓扑排序
	while (!q.empty())
	{
		temp = q.front();
		q.pop();

		tempEdge = graph2[temp];
		while (tempEdge)
		{
			//graph[temp]记录了以temp为起点的边
			int to = tempEdge->to;
			int val = tempEdge->val;
			//更新最小
			if (Vl[temp] - val < Vl[to])
				Vl[to] = Vl[temp] - val;
			//出度为零就入队
			if (--out[to] == 0)
				q.emplace(to);
			tempEdge = tempEdge->next;
		}
	}
	cout << "\n完成项目最少时间: ";
	cout << Ve[N - 1] << endl;
	cout << "关键活动为: \n";
	//遍历图中的边，符合要求就记录下来
	for (int i = 0; i < N; ++i)
	{
		if (graph1[i])
		{
			edge* cur = graph1[i];
			while (cur)
			{
				int to = cur->to;
				//最早开始和最晚开始的时间相同即为关键活动
				if (Ve[i] == Vl[i] && Ve[to] == Vl[to])
					cout << i + 1 << "->" << to + 1 << endl;
				cur = cur->next;
			}
		}
	}
	cout << endl;
}

/***************************************************************************
  函数名称：getNM
  功    能：关键路径类获得顶点数和边数的对外接口
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void criticalActivity::getNM(const int& N, const int& M)
{
	this->N = N;
	this->M = M;
}

/***************************************************************************
  函数名称：setEdge
  功    能：向图中添加有向边
  输入参数：
  返 回 值：
  说    明：需要判断是否重复，若重复则取权值较小的边
***************************************************************************/
void criticalActivity::setEdge(int from, int to, int val)
{
	/*
	* 要判断是否是重复的边
	* 重复了边的权值取最小值
	* 不重复就直接插入头头
	*/
	edge* cur1 = graph1[from], * cur2 = graph2[to];
	while (cur1)//如果有东西
	{
		if (cur1->to == to)//发现是相同的边就跳出
			break;
		cur1 = cur1->next;//没发现相同的边就继续往后找
	}
	if (cur1)//找到相同的边，比较权值大小
	{
		if (cur1->val > val)//更新更小
		{
			//此时需要更新，再去更新反图
			cur1->val = val;

			//反向图的搜索，此时一定存在
			while (cur2)
			{
				if (cur2->to == from)
					break;
				cur2 = cur2->next;
			}
			if (cur2)
				cur2->val = val;
			//更新完反图直接退出
			return;
		}
		//不用更新也直接退出
		return;
	}

	//没找到相同的边，插入到第一个
	edge* newNode = new edge(to, val);
	//插入
	newNode->next = graph1[from];
	graph1[from] = newNode;


	//没找到相同的边，插入到第一个
	newNode = new edge(from, val);
	//插入
	newNode->next = graph2[to];
	graph2[to] = newNode;

	//新添加边，没有重复边，才更新出度和入度
	++out[from];//记录出度
	++in[to];//记录入度
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
	criticalActivity ca;
	int tempN, tempM;

	cout << "请输入任务交接点个数N(N <= 100), 任务个数M: ";
	while (1)
	{
		cin >> tempN >> tempM;
		if (cin.fail() || tempN <= 0 || tempM <= 0)
		{
			cout << "输入有误，请输入正整数" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempN > 100)
		{
			cout << "任务交接点个数过多，注意N<=100" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempN == 1)
		{
			cout << "仅有一个任务交接点无法存在活动" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else if (tempM < tempN)
		{
			cout << "活动数过少，无法连通" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
		{
			ca.getNM(tempN, tempM);//将顶点个数，边个数传给对象
			break;
		}
	}
	//存图初始化
	ca.init();
	cout << "请依次输入任务交接点以及任务所需时间: " << endl;
	for (int i = 0; i < tempM;)
	{
		int from, to, val;
		cin >> from >> to >> val;
		if (cin.fail() || from <= 0 || to <= 0 || val <= 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "输入有误，请输入正整数" << endl;
		}
		else if (from > tempN || to > tempN)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "无此任务交接点，请重新输入" << endl;
		}
		else if (from == to)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "输入有误，两个任务交接点不应相同" << endl;
		}
		else
		{
			ca.setEdge(from - 1, to - 1, val);
			++i;//正确输入才下一个
		}
	}
	//检查是否合法
	if (ca.checkValid())
		ca.AOE();
	else
	{
		cout << "此方案不可行" << endl;
		cout << '0' << endl;
	}
	to_be_continue();
}