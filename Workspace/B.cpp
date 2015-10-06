#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define inf 2000000000
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,ind,cnt;
int f[100005],g[100005],mx[100005];
int dfn[100005],q[100005],fa[100005];
int last[100005],val[100005];
int a[100005];
bool mark[100005];
struct edge{
	int to,next;
}e[400005];
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;
}
void dp(int rt,int x)
{
	int u0=0,u1=0,v0,v1;
    for(int j=x;j!=rt;j=fa[j])
	{
		v1=u0+f[j];v0=u1+g[j];
		u0=v0;u1=max(v0,v1);
	}
	g[rt]+=u1;
	u0=-inf;u1=0;  //!
	for(int j=x;j!=rt;j=fa[j])
	{
		v1=u0+f[j];v0=u1+g[j];
	    u0=v0;u1=max(v0,v1);
	}
	f[rt]+=u0;
}
void dfs(int x)
{
	dfn[x]=++ind;
	for(int i=last[x];i;i=e[i].next)
		if(!dfn[e[i].to])
		{
			fa[e[i].to]=x;
			dfs(e[i].to);
		}
	f[x]=val[x];
    for(int i=last[x];i;i=e[i].next)
		if(dfn[e[i].to]>dfn[x]&&fa[e[i].to]!=x)
			dp(x,e[i].to);
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		insert(u,v);
	}
	for(int i=1;i<=n;i++)val[i]=read();
	dfs(1);
	printf("%d",max(f[1],g[1]));
	return 0;
}
