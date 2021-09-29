#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-9;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator /(const node &A){return fabs(A.x)<eps?y/A.y:x/A.x;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	void read(){scanf("%lf%lf",&x,&y);}
}a[55],b[55];
int Case,t,n,m,Q,x,y,d[55][55];
bool cross(node &A,node &B,node &C,node &D,node &E)
{
	double s1=(C-A)%(B-A),s2=(C+D-A)%(B-A);
	if (fabs(s1-s2)<eps) return 0; E=(C*s2-(C+D)*s1)/(s2-s1);
	return 1;
}
int cal(node A,node B)
{
	int cnt=-1;
	rep(i,t){
		double L=0,R=1;
		rep(j,t) if (i!=j){
			node C=(b[i]+b[j])/2.,D=node((b[j]-b[i]).y,-(b[j]-b[i]).x),E;
			bool flag=(A-C)%D>0==(b[i]-C)%D>0;
			if (cross(A,B,C,D,E)){
				double w=(E-A)/(B-A);
				if (w>-eps && w<1+eps){if (flag) R=min(R,w); else L=max(L,w); continue;}
			}
			if (!flag){R=-1; break;}
		}
		if (L<R) ++cnt;
	}
	return cnt;
}
int main()
{
	while (scanf("%d%d%d%d",&t,&n,&m,&Q),t||n||m||Q){
		rep(i,t) b[i].read(); rep(i,n) a[i].read();
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<20;
		rep(i,m) scanf("%d%d",&x,&y),d[x][y]=d[y][x]=cal(a[x],a[y]);
		rep(k,n) rep(i,n) rep(j,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		printf("Case %d:\n",++Case);
		rep(i,Q){
			scanf("%d%d",&x,&y);
			if (d[x][y]<1<<19) printf("%d\n",d[x][y]); else puts("Impossible");
		}
	}
	return 0;
}
