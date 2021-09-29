#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,m,d,h,a[105][105]; double ans,l;
void cal(int h1,int h2,bool flag)
{
	int x=(h1/h+1)*h,y=(h2-1)/h*h,z=(y-x)/h+1,H=h2-h1;
	if (flag) ans+=(l*(x-h1)/H+l*(y-h1)/H)*z/2;
	else ans+=(l*(h2-x)/H+l*(h2-y)/H)*z/2;
}
void work(int x,int y,int z)
{
	if (x>y) swap(x,y); if (x>z) swap(x,z); if (y>z) swap(y,z);
	double e=(y-x+0.)/(z-x)*d; l=sqrt(d*d+e*e-d*e);
	if (x<y) cal(x,y,1); if (y<z) cal(y,z,0); if (x<y && y<z && y%h==0) ans+=l;
}
void check(int x,int y,int h1,int h2){if (x==y && x%h==0 && (h1!=x || h2!=x)) ans+=d;}
int main()
{
	while (scanf("%d%d%d%d",&n,&m,&d,&h),n){
		memset(a,-1,sizeof(a)),ans=0;
		rep(i,n) rep(j,m+!(i&1)) scanf("%d",a[i]+j);
		rep(i,n) rep(j,m+!(i&1)){
			int t=i&1;
			if (i>1 && j<m+!t) work(a[i][j],a[i][j+1],a[i-1][j+t]);
			if (i<n && j<m+!t) work(a[i][j],a[i][j+1],a[i+1][j+t]);
			check(a[i][j],a[i][j+1],a[i-1][j+t],a[i+1][j+t]);
			if (t)
				check(a[i][j],a[i+1][j],a[i][j-1],a[i+1][j+1]),
				check(a[i][j],a[i+1][j+1],a[i][j+1],a[i+1][j]),
				check(a[i][j],a[i-1][j],a[i][j-1],a[i-1][j+1]),
				check(a[i][j],a[i-1][j+1],a[i][j+1],a[i-1][j]);
			}
		printf("Case %d: %.0lf\n",++Case,ans);
	}
	return 0;
}
