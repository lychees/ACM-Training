#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 110
using namespace std;
int n,m;
char map[maxn][maxn];
int use[maxn],id,vis[maxn],id1,cnt;
void read()
{
	scanf("%d %d",&n,&m);
	++m;
	for(int i=1;i<=n;++i)
		scanf("%s",map[i]+1);
}
void DFS(int p)
{
	use[p]=id,++cnt;
	for(int i=1;i<=n;++i)
		if(map[p][i]=='Y'&&use[i]!=id&&vis[i]!=id1)
			DFS(i);
}
bool Judge(int now,int p,int x)
{
	now=map[now][p]=='Y'?now:p;
	if(p==m)
	{
		if(now!=p)
			return false;
		for(int i=1;i<=n;++i)
			if(vis[i]!=id1&&i!=p&&map[i][p]=='Y')
				return false;
		printf("%d ",p-1);
		vis[p]=id1;
		for(int i=1;i<=n;++i)
			if(vis[i]!=id1)
				printf("%d ",i-1);
		printf("\n");
		return true;
	}
	else
	{
		++id,use[m]=id,use[p]=id,cnt=0;
		DFS(m);
		for(int i=1;i<=n;++i)
			if(vis[i]!=id1&&use[i]!=id&&map[now][i]=='Y')
				++cnt;
		return cnt==x;
	}
}
void work()
{
	cnt=0,use[m]=++id,++id1;
	DFS(m);
	if(cnt!=n)
	{
		printf("IMPOSSIBLE\n");
		return ;
	}
	int now=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(vis[j]!=id1&&Judge(now,j,n-i))
			{
				if(j==m)
					return ;
				vis[j]=id1;
				now=map[now][j]=='Y'?now:j;
				printf("%d ",j-1);
				break;
			}
	printf("\n");
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;++i)
	{
		read();
		printf("Case #%d: ",i);
		work();
	}
	return 0;
}
