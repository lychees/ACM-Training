#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double pi=acos(-1.);
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n; double a[15],b[25],L,R,C;
double f(double x){double y=x,res=0; rep(i,n+n) res+=b[i]*y,y*=x; return res;}
int main()
{
	freopen("bottle.in","r",stdin);
	freopen("bottle.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		++n; rep(i,n) scanf("%lf",a+i); rep(i,n+n) b[i]=0;
		rep(i,n) rep(j,n) b[i+j]+=a[i]*a[j]; rep(i,n+n) b[i]/=i+1;
		scanf("%lf %lf %lf",&L,&R,&C),C/=pi;
		printf("Case %d: %.2lf\n",++Case,(f(R)-f(L))*pi);
		if ((f(R)-f(L))<C){puts("insufficient volume"); continue;}
		for (int i=0,j=1;i<=(R-L)*200 && j<=8;++i) if (f(L+i/200.)-f(L)>C*j){
			if (j>1) putchar(' '); ++j;
			printf("%.2lf",i/200.-1e-8);
		}
		puts("");
	}
	return 0;
}
