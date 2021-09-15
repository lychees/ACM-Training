#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<bitset>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 110
using namespace std;
vector<int> can[maxn][maxn];
int dis[maxn][maxn];
int n,m,S,T,nB;
int from[maxn],to[maxn];
void read()
{
	cin>>n>>m>>S>>T;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
				dis[i][j]=1<<30;
	for(int i=1,a,b;i<=m;++i)
	{
		cin>>a>>b;
		dis[a][b]=1;
	}
}
void Prepare()
{
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			if(dis[i][k]!=1<<30)
				for(int j=1;j<=n;++j)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	int Q;
	cin>>Q;
	for(int i=1,a,b;i<=Q;++i)
	{
		cin>>a>>b;
		if(dis[a][b]!=1<<30)
		{
			++nB,from[nB]=a,to[nB]=b;
			for(int j=1;j<=n;++j)
				if(dis[a][j]+dis[j][b]==dis[a][b])
					can[nB][dis[a][j]].push_back(j);
		}
	}
}
int Dp()
{
	static int dp[maxn],g[maxn];
	fill(dp+1,dp+n+1,1<<30);
	dp[T]=0;
	for(bool mark=true;mark;)
	{
		mark=false;
		for(int i=1;i<=nB;++i)
		{
			g[to[i]]=dp[to[i]];
			for(int len=dis[from[i]][to[i]]-1;len>=0;--len)
			{
				each(p,can[i][len])
				{
					g[*p]=0;
					each(q,can[i][len+1])
						if(dis[*p][*q]==1)
							g[*p]=max(g[*p],g[*q]);
					g[*p]=min(g[*p],dp[*p]);
				}
				if(can[i][len].size()==1)
				{
					int p=can[i][len][0];
					if(dp[p]>g[p]+1)
						dp[p]=g[p]+1,mark=true;
				}
			}
		}
	}
	return dp[S]==1<<30?-1:dp[S];
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Prepare();
	printf("%d\n",Dp());
	return 0;
}
