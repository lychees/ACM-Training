#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int p[9]={0,1,2,5,4,3,6,7,8};
int Case,F=1,n,m,x,y; double X,Y,z,ans;
int chg(double &x){return x*=m-1,int(x+.5-1e-8);}
int dfs(int x,int y,int m)
{
	m/=3; if (!m) return 0; int c=p[y/m*3+x/m]; x%=m,y%=m;
	if (c==3 || c==4 || c==5) x=m-1-x;
	if (c==1 || c==4 || c==7) y=m-1-y;
	return c*m*m+dfs(x,y,m);
}
double work()
{
	scanf("%lf%lf",&X,&Y),x=chg(X),y=chg(Y);
	ans+=sqrt((X-x)*(X-x)+(Y-y)*(Y-y))*z;
	return dfs(x,y,m)*z;
}
int main()
{
	while (ans=0,scanf("%d",&n),n){
		m=1; rep(i,n) m*=3; z=1./(m-1);
		if (F) F=0; else puts("");
		printf("Case %d.  Distance is %.4lf\n",++Case,ans+fabs(work()-work()));
	}
	return 0;
}
