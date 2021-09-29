#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=200000,mod=10007;
int dp[maxn],g[11][maxn],n,m,s[maxn],N,id[1<<20];
char a[13][13],h[11][maxn];
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int T;scanf("%d",&T);
	for(int _=1;_<=T;_++)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
		N=0;
		for(int i=(1<<m)-1;i<(1<<(n+m));i++)
		{
			int cnt=0,x=0,y=m;id[i]=0;
			for(int j=i;j;j-=j&-j)cnt++;
			if(cnt!=m)continue;
			dp[++N]=0;id[i]=N;
			for(int j=0,k=1;j<n+m;j++,k<<=1)
				if(i&k)y--;else
				{
					g[++x][N]=0;
					if(y&&(i&(k<<1)))h[x][N]=a[x][y],g[x][N]=id[i^k^(k<<1)];
				}
		}
		dp[1]=1;
		for(char ch='a';ch<='z';ch++)
			for(int i=1;i<=n;i++)
				for(int t,j=1;j<=N;j++)
					if((t=g[i][j])&&dp[t]&&(h[i][j]==ch||h[i][j]=='.'))
						dp[j]+=dp[t],dp[j]-=dp[j]>=mod?mod:0;
		printf("Case #%d: %d\n",_,dp[N]);
	}
	return 0;
}
