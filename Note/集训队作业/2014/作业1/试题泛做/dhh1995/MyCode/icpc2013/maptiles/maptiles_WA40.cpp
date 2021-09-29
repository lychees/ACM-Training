#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-9;
int n,ans,xs,ys; bool b[15][15],c[15][15];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator %(const node &A){return x*A.y-y*A.x;}
	void read(){scanf("%lf%lf",&x,&y),x/=xs,y/=ys;}
	void prt(){printf("%lf %lf\n",x*xs,y*ys);}
}A[55],a[55],o[15][15],v[15][15],p[15][15][5];
bool cross(node &A,node &B,node &C,node &D)
{
	node V1=B-A,V2=D-C; double s1=(A-C)%V2,s2=(B-C)%V2;
//	A.prt(),B.prt(),C.prt(),D.prt();
//	printf("%lf %lf\n",((C-A)%V1)*((D-A)%V1),((A-C)%V2)*((B-C)%V2));
	return (fabs(s1)<eps?s2<-eps:fabs(s2)<eps?s1<-eps:s1*s2<-eps) && ((C-A)%V1)*((D-A)%V1)<-eps;
}
void cover(node A,node B)
{
	int x1=int(A.x),x2=int(B.x),y1=int(A.y),y2=int(B.y);
	if (x1>x2) swap(x1,x2); if (y1>y2) swap(y1,y2); if (x2>9) --x2;
	for (int i=x1;i<=x2;++i) for (int j=y1;j<10;++j){
		if (j<=y2) rep(k,4){if (b[i][j]) break;
//		A.prt(),B.prt(),printf("%d %d %d\n",i,j,k);
		b[i][j]=cross(A,B,p[i][j][k],p[i][j][k+1]);}
		c[i][j]^=cross(A,B,o[i][j],v[i][j]);
	}
}
void work(double x,double y)
{
	rep(i,10) rep(j,10) b[i][j]=c[i][j]=0;
	rep(i,n) a[i]=A[i]-node(x,y);
	x=y=1e3; rep(i,n) x=min(x,a[i].x),y=min(y,a[i].y); x=floor(x),y=floor(y);
	rep(i,n) a[i]=a[i]-node(x,y);
	a[n]=a[0]; rep(i,n) cover(a[i],a[i+1]);
	int res=0; rep(i,10) rep(j,10) res+=b[i][j]||c[i][j]; ans=min(ans,res);
//	printf("cnt=%d\n",res);
//	rep(i,n+1) a[i].prt();
//	rep(i,10){rep(j,10) printf("%d ",b[i][j]); puts("");}
}
int main()
{
	freopen("maptiles.in","r",stdin);
	freopen("maptiles.out","w",stdout);
	rep(i,10) rep(j,10){
		o[i][j]=node(i+.5+eps,j+.5+eps),v[i][j]=o[i][j]-node(0,100);
		rep(k,4) p[i][j][k]=node(i+(k&1),j+(k>>1&1));
		swap(p[i][j][2],p[i][j][3]); p[i][j][4]=p[i][j][0];
	}
	while (scanf("%d%d%d",&n,&xs,&ys)!=EOF){
		rep(i,n) A[i].read(); ans=101;
		rep(i,n) rep(j,n) work(A[i].x,A[j].y);
		printf("%d\n",ans);
	}
	return 0;
}
