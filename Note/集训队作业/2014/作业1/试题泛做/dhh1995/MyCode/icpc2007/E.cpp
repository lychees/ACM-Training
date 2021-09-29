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
	bool operator ==(const node &A){return fabs(x-A.x)<eps && fabs(y-A.y)<eps;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
	void prt(){printf("%lf %lf\n",x,y);}
}a[105],A,B;
bool up(node A,node B,node C)
{
	if (A.x>B.x) swap(A,B);
	return C.x+eps>A.x && C.x+eps<B.x && (C-A)%(B-A)>-eps;
}
bool in(node C){bool c=0; rep(i,n) if (up(a[i-1],a[i],C)) c^=1; return c;}
bool cross(node &A,node &B)
{
	if (A==B) return 0;
	rep(i,n){
		node C=a[i-1],D=a[i];
		if (((C-A)%(B-A))*((D-A)%(B-A))<eps && ((A-C)%(D-C))*((B-C)%(D-C))<-eps) return 1;
	}
	return in((A+B)/2);
}
void init()
{
	L=0; rep(i,n) L+=(a[i]-a[i-1]).len();
	rep(i,n+1) rep(j,n)
		d[i][j]=i==j?0:(i>n || abs(i-j)!=1) && cross(a[i],a[j])?1e9:(a[i]-a[j]).len();
	d[1][n]=d[n][1]=(a[1]-a[n]).len();
//	rep(i,n+1){rep(j,n) printf("%.3lf ",d[i][j]<1e9?d[i][j]:-1); puts("");}
	rep(k,n) rep(i,n+1) rep(j,n) if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
}
bool check(double t)
{
	double D=t*vl+(a[1]-a[0]).len(),e; D-=int(D/L)*L; int w;
	rep(i,n) if ((e=(a[i]-a[i-1]).len())>=D){B=a[i-1]+(a[i]-a[i-1])/e*D,w=i; break;} else D-=e;
	if ((A-B).len()>t*vp) return 0; if (!cross(A,B)) return 1;
	rep(i,n) *d[i]=i!=w && i%n!=w-1 && cross(a[i],B)?1e9:(a[i]-B).len();
	rep(i,n) if (d[n+1][i]+*d[i]<t*vp) return 1; return 0;
}
int main()
{
//	freopen("E.in","r",stdin);
//	freopen("E.out","w",stdout);
	while (scanf("%d",&n),n){
		rep(i,n) a[i].read(); a[0]=a[n],A.read(),a[n+1]=A; scanf("%lf%lf",&vl,&vp);
		init(); double l=0,r=1e8,m; while (l+1e-8<r) m=(l+r)/2,(check(m)?r:l)=m;
		ans=int(round(l*60)),printf("Case %d: Time = %d:%02d\n",++Case,ans/60,ans%60);
	}
	return 0;
}
