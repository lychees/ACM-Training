#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 20
#define lowbit(x) (x&-x)
using namespace std;
int dp[1<<18],sum[1<<18],a[maxn],Log[1<<18],n,m;
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		Log[1<<(i-1)]=i;
	}
}
int Dp()
{
	for(int i=1;i<(1<<n);++i)
		sum[i]=sum[i^lowbit(i)]+a[Log[lowbit(i)]];
	int all=(1<<n)-1;
	for(int i=0;i<=n-1;++i)
	{
		for(int j=1;j<(1<<n);++j)
			if(dp[j]<sum[j])
				for(int k=j;k;k-=lowbit(k))
					dp[j]=max(dp[j],dp[j^lowbit(k)]);
		if(dp[all]==sum[all])
			return i;
		for(int j=1;j<(1<<n);++j)
			if(sum[j]-dp[j]<=m)
				dp[j]=sum[j];
	}
	return n;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	cout<<Dp()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
