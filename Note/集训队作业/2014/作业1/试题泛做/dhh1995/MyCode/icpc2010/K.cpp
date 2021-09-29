#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
double eps=1e-8,mi,ma,dis,v1,v2,d; int Case,c[6];
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator +(const vec &A){return vec(x+A.x,y+A.y,z+A.z);}
	vec operator -(const vec &A){return vec(x-A.x,y-A.y,z-A.z);}
	vec operator *(const double A){return vec(x*A,y*A,z*A);}
	vec operator /(const double A){return vec(x/A,y/A,z/A);}
	vec operator ^(const vec &A){return vec(y*A.z-z*A.y,z*A.x-x*A.z,x*A.y-y*A.x);}
	double operator *(const vec &A){return x*A.x+y*A.y+z*A.z;}
	double area(){return sqrt(x*x+y*y+z*z);}
	bool read(){return scanf("%lf%lf%lf",&x,&y,&z)!=EOF;}
	void prt(){printf("%lf %lf %lf\n",x,y,z);}
}a[6],F,G,V;
int side(vec V,vec A)
{double vol=V*A; d=min(d,fabs(vol/V.area())); if (fabs(vol)<eps) return 2; return vol>0;}
bool check(vec &A,vec &B,vec &C,vec &D)
{
	rep(i,3) c[i]=0; d=1e9;
	++c[side((B-A)^V,G-A)],++c[side((C-B)^V,G-B)],++c[side((D-C)^V,G-C)],++c[side((A-D)^V,G-D)];
	return d>0.2-eps && (c[0]==4 || c[1]==4);
}
void work(vec &A,vec &B,vec &C,int x,int y,int z)
{
	V=(B-A)^(C-A),dis=fabs(V*(F-A)/V.area()); rep(i,3) c[i]=-1;
	rep(i,5) if (i!=x && i!=y && i!=z) c[side(V,a[i]-A)]=i;
	if (c[0]>=0 && c[1]>=0) return; x=c[2]; rep(i,3) c[i]=0;
	d=1e9,++c[side((B-A)^V,G-A)],++c[side((C-B)^V,G-B)],++c[side((A-C)^V,G-C)];
	bool flag=d>0.2-eps && (c[0]==3 || c[1]==3);
	if (flag || x>=0 && (check(A,B,C,a[x]) || check(A,B,a[x],C) || check(A,a[x],B,C) ) )
		mi=min(mi,dis),ma=max(ma,dis);
}
int main()
{
	freopen("K.in","r",stdin);
	freopen("K.out","w",stdout);
	for (;;){
		rep(i,5) if (!a[i].read()) return 0; F.read(); mi=1e9,ma=0;
		vec V=(a[2]-a[0])^(a[1]-a[0]); v1=fabs(V*(a[3]-a[0])),v2=fabs(V*(a[4]-a[0]));
		G=(a[0]+a[1]+a[2]+(a[3]*v1+a[4]*v2)/(v1+v2))/4.;
		rep(i,5) rep(j,i) rep(k,j) work(a[i],a[j],a[k],i,j,k);
		printf("Case %d: %.5lf %.5lf\n",++Case,mi,ma);
	}
}
