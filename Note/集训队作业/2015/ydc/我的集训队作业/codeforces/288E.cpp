#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define mod 1000000007
using namespace std;
typedef long long LL;
bool can[maxn][2];
int dp[maxn][2][3],sum[maxn][3],n,v1[maxn],v2[maxn],pw[maxn];
char a[maxn],b[maxn];
void add(int &a,LL b)
{
	a=(a+b)%mod;
}
void Dp(char *str)
{
	dp[0][0][0]=1,can[0][0]=true;
	for(int i=1;i<=n;++i)
		for(int t=0;t<=1;++t)
			for(int j=4;j<=7;j+=3)
				for(int k=0;k<=1;++k)
				{
					if(k==0&&str[i]<j+'0')
						continue;
					if((k|(str[i]>j+'0'))==t&&can[i-1][k])
					{
						can[i][t]|=can[i-1][k];
						add(dp[i][t][0],dp[i-1][k][0]);
						add(dp[i][t][1],10LL*dp[i-1][k][1]+(LL)dp[i-1][k][0]*j);
						add(dp[i][t][2],(LL)dp[i-1][k][0]*j*j);
						add(dp[i][t][2],20LL*dp[i-1][k][1]%mod*j);
						add(dp[i][t][2],100LL*dp[i-1][k][2]);
						if(t==1&&j==4)
							for(int p=0;p<=2;++p)
								add(sum[i][p],dp[i-1][k][p]);
					}
				}
}
int work()
{
	static int v1[maxn],v2[maxn];
	n=strlen(a+1);
	pw[0]=1;
	for(int i=1;i<=n;++i)
		pw[i]=10LL*pw[i-1]%mod;
	for(int i=n,s1=0,s2=0;i>=1;--i)
	{
		v1[i]=(4LL*pw[n-i]+s1)%mod;
		v2[i]=(7LL*pw[n-i]+s2)%mod;
		s1=(10LL*s1+7)%mod;
		s2=(10LL*s2+4)%mod;
	}
	int ans=0;
	Dp(a);
	for(int i=1;i<=n;++i)
		add(ans,mod-((LL)pw[n-i+1]*pw[n-i+1]%mod*sum[i][2]+(LL)pw[n-i+1]*sum[i][1]%mod*(v1[i]+v2[i])+(LL)v1[i]*v2[i]%mod*sum[i][0])%mod);
	memset(dp,0,sizeof(dp));
	memset(sum,0,sizeof(sum));
	memset(can,0,sizeof(can));
	Dp(b);
	for(int i=1;i<=n;++i)
		add(ans,(LL)pw[n-i+1]*pw[n-i+1]%mod*sum[i][2]+(LL)pw[n-i+1]*sum[i][1]%mod*(v1[i]+v2[i])+(LL)v1[i]*v2[i]%mod*sum[i][0]);
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%s %s",a+1,b+1);
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
