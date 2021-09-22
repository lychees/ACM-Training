#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;
typedef __int64 lld;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define eps 1e-8
#define maxn 100010
struct Edge
{
	int u,v,next;
}edge[1000010];
int head[maxn];
int pos;
void insert(int x,int y)
{
	edge[pos].u=x;
	edge[pos].v=y;
	edge[pos].next=head[x];
	head[x]=pos++;
}
int dfsn[maxn];
bool vis[maxn];
int low[maxn];
int stack[maxn];
int scc[maxn];
int front;
int number;
int pre;
bool Instack[maxn];
void dfs(int now)
{
	stack[++front]=now;
	vis[now]=true;
	dfsn[now]=low[now]=pre++;
	Instack[now]=true;
	for(int i=head[now];i;i=edge[i].next)
	{
		int v=edge[i].v;
		if(vis[v])
		{
			if(Instack[v])
				low[now]=min(low[now],dfsn[v]);
			continue;
		}
		dfs(v);
		low[now]=min(low[now],low[v]);
	}
	if(low[now] == dfsn[now])
	{
		number++;
		int mark;
		do
		{
			mark=stack[front--];
			scc[mark]=number;
			Instack[mark]=false;
		}while(mark!=now);
	}
}
void init()
{
	memset(dfsn,0,sizeof(dfsn));
	memset(low,0,sizeof(low));
	memset(vis,false,sizeof(vis));
	memset(Instack,false,sizeof(Instack));
	pre=1;
	number=0;
	memset(head,0,sizeof(head));
	pos=1;
}
int num[maxn];
bool in[maxn];
bool out[maxn];
int main()
{
//	freopen("in.txt","r",stdin);
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		init();
		for(int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			insert(x,y);
		}
		for(int i=1;i<=n;i++)
			if(!vis[i])
			{
				front=-1;
				dfs(i);
			}
		if(number == 1)
		{
			printf("Case %d: -1\n",cc);
			continue;
		}
		memset(num,0,sizeof(num));
		for(int i=1;i<=n;i++)
			num[scc[i]]++;
		memset(in,false,sizeof(in));
		memset(out,false,sizeof(out));
		for(int i=1;i<pos;i++)
		{
			int x=edge[i].u;
			int y=edge[i].v;
			x=scc[x];
			y=scc[y];
			if(x != y)
			{
				in[y]=true;
				out[x]=true;
			}
		}
		int mm=0xfffffff;
		for(int i=1;i<=number;i++)
			if(!in[i] || !out[i])
				mm=min(mm,num[i]);
		int x=mm;
		int y=n-mm;
		int T=x*(x-1)+y*(y-1)+x*y;
		printf("Case %d: %d\n",cc,T-m);
	}
	return 0;
}
