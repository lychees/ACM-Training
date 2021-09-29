#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
double x,p,lim;
double g(int a,int b){return (b+x*a)*(pow(p,a)-1)/(pow(p,a+b)-1)-x*a;}
double f(int a)
{
	int l=1,r=int(lim),m;
	while (l<r) m=l+r>>1,g(a,m)>g(a,m+1)?r=m:l=m+1;
	return g(a,l);
}
int main()
{
	freopen("bettor.in","r",stdin);
	freopen("bettor.out","w",stdout);
	while (scanf("%lf%lf",&x,&p)!=EOF){
		x=1-x/100,p/=100; if (p<1e-8){printf("%.9lf\n",0); continue;} p=(1-p)/p,lim=10/log10(p);
		int l=1,r=int(lim),m;
		while (l<r) m=l+r>>1,f(m)>f(m+1)?r=m:l=m+1;
		printf("%.9lf\n",max(0.,f(l)));
	}
	return 0;
}
