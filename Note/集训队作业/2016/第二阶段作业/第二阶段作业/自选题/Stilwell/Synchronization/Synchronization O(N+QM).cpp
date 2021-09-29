#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n,m,q,i,j,k,u,v,ans;
int son[100005],next[200005],ed[200005],tot;
int pre[100005],lson[100005],lnext[300005],l[300005],r[300005],cnt;
bool vis[100005];

void dfs(int x,int y)
{
	++ans;
	vis[x]=true;
	for(int i=son[x];i;i=next[i])
	if(!vis[ed[i]])
	for(int j=lson[i>>1];j;j=lnext[j])
	if(l[j]<=y)
	{
		dfs(ed[i],min(r[j],y));
		break;
	}
	vis[x]=false;
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(i=tot=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		++tot;next[tot]=son[u];son[u]=tot;ed[tot]=v;
		++tot;next[tot]=son[v];son[v]=tot;ed[tot]=u;
	}
	for(i=1;i<=m;++i)
	{
		scanf("%d",&u);
		if(pre[u])
		{
			l[++cnt]=pre[u];r[cnt]=i;
			lnext[cnt]=lson[u];lson[u]=cnt;
			pre[u]=0;
		}
		else pre[u]=i;
	}
	for(i=1;i<n;++i)
	if(pre[i])
	{
		l[++cnt]=pre[i];r[cnt]=m;
		lnext[cnt]=lson[i];lson[i]=cnt;
	}
	for(;q;--q)
	{
		scanf("%d",&u);ans=0;
		dfs(u,m);
		printf("%d\n",ans);
	}
}
