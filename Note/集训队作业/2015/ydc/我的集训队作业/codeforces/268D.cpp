#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 32
#define mod 1000000009
using namespace std;
typedef long long LL;
int n,m;
LL dp[2][2][maxn][maxn][maxn];
int Dp()
{
	int cur=0;
	dp[cur][1][1][1][1]=4;
	for(int i=1;i<n;++i)
	{
		for(int a=0;a<=1;++a)
			for(int b=1;b<=m+1;++b)
				for(int c=b;c<=m+1;++c)
					for(int d=c;d<=m+1;++d)
						if(dp[cur][a][b][c][d])
						{
							int val=dp[cur][a][b][c][d]%mod,vb=b+(b<=m),vc=c+(c<=m),vd=d+(d<=m);
							dp[cur^1][a][vb][vc][vd]+=val;
							if(!a)
							{
								dp[cur^1][b<m][vc][vd][m+1]+=val;
								dp[cur^1][c<m][vb][vd][m+1]+=val;
								dp[cur^1][d<m][vb][vc][m+1]+=val;
							}
							else
							{
								dp[cur^1][b<m][1][vc][vd]+=val;
								dp[cur^1][c<m][1][vb][vd]+=val;
								dp[cur^1][d<m][1][vb][vc]+=val;
							}
							dp[cur][a][b][c][d]=0;
						}
		cur^=1;
	}
	int ans=0;
	for(int a=0;a<=1;++a)
		for(int b=0;b<=m+1;++b)
			for(int c=b;c<=m+1;++c)
				for(int d=c;d<=m+1;++d)
					if(a||b<=m-1)
						ans=(ans+dp[cur][a][b][c][d])%mod;
	return ans;
}
int main()
{
	cin>>n>>m;
	cout<<Dp()<<endl;
	return 0;
}
