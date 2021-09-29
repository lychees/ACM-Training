#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define double long double
const int N=205;
int Case,n,m,x,y,tmp,p[N]; double last,z,ans,c[N*N],d[N*N];
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator +(const node &A){return node(x+A.x,y+A.y);}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	node operator *(const double &A){return node(x*A,y*A);}
	node operator /(const double &A){return node(x/A,y/A);}
	double operator ^(const node &A){return x*A.y-y*A.x;}
	double len(){return sqrt(x*x+y*y);}
};
struct seg{
	node A,B; seg(){}
	seg(node _A,node _B):A(_A),B(_B){}
}a[N];
node cross(seg A,seg B)
{
	double s1=(B.A-A.A)^(A.B-A.A),s2=(B.B-A.A)^(A.B-A.A);
	node O=(B.B*s1-B.A*s2)/(s1-s2);
	if (O.y<0 || A.A.y>0 && O.y>A.A.y+1e-5 || B.A.y>0 && O.y>B.A.y+1e-5) return node(last,0);
	return O;
}
bool cmp(const int i,const int j){return c[i]<c[j];}
int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	while (scanf("%d",&n),n){
		ans=0,m=0;
		rep(i,n) scanf("%d%d%d",&x,&y,&tmp),z=tmp/2.,c[m++]=x-z,c[m++]=x+z,last=x+z,
			a[i*2]=seg(node(x,y),node(x-z,0)),a[i*2+1]=seg(node(x,y),node(x+z,0));
		rep(i,m) p[i]=i; sort(p,p+m,cmp); int s=0;
		rep(i,m){
			if (i && !s) ans-=c[p[i]]-c[p[i-1]];
			if (p[i]&1) ++s; else --s;
			}
		rep(i,n*2) rep(j,i) c[m++]=cross(a[i],a[j]).x; sort(c,c+m),m=unique(c,c+m)-c;
		rep(i,m){
			d[i]=0; rep(j,n*2) d[i]=max(d[i],cross(seg(node(c[i],-1),node(c[i],1)),a[j]).y);
			if (i) ans+=node(c[i]-c[i-1],d[i]-d[i-1]).len();
			}
		printf("Case %d: %d\n\n",++Case,((int)((ans+0.5)*10))/10);
	}
	return 0;
}
