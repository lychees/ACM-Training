#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
const int mod=1000000007;
int a[22][22],id[22],n,m,K,val[22],ans=0,cnt,s[22][22];
bool g[22][22][22];

void dfs(int x,int y,int tot)
{
	if(tot>cnt)return;
	if(y>m)y=1,x++;
	if(x==n+1){ans=(ans+val[tot])%mod;return;}
	int S=s[x-1][y]|s[x][y-1];
	if(a[x][y]>=0)
	{
		if(!(S&(1<<a[x][y])))
			s[x][y]=S|(1<<a[x][y]),dfs(x,y+1,tot);
	}else
	{
		for(int i=0;i<K;i++)
			if(!(S&(1<<i))&&(i<=tot||(i>=cnt&&!g[i][x][y])))
				s[x][y]=S|(1<<i),dfs(x,y+1,tot+(i==tot));
	}
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	if(n+m-1>K)return puts("0"),0;
	cnt=K-1;
	memset(id,-1,sizeof(id));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);a[i][j]--;
			if(a[i][j]>=0)
			{
				if(id[a[i][j]]<0)id[a[i][j]]=cnt--;
				a[i][j]=id[a[i][j]];
			}
		}
	cnt++;
	for(int k=cnt;k<K;k++)
		for(int i=n;i;i--)
			for(int j=m;j;j--)
				g[k][i][j]=g[k][i][j+1]||g[k][i+1][j]||(a[i][j]==k);
	for(int i=0;i<=cnt;i++)
	{
		val[i]=1;
		for(int j=cnt;j>cnt-i;j--)val[i]=val[i]*j;
	}
	dfs(1,1,0);
	cout<<ans<<endl;
	cerr<<clock()<<endl;
	return 0;
}
