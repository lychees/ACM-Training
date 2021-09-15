#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 1010
#define maxm 410
using namespace std;
int n,G,R;
double p[maxn],sum1[maxn];
void read()
{
	scanf("%d %d %d",&n,&R,&G);
	R*=G;
	for(int i=1;i<=n;++i)
		scanf("%lf",p+i);
	sort(p+1,p+n+1);
	sum1[n+1]=0;
	for(int i=n;i>=1;--i)
		sum1[i]=sum1[i+1]+p[i];
}
bool check(double Q)
{
	static double dp[maxm];
	double sum2=0;
	dp[0]=sum1[1]/n-Q,sum2=dp[0]*G;
	for(int i=1;i<G;++i)
		dp[i]=dp[i-1];
	for(int i=G;i<R;++i)
	{
		dp[i]=dp[i-1];
		for(int j=0;j<n;++j)
			dp[i]=max(dp[i],(sum1[j+1]/n-Q*(n-j)/n+sum2*j/n)*n/(n-j));
		if(dp[i]>=0)
			return true;
		sum2+=dp[i]-dp[i-G];
	}
	dp[R]=dp[R-1];
	for(int i=0;i<n;++i)
		dp[R]=max(dp[R],sum1[i+1]/n-Q*(n-i)/n+sum2*i/n);
	return dp[R]>=0;
}
double binary(double l,double r)
{
	for(int i=1;i<=100;++i)
	{
		double mid=(l+r)/2;
		check(mid)>0?l=mid:r=mid;
	}
	return l;
}
int main()
{
	freopen("F20.in","r",stdin);
	freopen("F20.out","w",stdout);
	int T;
	scanf("%d",&T);
	for(int Case=1;Case<=T;++Case)
	{
		read();
		printf("Case #%d: %.20f\n",Case,binary(0,1));
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
