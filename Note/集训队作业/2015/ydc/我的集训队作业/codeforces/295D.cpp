#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 2010
#define mod 1000000007
using namespace std;
typedef long long LL;
int n,m;
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
int Dp()
{
	static int dp[maxn][maxn][2];
	for(int i=1;i<=n;++i)
		for(int j=2,sum1=0,sum2=0;j<=m;++j)
		{
			add(sum1,sum2);
			dp[i][j][1]=sum1+1;
			add(sum2,dp[i-1][j][0]),add(sum1,dp[i-1][j][0]);
			dp[i][j][0]=sum1+1;
		}
	int ans=0;
	for(int i=1;i<=n;++i)
		for(int j=2;j<=m;++j)
			add(ans,(LL)dp[i][j][0]*dp[n-i+1][j][1]%mod*(m-j+1)%mod);
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d",&n,&m);
	cout<<Dp()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
