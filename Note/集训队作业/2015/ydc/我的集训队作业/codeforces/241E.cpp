#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 1010
#define maxm 20010
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
struct Edge
{
	int u,v;
}e[maxm];
int n,m,dis[maxn];
int nEdge=1,to[maxm],next[maxm],len[maxm],start[maxn];
bool can1[maxn],can2[maxn];
vector<int> adj1[maxn],adj2[maxn];
void make(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],len[nEdge]=c,start[a]=nEdge;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d",&e[i].u,&e[i].v);
		adj1[e[i].u].push_back(e[i].v);
		adj2[e[i].v].push_back(e[i].u);
	}
}
void Fail()
{
	printf("No\n");
	exit(0);
}
void BFS(vector<int> *adj,bool *use,int p)
{
	static int queue[maxn];
	int front=0,rear=1;
	queue[rear]=p,use[p]=true;
	while(front<rear)
	{
		int p=queue[++front];
		each(x,adj[p])
			if(!use[*x])
			{
				queue[++rear]=*x;
				use[*x]=true;
			}
	}
}
void SPFA()
{
	static int queue[maxn],cnt[maxn];
	static bool use[maxn];
	int front=0,rear=1;
	fill(dis+1,dis+n+1,1<<30);
	queue[rear]=1,use[1]=true,dis[1]=0;
	while(front!=rear)
	{
		int p=queue[front=front%n+1];
		use[p]=false;
		for(int i=start[p];i;i=next[i])
			if(dis[to[i]]>dis[p]+len[i])
			{
				dis[to[i]]=dis[p]+len[i];
				if(++cnt[to[i]]==n)
					Fail();
				if(!use[to[i]])
				{
					queue[rear=rear%n+1]=to[i];
					use[to[i]]=true;
				}
			}
	}
}
void BuildGraph()
{
	for(int i=1;i<=m;++i)
		if(can1[e[i].u]&&can2[e[i].v])
		{
			make(e[i].u,e[i].v,2);
			make(e[i].v,e[i].u,-1);
		}
}
void print()
{
	for(int i=1;i<=m;++i)
		if(can1[e[i].u]&&can2[e[i].v])
		{
			int t=dis[e[i].v]-dis[e[i].u];
			if(t<1||t>2)
				Fail();
		}
	printf("Yes\n");
	for(int i=1;i<=m;++i)
		printf("%d\n",can1[e[i].u]&&can2[e[i].v]?dis[e[i].v]-dis[e[i].u]:1);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	BFS(adj1,can1,1),BFS(adj2,can2,n);
	BuildGraph();
	SPFA();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
