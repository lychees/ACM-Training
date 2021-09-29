#include<cstdio>
#include<set>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
//#define double long double
const double eps=1e-9,one=1.;
int n,ans,xs,ys; bool b[15][15],c[15][15],need;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A)const{return node(x+A.x,y+A.y);}
	node operator -(const node &A)const{return node(x-A.x,y-A.y);}
	node operator *(const double &A)const{return node(x*A,y*A);}
	node operator /(const double &A)const{return node(x/A,y/A);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	bool operator <(const node &A) const{return fabs(x-A.x)<eps?y<A.y:x<A.x;}
	double len(){return sqrt(x*x+y*y);}
//	void read(){scanf("%lf%lf",&x,&y),x/=xs,y/=ys;}
	void read(){int X,Y; scanf("%d%d",&X,&Y),x=1.*X/xs,y=1.*Y/ys;}
	void prt() const{printf("%lf %lf\n",x*xs,y*ys);}
}A[55],a[55],o[15][15],v[15][15],p[15][15][5],O;
set<node> H;
void in(const node &A)
{
//	printf("~"),A.prt();
	int x=int(A.x),y=int(A.y);
//	printf("%d %d %d\n",x,y,n);
	if (fabs(x-A.x)>eps && fabs(y-A.y)>eps) b[x][y]=1;
//	printf("!%d\n",b[2][0]);
//	printf("x=%d y=%d  %d  b[x][y]=%d\n",x,y,fabs(x-A.x)>eps && fabs(y-A.y)>eps,b[x][y]);
}
bool cross(const node &A,const node &B,const node &C,const node &D,node &O)
{
//	printf("1 %d\n",n);
	node V1=B-A,V2=D-C; double L=max(one,V1.len())*2,s1=(C-A)%V1,s2=(D-A)%V1,s3=(A-C)%V2,s4=(B-C)%V2;
	if (!need) if (fabs(s3)<eps) in(A+V1/L); else if (fabs(s4)<eps) in(B-V1/L);
	else if (fabs(s1)<eps && s3*s4<-eps) in(C+(C-A)/2/max(one,(C-A).len()));
//	printf("2 %d\n",n);
//	printf("^%d\n",b[2][0]);
	if (s1*s2>-eps || s3*s4>-eps) return 0; if (need) O=(C*s2-D*s1)/(s2-s1); return 1;
}
void cover(node A,node B)
{
	int x1=int(A.x),x2=int(B.x),y1=int(A.y),y2=int(B.y);
	if (x1>x2) swap(x1,x2); if (y1>y2) swap(y1,y2); if (x2>10) --x2;
//	puts("________");A.prt(),B.prt();
	for (int i=x1;i<=x2;++i) for (int j=y1;j<11;++j){
		if (j<=y2) rep(k,4){
			if (b[i][j]) break;
			int tmp=cross(A,B,p[i][j][k],p[i][j][k+1],O); b[i][j]|=tmp;
		}
		c[i][j]^=cross(A,B,o[i][j],v[i][j],O);
	}
}
void work(double x,double y)
{
//	puts("?");
	need=0; x-=int(x),y-=int(y);
	node V(x,y); if (H.find(V)!=H.end()) return; H.insert(V);
	rep(i,11) rep(j,11) b[i][j]=c[i][j]=0;
	rep(i,n) a[i]=A[i]-V;
	x=y=1e3; rep(i,n) x=min(x,a[i].x),y=min(y,a[i].y); x=floor(x),y=floor(y);
	rep(i,n) a[i]=a[i]-node(x,y),in(a[i]);
	a[n]=a[0]; rep(i,n) cover(a[i],a[i+1]);
	int res=0; rep(i,11) rep(j,11) res+=b[i][j]||c[i][j]; ans=min(ans,res);
	if (res<=-1){
		printf("cnt=%d\n",res);
		rep(i,n+1) a[i].prt();
		for (int j=9;j>=0;--j){rep(i,10) printf("%d ",b[i][j]||c[i][j]); puts("");}
	}
}
int main()
{
	freopen("maptiles.in","r",stdin);
	freopen("maptiles.out","w",stdout);
	rep(i,11) rep(j,11){
		o[i][j]=node(i+.5+eps,j+.5+eps),v[i][j]=o[i][j]-node(0,100);
		rep(k,4) p[i][j][k]=node(i+(k&1),j+(k>>1&1));
		swap(p[i][j][2],p[i][j][3]); p[i][j][4]=p[i][j][0];
	}
	while (scanf("%d%d%d",&n,&xs,&ys)!=EOF){
		rep(i,n) A[i].read(); A[n]=*A; ans=101; H.clear();
		rep(i,n) rep(j,n){
			work(A[i].x,A[j].y);
			rep(x,10){
				if (need=1,cross(node(A[i].x+x,-1e3),node(A[i].x+x,1e3),A[j],A[j+1],O)) work(O.x,O.y);
				if (need=1,cross(node(A[i].x-x,-1e3),node(A[i].x-x,1e3),A[j],A[j+1],O)) work(O.x,O.y);
			}
			rep(y,10){
				if (need=1,cross(node(-1e3,A[i].y+y),node(1e3,A[i].y+y),A[j],A[j+1],O)) work(O.x,O.y);
				if (need=1,cross(node(-1e3,A[i].y-y),node(1e3,A[i].y-y),A[j],A[j+1],O)) work(O.x,O.y);
			}
			rep(x,10) rep(y,10){
				if (need=1,cross(A[i]-node(x,y),A[i+1]-node(x,y),A[j],A[j+1],O)) work(O.x,O.y);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
