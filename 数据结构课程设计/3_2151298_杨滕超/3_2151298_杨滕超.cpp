#include "3_2151298_������.h"

using namespace std;

//����CMP��ʼ����
//ע�⵽struct�о�̬���ݳ�Ա�ĸ�ֵӦ������Ķ�Ӧcpp�ļ���
int CMP::beg_c = 1;
int CMP::beg_r = 1;
int CMP::end_r = 5;
int CMP::end_c = 5;

/***************************************************************************
  �������ƣ�to_be_continue
  ��    �ܣ����������ȵ��û����������ַ��ٹر�cmd����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continue()
{
	cin.ignore(65536, '\n');
	cout << endl << "�س�����������" << endl;

	cin.get();
	return;
}

/***************************************************************************
  �������ƣ�maze
  ��    �ܣ���ʼ��maze�࣬�����Թ���С���Թ�������յ������
  ���������
  �� �� ֵ��
  ˵    ����maze��Ĺ��캯��
***************************************************************************/
maze::maze()
{
	//�Թ�Ĭ�ϴ�С
	R = C = 7;
	//�����Թ������С
	map = new char* [R];
	for (int i = 0; i < R; ++i)
		map[i] = new char[C];

	//{'#', '#', '#', '#', '#', '#', '#' }
	map[0][0] = WALL, map[0][1] = WALL, map[0][2] = WALL, map[0][3] = WALL,
		map[0][4] = WALL, map[0][5] = WALL, map[0][6] = WALL;

	//{'#', '0', '#', '0', '0', '0', '#' }
	map[1][0] = WALL, map[1][1] = EMPTY, map[1][2] = WALL, map[1][3] = EMPTY,
		map[1][4] = EMPTY, map[1][5] = EMPTY, map[1][6] = WALL;

	//{ '#', '0', '#', '0', '#', '#', '#' }
	map[2][0] = WALL, map[2][1] = EMPTY, map[2][2] = WALL, map[2][3] = EMPTY,
		map[2][4] = WALL, map[2][5] = WALL, map[2][6] = WALL;

	//{ '#', '0', '0', '0', '#', '0', '#' }
	map[3][0] = WALL, map[3][1] = EMPTY, map[3][2] = EMPTY, map[3][3] = EMPTY,
		map[3][4] = WALL, map[3][5] = EMPTY, map[3][6] = WALL;

	//{ '#', '0', '#', '0', '0', '0', '#' }
	map[4][0] = WALL, map[4][1] = EMPTY, map[4][2] = WALL, map[4][3] = EMPTY,
		map[4][4] = EMPTY, map[4][5] = EMPTY, map[4][6] = WALL;

	//{ '#', '0', '#', '0', '#', '0', '#' }
	map[5][0] = WALL, map[5][1] = EMPTY, map[5][2] = WALL, map[5][3] = EMPTY,
		map[5][4] = WALL, map[5][5] = EMPTY, map[5][6] = WALL;

	//{ '#', '#', '#', '#', '#', '#', '#' }
	map[6][0] = WALL, map[6][1] = WALL, map[6][2] = WALL, map[6][3] = WALL,
		map[6][4] = WALL, map[6][5] = WALL, map[6][6] = WALL;


	//Ĭ������յ�
	this->beg_r = 1;
	this->beg_c = 1;
	this->end_r = 5;
	this->end_c = 5;
	this->op = 1;
	this->isDiv = false;
	//���������
	srand(unsigned(time(NULL)));
}

/***************************************************************************
  �������ƣ�bfs
  ��    �ܣ�ͨ�������������������Թ�·��������¼�ڶ�ά������
  ���������
  �� �� ֵ��bool���ͣ�true��ʾ���ҵ��Թ�·����false��ʾ�Ҳ����Թ�·��
  ˵    �������ö��н��й����������
***************************************************************************/
bool maze::bfs()
{
	vis.resize(R, Vector<bool>(C, false));
	Queue<Pair<int, int>> q;
	path.resize(R, Vector<Pair<int, int>>(C, Pair<int, int>{0, 0}));


	q.emplace(Pair<int, int> { beg_r, beg_c });
	int temp_x, temp_y;

	while (!q.empty())
	{
		temp_x = q.front().first;
		temp_y = q.front().second;
		q.pop();
		//�ҵ��յ�
		if (temp_x == end_r && temp_y == end_c)
			return true;

		//�ĸ�����
		for (int i = 0; i < 4; ++i)
		{
			int new_x = temp_x + dx[i];
			int new_y = temp_y + dy[i];
			//�����磬�����谭��û�е���
			if (new_x >= 0 && new_y >= 0 && new_x < R
				&& new_y < C && vis[new_x][new_y] == false
				&& map[new_x][new_y] != WALL)
			{
				//�����¼·��
				path[new_x][new_y] = Pair<int, int>{ temp_x, temp_y };
				vis[new_x][new_y] = true;//����Ѿ�����
				q.emplace(Pair<int, int>{new_x, new_y});
			}
		}

	}
	//�Ҳ����յ�
	return false;
}

/***************************************************************************
  �������ƣ�A*�㷨
  ��    �ܣ�ͨ��A*�㷨����Թ�·��������¼�ڶ�ά������
  ���������
  �� �� ֵ��bool���ͣ�true��ʾ���ҵ��Թ�·����false��ʾ�Ҳ����Թ�·��
  ˵    ����ͨ�����ȶ�����⣬ÿ�ξ�ѡȡ������С������
***************************************************************************/
bool maze::a_star()
{
	vis.resize(R, Vector<bool>(C, false));
	path.resize(R, Vector<Pair<int, int>>(C, Pair<int, int>{0, 0}));

	//����CMP����
	CMP::beg_c = this->beg_c;
	CMP::beg_r = this->beg_r;
	CMP::end_r = this->end_r;
	CMP::end_c = this->end_c;

	Priority_queue < Pair<int, int>, Vector<Pair<int, int>>, CMP> q;//��ʼ��һ��Ҫ��Ӧtemplate��˳��

	q.emplace(Pair<int, int>{beg_r, beg_c});
	int temp_x, temp_y;

	while (!q.empty())
	{
		temp_x = q.top().first;
		temp_y = q.top().second;
		q.pop();
		//�ҵ��յ�
		if (temp_x == end_r && temp_y == end_c)
			return true;

		//�ĸ�����
		for (int i = 0; i < 4; ++i)
		{
			int new_x = temp_x + dx[i];
			int new_y = temp_y + dy[i];
			//�����磬�����谭��û�е���
			if (new_x >= 0 && new_y >= 0 && new_x < R
				&& new_y < C && vis[new_x][new_y] == false
				&& map[new_x][new_y] != WALL)
			{
				//�����¼·��
				path[new_x][new_y] = Pair<int, int>{ temp_x, temp_y };
				vis[new_x][new_y] = true;//����Ѿ�����
				q.emplace(Pair<int, int>{new_x, new_y});
			}
		}

	}
	//�Ҳ����յ�
	return false;
}

/***************************************************************************
  �������ƣ�showPath
  ��    �ܣ���bfs��a star��¼�ڶ�ά�����е�·��������¼�ڴ�����ans��
			�����������ans
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void maze::showPath()
{
	ans.clear();
	int x = end_r, y = end_c;
	ans.emplace_back(Pair<int, int>{end_r, end_c});
	//���յ����������
	while (!(x == beg_r && y == beg_c))
	{
		ans.emplace_back(Pair<int, int>{path[x][y].first, path[x][y].second});
		int temp_x = x, temp_y = y;

		x = path[temp_x][temp_y].first;
		y = path[temp_x][temp_y].second;
	}
	cout << "�Թ�·��Ϊ��" << endl;
	int Size = ans.size();
	//���ڷ����¼�����ڷ����ӡ������ȷ˳��
	for (int i = Size - 1; i >= 0; --i)
	{
		cout << '<' << ans[i].first << ',' << ans[i].second << '>';
		if (i != 0)
			cout << " ---> ";
	}
	cout << endl;
}

/***************************************************************************
  �������ƣ�_dsf
  ��    �ܣ�������������ĵݹ麯�����жϵ�ǰ�����Ƿ�Ϊ�յ㣬����return������
			�������ѵ�ǰ������Χ������
  ���������int cur_r, int cur_c����ǰ��������к�
  �� �� ֵ��bool���ͣ�true��ʾ���ҵ��Թ�·����false��ʾ�Ҳ����Թ�·��
  ˵    ��������һ��ջ��¼�߹������꣬����Χ���궼�޷��ҵ��յ�ʱ����ջ
			����ջ�е����꼴Ϊ������Թ�·��
***************************************************************************/
bool maze::_dfs(int cur_r, int cur_c)
{
	stk.emplace_back(Pair<int, int>{cur_r, cur_c});
	//�յ�
	if (cur_r == end_r && cur_c == end_c)
		return true;

	vis[cur_r][cur_c] = true;//�����յ��Ѿ����������
	for (int i = 0; i < 4; ++i)//�ĸ�����
	{
		int new_r = cur_r + dx[i];
		int new_c = cur_c + dy[i];
		//�����磬�����ظ���λ�ã������ϰ�
		if (new_r < 0 || new_c < 0 || new_r >= R || new_c >= C || vis[new_r][new_c] || map[new_r][new_c] == WALL)
			continue;

		if (_dfs(new_r, new_c))
			return true;

	}
	//���Ҳ���
	stk.pop_back();
	return false;//�Ҳ����յ�
}

/***************************************************************************
  �������ƣ�dfsStack
  ��    �ܣ�������������ķǵݹ��㷨
  ���������
  �� �� ֵ��bool���ͣ�true��ʾ���ҵ��Թ�·����false��ʾ�Ҳ����Թ�·��
  ˵    ��������һ��ջ��¼�߹������꣬����Χ���궼�޷��ҵ��յ�ʱ����ջ��
		   ��ջ�󣬵�ǰ����ȡջ���ģ�����ջ�е����꼴Ϊ������Թ�·����
		   �����ø�ջģ��ݹ���̡������Ҫ�ж�ջ��Ԫ���Ƿ�Ϊ�յ�
***************************************************************************/
bool maze::dfsStack()
{
	stk.clear();
	vis.resize(R, Vector<bool>(C, false));
	bool success = false;
	Pair<int, int> cur(beg_r, beg_c);
	stk.emplace_back(cur);

	while (!(cur.first == end_r && cur.second == end_c) && !stk.empty())
	{
		//��Ǳ�����
		vis[cur.first][cur.second] = true;

		int cnt = 0;
		for (int i = 0; i < 4; ++i)//�ĸ�����
		{
			int new_r = cur.first + dx[i];
			int new_c = cur.second + dy[i];
			//�����磬�����ظ���λ�ã������ϰ�
			if (new_r < 0 || new_c < 0 || new_r >= R || new_c >= C || vis[new_r][new_c] || map[new_r][new_c] == WALL)
			{
				++cnt;
				continue;
			}
			//��ջ
			stk.emplace_back(Pair<int, int>{new_r, new_c});
			cur.first = new_r, cur.second = new_c;//��ǰ�ڵ��ƶ�
			break;//ֻҪ�ҵ�һ��λ�����߾�����
		}
		if (cnt == 4)//�ĸ������߲��ˣ���ջ
		{
			stk.pop_back();//������·ʧ�ܵ�λ��
			cur = stk.getTail()->val;//����
		}
	}

	/*
	//���ջ������Ԫ��
	for (auto it = stk.begin(); it != stk.end(); ++it)
	{
		if (it != stk.begin())
			cout << " ---> ";
		cout << '<' << it->first << ',' << it->second << '>';
	}
	*/

	if (stk.empty())//���˶�û��·��
		return false;
	//�����Ƿ��յ�
	auto last = stk.getTail()->val;
	return (last.first == end_r && last.second == end_c);
}

/***************************************************************************
   �������ƣ�showPathDfs
   ��    �ܣ�չʾdfs���ݹ�ͷǵݹ飩�㷨���Թ�·�������
   ���������
   �� �� ֵ��
   ˵    ����
***************************************************************************/
void maze::showPathDfs()
{
	cout << "�Թ�·��Ϊ��" << endl;
	for (auto it = stk.begin(); it != stk.end(); ++it)
	{
		auto node = *it;
		if (it != stk.begin())
			cout << " ---> ";
		cout << '<' << node.first << ',' << node.second << '>';
	}
	cout << endl;
}

/***************************************************************************
	�������ƣ�solutions
	��    �ܣ��Թ���Ķ���ӿڣ��û�ѡ������Թ�·���ķ������������Ӧ�Ľ��
	���������
	�� �� ֵ��
	˵    �������û�����Ƿ�����������ʾ
 ***************************************************************************/
void maze::solutions() {
	show();
	bool find = false;
	cout << "1.������ȱ������ݹ飩" << endl;
	cout << "2.������ȱ�����������" << endl;
	cout << "3.������ȱ���" << endl;
	cout << "4.A_star�㷨" << endl;
	cout << endl << "��ѡ��Ѱ·����: ";
	op = 0;
	while (1)
	{
		cin >> op;
		if (cin.fail() || op < 1 || op > 4)
		{
			cout << "������������������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}
	switch (op)
	{
		case 1:
			if (dfs())
				showPathDfs(), find = true;
			else
				cout << "�Ҳ���·����" << endl;
			break;
		case 2:
			if (dfsStack())
				showPathDfs(), find = true;
			else
				cout << "�Ҳ���·����" << endl;
			break;
		case 3:
			if (bfs())
				showPath(), find = true;
			else
				cout << "�Ҳ���·��" << endl;
			break;
		case 4:
			if (a_star())
				showPath(), find = true;
			else
				cout << "�Ҳ���·��" << endl;
			break;
		default:
			cout << "��������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			break;
	}
	//����ҵ���·��������չʾ
	if (find)
	{
		markPath();
		cout << endl;
		show();
	}
}

/***************************************************************************
	�������ƣ�markPath
	��    �ܣ�ͨ���Թ�����㷨�ó���·���޸����б�ʾ�Թ��Ķ�ά����
	���������
	�� �� ֵ��
	˵    ����ѡ��ͬ�Թ��㷨���洢·����Ӧ��ͬ�����ݽṹ��������Ҫ����
 ***************************************************************************/
void maze::markPath()
{
	if (op == 1 || op == 2)
		for (auto it = stk.begin(); it != stk.end(); ++it)
			map[it->first][it->second] = PATH;
	else if (op == 3 || op == 4)
		for (auto it = ans.begin(); it != ans.end(); ++it)
			map[it->first][it->second] = PATH;

}

/***************************************************************************
	�������ƣ�prim
	��    �ܣ�ͨ��prim�㷨�����Թ�
	���������
	�� �� ֵ��
	˵    ����
 ***************************************************************************/
void maze::prim()
{
	Vector<Pair<int, int>> stk;
	//�������
	stk.emplace_back(Pair<int, int>(beg_r, beg_c));

	while (!stk.empty())
	{
		//�����ջ��ȡһ��·��λ��
		int index = rand() % stk.size();
		Pair<int, int> temp = stk[index];
		stk.remove(stk.begin() + index);

		//��¼�ĸ������ж���������
		int road_count = 0;
		for (int i = 0; i < 4; ++i)
		{
			Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
			if (isRoad(nextPlace))
				++road_count;
		}
		//û�л���ֻ��һ��·����ȥ�����µķ��򣬱�֤·�����Ϊ1
		if (road_count <= 1)
		{
			map[temp.first][temp.second] = '0';
			//��Χ�ĸ�������ջ
			for (int i = 0; i < 4; ++i)
			{
				Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
				if (isWall(nextPlace))//��ǽ����ջ
					stk.emplace_back(nextPlace);
			}
		}
	}
}

/***************************************************************************
	 �������ƣ�trackBack
	 ��    �ܣ�ͨ�������㷨�����Թ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
  ***************************************************************************/
void maze::trackBack()
{
	List<Pair<int, int>> stk;
	//�������
	stk.emplace_back(Pair<int, int>(beg_r, beg_c));

	while (!stk.empty())
	{
		Pair<int, int> temp = stk.getTail()->val;
		stk.pop_back();

		//��¼�ĸ������ж���������
		int road_count = 0;
		for (int i = 0; i < 4; ++i)
		{
			Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
			if (isRoad(nextPlace))
				++road_count;
		}
		//û�л���ֻ��һ��·����ȥ�����µķ��򣬱�֤·�����Ϊ1
		if (road_count <= 1)
		{
			map[temp.first][temp.second] = '0';
			Vector<Pair<int, int>> nextPlaces;
			//��Χ�ĸ�������ջ
			for (int i = 0; i < 4; ++i)
			{
				Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
				if (isWall(nextPlace))//��ǽ����ջ
					nextPlaces.emplace_back(nextPlace);
			}
			//��ջǰ����˳�򣬴�ջ��ȡԪ�ص�ʱ�����
			Random_shuffle(nextPlaces.begin(), nextPlaces.end());
			for (auto it = nextPlaces.begin(); it != nextPlaces.end(); ++it)
				stk.emplace_back(*it);
		}
	}
}

/***************************************************************************
	 �������ƣ�division
	 ��    �ܣ�ͨ���ݹ���εķ��������Թ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
  ***************************************************************************/
void maze::division()
{
	//��Ҫһ���߿�
	for (int i = 0; i < R; ++i)
		delete[] map[i];
	delete[] map;

	//���������Թ������С
	map = new char* [R + 2];
	for (int i = 0; i < R + 2; ++i)
		map[i] = new char[C + 2];

	//���ϱ߿�
	for (int i = 0; i < R + 2; ++i)
		map[i][0] = map[i][C + 1] = WALL;

	for (int i = 0; i < C + 2; ++i)
		map[0][i] = map[R + 1][i] = WALL;

	//�м�û�б߿�
	for (int i = 1; i < R + 1; ++i)
		for (int j = 1; j < C + 1; ++j)
			map[i][j] = EMPTY;

	_division(1, 1, R, C);
	//����������˱߿�
	isDiv = true;
}

/***************************************************************************
	�������ƣ�_division
	��    �ܣ��ݹ�����㷨�ĵݹ麯��
	���������
	�� �� ֵ��
	˵    ����
 ***************************************************************************/
void maze::_division(int x1, int y1, int x2, int y2)
{
	//�ݹ���������������ٷָ�
	if (x2 - x1 <= 1 || y2 - y1 <= 1)
		return;

	//���ȡ�ָ���λ��
	int x = x1 + 1 + rand() % (x2 - x1 - 1);
	int y = y1 + 1 + rand() % (y2 - y1 - 1);

	//��ǽ
	for (int i = x1; i <= x2; ++i)
		map[i][y] = WALL;
	for (int i = y1; i <= y2; ++i)
		map[x][i] = WALL;

	//�ݹ�����С�ķָ�õķ���
	_division(x1, y1, x - 1, y - 1);//����
	_division(x + 1, y1, x2, y - 1);//����
	_division(x1, y + 1, x - 1, y2);//����
	_division(x + 1, y + 1, x2, y2);//����

	//���ȡ����ǽ����
	bool walls[4] = { false };
	walls[rand() % 4] = true;

	for (int i = 0; i < 4; ++i)
	{
		if (walls[i])
			continue;
		int wall_x = x;
		int wall_y = y;
		switch (i)
		{
			//��Ҫ�ж��������λ���Ƿ��ܴ�ͨ������������
			//�ж��������������ڵ�������ǽ
			case 0:
				do {
					wall_x = x1 + rand() % (x - x1);
				} while (map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 3 * WALL
					|| map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 4 * WALL);
				break;
			case 1:
				do {
					wall_y = y + 1 + rand() % (y2 - y);
				} while (map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 3 * WALL
					|| map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 4 * WALL);
				break;
			case 2:
				do {
					wall_x = x + 1 + rand() % (x2 - x);
				} while (map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 3 * WALL
					|| map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 4 * WALL);
				break;
			case 3:
				do {
					wall_y = y1 + rand() % (y - y1);
				} while (map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 3 * WALL
					|| map[wall_x - 1][wall_y] + map[wall_x + 1][wall_y]
					+ map[wall_x][wall_y - 1] + map[wall_x][wall_y + 1] == 4 * WALL);
				break;
			default:
				break;
		}
		map[wall_x][wall_y] = EMPTY;
	}
}

/***************************************************************************
	 �������ƣ�kruskal
	 ��    �ܣ�ͨ��kruskal�㷨�����Թ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
  ***************************************************************************/
void maze::kruskal()
{
	//��ż�������ȱ����������
	bool RIsEven = R % 2 == 0;
	bool CIsEven = C % 2 == 0;

	Vector<Pair<int, int>> walls;
	//��ͼ��ʼ�����ֳ�С�ң�����¼ǽ
	for (int i = 0; i < R - RIsEven; i += 2)
		for (int j = 0; j < C - CIsEven; j += 2)
		{
			map[i][j] = EMPTY;
			//�������Ҷ���ǽ��ǽ�ǲ���¼��
			if (j + 1 < C - CIsEven)//��¼�ո��ұߵ�
				walls.emplace_back(Pair<int, int>(i, j + 1));
			if (i + 1 < R - RIsEven)
				walls.emplace_back(Pair<int, int>(i + 1, j));
		}
	//���鼯
	const int TOTAL = (R - RIsEven) * (C - CIsEven);
	Vector<int> fa(TOTAL);
	for (int i = 0; i < TOTAL; ++i)
		fa[i] = i;
	//����ǽ����
	Random_shuffle(walls.begin(), walls.end());

	while (!walls.empty())
	{
		Pair<int, int> wall = walls.back();
		int x = wall.first, y = wall.second;

		//����ֻ���������У�������ż����
		Pair<int, int> c1 = x % 2 ? Pair<int, int>(x - 1, y) : Pair<int, int>(x, y - 1);
		Pair<int, int> c2 = x % 2 ? Pair<int, int>(x + 1, y) : Pair<int, int>(x, y + 1);


		int index1 = c1.first * (R - RIsEven) + c1.second;
		int index2 = c2.first * (R - RIsEven) + c2.second;
		int index3 = x * (R - RIsEven) + y;
		if (is_connected(index1, index2, fa) == false)//������ͨ������
		{
			union_xy(index1, index2, fa);
			union_xy(index1, index3, fa);
			map[x][y] = '0';
		}

		walls.pop_back();
	}

}
/***************************************************************************
	�������ƣ�showNew
	��    �ܣ�չʾ�µ��Թ���ͼ
	���������
	�� �� ֵ��
	˵    ����
 ***************************************************************************/
void maze::showNew()
{
	for (int i = 0; i < C + 2; ++i)
		printf("%c ", WALL);
	cout << endl;

	for (int i = 0 + isDiv; i < R + isDiv; ++i)
	{
		printf("%c ", WALL);
		for (int j = 0 + isDiv; j < C + isDiv; ++j)
		{
			printf("%-2c", map[i][j]);
		}
		printf("%c ", WALL);
		cout << endl;
	}

	for (int i = 0; i < C + 2; ++i)
		printf("%c ", WALL);
	cout << endl;
}

/***************************************************************************
	�������ƣ�setWidHei
	��    �ܣ��������õ�ͼ�Ĵ�С�ߴ�
	���������const int R, const int C���µ�ͼ������������
	�� �� ֵ��
	˵    ����
 ***************************************************************************/
void maze::setWidHei(const int R, const int C) {
	//һ���ľ�ֱ���˳�
	if (this->R == R && this->C == C)
		return;

	//����ԭ����
	for (int i = 0; i < this->R; ++i)
		delete[] map[i];
	delete[] map;

	//��������ռ�
	map = new char* [R];
	for (int i = 0; i < R; ++i)
		map[i] = new char[C];

	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			map[i][j] = WALL;

	this->R = R;
	this->C = C;
}

/***************************************************************************
	 �������ƣ�setStartEnd
	 ��    �ܣ������Թ�������յ�
	 ���������const int beg_r, const int beg_c, const int end_r, const int end_c
			   �ֱ�����ͼ����������յ�����
	 �� �� ֵ��
	 ˵    ����
  ***************************************************************************/
void maze::setStartEnd(const int beg_r, const int beg_c, const int end_r, const int end_c)
{
	this->beg_r = beg_r;
	this->beg_c = beg_c;
	this->end_r = end_r;
	this->end_c = end_c;
}

//���������С������յ㣬�㷨ѡ��
/***************************************************************************
	�������ƣ�SlcSizePointAlg
	��    �ܣ����������С������յ㣬�㷨ѡ��
	���������
	�� �� ֵ��
	˵    ����
 ***************************************************************************/
void maze::SlcSizePointAlg()
{
	int tempR, tempC;
	//������������
	while (1)
	{
		cout << "�������ͼ������������" << endl;
		cin >> tempR >> tempC;
		if (cin.fail())
			cout << "��������" << endl;
		else if (tempR <= 0)
			cout << "����ӦΪ������" << endl;
		else if (tempC <= 0)
			cout << "����ӦΪ������" << endl;
		else if (tempR > 150)
			cout << "��������" << endl;
		else if (tempC > 150)
			cout << "��������" << endl;
		else
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	//�����Թ���С
	setWidHei(tempR, tempC);

	cout << "��ѡ���Թ����ɷ�ʽ" << endl;
	cout << "1.prim(Ĭ��)" << endl;
	cout << "2.�ݹ����" << endl;
	cout << "3.�ݹ�ָ�" << endl;
	cout << "4.kruskal" << endl;
	char ch;
	cin >> ch;
	switch (ch)
	{
		case '2':
			trackBack();
			break;
		case '3':
			division();
			break;
		case '4':
			kruskal();
			break;
		default:
			prim();
			break;
	}
	cout << endl;
	//չʾ���ɵĵ�ͼ
	showNew();
	//����������յ�����
	Pair<int, int> beg, end;
	cout << "����������յ�����(�� ��, ���кŴ�-1��ʼ)" << endl;
	while (1)
	{
		cin >> beg.first >> beg.second >> end.first >> end.second;
		if (cin.fail())
			cout << "��������" << endl;
		else if (isUnreachable(beg))
			cout << "�������" << endl;
		else if (isUnreachable(end))
			cout << "�յ�����" << endl;
		else
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}

	setStartEnd(beg.first, beg.second, end.first, end.second);

	if (bfs())
		showPath();
	else
		cout << "�Ҳ���·��" << endl;
}

int main() {
	maze m;
	m.solutions();
	//m.SlcSizePointAlg();
	to_be_continue();
	return 0;
}
