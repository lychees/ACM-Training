#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
using namespace std;
int a[maxn],n,m;
double dp[maxn][maxn];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
}
void work()
{
	double ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dp[i][j]=a[i]>a[j];
	for(int i=1,a,b;i<=m;++i)
	{
		scanf("%d %d",&a,&b);
		for(int j=1;j<=n;++j)
			if(j!=a&&j!=b)
				dp[a][j]=dp[b][j]=(dp[a][j]+dp[b][j])/2;
		dp[a][b]=dp[b][a]=0.5;
		for(int j=1;j<=n;++j)
			if(j!=a&&j!=b)
				dp[j][a]=dp[j][b]=(dp[j][a]+dp[j][b])/2;
	}
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			ans+=dp[i][j];
	printf("%.20f\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
