#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,m,H; double d,h; char ch,a[55],*b;
double g(double a,double x)
{
	double t=2*a*x,sq=sqrt(1+t*t);
	return (t*sq+log(fabs(t+sq)))/4/a;
}
double work(double y1,double y2)
{
	double s=(sqrt(y1)+sqrt(y2))/d,a=s*s;
	return g(a,sqrt(y2/a))-g(a,-sqrt(y1/a));
}
int main()
{
	while (scanf("%d%d%lf",&n,&m,&d),n||m){
		rep(i,n+m){do ch=getchar(); while (ch!='N' && ch!='C' && ch!='B'); a[i]=ch;}
		b=a+n,H=min(n,m),h=-1;
		rep(i,H-1){
			if (i>1 && (a[i]!='C' && b[i]!='C' || a[i-1]!='B' && b[i-1]!='B')){h=i*3-2.5; break;}
			if (a[i]!='C' && b[i]!='C' || a[i]!='B' && b[i]!='B'){h=i*3-2; break;}
			if (a[i+1]!='C' && b[i+1]!='C' || a[i]!='B' && b[i]!='B'){h=i*3-1.5; break;}
		}
		if (Case) puts(""); printf("Case %d: ",++Case);
		if (h<0) puts("impossible"); else h+=1,printf("%.3lf\n",work(n*3-2-h,m*3-2-h));
	}
	return 0;
}
