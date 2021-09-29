#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double pi=acos(-1.),eps=1e-5; int n; double r,ans;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator ^(const node &A){return x*A.y-y*A.x;}
	double norm(){return x*x+y*y;}
	void read(){scanf("%lf%lf",&x,&y);}
	void prt(bool flag){printf("(%lf %lf)",x,y); if (!flag) putchar(' '); else puts("");}
}a[105];
double angel(node &A){double res=atan2(A.y,A.x); if (res<0) res+=pi; return res;}
bool get(double a,double b,double c,node &C,node &D)
{
	double delta=b*b-4*a*c;
//	printf("%lf\n",delta);
	if (delta<0) return 0; delta=sqrt(delta);
	C.x=(-b-delta)/2/a,D.x=(-b+delta)/2/a; return 1;
}
bool solve(node &A,node &B,node &C)
{
//	(B.y-A.y)/(B.x-A.x),(B^A)/(B.x-A.x),
	node D=B-A; double a=D.y/D.x,b=(B^A)/D.x;
	if (fabs(D.x)<eps){
		C.x=A.x,C.y=sqrt(r*r-C.x*C.x);
		return (C-A).y/(B-A).y>eps && (C-A).y/(B-A).y<1-eps;
	}
//	printf("%lf %lf\n",a,b);
//	puts("?");
	if (!get(1+a*a,2*a*b,b*b-r*r,C,D)) return 0; C.y=a*C.x+b,D.y=a*D.x+b;
	double c=(C-A).x/(B-A).x,d=(D-A).x/(B-A).x;
	if (c>eps && c<1-eps && d>eps && d<1-eps) C=(C+D)/2;
	else if (d>eps && d<1-eps) swap(C,D),swap(c,d);
	return c>eps && c<1-eps;
}
double work(node A,node B)
{
//	A.prt(0),B.prt(1);
	if ((A.norm()<r*r+eps && B.norm()<r*r+eps)) return (A^B)/2; node C;
	if (!solve(A,B,C)) return //printf("%lf\n",r*r*(angel(B)-angel(A))/2),
		r*r*(angel(B)-angel(A))/2;
	return work(A,C)+work(C,B);
}
int main()
{
	freopen("pollution.in","r",stdin);
	freopen("pollution.out","w",stdout);
	while (scanf("%d%lf",&n,&r)!=EOF){
		rep(i,n) a[i].read(); a[n]=a[0],ans=0;
		rep(i,n) ans+=work(a[i],a[i+1]);
//			printf("%lf\n",work(a[i],a[i+1]));
		printf("%.9lf\n",ans);
		}
	return 0;
}
