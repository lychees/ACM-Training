#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 3000010
using namespace std;
int l,r,p,a[maxn],dp[maxn];
void work()
{
	static bool ans[maxn];
	int tot=0;
	a[++tot]=1;
	for(int i=2;i<=p;++i)
	{
		bool isPrime=true;
		for(int j=2;j*j<=i;++j)
			if(i%j==0)
				isPrime=false;
		if(!isPrime)
			continue;
		for(int j=1;j<=tot;++j)
			if(a[j]<=r/i)
				a[++tot]=a[j]*i;
	}
	sort(a+1,a+tot+1);
	fill(dp+2,dp+tot+1,1<<30);
	for(int i=2;i<=p;++i)
		for(int j=1,k=1;j<=tot;++j)
			if(a[j]%i==0)
			{
				dp[j]=min(dp[j],dp[k]+1);
				if(dp[j]+i<=p)
					ans[j]=true;
				++k;
			}
	int total=0;
	for(int i=1;i<=tot;++i)
		if(a[i]>=l&&ans[i])
			++total;
	printf("%d\n",total);
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%d %d %d",&l,&r,&p);
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
