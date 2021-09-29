#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-10;
int Case,n,ans; double L,vl,vp,d[105][105],l[105],r[105];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator /(const node &A){return fabs(x-A.x)<eps?y/A.y:x/A.x;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
	void prt(){printf("%lf %lf\n",x,y);}
}a[105],A,B;
bool in(double l,double r,double a){if (l<r) return l+eps<a && a<r-eps; return a>l+eps || a<r-eps;}
bool on(node U,node V,double e){return fabs(U%V)<eps && U/V>e && U/V<1-e;}
bool cross(node &A,node &B,node &C,node &D){return ((C-A)%(B-A))*((D-A)%(B-A))<-eps;}
bool cross(node &A,node B)
{
	node V=B-A,last=a[0]; bool flag=0;
	rep(i,n) if (cross(A,B,a[i],a[i+1]) && cross(a[i],a[i+1],A,B)) return 1;
	rep(i,n) if (on(a[i]-A,V,eps))
		if (cross(A,B,a[i-1],a[i+1]) ||
			on(a[i-1]-A,V,-eps) && (a[i+1]-a[i-1])%(a[i]-a[i-1])>0 ||
			on(a[i+1]-A,V,-eps) && (a[i-1]-a[i])%(a[i+1]-a[i])>0) return 1;
	return 0;
}
bool cross(int i,node &A){if (in(l[i],r[i],(A-a[i]).angle())) return 1; return cross(a[i],A);}
void init()
{
	L=0; rep(i,n) L+=(a[i+1]-a[i]).len(),l[i]=(a[i+1]-a[i]).angle(),r[i]=(a[i-1]-a[i]).angle();
	rep(i,n){
		d[n+1][i]=cross(i,A)?1e9:(a[i]-A).len();
		rep(j,n) d[i][j]=i==j?0:cross(i,a[j])?1e9:(a[i]-a[j]).len();
	}
	rep(k,n) rep(i,n+1) rep(j,n) if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
}
bool check(double t)
{
	double D=t*vl,e; D-=int(D/L)*L;
	rep(i,n) if ((e=(a[i+1]-a[i]).len())>=D){B=a[i]+(a[i+1]-a[i])/e*D; break;} else D-=e;
	if ((A-B).len()>t*vp) return 0; if (!cross(A,B)) return 1;
	rep(i,n) *d[i]=cross(i,B)?1e9:(a[i]-B).len();
	rep(i,n) if (d[n+1][i]+*d[i]<t*vp) return 1; return 0;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) a[i].read(); a[0]=a[n],a[n+1]=a[1],A.read(); scanf("%lf%lf",&vl,&vp);
		init(); double l=0,r=1e9,m; while (l+1e-6<r) m=(l+r)/2,(check(m)?r:l)=m;
		ans=int(round(l*60)),printf("Case %d: Time = %d:%02d\n",++Case,ans/60,ans%60);
	}
	return 0;
}
