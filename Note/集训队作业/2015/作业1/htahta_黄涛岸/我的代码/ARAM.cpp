#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=1003;
double a[maxn],s[maxn],f[maxn];
int T,n,G,R;
inline bool can(double x)
{
	for(int i=0;i<G;i++)f[i]=s[n]-x;
	double tp=f[0]*G,p;
	for(int i=G,j;i<=R*G;tp+=f[i]-f[i-G],i++)
		for(f[i]=-1e100,j=0;j<n;j++)
		{
			p=1-double(j)/n,f[i]=max(f[i],s[j]-x+p/(1-p)*tp);
			if(f[i]>=0)return 1;
		}
	return 0;
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d%d",&n,&R,&G);
		for(int i=1;i<=n;i++)scanf("%lf",a+i);
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[n-i+1];
		for(int i=1;i<=n;i++)s[i]/=i;
		double l=0,r=1,m;
		//for(int i=0;i<60;i++)
		while(r-l>1e-13)
		{
			m=(l+r)/2;
			if(can(m))l=m;else r=m;
		}
		printf("Case #%d: %.12lf\n",t,l);
	}
	return 0;
}
