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
#define maxn 20
struct Edge
{
	int v,s,next;
}edge[1000010];
int head[maxn];
int pos;
void insert(int x,int y,int s)
{
	edge[pos].v=y;
	edge[pos].s=s;
	edge[pos].next=head[x];
	head[x]=pos++;
}
int dis[1<<16][16];
bool vis[1<<16][16];
pair<int,int>queue[2000010];
int rear,front;
int maxQ=2000010;
int dp[1<<16];
int f[1<<16];
int main()
{
//	freopen("input.txt","r",stdin);
	int cas;
	scanf("%d",&cas);
	for(int cc=1;cc<=cas;cc++)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		memset(head,0,sizeof(head));
		pos=1;
		while(m--)
		{
			int x,y,s;
			scanf("%d %d %d",&x,&y,&s);
			insert(x,y,s);
			insert(y,x,s);
		}
		memset(dis,-1,sizeof(dis));
		memset(vis,false,sizeof(vis));
		rear=front=0;
		for(int i=head[1];i;i=edge[i].next)
		{
			int v=edge[i].v;
			v-=2;
			if(dis[1<<v][v] == -1 || edge[i].s < dis[1<<v][v])
			{
				dis[1<<v][v]=edge[i].s;
				if(!vis[1<<v][v])
				{
					vis[1<<v][v]=true;
					queue[front++]=mp(1<<v,v);
				}
			}
		}
		while(rear != front)
		{
			int mask=queue[rear].X;
			int u=queue[rear].Y;
			rear++;
			if(rear == maxQ)
				rear=0;
			vis[mask][u]=false;
			for(int i=head[u+2];i;i=edge[i].next)
			{
				int v=edge[i].v;
				if(v == 1)
					continue;
				v-=2;
				int next=mask|(1<<v);
				if(dis[next][v] == -1 || dis[mask][u]+edge[i].s < dis[next][v])
				{
					dis[next][v]=dis[mask][u]+edge[i].s;
					if(!vis[next][v])
					{
						vis[next][v]=true;
						queue[front++]=mp(next,v);
						if(front == maxQ)
							front=0;
					}
				}
			}
		}
		memset(dp,-1,sizeof(dp));
		dp[0]=0;
		int T=1<<(n-1);
		for(int mask=1;mask<T;mask++)
			for(int i=0;i<n-1;i++)
			{
				if(dis[mask][i] == -1)
					continue;
				if(dp[mask] == -1 || dis[mask][i] < dp[mask])
					dp[mask]=dis[mask][i];
			}
		for(int mask=0;mask<T;mask++)
			f[mask]=dp[mask];
		for(int k=0;k<2;k++)
		{
			for(int u=T-1;u>0;u--)
				for(int v1=u;;v1=(v1-1)&u)
				{
					int v2=u^v1;
					if(dp[v1] == -1 || f[v2] == -1)
					{
						if(v1 == 0)
							break;
						continue;
					}
					if(dp[u] == -1 || max(dp[v1],f[v2]) < dp[u])
						dp[u]=max(dp[v1],f[v2]);
					if(v1 == 0)
						break;
				}
		}
		int Q;
		scanf("%d",&Q);
		int mask=0;
		while(Q--)
		{
			int x;
			scanf("%d",&x);
			x-=2;
			mask|=1<<x;
		}
		int ans=-1;
		for(int u=0;u<T;u++)
			if((u&mask) == mask)
			{
				if(dp[u] == -1)
					continue;
				if(ans == -1 || dp[u] < ans)
					ans=dp[u];
			}
		printf("Case %d: %d\n",cc,ans);
	}
	return 0;
}
