#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-8,pi=acos(-1.);
int Case,n,m; double Min,Max;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator *(const node &A){return x*A.x+y*A.y;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double angle() const{return atan2(y,x);}
	double len() const{return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}a[105],h[105];
bool cmp(const node &A,const node &B)
{return fabs(A.angle()-B.angle())<eps?A.len()<B.len():A.angle()<B.angle();}
double f(double theta)
{
	node V(cos(theta),sin(theta)); double L=0,R=0,H=0,D;
	rep(i,m) D=a[i]*V,L=min(L,D),R=max(R,D),H=max(H,fabs(a[i]%V));
	return (R-L)*H;
}
void cal(double L,double R)
{
	while (L+eps<R){double m1=L+(R-L)/3,m2=R-(R-L)/3; if (f(m1)<f(m2)) L=m1; else R=m2;}
	Max=max(Max,f(L));
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n){a[i].read(); if (a[i].x<a[1].x) swap(a[1],a[i]);}
		for (int i=n;i;--i) a[i]=a[i]-a[1]; a[n+1]=a[1]; sort(a+2,a+n+1,cmp),m=0;
		rep(i,n+1){
			while (m>2 && (a[i]-h[m-1])%(h[m]-h[m-1])>-eps) --m;
			h[++m]=a[i];
		}
		--m,Min=1e20,Max=0;
		rep(i,m){
			rep(j,m+1) a[j]=h[j]-h[i]; a[0]=a[m]; 
			double L=a[i-1].angle(),R=a[i+1].angle(); Min=min(Min,f(R));
			if (L<0) L+=pi; else L-=pi;
			if (L<R) cal(L,R); else cal(R,pi*2),cal(-pi*2,L);
		}
		printf("Gift %d\nMinimum area = %.3lf\nMaximum area = %.3lf\n\n",++Case,Min,Max);
	}
	return 0;
}
