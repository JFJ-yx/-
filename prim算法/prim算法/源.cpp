#include<iostream>
#include<cstring>
#include<string> 
using namespace std;
const int MaxSize = 100;
const int MAX = 9999;

class MGraph
{
	string vertex[MaxSize];   //ͼ�Ķ�����Ϣ 
	int adj[MaxSize][MaxSize];    //ͼ���ڽӾ��� 
	int vertexNum, edgeNum;
public:
	MGraph(int n);
	void print();
	int W(int i, int j);
	void InsertEdge(int i, int j, int p);
	int VexNum()
	{
		return vertexNum;
	}
	friend void Prim(MGraph& g, int u0);
};

void MGraph::print()
{
	for (int i = 0; i < vertexNum; i++) {
		for (int j = 0; j < vertexNum; j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}

MGraph::MGraph(int n)
{
	vertexNum = n;
	edgeNum = 0;
   //���ڽӾ�������Ԫ�ظ�Ϊ0 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				adj[i][j] = 0;
			else
				adj[i][j] = MAX;
		}
	}
}


void MGraph::InsertEdge(int i, int j, int p)   //���붥��i��j�����ı��Լ��ñߵ�Ȩֵ 
{
	adj[i][j] = adj[j][i] = p;
	edgeNum++;
}

int MGraph::W(int i, int j)
{
	return adj[i][j];
}

void Prim(MGraph& g, int u0)
{
	int k;
	int n = g.VexNum();
	struct node  //����һ���ڵ�ṹ�� �����ýڵ�������������ڵ�����Ľڵ㼰��ߵ�Ȩֵ
	{
		int adjvex;
		int lowcost;
	}closedge[MaxSize];
	closedge[u0].adjvex = u0;
	closedge[u0].lowcost = 0;
	for (int v = 0; v < n; v++)
	{
		if (v != u0)
		{
			closedge[v].adjvex = u0;
			closedge[v].lowcost = g.W(u0, v);
		}
	}
	closedge[u0].lowcost = 0;
	for (int i = 0; i <= n - 2; i++)
	{
		k = 0;
		int minw = MAX;
		for (int v = 0; v <= n - 1; v++)
		{
			if (closedge[v].lowcost > 0 && closedge[v].lowcost < minw)
			{
				k = v;
				minw = closedge[v].lowcost;
			}
		}
		cout << "(" << closedge[k].adjvex << "," << k << ")" << ":" << minw << " " << endl;
		closedge[k].lowcost = 0;   //����k����U�� 
		for (int v = 0; v <= n - 1; v++) //���»�û����U���ڵ����Ϣ
		{
			if (closedge[v].lowcost != 0 && g.W(k, v) < closedge[v].lowcost)
			{
				closedge[v].lowcost = g.W(k, v);
				closedge[v].adjvex = k;
			}
		}
	}
}

int main()
{
	struct Edge
	{
		int from, end, power;
	};

	int n = 6;   //6������ 
	int e = 10;
	Edge b[] = { {0,1,6},{0,2,1},{0,3,5},{1,2,5},{1,4,3},{2,3,5},{2,4,6},{2,5,4},{3,5,2},{4,5,6} };
	MGraph m(n);
	for (int k = 0; k < e; k++)m.InsertEdge(b[k].from, b[k].end, b[k].power);  //�������б�,���ڽӾ���ֵ
	cout << "��ӡ���ڽӾ���9999���������" << endl;
	m.print();//��ӡ���ڽӾ���
	cout << "��ӡ�������µı�" << endl;
	Prim(m, 0);// ��ӡ�������µı�
	return 0;
}
