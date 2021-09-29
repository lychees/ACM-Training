#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n,m,q,i,j,k,u,v;
int l[100005],r[100005],fa[100005];
int son[100005],next[200005],ed[200005],tot;
int ans[100005],deep[100005],last[100005];
bool del[100005];

inline bool top(int p){return (!fa[p])||(l[fa[p]]!=p&&r[fa[p]]!=p);}
inline void zig(int x)
{
	int y=fa[x],z=fa[y];
	if(l[z]==y)l[z]=x;else if(r[z]==y)r[z]=x;
	fa[x]=z,fa[y]=x,fa[r[x]]=y;
	l[y]=r[x],r[x]=y;
}

inline void zag(int x)
{
	int y=fa[x],z=fa[y];
	if(l[z]==y)l[z]=x;else if(r[z]==y)r[z]=x;
	fa[x]=z,fa[y]=x,fa[l[x]]=y;
	r[y]=l[x];l[x]=y;
}
inline void splay(int x)
{
	int y,z;
	while(!top(x))
	{
		y=fa[x],z=fa[y];
		if(!top(y))
		{
			if(l[z]==y){if(l[y]==x)zig(y),zig(x);else zag(x),zig(x);}
			else{if(l[y]==x)zig(x),zag(x);else zag(y),zag(x);}
		}
		else{if(l[y]==x)zig(x);else zag(x);}
	}
}
inline int access(int x)
{
	int y=0;
	for(;x;y=x,x=fa[x])
	{
		splay(x);
		r[x]=y;
	}
	return y;
}
void dfs(int p)
{
	for(int i=son[p];i;i=next[i])
	if(ed[i]!=fa[p])
	{
		deep[ed[i]]=deep[p]+1;
		fa[ed[i]]=p;
		dfs(ed[i]);
	}
}

int U[100005],V[100005];

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);U[i]=u;V[i]=v;
		++tot;next[tot]=son[u];son[u]=tot;ed[tot]=v;
		++tot;next[tot]=son[v];son[v]=tot;ed[tot]=u;
	}
	dfs(1);
	for(i=1;i<n;++i)
	{
		del[i]=true;
		if(deep[U[i]]<deep[V[i]])swap(U[i],V[i]);
	}
	for(i=1;i<=n;++i)ans[i]=1,fa[i]=0;
	for(;m;--m)
	{
		scanf("%d",&k);
		u=U[k];v=V[k];
		if(del[k])
		{
			splay(u);fa[u]=v;
			access(v);splay(v);for(;l[v];v=l[v]);splay(v);
			ans[v]=ans[v]+ans[u]-last[k];
		}
		else
		{
			access(u);splay(u);fa[l[u]]=0;l[u]=0;
			splay(v);for(;l[v];v=l[v]);splay(v);
			last[k]=ans[u]=ans[v];
		}
		del[k]^=1;
	}
	for(;q;--q)
	{
		scanf("%d",&u);
		access(u);splay(u);
		for(;l[u];u=l[u]);splay(u);
		printf("%d\n",ans[u]);
	}
}
