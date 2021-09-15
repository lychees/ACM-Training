#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 40010
using namespace std;
int dp[maxn],n,a[maxn];
void read()
{
	int m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
}
int Dp()
{
	static bool vis[maxn];
	static int may[maxn];
	int tot=0,cnt=0;
	for(int i=1;i<=n;++i)
	{
		cnt+=vis[a[i]]==0;
		vis[a[i]]=1;
		int id=tot+1;
		for(int j=1;j<=tot;++j)
			if(a[may[j]]==a[i])
				id=j;
		tot=max(tot,id);
		for(int j=id;j<tot;++j)
			may[j]=may[j+1];
		may[tot]=i;
		if((tot-1)*(tot-1)>n)
		{
			for(int j=1;j<tot;++j)
				may[j]=may[j+1];
			--tot;
		}
		dp[i]=cnt*cnt;
		for(int j=1;j<tot;++j)
			dp[i]=min(dp[i],dp[may[j]]+(tot-j)*(tot-j));
	}
	return dp[n];
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	printf("%d\n",Dp());
	return 0;
}
