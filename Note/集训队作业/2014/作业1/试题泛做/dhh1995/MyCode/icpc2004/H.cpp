#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const double eps=1e-9;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator *(const node &A){return x*A.x+y*A.y;}
	double operator %(const node &A){return x*A.y-y*A.x;}
	bool operator <(const node &A) const{return fabs(x-A.x)<eps?y<A.y:x<A.x;}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}a[105],b[105],c[105];
int Case,n,m,ans;
bool cross(node &A,node &B,node &C,node &D,node &O)
{
	double s1=(C-A)%(B-A),s2=(D-A)%(B-A);
	if (s1*s2>0 || ((A-C)%(D-C))*((B-C)%(D-C))>0) return 0;
	return O=(C*s2-D*s1)/(s2-s1),1;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) a[i].read(),b[i].read(); ans=0;
		rep(i,n){
			c[0]=a[i],c[1]=b[i],m=2;
			rep(j,n) if (i!=j && cross(a[i],b[i],a[j],b[j],c[m])) m++;
			sort(c,c+m); rep(i,m-1) ans+=int((c[i]-c[i+1]).len()/50+((!i)+(i+2==m))*.5+eps);
		}
		printf("Map %d\nTrees = ",++Case);
		printf("%d\n",ans);
	}
	return 0;
}
