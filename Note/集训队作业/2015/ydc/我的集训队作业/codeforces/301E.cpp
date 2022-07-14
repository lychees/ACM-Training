#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define mod 1000000007
#define maxn 110
using namespace std;
typedef long long LL;
int dp[2][maxn][maxn][maxn],n,m,p,comb[maxn][maxn];
int Dp()
{
	int ans=0;
	comb[0][0]=1;
	for(int i=1;i<=50;++i)
	{
		comb[i][0]=1;
		for(int j=1;j<=i;++j)
			comb[i][j]=min(comb[i-1][j]+comb[i-1][j-1],200);
	}
	int cur=0;
	dp[0][1][0][1]=1;
	for(int i=0;i<m&&i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			for(int k=0;k<=n;++k)
				for(int w=1;w<=p;++w)
					if(dp[cur][j][k][w])
					{
						int val=dp[cur][j][k][w];
						dp[cur][j][k][w]=0;
						if(i)
							ans=(ans+(LL)val*(m-i))%mod;
						for(int x=1;2*x+k<=n;++x)
						{
							int neww=w*comb[x+j-1][x];
							if(neww>p)
								break;
							dp[cur^1][x][k+2*x][neww]=(dp[cur^1][x][k+2*x][neww]+val)%mod;
						}
					}
		cur^=1;
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m>>p;
	cout<<Dp()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
