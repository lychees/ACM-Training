#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 2010
#define maxm 10010
#define mod 10007
#define lowbit(x) (x&-x)
using namespace std;
int dp[maxn],sum[maxn][maxm],fact[maxn],n;
void Prepare()
{
	fact[0]=1;
	for(int i=1;i<=2000;++i)
		fact[i]=fact[i-1]*i%mod;
}
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a%=mod;
}
void add(int p,int x,int *sum)
{
	for(int i=p;i<=10000;i+=lowbit(i))
		add(sum[i],x);
}
int getsum(int p,int *sum)
{
	int ans=0;
	for(int i=p;i;i-=lowbit(i))
		add(ans,sum[i]);
	return ans;
}
void read()
{
	memset(sum,0,sizeof(sum));
	memset(dp,0,sizeof(dp));
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		for(int j=i;j>1;--j)
		{
			int val=getsum(10000-x+1,sum[j-1]);
			add(10000-x+1,val,sum[j]),add(dp[j],val);
		}
		add(10000-x+1,1,sum[1]),add(dp[1],1);
	}
}
int work()
{
	int ans=dp[n];
	for(int i=n-1;i>=1;--i)
		add(ans,(dp[i]*fact[n-i]-dp[i+1]*fact[n-i-1]%mod*(i+1)));
	return ans;
}
int main()
{
	Prepare();
	int T;
	cin>>T;
	for(int i=1;i<=T;++i)
	{
		read();
		printf("Case #%d: %d\n",i,work());
	}
	return 0;
}
