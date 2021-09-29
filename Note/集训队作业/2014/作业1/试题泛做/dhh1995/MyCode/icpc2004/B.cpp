#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-6; int Case,n,z; char ch;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	node operator *(const node &A){return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	double operator &(const node &A){return x*A.x+y*A.y;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%d%*c%c",&z,&ch),x=z*(ch=='L'?-1:ch=='R'),y=z*(ch=='D'?-1:ch=='U');}
	void prt(){printf("%lf %lf\n",x,y);}
}a[25],d[25],U,V,A,B,C;
node polar(double A){return node(cos(A),sin(A));}
bool cross(node &A,node &B,double R,node &C,node &D)
{
	double L=(A-B).len(),p; if (R+R<L) return 0; node V=(B-A)*(R/(B-A).len());
	p=acos(L/2/R),C=A+V*polar(p),D=A+V*polar(-p); return 1;
}
bool cross(node &A,node &B,node O,double R,node &C,node &D)
{
	double L=(O-A)%(B-A)/(B-A).len(); node V=(B-A); V=node(-V.y,V.x),V=V*(L/V.len());
	O=O+V,L=sqrt(R*R-L*L); V=(B-A),V=V*(L/V.len()),C=O+V,D=O-V; return 1;
}
bool cross(node &A,node &B,node &C,node &D,node &E)
{
	double s1=(C-A)%(B-A),s2=(D-A)%(B-A);
	if (s1*s2>eps || ((A-C)%(D-C))*((B-C)%(D-C))>eps) return 0;
	return E=(C*s2-D*s1)/(s2-s1),1;
}
bool up(node A,node B,node &C)
{
	if (A.x>B.x) swap(A,B);
	return A.x<C.x+eps && C.x+eps<B.x && (C-A)%(B-A)>eps;
}
double dist(node &A,int i)
{
	if (((A-a[i-1])&d[i])<0) return (A-a[i-1]).len();
	if (((A-a[i])&d[i])>0) return (A-a[i]).len();
	return fabs((A-a[i-1])%d[i])/d[i].len();
}
bool work(node &A,double R)
{
	bool c=0;
	rep(i,n){if (dist(A,i)+eps<R) return 0; if (up(a[i-1],a[i],A)) c^=1;} return c;
}
void move(node &A,node &B,double R){node V=(B-A); V=node(-V.y,V.x),V=V*(R/V.len()); A=A+V,B=B+V;}
bool check(double R)
{
	rep(i,n){
		U=a[i-1],V=a[i],move(U,V,R);
		rep(j,n) if (i!=j)
			if (cross(U,V,a[j],R,A,B)) if (work(A,R) || work(B,R)) return 1;
		rep(j,i-1){
			if (cross(a[i],a[j],R,A,B)) if (work(A,R) || work(B,R)) return 1;
			A=a[j-1],B=a[j],move(A,B,R); if (cross(U,V,A,B,C)) if (work(C,R)) return 1;
		}
	}
	return 0;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) d[i].read(),a[i]=a[i-1]+d[i];
		double l=0,r=250,m; while (l+eps<r) m=(l+r)/2,(check(m)?l:r)=m;
		if (Case) puts(""); printf("Case Number %d radius is: %.2lf\n",++Case,l+eps);
	}
	return 0;
}
