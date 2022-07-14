#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,sum[maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
	{
		scanf("%d",&x);
		sum[i]=sum[i-1]+x;
	}
}
int Dp()
{
	static int F[maxn],dp[maxn],queue[maxn];
	int front=1,rear=0;
	F[n]=sum[n]-sum[n-1],dp[n]=1,sum[n+1]=sum[n],F[n+1]=0;
	for(int i=n;i>=1;--i)
	{
		while(rear>=front&&sum[i]-F[i+1]>=sum[queue[rear]-1]-F[queue[rear]])
			--rear;
		queue[++rear]=i+1;
		while(front<=rear&&sum[queue[front]-1]-sum[i-1]>=F[queue[front]])
			++front;
		F[i]=sum[queue[front-1]-1]-sum[i-1],dp[i]=dp[queue[front-1]]+1;
	}
	return dp[1];
}
int main()
{
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	read();
	printf("%d\n",Dp());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
