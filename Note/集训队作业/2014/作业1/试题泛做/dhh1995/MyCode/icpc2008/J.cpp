#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
#define double long double
const int N=205;
int Case,n,m,tmp,x[N],y[N],p[N]; double last,ans,z[N],c[N*N],d[N*N];
bool cross(int x1,int y1,double z1,int x2,int y2,double z2,double &x)
{
	double v1=y1/z1,v2=y2/z2;
//	(1-(x-x1)/z1)*y1=(1-(x-x2)/z2)*y2
//	y1-(x-x1)*y1/z1 = y2-(x-x2)*y2/z2
//	x*(y2/z2-y1/z1) = x2*y2/z2 - x1*y1/z1 + y2 -y1
	x=(x2*v2-x1*v1+y2-y1)/(v2-v1); double y=(1-(x-x1)/z1)*y1;
	return y>=0 && y<=y1 && y<=y2;
}
double get(double x0,int x,int y,double z)
{
	double v=(x0-x)/z;
	if (v<0 || v>1) return 0;
	return (1-v)*y;
}
bool cmp(const int i,const int j){return c[i]<c[j];}
double len(double x,double y){return sqrt(x*x+y*y);}
int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	while (scanf("%d",&n),n){
		ans=0,m=0;
		rep(i,n) scanf("%d%d%d",x+i,y+i,&tmp),z[i]=tmp/2.,c[m++]=x[i]-z[i],c[m++]=x[i]+z[i];
		rep(i,m) p[i]=i; sort(p,p+m,cmp); int s=0;
		rep(i,m){
			if (i && !s) ans-=c[p[i]]-c[p[i-1]];
			if (p[i]&1) ++s; else --s;
			}
		rep(i,n){
			c[m++]=x[i];
			rep(j,i) rep(k,2) rep(l,2)
				if (cross(x[i],y[i],z[i]*(k-!k),x[j],y[j],z[j]*(l-!l),c[m])) ++m;
		}
		sort(c,c+m),m=unique(c,c+m)-c;
		rep(i,m){
			d[i]=0; rep(j,n) rep(k,2) d[i]=max(d[i],get(c[i],x[j],y[j],z[j]*(k-!k)));
			if (i) ans+=len(c[i]-c[i-1],d[i]-d[i-1]);
			}
		printf("Case %d: %d\n\n",++Case,((int)((ans+0.5)*10))/10);
	}
	return 0;
}
