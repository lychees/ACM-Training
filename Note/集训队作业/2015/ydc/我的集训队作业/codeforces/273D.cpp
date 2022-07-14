#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 160
#define mod 1000000007
using namespace std;
int n,m,sum[2][2][maxn][maxn];
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
int getsum(int a,int b,int c,int d,int t1,int t2)
{
	if(a>b||c>d)
		return 0;
	swap(b,c);
	int ans=sum[t1][t2][c][d];
	add(ans,mod-sum[t1][t2][c][b-1]);
	add(ans,mod-sum[t1][t2][a-1][d]);
	add(ans,sum[t1][t2][a-1][b-1]);
	return ans;
}
int Dp()
{
	static int dp[maxn][maxn][maxn][2][2];
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			for(int k=1;k<=m;++k)
				for(int t1=0;t1<=1;++t1)
					for(int t2=0;t2<=1;++t2)
					{
						sum[t1][t2][j][k]=dp[i-1][j][k][t1][t2];
						add(sum[t1][t2][j][k],sum[t1][t2][j-1][k]);
						add(sum[t1][t2][j][k],sum[t1][t2][j][k-1]);
						add(sum[t1][t2][j][k],mod-sum[t1][t2][j-1][k-1]);
					}
		for(int j=1;j<=m;++j)
			for(int k=j;k<=m;++k)
			{
				dp[i][j][k][0][0]=(getsum(j,k,j,k,0,0)+1)%mod;
				dp[i][j][k][0][1]=(getsum(j,k,k,m,0,1)+getsum(j,k,k+1,m,0,0))%mod;
				dp[i][j][k][1][0]=(getsum(1,j,j,k,1,0)+getsum(1,j-1,j,k,0,0))%mod;
				dp[i][j][k][1][1]=(getsum(1,j,k,m,1,1)+getsum(1,j-1,k+1,m,0,0))%mod;
				add(dp[i][j][k][1][1],getsum(1,j-1,k,m,0,1));
				add(dp[i][j][k][1][1],getsum(1,j,k+1,m,1,0));
				add(ans,dp[i][j][k][0][0]);
				add(ans,dp[i][j][k][0][1]);
				add(ans,dp[i][j][k][1][0]);
				add(ans,dp[i][j][k][1][1]);
			}
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	cout<<Dp()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
