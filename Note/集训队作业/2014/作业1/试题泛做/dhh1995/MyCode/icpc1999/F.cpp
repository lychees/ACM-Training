#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double pi=acos(-1.),eps=1e-8;
void rotate(double &x,double &y,double e)
{double tx=x*cos(e)-y*sin(e),ty=x*sin(e)+y*cos(e); x=tx,y=ty;}
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator +(const vec &A){return vec(x+A.x,y+A.y,z+A.z);}
	vec operator -(const vec &A){return vec(x-A.x,y-A.y,z-A.z);}
	vec operator *(const double A){return vec(x*A,y*A,z*A);}
	vec operator /(const double A){return vec(x/A,y/A,z/A);}
	vec operator %(const vec &A){return vec(y*A.z-z*A.y,z*A.x-x*A.z,x*A.y-y*A.x);}
	double operator *(const vec &A){return x*A.x+y*A.y+z*A.z;}
	double operator /(const vec &A){return fabs(A.x)<eps?fabs(A.y)<eps?z/A.z:y/A.y:x/A.x;}
	bool operator ==(const vec &A){return fabs(x-A.x)<eps && fabs(y-A.y)<eps && fabs(z-A.z)<eps;}
	void turn(double e,bool f){rotate(f?x:y,z,(f?-e:e)*pi/180);}
	double area(){return sqrt(x*x+y*y+z*z);}
	void Prt(){printf("(%.3lf,%.3lf,%.3lf)\n",x+eps,y+eps,z+eps);}
}a[15];
int Case,n; double L[15],e[15];
bool cross(vec &A,vec &B,vec &C,vec &D)
{
	vec AB=B-A,AC=C-A,AD=D-A,U,V=AB%(D-C);
	if (fabs(V.area())>eps && fabs((C-A)*V/V.area())>1e-3) return 0;
	U=AC%AB,V=AD%AB; bool inC=0<AC/AB && AC/AB<1,inD=0<AD/AB && AD/AB<1;
	if (U.area()<eps && V.area()<eps) return inC || inD;
	if (U.area()<eps) return inC; if (V.area()<eps) return inD;
	U=U/U.area(),V=V/V.area(); if (U==V) return 0;
	U=(A-C)%(D-C),V=(B-C)%(D-C); U=U/U.area(),V=V/V.area(); if (U==V) return 0;
	return 1;
}
int work()
{
	for (int i=n;i;--i){
		a[i]=vec(0,0,0);
		for (int j=n;j>=i;--j) a[j]=a[j]+vec(0,0,L[i]),a[j].turn(e[i],i&1);
	}
	rep(i,n){
		if (a[i].z<-eps) return -i;
		rep(j,i-2) if (cross(a[j-1],a[j],a[i-1],a[i])) return i;
	}
	return 0;
}
int main()
{
	while (scanf("%d",&n)!=EOF && n>=0){
		rep(i,n) scanf("%lf",L+i); rep(i,n) scanf("%lf",e+i);
		printf("Case %d: ",++Case); int res=work();
		if (!res) printf("robot's hand is at "),a[n].Prt();
		else if (res>0) printf("servo %d causes link collision\n",res);
		else printf("servo %d attempts to move arm below floor\n",-res);
	}
	return 0;
}
