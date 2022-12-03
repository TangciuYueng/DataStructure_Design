#include "8_2151298_������.h"


/***************************************************************************
  �������ƣ�clear
  ��    �ܣ����
  ���������
  �� �� ֵ��
  ˵    �����Ե���ϵͳ�����������ݽṹ��ճ�ʼ�����Ա�֤��һ�����е���ȷ��
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
  �������ƣ�buildNode
  ��    �ܣ���õ����������
  ���������
  �� �� ֵ��
  ˵    ������Ҫ�ж�����������Ƿ�Ϸ�
            ��Ҫ�ж�������Ľ���Ƿ������ϵͳ�����н������
            ����������������ʾ��������
***************************************************************************/
void elecSys::buildNode()
{
    //����ϴμ�¼
    clear();
    cout << "��������ĸ���: ";
    while (1)
    {
        cin >> tot;
        if (cin.fail() || tot <= 0)
        {
            cout << "������������" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
        }
        else
            break;
    }
    cout << "��������������������:" << endl;
    String temp;
    for (int i = 0; i < tot; ++i)
    {
        cin >> temp;
        //��֤û����ͬ����
        auto Nullptr = tree_iterator<String, int>(NULL);
        auto it = hash.find(temp);
        if (it == Nullptr)
        {
            hash[temp] = i;//�����������±��Ӧ
            node.emplace_back(temp);
        }
        else
        {
            cout << "���ܳ�����ͬ���㣬����������ö�������" << endl;
            --i;
        }
    }
    //�ڽӾ����ʼ��
    adj.resize(tot, Vector<int>(tot, INT_MAX));
    //���鼯��ʼ��
    uf.resize(tot);
}

/***************************************************************************
  �������ƣ�addEdges
  ��    �ܣ���ӵ���ϵͳ�ı�
  ���������
  �� �� ֵ��
  ˵    ����������֮ǰ������Ҫ�ж��Ƿ��Ѿ���������
            ��Ҫ�жϽ��������ֻ��һ��������蹹����С������
            ����ı� �������1 �������2 ��Ȩֵ
            ����������������������ƣ�����������ʾ
            ��ȨֵΪ����ʱ�˳�����
            ͬʱ��Ҫ�жϹ��ɵ�ͼ�Ƿ���ͨ
***************************************************************************/
void elecSys::addEdges()
{
    if (tot == 0)
    {
        cout << "���ȹ�����������" << endl;
        return;
    }
    if (tot == 1)
    {
        cout << "ֻ��һ�����㣬���蹹����С������" << endl;
        return;
    }
    String nodeA, nodeB;
    int val;
    cout << endl << "����ߵ�ֵΪ����ʱ���˳�����" << endl;
    while (1)
    {
        cout << "�������������㼰��: ";
        cin >> nodeA >> nodeB >> val;
        //�ж����붥���Ƿ���ͬ
        if (nodeA == nodeB)
        {
            cout << "����������㲻Ӧ��ͬ������������" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (cin.fail())
        {
            cout << "���������ֵ��������������" << endl;
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (val <= 0)//�����ָ��ߣ��˳�
            break;
        //�ж����붥���Ƿ���Ч
        auto itA = hash.find(nodeA);
        auto itB = hash.find(nodeB);
        if (itA == hash.end())
        {
            cout << "����" << nodeA << "������" << endl;
            continue;
        }
        if (itB == hash.end())
        {
            cout << "����" << nodeB << "������" << endl;
            continue;
        }
        //�����ڽӱ�
        adj[itA->second][itB->second] = min(adj[itA->second][itB->second], val);
        adj[itB->second][itA->second] = adj[itA->second][itB->second];
        adj[itA->second][itA->second] = 0;
        adj[itB->second][itB->second] = 0;
        //��������Ͻ��
        uf.union_xy(itA->second, itB->second);
    }
    //��������numOfSet == 1
    if (uf.getNumOfSet() == 1)
        edgeFinish = true;
}

/***************************************************************************
  �������ƣ�buildTree
  ��    �ܣ�����������С��������ʾ�������û��������㹹����С������
  ���������
  �� �� ֵ��
  ˵    �����жϽ�����������Ϊ0��ʾ�ȹ�����㣬Ϊ1��ʾ���蹹��
            �ж��Ƿ���ͨ��δ��ͨ��ʾ������һ������

***************************************************************************/
void elecSys::buildTree()
{
    if (tot == 0)
    {
        cout << "���ȹ�����������" << endl;
        return;
    }
    if (tot == 1)
    {
        cout << "ֻ��һ�����㣬���蹹����С������" << endl;
        return;
    }
    if (edgeFinish == false)
    {
        cout << "���е���������δ���ӣ��޷�������С���������������ӵ�����" << endl;
        return;
    }
    String startNode;
    cout << "���������: ";
    while (1)
    {
        cin >> startNode;
        if (hash.find(startNode) == hash.end())
        {
            cout << "����" << startNode << "�����ڣ�����������" << endl;
            cin.ignore(65536, '\n');
        }
        else
            break;
    }
    start = hash[startNode];
    cout << "����Prim��С����" << endl;
    //ʹ��prim�㷨������С��
    //Prim();
    PrimPriorityQueue();
}

/***************************************************************************
  �������ƣ�Kruskal
  ��    �ܣ�����kruskal�㷨������С������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int elecSys::Kruskal()
{
    if (tot == 1)
    {
        cout << "ֻ��һ����㣬����������С������" << endl;
        return 0;
    }
    int edgeNum = 0;
    //�߼�����
    for (int i = 0; i < tot; ++i)
        for (int j = 0; i < tot - i; ++j)
            if (i != j)
                edges.emplace_back(edge{ i, j, adj[i][j] });

    //��С�����������
    Sort(&edges[0], edges.size());
    //���������ʼ�����鼯
    unionFind uf(tot);
    for (int i = 0; i < edges.size(); ++i)
    {
        //�ж��Ƿ�ɻ�
        if (uf.is_connected(edges[i].first, edges[i].second))
            continue;
        //�ܴ���
        cost += edges[i].val;
        //�������ı���
        ++edgeNum;
        //����������������
        uf.union_xy(edges[i].first, edges[i].second);
        //�������ı���Ϊtot-1����˵�����
        if (edgeNum == tot - 1)
            break;
    }
    return cost;
}

/***************************************************************************
  �������ƣ�Prim
  ��    �ܣ�����Prim�㷨������С������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void elecSys::Prim()
{
    int index;
    Vector<bool> vis(tot, false);//��¼�Ƿ���ʹ�
    Vector<int> dis(tot, 0);//��ÿ����Ĵ���

    vis[start] = true;
    index = start;
    //�������ֱ�����ӵı߷���dis����
    for (int i = 0; i < tot; ++i)
        dis[i] = adj[start][i];

    //��ʣ��tot - 1������Ҫ�� 
    for (int i = 1; i < tot; ++i)
    {
        int Min = INT_MAX, temp = index;
        //�ҵ�ǰû���ʹ�����С���۱� 
        for (int j = 0; j < tot; ++j)
            if (!vis[j] && dis[j] < Min)//û�з��ʹ�����������ΧһȦ������С�ģ�̰��
            {
                Min = dis[j];
                index = j;
            }
        //��¼�������ıߺʹ���
        ansEdge.emplace_back(edge{ temp, index, Min });

        //����������¼�Ѿ����ʣ����ۼ���
        vis[index] = true;
        cost += Min;
        //��index����Χ���޸�С�ı��о͸���dis��������û�о���ԭ����dis�����ң����� !������㣡 
        for (int j = 0; j < tot; ++j)
            if (!vis[j] && dis[j] > adj[index][j])
                //�ҵ���С�ģ�����dis[]
                dis[j] = adj[index][j];
    }
    cout << "������С����������: " << cost << endl;
}

/***************************************************************************
  �������ƣ�PrimPriorityQueue
  ��    �ܣ�����Prim�㷨�����ȶ���������С������
  ���������
  �� �� ֵ��
  ˵    ����
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
        //ȡ����С����
        temp = q.top();
        q.pop();
        //������������
        if (vis[temp.second])
            continue;
        //û����������𰸱߼�
        if (temp.first != temp.second)
            ansEdge.emplace_back(temp);
        //����Ѿ�������
        vis[temp.second] = true;
        //���´���
        cost += temp.val;

        //��temp.second��Χ�Ҹ��̵ı�
        for (int j = 0; j < tot; ++j)
        {
            //û�б����������Ҵ�start��j��temp.second��j��
            if (vis[j] == false && adj[temp.second][j] < dis[j])
            {
                dis[j] = adj[temp.second][j];
                q.emplace(edge{ temp.second, j, dis[j] });
            }
        }

    }

    cout << "������С����������: " << cost << endl;
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ�չʾ������С�����ӵı�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void elecSys::show()
{
    if (ansEdge.empty())
    {
        cout << "����������С��������" << endl;
        return;
    }
    cout << "��С�������Ķ���ͱ�Ϊ: " << endl;
    for (int i = 0; i < ansEdge.size(); ++i)
    {
        cout << node[ansEdge[i].first] << "-<"
            << ansEdge[i].val << ">-"
            << node[ansEdge[i].second] << "    ";
    }
    cout << endl;
}

//������
int main() {
    cout << "**\t\t�������ģ��ϵͳ\t\t**" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\tA --- ������������\t\t**" << endl;
    cout << "**\t\tB --- ��ӵ����ı�\t\t**" << endl;
    cout << "**\t\tC --- ������С������\t\t**" << endl;
    cout << "**\t\tD --- ��ʾ��С������\t\t**" << endl;
    cout << "**\t\tE --- �˳�   ����\t\t**" << endl;
    cout << "==================================================" << endl;
    elecSys es;
    bool loop = true;
    char op;
    while (loop)
    {
        cout << "\n��ѡ�����: ";
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
                cout << "�����������������룡" << endl;
                cin.clear();
                cin.ignore(65536, '\n');
                break;
        }
    }


    cout << endl << "����س�����" << endl;
    cin.ignore(65536, '\n');
    cin.get();
    return 0;
}