#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
const int N = 305;
const int M = 16;
const long long inf = 987654321987654321LL;
long long dp[N][N][M];
int n,m,p;
long long f(int x,int y,int z)
{
	if(dp[x][y][z]==inf && z)
	{
		long long now=x*y-p;
		now*=now;
		if((z&11) && (z&14))
		{
			int i;
			if((z&5)==5)
			{
				for(i=1;i<=y/2;i++)
					now=min(now,f(x,i,(z|4)^4)+f(x,y-i,(z|1)^1));
			}
			else
			{
				for(i=1;i<y;i++)
					now=min(now,f(x,i,(z|4)^4)+f(x,y-i,(z|1)^1));
			}
		}
		if((z&7) && (z&13))
		{
			int i;
			if((z&10)==10)
			{
				for(i=1;i<=x/2;i++)
					now=min(now,f(i,y,(z|8)^8)+f(x-i,y,(z|2)^2));
			}
			else
			{
				for(i=1;i<x;i++)
					now=min(now,f(i,y,(z|8)^8)+f(x-i,y,(z|2)^2));
			}
		}
		dp[x][y][z]=now;
	}
	return dp[x][y][z];
}
int main()
{
	int i,j,k;
	cin>>n>>m>>p;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			for(k=0;k<=15;k++)
				dp[i][j][k]=inf;
		}
	}
	cout<<f(n,m,15)<<endl;
	return 0;
}
