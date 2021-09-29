#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define double long double
const double eps=1e-15; int Case,n,m;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double operator /(const node &A){return fabs(x-A.x)<eps?y/A.y:x/A.x;}
	bool operator ==(const node &A) const{return fabs(x-A.x)<eps && fabs(y-A.y)<eps;}
	bool operator <(const node &A) const{
		return fabs(angle()==A.angle())?len()<A.len():angle()<A.angle();
	}
	double angle() const{return atan2(y,x);}
	double len() const{return sqrt(x*x+y*y);}
	void read(){int X,Y,Z; scanf("%d%d%d",&X,&Y,&Z),Z+=X+Y,x=1.*X/Z,y=1.*Y/Z;}
}a[105],h[105],A;
bool check()
{
	if (m==2 && a[0]==a[n-1]) return A==h[0]; double x=(A-a[0])/(a[n-1]-a[0]);
	if (m==2) return fabs((A-a[0])%(a[n-1]-a[0]))<eps && x>-eps && x<1+eps;
	rep(i,m-1) if ((A-h[i])%(h[i+1]-h[i])>eps) return 0; return 1;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n){a[i].read(); if (a[i].x<a[0].x) swap(a[i],a[0]);} A.read();
		A=A-(a[n]=a[0]); rep(i,n+1) a[i]=a[i]-a[n]; sort(a+1,a+n),m=0;
		rep(i,n+1){while (m>1 && (h[m-1]-h[m-2])%(a[i]-h[m-2])<eps) --m; h[m++]=a[i];}
		if (Case) puts(""); printf("Mixture %d\n%s\n",++Case,check()?"Possible":"Impossible");
	}
	return 0;
}
