#include "3_2151298_杨滕超.h"

using namespace std;

//设置CMP初始参数
//注意到struct中静态数据成员的赋值应在类外的对应cpp文件中
int CMP::beg_c = 1;
int CMP::beg_r = 1;
int CMP::end_r = 5;
int CMP::end_c = 5;

/***************************************************************************
  函数名称：to_be_continue
  功    能：程序结束后等到用户输入任意字符再关闭cmd窗口
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continue()
{
	cin.ignore(65536, '\n');
	cout << endl << "回车键继续操作" << endl;

	cin.get();
	return;
}

/***************************************************************************
  函数名称：maze
  功    能：初始化maze类，包括迷宫大小和迷宫的起点终点和内容
  输入参数：
  返 回 值：
  说    明：maze类的构造函数
***************************************************************************/
maze::maze()
{
	//迷宫默认大小
	R = C = 7;
	//设置迷宫数组大小
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


	//默认起点终点
	this->beg_r = 1;
	this->beg_c = 1;
	this->end_r = 5;
	this->end_c = 5;
	this->op = 1;
	this->isDiv = false;
	//生成随机数
	srand(unsigned(time(NULL)));
}

/***************************************************************************
  函数名称：bfs
  功    能：通过广度优先搜索，求解迷宫路径，并记录在二维数组中
  输入参数：
  返 回 值：bool类型，true表示能找到迷宫路径，false表示找不到迷宫路径
  说    明：利用队列进行广度优先搜索
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
		//找到终点
		if (temp_x == end_r && temp_y == end_c)
			return true;

		//四个方向
		for (int i = 0; i < 4; ++i)
		{
			int new_x = temp_x + dx[i];
			int new_y = temp_y + dy[i];
			//不出界，不是阻碍，没有到过
			if (new_x >= 0 && new_y >= 0 && new_x < R
				&& new_y < C && vis[new_x][new_y] == false
				&& map[new_x][new_y] != WALL)
			{
				//反向记录路线
				path[new_x][new_y] = Pair<int, int>{ temp_x, temp_y };
				vis[new_x][new_y] = true;//标记已经到过
				q.emplace(Pair<int, int>{new_x, new_y});
			}
		}

	}
	//找不到终点
	return false;
}

/***************************************************************************
  函数名称：A*算法
  功    能：通过A*算法求解迷宫路径，并记录在二维数组中
  输入参数：
  返 回 值：bool类型，true表示能找到迷宫路径，false表示找不到迷宫路径
  说    明：通过优先队列求解，每次均选取估价最小的坐标
***************************************************************************/
bool maze::a_star()
{
	vis.resize(R, Vector<bool>(C, false));
	path.resize(R, Vector<Pair<int, int>>(C, Pair<int, int>{0, 0}));

	//设置CMP参数
	CMP::beg_c = this->beg_c;
	CMP::beg_r = this->beg_r;
	CMP::end_r = this->end_r;
	CMP::end_c = this->end_c;

	Priority_queue < Pair<int, int>, Vector<Pair<int, int>>, CMP> q;//初始化一定要对应template的顺序

	q.emplace(Pair<int, int>{beg_r, beg_c});
	int temp_x, temp_y;

	while (!q.empty())
	{
		temp_x = q.top().first;
		temp_y = q.top().second;
		q.pop();
		//找到终点
		if (temp_x == end_r && temp_y == end_c)
			return true;

		//四个方向
		for (int i = 0; i < 4; ++i)
		{
			int new_x = temp_x + dx[i];
			int new_y = temp_y + dy[i];
			//不出界，不是阻碍，没有到过
			if (new_x >= 0 && new_y >= 0 && new_x < R
				&& new_y < C && vis[new_x][new_y] == false
				&& map[new_x][new_y] != WALL)
			{
				//反向记录路线
				path[new_x][new_y] = Pair<int, int>{ temp_x, temp_y };
				vis[new_x][new_y] = true;//标记已经到过
				q.emplace(Pair<int, int>{new_x, new_y});
			}
		}

	}
	//找不到终点
	return false;
}

/***************************************************************************
  函数名称：showPath
  功    能：将bfs与a star记录在二维数组中的路径求解出记录在答案数组ans中
			并输出答案数组ans
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void maze::showPath()
{
	ans.clear();
	int x = end_r, y = end_c;
	ans.emplace_back(Pair<int, int>{end_r, end_c});
	//从终点往回找起点
	while (!(x == beg_r && y == beg_c))
	{
		ans.emplace_back(Pair<int, int>{path[x][y].first, path[x][y].second});
		int temp_x = x, temp_y = y;

		x = path[temp_x][temp_y].first;
		y = path[temp_x][temp_y].second;
	}
	cout << "迷宫路径为：" << endl;
	int Size = ans.size();
	//由于反向记录，现在反向打印才是正确顺序
	for (int i = Size - 1; i >= 0; --i)
	{
		cout << '<' << ans[i].first << ',' << ans[i].second << '>';
		if (i != 0)
			cout << " ---> ";
	}
	cout << endl;
}

/***************************************************************************
  函数名称：_dsf
  功    能：深度优先搜索的递归函数，判断当前坐标是否为终点，是则return，否则
			继续深搜当前坐标周围的坐标
  输入参数：int cur_r, int cur_c，当前坐标的行列号
  返 回 值：bool类型，true表示能找到迷宫路径，false表示找不到迷宫路径
  说    明：利用一个栈记录走过的坐标，当周围坐标都无法找到终点时候退栈
			最终栈中的坐标即为所求的迷宫路径
***************************************************************************/
bool maze::_dfs(int cur_r, int cur_c)
{
	stk.emplace_back(Pair<int, int>{cur_r, cur_c});
	//终点
	if (cur_r == end_r && cur_c == end_c)
		return true;

	vis[cur_r][cur_c] = true;//不是终点已经遍历过标记
	for (int i = 0; i < 4; ++i)//四个方向
	{
		int new_r = cur_r + dx[i];
		int new_c = cur_c + dy[i];
		//不出界，不走重复的位置，不是障碍
		if (new_r < 0 || new_c < 0 || new_r >= R || new_c >= C || vis[new_r][new_c] || map[new_r][new_c] == WALL)
			continue;

		if (_dfs(new_r, new_c))
			return true;

	}
	//都找不到
	stk.pop_back();
	return false;//找不到终点
}

/***************************************************************************
  函数名称：dfsStack
  功    能：深度优先搜索的非递归算法
  输入参数：
  返 回 值：bool类型，true表示能找到迷宫路径，false表示找不到迷宫路径
  说    明：利用一个栈记录走过的坐标，当周围坐标都无法找到终点时候退栈，
		   退栈后，当前坐标取栈顶的，最终栈中的坐标即为所求的迷宫路径。
		   并利用该栈模拟递归过程。最后需要判断栈顶元素是否为终点
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
		//标记遍历过
		vis[cur.first][cur.second] = true;

		int cnt = 0;
		for (int i = 0; i < 4; ++i)//四个方向
		{
			int new_r = cur.first + dx[i];
			int new_c = cur.second + dy[i];
			//不出界，不走重复的位置，不是障碍
			if (new_r < 0 || new_c < 0 || new_r >= R || new_c >= C || vis[new_r][new_c] || map[new_r][new_c] == WALL)
			{
				++cnt;
				continue;
			}
			//入栈
			stk.emplace_back(Pair<int, int>{new_r, new_c});
			cur.first = new_r, cur.second = new_c;//当前节点移动
			break;//只要找到一个位置能走就先走
		}
		if (cnt == 4)//四个方向都走不了，出栈
		{
			stk.pop_back();//弹出找路失败的位置
			cur = stk.getTail()->val;//回溯
		}
	}

	/*
	//输出栈中所有元素
	for (auto it = stk.begin(); it != stk.end(); ++it)
	{
		if (it != stk.begin())
			cout << " ---> ";
		cout << '<' << it->first << ',' << it->second << '>';
	}
	*/

	if (stk.empty())//空了都没有路径
		return false;
	//最后的是否终点
	auto last = stk.getTail()->val;
	return (last.first == end_r && last.second == end_c);
}

/***************************************************************************
   函数名称：showPathDfs
   功    能：展示dfs（递归和非递归）算法的迷宫路径求解结果
   输入参数：
   返 回 值：
   说    明：
***************************************************************************/
void maze::showPathDfs()
{
	cout << "迷宫路径为：" << endl;
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
	函数名称：solutions
	功    能：迷宫类的对外接口，用户选择求解迷宫路径的方法，并输出对应的结果
	输入参数：
	返 回 值：
	说    明：若用户输入非法，输出相关提示
 ***************************************************************************/
void maze::solutions() {
	show();
	bool find = false;
	cout << "1.深度优先遍历（递归）" << endl;
	cout << "2.深度优先遍历（迭代）" << endl;
	cout << "3.广度优先遍历" << endl;
	cout << "4.A_star算法" << endl;
	cout << endl << "请选择寻路方法: ";
	op = 0;
	while (1)
	{
		cin >> op;
		if (cin.fail() || op < 1 || op > 4)
		{
			cout << "输入有误，请重新输入" << endl;
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
				cout << "找不到路径！" << endl;
			break;
		case 2:
			if (dfsStack())
				showPathDfs(), find = true;
			else
				cout << "找不到路径！" << endl;
			break;
		case 3:
			if (bfs())
				showPath(), find = true;
			else
				cout << "找不到路径" << endl;
			break;
		case 4:
			if (a_star())
				showPath(), find = true;
			else
				cout << "找不到路径" << endl;
			break;
		default:
			cout << "输入有误！" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
			break;
	}
	//如果找到了路径，重新展示
	if (find)
	{
		markPath();
		cout << endl;
		show();
	}
}

/***************************************************************************
	函数名称：markPath
	功    能：通过迷宫求解算法得出的路径修改类中表示迷宫的二维数组
	输入参数：
	返 回 值：
	说    明：选择不同迷宫算法，存储路径对应不同的数据结构，这里需要区分
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
	函数名称：prim
	功    能：通过prim算法生成迷宫
	输入参数：
	返 回 值：
	说    明：
 ***************************************************************************/
void maze::prim()
{
	Vector<Pair<int, int>> stk;
	//设置起点
	stk.emplace_back(Pair<int, int>(beg_r, beg_c));

	while (!stk.empty())
	{
		//随机从栈中取一个路径位置
		int index = rand() % stk.size();
		Pair<int, int> temp = stk[index];
		stk.remove(stk.begin() + index);

		//记录四个方向有多少条能走
		int road_count = 0;
		for (int i = 0; i < 4; ++i)
		{
			Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
			if (isRoad(nextPlace))
				++road_count;
		}
		//没有或者只有一条路，就去开辟新的方向，保证路径宽度为1
		if (road_count <= 1)
		{
			map[temp.first][temp.second] = '0';
			//周围四个方向入栈
			for (int i = 0; i < 4; ++i)
			{
				Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
				if (isWall(nextPlace))//是墙才入栈
					stk.emplace_back(nextPlace);
			}
		}
	}
}

/***************************************************************************
	 函数名称：trackBack
	 功    能：通过回溯算法生成迷宫
	 输入参数：
	 返 回 值：
	 说    明：
  ***************************************************************************/
void maze::trackBack()
{
	List<Pair<int, int>> stk;
	//设置起点
	stk.emplace_back(Pair<int, int>(beg_r, beg_c));

	while (!stk.empty())
	{
		Pair<int, int> temp = stk.getTail()->val;
		stk.pop_back();

		//记录四个方向有多少条能走
		int road_count = 0;
		for (int i = 0; i < 4; ++i)
		{
			Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
			if (isRoad(nextPlace))
				++road_count;
		}
		//没有或者只有一条路，就去开辟新的方向，保证路径宽度为1
		if (road_count <= 1)
		{
			map[temp.first][temp.second] = '0';
			Vector<Pair<int, int>> nextPlaces;
			//周围四个方向入栈
			for (int i = 0; i < 4; ++i)
			{
				Pair<int, int> nextPlace(temp.first + dx[i], temp.second + dy[i]);
				if (isWall(nextPlace))//是墙才入栈
					nextPlaces.emplace_back(nextPlace);
			}
			//入栈前打乱顺序，从栈顶取元素的时候随机
			Random_shuffle(nextPlaces.begin(), nextPlaces.end());
			for (auto it = nextPlaces.begin(); it != nextPlaces.end(); ++it)
				stk.emplace_back(*it);
		}
	}
}

/***************************************************************************
	 函数名称：division
	 功    能：通过递归分治的方法生成迷宫
	 输入参数：
	 返 回 值：
	 说    明：
  ***************************************************************************/
void maze::division()
{
	//需要一个边框
	for (int i = 0; i < R; ++i)
		delete[] map[i];
	delete[] map;

	//重新设置迷宫数组大小
	map = new char* [R + 2];
	for (int i = 0; i < R + 2; ++i)
		map[i] = new char[C + 2];

	//加上边框
	for (int i = 0; i < R + 2; ++i)
		map[i][0] = map[i][C + 1] = WALL;

	for (int i = 0; i < C + 2; ++i)
		map[0][i] = map[R + 1][i] = WALL;

	//中间没有边框
	for (int i = 1; i < R + 1; ++i)
		for (int j = 1; j < C + 1; ++j)
			map[i][j] = EMPTY;

	_division(1, 1, R, C);
	//标记了扩大了边框
	isDiv = true;
}

/***************************************************************************
	函数名称：_division
	功    能：递归分治算法的递归函数
	输入参数：
	返 回 值：
	说    明：
 ***************************************************************************/
void maze::_division(int x1, int y1, int x2, int y2)
{
	//递归结束条件，不能再分割
	if (x2 - x1 <= 1 || y2 - y1 <= 1)
		return;

	//随机取分割线位置
	int x = x1 + 1 + rand() % (x2 - x1 - 1);
	int y = y1 + 1 + rand() % (y2 - y1 - 1);

	//画墙
	for (int i = x1; i <= x2; ++i)
		map[i][y] = WALL;
	for (int i = y1; i <= y2; ++i)
		map[x][i] = WALL;

	//递归进入更小的分割好的方格
	_division(x1, y1, x - 1, y - 1);//左上
	_division(x + 1, y1, x2, y - 1);//左下
	_division(x1, y + 1, x - 1, y2);//右上
	_division(x + 1, y + 1, x2, y2);//右下

	//随机取三面墙开点
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
			//需要判断随机到的位置是否能打通相邻两块区域
			//判断其上下左右少于等于两个墙
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
	 函数名称：kruskal
	 功    能：通过kruskal算法生成迷宫
	 输入参数：
	 返 回 值：
	 说    明：
  ***************************************************************************/
void maze::kruskal()
{
	//对偶数个边先变成奇数个边
	bool RIsEven = R % 2 == 0;
	bool CIsEven = C % 2 == 0;

	Vector<Pair<int, int>> walls;
	//地图初始化，分成小室，并记录墙
	for (int i = 0; i < R - RIsEven; i += 2)
		for (int j = 0; j < C - CIsEven; j += 2)
		{
			map[i][j] = EMPTY;
			//上下左右都是墙的墙是不记录的
			if (j + 1 < C - CIsEven)//记录空格右边的
				walls.emplace_back(Pair<int, int>(i, j + 1));
			if (i + 1 < R - RIsEven)
				walls.emplace_back(Pair<int, int>(i + 1, j));
		}
	//并查集
	const int TOTAL = (R - RIsEven) * (C - CIsEven);
	Vector<int> fa(TOTAL);
	for (int i = 0; i < TOTAL; ++i)
		fa[i] = i;
	//打乱墙序列
	Random_shuffle(walls.begin(), walls.end());

	while (!walls.empty())
	{
		Pair<int, int> wall = walls.back();
		int x = wall.first, y = wall.second;

		//上下只有在奇数行，左右在偶数行
		Pair<int, int> c1 = x % 2 ? Pair<int, int>(x - 1, y) : Pair<int, int>(x, y - 1);
		Pair<int, int> c2 = x % 2 ? Pair<int, int>(x + 1, y) : Pair<int, int>(x, y + 1);


		int index1 = c1.first * (R - RIsEven) + c1.second;
		int index2 = c2.first * (R - RIsEven) + c2.second;
		int index3 = x * (R - RIsEven) + y;
		if (is_connected(index1, index2, fa) == false)//还不连通可以连
		{
			union_xy(index1, index2, fa);
			union_xy(index1, index3, fa);
			map[x][y] = '0';
		}

		walls.pop_back();
	}

}
/***************************************************************************
	函数名称：showNew
	功    能：展示新的迷宫地图
	输入参数：
	返 回 值：
	说    明：
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
	函数名称：setWidHei
	功    能：重新设置地图的大小尺寸
	输入参数：const int R, const int C，新地图的行数和列数
	返 回 值：
	说    明：
 ***************************************************************************/
void maze::setWidHei(const int R, const int C) {
	//一样的就直接退出
	if (this->R == R && this->C == C)
		return;

	//析构原来的
	for (int i = 0; i < this->R; ++i)
		delete[] map[i];
	delete[] map;

	//重新申请空间
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
	 函数名称：setStartEnd
	 功    能：设置迷宫的起点终点
	 输入参数：const int beg_r, const int beg_c, const int end_r, const int end_c
			   分别代表地图的起点坐标终点坐标
	 返 回 值：
	 说    明：
  ***************************************************************************/
void maze::setStartEnd(const int beg_r, const int beg_c, const int end_r, const int end_c)
{
	this->beg_r = beg_r;
	this->beg_c = beg_c;
	this->end_r = end_r;
	this->end_c = end_c;
}

//设置数组大小，起点终点，算法选择
/***************************************************************************
	函数名称：SlcSizePointAlg
	功    能：设置数组大小，起点终点，算法选择
	输入参数：
	返 回 值：
	说    明：
 ***************************************************************************/
void maze::SlcSizePointAlg()
{
	int tempR, tempC;
	//输入行数列数
	while (1)
	{
		cout << "请输入地图的行数与列数" << endl;
		cin >> tempR >> tempC;
		if (cin.fail())
			cout << "输入有误" << endl;
		else if (tempR <= 0)
			cout << "行数应为正整数" << endl;
		else if (tempC <= 0)
			cout << "列数应为正整数" << endl;
		else if (tempR > 150)
			cout << "行数过大" << endl;
		else if (tempC > 150)
			cout << "列数过大" << endl;
		else
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}
	//设置迷宫大小
	setWidHei(tempR, tempC);

	cout << "请选择迷宫生成方式" << endl;
	cout << "1.prim(默认)" << endl;
	cout << "2.递归回溯" << endl;
	cout << "3.递归分割" << endl;
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
	//展示生成的地图
	showNew();
	//请输入起点终点坐标
	Pair<int, int> beg, end;
	cout << "请输入起点终点坐标(行 列, 行列号从-1开始)" << endl;
	while (1)
	{
		cin >> beg.first >> beg.second >> end.first >> end.second;
		if (cin.fail())
			cout << "输入有误" << endl;
		else if (isUnreachable(beg))
			cout << "起点有误" << endl;
		else if (isUnreachable(end))
			cout << "终点有误" << endl;
		else
			break;
		cin.clear();
		cin.ignore(65536, '\n');
	}

	setStartEnd(beg.first, beg.second, end.first, end.second);

	if (bfs())
		showPath();
	else
		cout << "找不到路径" << endl;
}

int main() {
	maze m;
	m.solutions();
	//m.SlcSizePointAlg();
	to_be_continue();
	return 0;
}
