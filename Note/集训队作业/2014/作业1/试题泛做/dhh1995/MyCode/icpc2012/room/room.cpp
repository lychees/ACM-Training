#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const double eps=1e-8;
int Case,n; double ans,d[205][205];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	double operator *(const node &A){return x*A.x+y*A.y;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	double norm(){return x*x+y*y;}
	double len(){return sqrt(norm());}
	void read(){scanf("%lf%lf",&x,&y);}
}a[205];
bool cross(node &A,node &B,node &C,node &D)
{return ((C-A)%(B-A))*((D-A)%(B-A))<=0 && ((C-A)%(B-A))*((D-A)%(B-A))<=0;}
void rev(node A,node B,node &C){node V=B-A; C=(A+V*(((C-A)*V)/V.norm()))*2-C;}
double work(node A,int l,node B,int r)
{
	for (int i=l;i<r;++i) rev(a[i],a[i+1],A);
	for (int i=r;i>l;--i){
		if (!cross(A,B,a[i-1],a[i])) return 1e9;
		rev(a[i-1],a[i],A),rev(a[i-1],a[i],B);
	}
	return (A-B).len();
}
inline int chg(int x){return x>n?x-n:x;}
inline void Min(double &x,double y){if (y<x) x=y;}
int main()
{
	freopen("room.in","r",stdin);
	freopen("room.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		ans=1e9,a[0].read(); rep(i,n) a[i].read(),a[n+i]=a[i];
		rep(i,n) rep(j,n-1) d[i][chg(i+j)]=work(a[i],i+1,a[i+j],i+j-1);
		rep(k,n) rep(i,n) rep(j,n) Min(d[i][j],d[i][k]+d[k][j]);
		rep(i,n){
			ans=min(ans,work(*a,i,*a,i+n));
			for (int j=0;j<n;++j) d[0][chg(i+j)]=work(*a,i,a[i+j],i+j-1),
					d[chg(i+j)][0]=work(a[i+j],i+j+1,*a,i+n);
			rep(j,n) rep(k,n) Min(ans,d[0][j]+d[j][k]+d[k][0]);
		}
		printf("Case %d: %.2lf\n",++Case,ans);
	}
	return 0;
}
