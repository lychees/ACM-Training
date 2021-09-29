#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,x[9],y[9],z[9]; double ans,r[9],pi=acos(-1.);
double sqr(int x){return x*x;}
double D(int i,int j)
{
	if (j<2) return min(abs(x[i]-x[j]),min(abs(y[i]-y[j]),abs(z[i]-z[j])));
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j]));
}
void dfs(int a,double s)
{
	ans=max(ans,s);
	rep(i,n) if (!(a>>i&1)){
		r[i]=1e9; rep(j,n) if (a>>j&1) r[i]=min(r[i],D(i,j)-r[j]);
		if (x[i]<x[0] || y[i]<y[0] || z[i]<z[0] || x[i]>x[1] || y[i]>y[1] || z[i]>z[1] || r[i]<0) r[i]=0;
		dfs(a|1<<i,s+r[i]*r[i]*r[i]*4/3*pi);
	}
}
int main()
{
	while (scanf("%d",&n)!=EOF){
		n+=2; rep(i,n) scanf("%d%d%d",x+i,y+i,z+i),r[i]=0;
		if (x[0]>x[1]) swap(x[0],x[1]);
		if (y[0]>y[1]) swap(y[0],y[1]);
		if (z[0]>z[1]) swap(z[0],z[1]);
		ans=0,dfs(3,0),printf("%.0lf\n",(x[1]-x[0])*(y[1]-y[0])*(z[1]-z[0])-ans);
	}
	return 0;
}
