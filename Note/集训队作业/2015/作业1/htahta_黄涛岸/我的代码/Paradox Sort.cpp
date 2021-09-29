#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=103,maxN=103*103;
int T,n,K,Link[maxn],pre[maxN],t[maxN],tot;
char a[maxn][maxn];
bool vis[maxn],used[maxn];
inline char getch()
{
	char ch;
	while(!isalpha(ch=getchar()));
	return ch;
}
void dfs(int x)
{
	vis[x]=1;
	for(int i=Link[x];i;i=pre[i])
		if(!vis[t[i]])dfs(t[i]);
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	for(int _=1;_<=T;_++)
	{
		printf("Case #%d:",_);
		scanf("%d%d\n",&n,&K);
		tot=0;K++;
		memset(Link,0,4*(n+1));
		for(int i=1;i<=n;vis[i]=used[i]=0,i++)
			for(int j=1;j<=n;j++)
			{
				if(i==j)continue;
				if((a[i][j]=getch())=='Y')
					pre[++tot]=Link[i],Link[i]=tot,t[tot]=j;
			}
		getchar();
		dfs(K);
		for(int i=1;i<=n;i++)
			if(!vis[i])puts(" IMPOSSIBLE"),n=0;
		if(!n)continue;
		for(int r=1,cur=-1;r<=n;r++)
			for(int j=1;j<=n;j++)
			{
				if(used[j]||(cur!=-1&&j==K&&a[cur][j]=='Y'))continue;
				if(used[K]){printf(" %d",j-1);used[j]=1;break;}
				int best=(cur==-1||a[j][cur]=='Y')?j:cur;
				used[j]=1;
				bool ok=1;
				if(j==K)
				{
					for(int k=1;k<=n&&ok;k++)
						if(!used[k]&&a[k][j]=='Y')ok=0;
				}else
				{
					memcpy(vis+1,used+1,n);
					dfs(K);
					for(int k=1;k<=n&&ok;k++)
						if(!vis[k]&&a[best][k]!='Y')ok=0;
				}
				if(ok){cur=best;printf(" %d",j-1);break;}
				used[j]=0;
			}
		puts("");
	}
	return 0;
}

