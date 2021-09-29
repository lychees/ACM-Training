#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=110;
const int maxm=maxn*maxn<<1;
const int INF=0x3f3f3f3f;

int n,en,s,t,m,q[maxn],depth[maxn];

struct edge
{
	int e,f;
	edge *next,*op;
}*v[maxn],ed[maxm];

void add_edge(int s,int e,int f)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->f=f;
	en++;
	ed[en].next=v[e];v[e]=ed+en;v[e]->e=s;v[e]->f=f;
	v[s]->op=v[e];v[e]->op=v[s];
}

bool bfs()
{
	memset(depth,0,sizeof(depth));
	int front=1,tail=1;
	q[1]=s;
	depth[s]=1;
	for (;front<=tail;)
	{
		int now=q[front++];
		for (edge *e=v[now];e;e=e->next)
			if (e->f && !depth[e->e])
			{
				depth[e->e]=depth[now]+1;
				if (e->e==t) return true;
				q[++tail]=e->e;
			}
	}
	return false;
}

int dfs(int now,int cur_flow)
{
	if (now==t) return cur_flow;
	int rest=cur_flow;
	for (edge *e=v[now];e && rest;e=e->next)
		if (e->f && depth[e->e]==depth[now]+1)
		{
			int new_flow=dfs(e->e,min(rest,e->f));
			e->f-=new_flow;
			e->op->f+=new_flow;
			rest-=new_flow;
		}
	if (cur_flow==rest) depth[now]=-1;
	return cur_flow-rest;
}

int dinic()
{
	int ans=0;
	while (bfs())
		ans+=dfs(s,INF);
	return ans;
}

int main()
{
	scanf("%d",&n);
	scanf("%d%d%d",&s,&t,&m);
	for (int a=1;a<=m;a++)
	{
		int s,e,f;
		scanf("%d%d%d",&s,&e,&f);
		add_edge(s,e,f);
	}
	printf("%d\n",dinic());

	return 0;
}
