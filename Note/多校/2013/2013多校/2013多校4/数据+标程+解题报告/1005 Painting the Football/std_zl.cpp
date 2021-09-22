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
int g[40][40]=
{
		{},
		{17,18,20,3,2,13},
		{1,3,4,7,12,13},
		{1,2,4,5,20},
		{2,3,5,6,7,8},
		{3,4,6,24,21,20},
		{4,5,8,9,24},
		{2,4,8,10,12},
		{4,6,9,11,10,7},
		{6,24,26,27,11,8},
		{7,8,11,16,14,12},

		{8,9,27,16,10},
		{2,7,10,14,15,13},
		{1,2,12,15,17},
		{10,12,15,16,30},
		{12,14,30,32,17,13},
		{10,11,27,29,30,14},
		{13,15,32,19,18,1},
		{1,17,19,22,20},
		{17,18,22,23,31,32},
		{1,3,5,21,22,18},

		{5,20,22,25,24},
		{18,20,21,25,23,19},
		{19,22,25,28,31},
		{5,6,9,26,25,21},
		{21,24,26,28,23,22},
		{9,27,28,25,24},
		{9,11,16,29,28,26},
		{25,26,27,29,31,23},
		{16,30,31,28,27},
		{16,14,15,32,31,29},

		{29,30,32,19,23,28},
		{15,17,19,31,30},
};
struct Edge
{
	int v,next,s;
}edge[100010];
int head[40];
int pos;
void insert(int x,int y,int s)
{
	edge[pos].v=y;
	edge[pos].s=s;
	edge[pos].next=head[x];
	head[x]=pos++;
}
int color[40];
void init()
{
	memset(head,0,sizeof(head));
	pos=1;
	for(int i=1;i<=32;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(g[i][j] == 0)
				break;
			int x=i;
			int y=g[i][j];
			if(color[x] == color[y])
				insert(x,y,0);
			else
				insert(x,y,1);
		}
	}
}
int queue[40];
int rear,front;
int maxQ=40;
bool vis[40];
int dis[40];
int solve(int rt)
{
	for(int i=1;i<=32;i++)
		dis[i]=0xfffffff;
	dis[rt]=0;
	rear=front=0;
	queue[front++]=rt;
	memset(vis,false,sizeof(vis));
	vis[rt]=true;
	while(rear != front)
	{
		int now=queue[rear++];
		if(rear == maxQ)
			rear=0;
		vis[now]=false;
		for(int i=head[now];i;i=edge[i].next)
		{
			int v=edge[i].v;
			if(dis[now]+edge[i].s < dis[v])
			{
				dis[v]=dis[now]+edge[i].s;
				if(!vis[v])
				{
					vis[v]=true;
					queue[front++]=v;
					if(front == maxQ)
						front=0;
				}
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=32;i++)
		if(color[i] == 1)
			cnt=max(cnt,dis[i]);
	return cnt;
}
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		for(int i=1;i<=32;i++)
			scanf("%d",&color[i]);
		bool black=false;
		for(int i=1;i<=32;i++)
			if(color[i] == 1)
				black=true;
		if(!black)
		{
			printf("Case %d: %d\n",cc,0);
			continue;
		}
		init();
		int ans=0xfffffff;
		for(int i=1;i<=32;i++)
			ans=min(ans,solve(i));
		printf("Case %d: %d\n",cc,ans+1);
	}
	return 0;
}

