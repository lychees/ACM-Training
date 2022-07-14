#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 101000
#define maxm 1000
using namespace std;
int n,m,total,dp[maxn],g[maxn];
short sum[maxn][maxm];
void update(int &a,int b)
{
	if(a>b)
		a=b;
}
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	int N;
	Read(n),Read(N);
	for(m=1;m*(m+1)/2+2<=3*N;++m);
	for(int i=1,a,b;i<=N;++i)
	{
		Read(a),Read(b);
		a=n-a+1,swap(a,b);
		if(b>m)
			total+=3;
		else
			++sum[a][b];
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			sum[i][j]+=sum[i][j-1];
}
int Dp()
{
	for(int i=1;i<=m;++i)
		for(int j=1;j<=i;++j)
			g[i]+=sum[j][i-j+1];
	for(int i=1;i<=n;++i)
		dp[i]=1<<30;
	for(int i=1;i<=n;++i)
	{
		update(dp[i],dp[i-1]+sum[i][m]*3);
		for(int j=1;j<=m;++j)
			if(j*(j+1)/2+2<=g[j]*3)
			{
				int val=dp[i-1];
				for(int k=1;k<=j;++k)
				{
					val+=(sum[i+k-1][m]-sum[i+k-1][j-k+1])*3;
					update(dp[i+k-1],val+j*(j+1)/2+2);
				}
			}
		for(int j=1;j<m;++j)
			g[j]=g[j+1]-sum[i][j+1];
		g[m]=0;
		for(int j=1;j<=m;++j)
			g[m]+=sum[i+j][m-j+1];
	}
	return dp[n]+total;
}
int main()
{
	read();
	cout<<Dp()<<endl;
	return 0;
}
