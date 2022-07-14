#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 35
#define maxm 50010
using namespace std;
typedef long long LL;
int mod,n,p[maxn][2],Log[maxn],Power[1000];
bool dp[maxn][maxn][maxm],used[maxn][maxn][maxm];
void read()
{
	scanf("%d %d",&n,&mod);
	int tot=0;
	for(int i=1;i<=40;++i)
		Log[i]=Log[i/10]+1;
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		if(x<32)
			++tot,p[tot][0]=x,p[tot][1]=i;
	}
	Power[0]=1;
	for(int i=1;i<=100;++i)
		Power[i]=Power[i-1]*10%mod;
	n=min(n,31);
}
void print()
{
	for(int i=1;i<=n;++i)
	{
		dp[i][p[i][0]][p[i][0]%mod]=true;
		used[i][p[i][0]][p[i][0]%mod]=true;
		for(int j=0;j<32;++j)
			for(int k=0;k<mod;++k)
				if(dp[i-1][j][k])
				{
					dp[i][j][k]=true;
					dp[i][j^p[i][0]][(k*Power[Log[p[i][0]]]+p[i][0])%mod]=true;
					used[i][j^p[i][0]][(k*Power[Log[p[i][0]]]+p[i][0])%mod]=true;
				}
	}
	static int ans[maxn];
	int na=n,nb=0,nc=0;
	if(!dp[na][nb][nc])
		printf("No\n");
	else
	{
		dp[0][0][0]=true;
		int tot=0;
		while(na)
		{
			if(!used[na][nb][nc])
				--na;
			else
			{
				ans[++tot]=p[na][1];
				nb^=p[na--][0];
				for(int j=0;j<mod;++j)
					if(dp[na][nb][j]&&(j*Power[Log[p[na+1][0]]]+p[na+1][0])%mod==nc)
					{
						nc=j;
						break;
					}
			}
		}
		printf("Yes\n");
		printf("%d\n",tot);
		for(int i=tot;i>=1;--i)
			printf("%d%c",ans[i],i>1?' ':'\n');
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
