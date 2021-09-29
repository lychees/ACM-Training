#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n,m,i,j,k,u,v,c,lca;
int fa[100005],son[100005],next[200005],ed[200005],tot;
int heavy[100005],head[100005],size[100005],deep[100005];
int lson[100005],lnext[100005],A[100005],B[100005],C[100005];
int f[100005],g[100005],t[100005],sum;

void dfs1(int x)
{
	size[x]=1;
	for(int i=son[x];i;i=next[i])
	if(!size[ed[i]])
	{
		fa[ed[i]]=x;
		deep[ed[i]]=deep[x]+1;
		dfs1(ed[i]);
		size[x]+=size[ed[i]];
		if(size[ed[i]]>size[heavy[x]])heavy[x]=ed[i];
	}
}

void dfs2(int x)
{
	if(!head[x])head[x]=x;
	if(heavy[x])head[heavy[x]]=head[x],dfs2(heavy[x]);
	for(int i=son[x];i;i=next[i])
	if(!head[ed[i]])dfs2(ed[i]);
}

int LCA(int u,int v)
{
	for(;head[u]!=head[v];)
	if(deep[head[u]]>deep[head[v]])u=fa[head[u]];
	else v=fa[head[v]];
	if(deep[u]<deep[v])return u;
	return v;
}

int calc(int u,int v)
{
	int sum=0;
	for(;head[u]!=head[v];u=fa[head[u]])sum+=t[head[u]]-t[heavy[u]];
	sum+=t[heavy[v]]-t[heavy[u]];
	return sum;
}

void dfs(int x)
{
	for(int i=son[x];i;i=next[i])
	if(deep[ed[i]]>deep[x])
	{
		dfs(ed[i]);
		g[x]+=f[ed[i]];
	}
	f[x]=g[x];
	for(int i=lson[x];i;i=lnext[i])
	{
		sum=g[x]+C[i]+calc(A[i],x)+calc(B[i],x);
		if(sum>f[x])f[x]=sum;
	}
	t[x]=g[x]-f[x]+t[heavy[x]];
}

int main()
{
	scanf("%d",&n);
	for(i=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		++tot;next[tot]=son[u];son[u]=tot;ed[tot]=v;
		++tot;next[tot]=son[v];son[v]=tot;ed[tot]=u;
	}
	dfs1(1);dfs2(1);
	scanf("%d",&m);
	for(i=1;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&C[i]);
		A[i]=u;B[i]=v;lca=LCA(u,v);
		lnext[i]=lson[lca];lson[lca]=i;
	}
	dfs(1);
	printf("%d\n",f[1]);
}
