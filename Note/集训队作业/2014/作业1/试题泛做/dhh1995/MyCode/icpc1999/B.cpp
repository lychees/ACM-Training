#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-6;
int Case,n; double d,h,H,ans;
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator *(const double &A){return vec(x*A,y*A,z*A);}
	vec operator +(const vec &A){return vec(x+A.x,y+A.y,z+A.z);}
	vec operator -(const vec &A){return vec(x-A.x,y-A.y,z-A.z);}
	vec operator %(const vec &A){return vec(y*A.z-z*A.y,z*A.x-x*A.z,x*A.y-y*A.x);}
	double operator *(const vec &A){return x*A.x+y*A.y+z*A.z;}
	bool operator <(const vec &A){return x<A.x+eps && y<A.y+eps && z<A.z+eps;}
	double norm(){return x*x+y*y+z*z;}
	void read(){scanf("%lf%lf%lf",&x,&y,&z);}
	void prt(){printf("%lf %lf %lf\n",x,y,z);}
}A,B,E,X,Y,Z,O;
bool cross(vec &A,vec &B,vec &C,vec &D,vec &E)
{
	vec V=C%D,U=V%B%V; if (fabs(V*B)<eps) return 0; if (U.norm()<eps) U=C; V=B%U;
	double d=A*V/V.norm(),t=(V*d-A)%U*V/V.norm();
	if (t<-eps) return 0; return E=A+B*t,1;
}
void work(vec A,vec &C,vec &D)
{
	if (cross(A,B,C,D,E)) if (O<E && E<C+D && E.z<h) h=E.z;
	if (O<A && A<C+D && A.z<h) h=A.z;
}
int main()
{
	while (scanf("%d",&n),n){
		scanf("%lf",&d),ans=0,A.read(),B.read(),B=B-A;
		X=vec(d,0,0),Y=vec(0,d,0),Z=vec(0,0,d),h=d;
		work(A-Y,X,Z),work(A-X,Y,Z),work(A,X,Y),work(A,X,Z),work(A,Y,Z),H=h;
		d/=n,X=vec(d,0,0),Y=vec(0,d,0),Z=vec(0,0,d);
		rep(i,n) rep(j,n) rep(k,n){
			double x=i*d,y=j*d,z=k*d; h=d;
			work(A-vec(x,y+d,z),X,Z);
			work(A-vec(x+d,y,z),Y,Z);
			work(A-vec(x,y,z),X,Y);
			work(A-vec(x,y,z),X,Z);
			work(A-vec(x,y,z),Y,Z);
			ans+=(max(0.,d-max(H-z,h)))*d*d;
		}
		if (Case) puts("");
		printf("Trial %d, Volume = %.2lf\n",++Case,ans);
	}
	return 0;
}
