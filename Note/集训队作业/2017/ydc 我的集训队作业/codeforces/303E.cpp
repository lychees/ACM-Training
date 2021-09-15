#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 90
using namespace std;
int v[maxn*2],L[maxn],R[maxn],tot,n;
double ans[maxn][maxn];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d",L+i,R+i);
		v[++tot]=L[i],v[++tot]=R[i];
	}
	sort(v+1,v+tot+1);
	tot=unique(v+1,v+tot+1)-v-1;
}
void Dp()
{
	static double dp[maxn][maxn],ans[maxn];
	static int va[maxn],vb[maxn];
	for(int i=1;i<=n;++i)
	{
		memset(ans,0,sizeof(ans));
		for(int *x=find(v+1,v+tot+1,L[i]);*x!=R[i];++x)
		{
			int cnt=0,m=0,a=*x,b=*(x+1);
			for(int j=1;j<=n;++j)
				if(i!=j)
				{
					if(R[j]<=*x)
						++cnt;
					else if(L[j]<=*x)
					{
						++m;
						va[m]=L[j],vb[m]=R[j];
					}
				}
			dp[0][0]=b-a;
			for(int j=1;j<=m;++j)
			{
				double v=1.0/(vb[j]-va[j]);
				double v1=max(0,vb[j]-b)*v,v2=(b-a)*v,v3=max(0,a-va[j])*v;
				for(int k=j;k>=0;--k)
				{
					dp[k][j-k]=0;
					for(int l=j-k;l>=0;--l)
					{
						dp[k][l]=dp[k][l]*v1;
						dp[k][l]+=dp[k-1][l]*v2;
						dp[k][l]+=dp[k][l-1]*v3;
					}
				}
			}
			for(int j=0;j<=m;++j)
			{
				double v=1.0/(j+1)/(R[i]-L[i]);
				for(int k=0;k+j<=m;++k)
				{
					double val=dp[j][k]*v;
					ans[k+cnt+1]+=val,ans[k+cnt+j+2]-=val;
				}
			}
		}
		for(int j=1;j<=n;++j)
		{
			ans[j]+=ans[j-1];
			printf("%.10f%c",ans[j],j<n?' ':'\n');
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Dp();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
