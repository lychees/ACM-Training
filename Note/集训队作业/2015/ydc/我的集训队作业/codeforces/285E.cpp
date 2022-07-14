#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
#define mod 1000000007
using namespace std;
typedef long long LL;
LL dp[maxn][maxn][2][2],comb[maxn][maxn],ans[maxn],fact[maxn];
int n,m;
int Dp()
{
	comb[0][0]=1,fact[0]=1;
	for(int i=1;i<=n;++i)
	{
		comb[i][0]=1,fact[i]=fact[i-1]*i%mod;
		for(int j=1;j<=i;++j)
			comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%mod;
	}
	dp[0][0][0][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=i;++j)
			for(int a=0;a<=1;++a)
				for(int b=0;b<=1;++b)
				{
					dp[i][j][b][0]=(dp[i][j][b][0]+dp[i-1][j][a][b])%mod;
					if(j>=1&&i<n)
						dp[i][j][b][1]=(dp[i][j][b][1]+dp[i-1][j-1][a][b])%mod;
					if(a==0&&i>1&&j>=1)
						dp[i][j][b][0]=(dp[i][j][b][0]+dp[i-1][j-1][a][b])%mod;
				}
	for(int i=n;i>=0;--i)
	{
		for(int j=0;j<=1;++j)
			for(int k=0;k<=1;++k)
				ans[i]+=dp[n][i][j][k];
		ans[i]=ans[i]*fact[n-i]%mod;
		for(int j=i+1;j<=n;++j)
			ans[i]=(ans[i]-ans[j]*comb[j][i]%mod+mod)%mod;
	}
	return ans[m];
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	cin>>n>>m;
	cout<<Dp()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
