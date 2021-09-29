#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double pi=acos(-1.); const int N=40005;
int Case,n,m,c,t,flag,x[N],y[N],p[N]; double ans,a[N];
bool cmp(const int i,const int j){return a[i]<a[j];}
void upd(double a){if (fabs(a)<fabs(ans)) ans=a;}
void add(double l,double r){a[++m]=l,a[++m]=r;}
void ins(double a)
{
	double l=-pi/2+a,r=pi/2+a;
	if (l<-pi) add(l+2*pi,pi),add(-pi,r);
	else if (r>pi) add(l,pi),add(-pi,r-2*pi);
	else add(l,r);
}
int main()
{
	while (scanf("%d%d",&n,&t),n){
		ans=pi+1,c=m=0,flag=1; rep(i,n) scanf("%d%d",x+i,y+i),flag&=x[i]>=x[i-1];
		printf("Case %d: ",++Case);
		if (!t || flag){puts("Acceptable as proposed\n"); continue;}
		rep(i,n) ins(atan2(y[i]-y[i-1]+0.,x[i]-x[i-1]+0.));
		rep(i,m) p[i]=i; sort(p+1,p+m+1,cmp);
		rep(k,m){int i=p[k]; if (c==n) upd(a[i]); c+=i&1?1:-1; if (c==n) upd(a[i]);}
		if (ans>pi+.5) puts("Unacceptable\n");
		else printf("Acceptable after %sclockwise rotation of %.2lf degrees\n\n",
			ans<0?"counter":"",fabs(ans/pi*180));
	}
	return 0;
}
