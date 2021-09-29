#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double Re=6370.,pi=acos(-1.),eps=1e-8; const int N=30,M=N*N;
int n,m,x,y,s,Case,Test,S,T,C,p[M]; double R,theta,d[M][M],e[M],ans[N][N];
struct vec{
	double x,y,z; vec(){}
	vec(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	vec operator +(const vec &A) const{return vec(x+A.x,y+A.y,z+A.z);}
	vec operator -(const vec &A) const{return vec(x-A.x,y-A.y,z-A.z);}
	vec operator *(const double A) const{return vec(x*A,y*A,z*A);}
	vec operator /(const double A) const{return vec(x/A,y/A,z/A);}
	vec operator %(const vec &A) const{return vec(y*A.z-z*A.y,z*A.x-x*A.z,x*A.y-y*A.x);}
	double operator *(const vec &A) const{return x*A.x+y*A.y+z*A.z;}
	double norm() const{return x*x+y*y+z*z;}
	double len() const{return sqrt(x*x+y*y+z*z);}
	void prt() const{printf("(%lf,%lf,%lf) %lf\n",x,y,z,len());}
}a[M],c[N],X,Y,P,Q,V,O;
vec polar(double x,double y){return vec(cos(x)*cos(y),sin(x)*cos(y),sin(y))*Re;}
double cross(const vec &A,double &theta)
{
	double d=A*V; if (R<fabs(d)) return 0;
	double r=sqrt(R*R-d*d); X=A-V*d; if (Re>X.len()+r) return 0;
//	printf("d=%lf %lf %lf\n",d,r,X*V),A.prt(),X.prt();
	theta=acos((X.norm()+Re*Re-r*r)/(2*Re*X.len()));
//	printf("%lf %lf %lf  theta=%lf\n",X.len(),Re,r,theta);
	return 1;
}
void circle(const vec &A,const vec &B)
{
	V=A%B; if (V.len()<eps) return; V=V%((A+B)/2),V=V/V.len();
//	A.prt(),B.prt(),V.prt(); printf("R=%lf\n",R);
	if (cross(A,theta)) Y=X%V,X=X/X.len()*Re,Y=Y/Y.len()*Re,//X.prt(),Y.prt(),printf("%lf\n",theta),
		a[m++]=X*cos(theta)+Y*sin(theta),a[m++]=X*cos(-theta)+Y*sin(-theta);
	//a[m].prt(),a[m-1].prt();
//	puts("-------------------");
}
void add(double x,double y)
{
//	printf("%lf %lf\n",x,y);
	if (x<-pi) add(x+2*pi,pi),add(-pi,y); //e[s++]=x+2*pi,e[s++]=pi,e[s++]=-pi,e[s++]=y;
	else if (y>pi) add(x,pi),add(-pi,y-2*pi);
	else e[s++]=x-eps,e[s++]=y+eps;
}
void solve(vec A,vec B,vec C,double &x,double &y)
{
/*	if (fabs(A.x)<eps && fabs(B.x)<eps) swap(A.x,A.y),swap(B.x,B.y),swap(C.x,C.y);
	if (fabs(A.x)<eps && fabs(B.x)<eps) swap(A.x,A.z),swap(B.x,B.z),swap(C.x,C.z);
	if (fabs(A.y)<eps && fabs(B.y)<eps) swap(A.y,A.z),swap(B.y,B.z),swap(C.y,C.z);
	A.prt(),B.prt(),C.prt();
	//A.x*x+B.x*y=C.x;
	//A.y*x+B.y*y=C.y;
	//A.z*x+B.z*y=C.z;
	printf("?? %lf %lf\n",(C.x*B.y-C.y*B.x),(A.x*B.y-A.y*B.x));
	printf("?? %lf %lf\n",(C.x*A.y-C.y*A.x),(B.x*A.y-B.y*A.x));
	x=(C.x*B.y-C.y*B.x)/(A.x*B.y-A.y*B.x);
	y=(C.x*A.y-C.y*A.x)/(B.x*A.y-B.y*A.x);
	printf("!! %lf %lf\n",x,y);*/
	if (fabs(A.x*B.y-A.y*B.x)<eps) swap(A.y,A.z),swap(B.y,B.z),swap(C.y,C.z);
	x=(C.x*B.y-C.y*B.x)/(A.x*B.y-A.y*B.x);
	y=(C.x*A.y-C.y*A.x)/(B.x*A.y-B.y*A.x);
}
double angle(const vec &A)
{
	//P,Q->(1,0),(0,1) P*cos(p)+Q*sin(p)=A
	double x,y; solve(P,Q,A,x,y); return atan2(y,x);
}
bool cmp(const int i,const int j){return e[i]<e[j];}
double dist(const vec &A,const vec &B)
{
	V=A%B; if (V.len()<eps) return 1e9;
	V=V/V.len(),s=0; P=A,Q=A%V; P=P/P.len()*Re,Q=Q/Q.len()*Re;
//	P.prt(),Q.prt();
	double ang=angle(B); add(min(ang,0.),max(ang,0.));
//	P.prt(),Q.prt(),A.prt(),B.prt();
//	printf("%lf\n",ang);
	rep(i,n) if (cross(c[i],theta)) ang=angle(X),add(ang-theta,ang+theta);
	rep(i,s) p[i]=i; sort(p,p+s,cmp); int c=0,flag=0;
	rep(k,s){
		int i=p[k];
		if (i<2) flag^=1; else if (i&1) --c; else ++c;
		if (flag && !c) return 1e9;
	}
	return Re*acos(A*B/A.len()/B.len());
}
int main()
{
	freopen("shortest.in","r",stdin);
	freopen("shortest_dev.out","w",stdout);
	while (scanf("%d%lf",&n,&R)!=EOF){
		theta=R/Re,R=Re*sin(theta),m=n;
		rep(i,n) scanf("%d%d",&x,&y),a[i]=polar(x*pi/180,y*pi/180),c[i]=a[i]*cos(theta);
		rep(i,n) rep(j,i) circle(c[i],c[j]);
//		printf("%d\n",m);
//		rep(i,m) a[i].prt(); puts("");
//		puts("-----------------------------------------------");
//		printf("%lf\n",dist(a[1],a[11]));
//		puts("-----------------------------------------------");
		rep(i,m){d[i][i]=0; rep(j,i) d[i][j]=d[j][i]=dist(a[i],a[j]);}
//		rep(i,m){rep(j,m) printf("%.3lf ",d[i][j]); puts("");}
//		rep(i,m) rep(j,m) printf("%d %d %.3lf\n",i,j,d[i][j]);
		rep(k,m) rep(i,m) rep(j,m)
			if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
//		puts("-----------------------------------------------");
//		rep(i,m){rep(j,m) printf("%.3lf ",d[i][j]); puts("");}
		printf("Case %d:\n",++Case);
//		rep(i,m){rep(j,m) printf("%lf\n",d[i][j]); puts("");}
		for (scanf("%d",&Test);Test--;){
			scanf("%d%d%d",&S,&T,&C),--S,--T;
			rep(i,n) rep(j,n) ans[i][j]=d[i][j]>C?1e9:d[i][j];
			rep(k,n) rep(i,n) rep(j,n)
				if (ans[i][k]+ans[k][j]<ans[i][j]) ans[i][j]=ans[i][k]+ans[k][j];
//			rep(i,n){rep(j,n) printf("%lf ",ans[i][j]); puts("");}
			if (ans[S][T]<1e9) printf("%.3lf\n",ans[S][T]); else puts("impossible");
		}
	}
	return 0;
}
