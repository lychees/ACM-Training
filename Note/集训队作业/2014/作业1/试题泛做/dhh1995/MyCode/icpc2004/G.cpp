#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=.1,pi=acos(-1.);
int Case,n; double m,d,t,r[15];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator *(const node &A){return node(x*A.x-y*A.y,x*A.y+y*A.x);}
	bool operator !=(const node &A) const{return fabs(x-A.x)>eps || fabs(y-A.y)>eps;}
	double angle(){return atan2(y,x);}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
	void prt(){printf("%lf %lf\n",x,y);}
}a[15],T,S,A,B;
node polar(double a){return node(cos(a),sin(a));}
bool cross(node &A,double r1,node &B,double r2,node &C,node &D)
{
	double L=(B-A).len(); if (r1+r2+eps<L || L+eps<fabs(r1-r2)) return 0;
	double a=acos((r1*r1+L*L-r2*r2)/2/r1/L); node V=(B-A)*(r1/L);
	return C=A+V*polar(a),D=A+V*polar(-a),1;
}
bool check(node &A){rep(i,n) if (fabs((A-a[i]).len()-r[i])>eps) return 0; return 1;}
int main()
{
	while (scanf("%d%lf",&n,&m),n){
		T.read(); int cnt=0,j;
		rep(i,n) a[i].read(),scanf("%lf%lf",&d,&t),d=90-d,
			a[i]=a[i]+polar(d/180*pi)*100*t,r[i]=(m-t)*350;
		printf("Trial %d: ",++Case);
		if (n==1) if (*r<=eps) S=*a,++cnt; else cnt=2;
		else{
			for (j=1;j<n;++j)
				if (fabs(a[j].x-a[0].x)+fabs(a[j].y-a[0].y)+fabs(r[j]-r[0])>eps) break;
			if (j==n) cnt=2; else
			if (cross(a[0],r[0],a[j],r[j],A,B)){
				if (check(A)) ++cnt,S=A;
				if (A!=B && check(B)) ++cnt,S=B;
			}
		}
		if (!cnt) puts("Inconsistent");
		else if (cnt>1) puts("Inconclusive");
		else if ((T-S).len()<=eps) puts("Arrived");
		else printf("%d degrees\n",int(90-(T-S).angle()/pi*180+360.5)%360);
	}
	return 0;
}
