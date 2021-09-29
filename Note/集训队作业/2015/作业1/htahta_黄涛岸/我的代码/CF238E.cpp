#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=103,inf=1000000000;
int d[maxn][maxn],n,f[maxn],g[maxn],vis[maxn],cnt[maxn][maxn],T[maxn],m,A,B,tot=1;
bool p[maxn][maxn];
int dfs(int x,int aim)
{
	if(x==aim)return f[x];
	if(vis[x]==tot)return g[x];
	g[x]=0;vis[x]=tot;
	for(int i=1;i<=n;i++)
		if(d[x][i]==1&&1+d[i][aim]==d[x][aim])g[x]=max(g[x],dfs(i,aim));
	return g[x]=min(g[x],f[x]);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get(),A=get(),B=get();
	for(int i=1;i<=n;d[i][i]=0,f[i]=inf,i++)
		for(int j=1;j<=n;j++)d[i][j]=inf;
	f[B]=0;
	for(int i=1,x;i<=m;i++)x=get(),d[x][get()]=1;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	m=get();
	for(int i=1;i<=m;i++)
	{
		int x=get(),y=get();T[i]=y;
		if(d[x][y]==inf)continue;
		for(int j=1;j<=n;j++)
			if(d[x][j]+d[j][y]==d[x][y])cnt[i][d[x][j]]++;
		for(int j=1;j<=n;j++)
			if(d[x][j]+d[j][y]==d[x][y]&&cnt[i][d[x][j]]==1)p[i][j]=1;
	}
	for(bool flag=1;flag;)
	{
		flag=0;
		for(int i=1;i<=m;i++,tot++)
			for(int j=1;j<=n;j++)
			{
				if(!p[i][j])continue;
				int tp=dfs(j,T[i])+1;
				if(tp<f[j])f[j]=tp,flag=1;
			}
	}
	printf("%d\n",f[A]==inf?-1:f[A]);
	return 0;
}
