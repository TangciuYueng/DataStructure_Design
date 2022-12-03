#include "8_2151298_杨滕超.h"


/***************************************************************************
  函数名称：clear
  功    能：清空
  输入参数：
  返 回 值：
  说    明：对电网系统类中所有数据结构清空初始化，以保证下一次运行的正确性
***************************************************************************/
void elecSys::clear()
{
    hash.clear();
    node.clear();
    adj.clear();
    ansEdge.clear();
    uf.clear();
    cost = 0;
    start = 0;
    tot = 0;
    edgeFinish = false;
}

/***************************************************************************
  函数名称：buildNode
  功    能：获得电网结点名称
  输入参数：
  返 回 值：
  说    明：需要判断输入结点个数是否合法
            需要判断所输入的结点是否与电网系统中已有结点重名
            若重名则输出相关提示重新输入
***************************************************************************/
void elecSys::buildNode()
{
    //清除上次记录
    clear();
    cout << "请输入结点的个数: ";
    while (1)
    {
        cin >> tot;
        if (cin.fail() || tot <= 0)
        {
            cout << "请输入正整数" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
        }
        else
            break;
    }
    cout << "请依次输入各顶点的名称:" << endl;
    String temp;
    for (int i = 0; i < tot; ++i)
    {
        cin >> temp;
        //保证没有相同顶点
        auto Nullptr = tree_iterator<String, int>(NULL);
        auto it = hash.find(temp);
        if (it == Nullptr)
        {
            hash[temp] = i;//顶点名称与下标对应
            node.emplace_back(temp);
        }
        else
        {
            cout << "不能出现相同顶点，请重新输入该顶点名称" << endl;
            --i;
        }
    }
    //邻接矩阵初始化
    adj.resize(tot, Vector<int>(tot, INT_MAX));
    //并查集初始化
    uf.resize(tot);
}

/***************************************************************************
  函数名称：addEdges
  功    能：添加电网系统的边
  输入参数：
  返 回 值：
  说    明：建立边之前首先需要判断是否已经建立顶点
            需要判断结点数量，只有一个结点无需构造最小生成树
            输入的边 结点名称1 结点名称2 边权值
            若不存在与电网中已有名称，则输出相关提示
            边权值为负数时退出输入
            同时需要判断构成的图是否连通
***************************************************************************/
void elecSys::addEdges()
{
    if (tot == 0)
    {
        cout << "请先构建电网顶点" << endl;
        return;
    }
    if (tot == 1)
    {
        cout << "只有一个顶点，无需构造最小生成树" << endl;
        return;
    }
    String nodeA, nodeB;
    int val;
    cout << endl << "输入边的值为负数时候退出输入" << endl;
    while (1)
    {
        cout << "请输入两个顶点及边: ";
        cin >> nodeA >> nodeB >> val;
        //判断输入顶点是否相同
        if (nodeA == nodeB)
        {
            cout << "输入电网顶点不应相同，请重新输入" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (cin.fail())
        {
            cout << "输入电网边值有误，请重新输入" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (val <= 0)//不出现负边，退出
            break;
        //判断输入顶点是否有效
        auto itA = hash.find(nodeA);
        auto itB = hash.find(nodeB);
        if (itA == hash.end())
        {
            cout << "顶点" << nodeA << "不存在" << endl;
            continue;
        }
        if (itB == hash.end())
        {
            cout << "顶点" << nodeB << "不存在" << endl;
            continue;
        }
        //更新邻接表
        adj[itA->second][itB->second] = min(adj[itA->second][itB->second], val);
        adj[itB->second][itA->second] = adj[itA->second][itB->second];
        adj[itA->second][itA->second] = 0;
        adj[itB->second][itB->second] = 0;
        //标记连接上结点
        uf.union_xy(itA->second, itB->second);
    }
    //都连上了numOfSet == 1
    if (uf.getNumOfSet() == 1)
        edgeFinish = true;
}

/***************************************************************************
  函数名称：buildTree
  功    能：调用生成最小生成树提示，根据用户输入的起点构造最小生成树
  输入参数：
  返 回 值：
  说    明：判断结点个数，个数为0提示先构建结点，为1提示无需构造
            判断是否连通，未连通提示返回上一个步骤

***************************************************************************/
void elecSys::buildTree()
{
    if (tot == 0)
    {
        cout << "请先构建电网顶点" << endl;
        return;
    }
    if (tot == 1)
    {
        cout << "只有一个顶点，无需构造最小生成树" << endl;
        return;
    }
    if (edgeFinish == false)
    {
        cout << "仍有电网顶点尚未连接，无法构造最小生成树，请继续添加电网边" << endl;
        return;
    }
    String startNode;
    cout << "请输入起点: ";
    while (1)
    {
        cin >> startNode;
        if (hash.find(startNode) == hash.end())
        {
            cout << "顶点" << startNode << "不存在，请重新输入" << endl;
            cin.ignore(65536, '\n');
        }
        else
            break;
    }
    start = hash[startNode];
    cout << "生成Prim最小树！" << endl;
    //使用prim算法生成最小数
    //Prim();
    PrimPriorityQueue();
}

/***************************************************************************
  函数名称：Kruskal
  功    能：利用kruskal算法生成最小生成树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int elecSys::Kruskal()
{
    if (tot == 1)
    {
        cout << "只有一个结点，无需生成最小生成树" << endl;
        return 0;
    }
    int edgeNum = 0;
    //边集数组
    for (int i = 0; i < tot; ++i)
        for (int j = 0; i < tot - i; ++j)
            if (i != j)
                edges.emplace_back(edge{ i, j, adj[i][j] });

    //从小到达代价排序
    Sort(&edges[0], edges.size());
    //顶点个数初始化并查集
    unionFind uf(tot);
    for (int i = 0; i < edges.size(); ++i)
    {
        //判断是否成环
        if (uf.is_connected(edges[i].first, edges[i].second))
            continue;
        //总代价
        cost += edges[i].val;
        //连起来的边数
        ++edgeNum;
        //将两个顶点连起来
        uf.union_xy(edges[i].first, edges[i].second);
        //连起来的边数为tot-1，则说明完成
        if (edgeNum == tot - 1)
            break;
    }
    return cost;
}

/***************************************************************************
  函数名称：Prim
  功    能：利用Prim算法生成最小生成树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void elecSys::Prim()
{
    int index;
    Vector<bool> vis(tot, false);//记录是否访问过
    Vector<int> dis(tot, 0);//到每个点的代价

    vis[start] = true;
    index = start;
    //将与起点直接连接的边放入dis数组
    for (int i = 0; i < tot; ++i)
        dis[i] = adj[start][i];

    //还剩下tot - 1个顶点要找 
    for (int i = 1; i < tot; ++i)
    {
        int Min = INT_MAX, temp = index;
        //找当前没访问过的最小代价边 
        for (int j = 0; j < tot; ++j)
            if (!vis[j] && dis[j] < Min)//没有访问过，并且找周围一圈距离最小的，贪心
            {
                Min = dis[j];
                index = j;
            }
        //记录连起来的边和代价
        ansEdge.emplace_back(edge{ temp, index, Min });

        //连起来，记录已经访问，代价加上
        vis[index] = true;
        cost += Min;
        //看index点周围有无更小的边有就更新dis连起来，没有就在原来的dis里面找，联想 !超级结点！ 
        for (int j = 0; j < tot; ++j)
            if (!vis[j] && dis[j] > adj[index][j])
                //找到更小的，更新dis[]
                dis[j] = adj[index][j];
    }
    cout << "生成最小生成树代价: " << cost << endl;
}

/***************************************************************************
  函数名称：PrimPriorityQueue
  功    能：利用Prim算法和优先队列生成最小生成树
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void elecSys::PrimPriorityQueue()
{
    Vector<bool> vis(tot, false);
    Vector<int> dis(tot, INT_MAX);
    Priority_queue<edge> q;

    q.emplace(edge{ start, start, 0 });
    edge temp;
    while (!q.empty())
    {
        //取出最小距离
        temp = q.top();
        q.pop();
        //遍历过了跳过
        if (vis[temp.second])
            continue;
        //没遍历过加入答案边集
        if (temp.first != temp.second)
            ansEdge.emplace_back(temp);
        //标记已经遍历过
        vis[temp.second] = true;
        //更新代价
        cost += temp.val;

        //从temp.second周围找更短的边
        for (int j = 0; j < tot; ++j)
        {
            //没有遍历过，并且从start到j比temp.second到j长
            if (vis[j] == false && adj[temp.second][j] < dis[j])
            {
                dis[j] = adj[temp.second][j];
                q.emplace(edge{ temp.second, j, dis[j] });
            }
        }

    }

    cout << "生成最小生成树代价: " << cost << endl;
}

/***************************************************************************
  函数名称：show
  功    能：展示生成最小树连接的边
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void elecSys::show()
{
    if (ansEdge.empty())
    {
        cout << "请先生成最小生成树！" << endl;
        return;
    }
    cout << "最小生成树的顶点和边为: " << endl;
    for (int i = 0; i < ansEdge.size(); ++i)
    {
        cout << node[ansEdge[i].first] << "-<"
            << ansEdge[i].val << ">-"
            << node[ansEdge[i].second] << "    ";
    }
    cout << endl;
}

//主函数
int main() {
    cout << "**\t\t电网造价模拟系统\t\t**" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
    cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
    cout << "**\t\tC --- 构建最小生成树\t\t**" << endl;
    cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
    cout << "**\t\tE --- 退出   程序\t\t**" << endl;
    cout << "==================================================" << endl;
    elecSys es;
    bool loop = true;
    char op;
    while (loop)
    {
        cout << "\n请选择操作: ";
        cin >> op;
        switch (op)
        {
            case 'a':
            case 'A':
                es.buildNode();
                break;
            case 'b':
            case 'B':
                es.addEdges();
                break;
            case 'c':
            case 'C':
                es.buildTree();
                break;
            case 'd':
            case 'D':
                es.show();
                break;
            case 'e':
            case 'E':
                loop = false;
                break;
            default:
                cout << "输入有误，请重新输入！" << endl;
                cin.clear();
                cin.ignore(65536, '\n');
                break;
        }
    }


    cout << endl << "输入回车继续" << endl;
    cin.ignore(65536, '\n');
    cin.get();
    return 0;
}