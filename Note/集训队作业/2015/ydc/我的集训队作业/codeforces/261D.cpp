#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,vA,m,A[maxn];
inline void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
void read()
{
	for(int i=1;i<=n;++i)
		Read(A[i]);
}
int LIS()
{
	static bool use[maxn];
	static int dp[maxn],tmp[maxn];
	static int b[maxn];
	int cnt=0;
	for(int i=1;i<=n;++i)
		use[A[i]]=true;
	for(int i=1;i<=vA;++i)
		if(use[i])
			b[++cnt]=i,use[i]=false;
	if(cnt<=m)
		return cnt;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=cnt;++i)
	{
		int minv=dp[0];
		bool mark=true;
		dp[0]=1<<30;
		for(int j=1;j<=cnt;++j)
		{
			int x=b[j];
			tmp[x]=minv;
			if(minv>dp[x])
				minv=dp[x];
			dp[x]=1<<30;
		}
		for(int j=n;j>=1;--j)
		{
			int v=A[j],x=(tmp[v]-1+n)%n+1,val=(tmp[v]-1+n)/n*n+j;
			if(x<j)
				val-=n;
			if(dp[v]>val)
				dp[v]=val;
			if(dp[v]<=n*m)
				mark=false;
		}
		if(mark)
			return i-1;
	}
	return cnt;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	for(Read(T),Read(n),Read(vA),Read(m);T;--T)
	{
		read();
		printf("%d\n",LIS());
	}
	return 0;
}
