#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int n,Case;
struct node{
	double x,y; node(){}
	node(double _x,double _y):x(_x),y(_y){}
	node operator -(const node &A){return node(x-A.x,y-A.y);}
	double operator ^(const node &A){return x*A.y-y*A.x;}
	double len(){return sqrt(x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
}a[105];
int main()
{
	freopen("K.in","r",stdin);
	freopen("K.out","w",stdout);
	while (scanf("%d",&n),n){
		rep(i,n) a[i].read(); double ans=1e9;
		rep(i,n){
			int k=-1; double res=0;
			rep(j,n) if (i!=j && (k<0 || ((a[k]-a[i])^(a[j]-a[i]))<0)) k=j;
			rep(j,n) if (i!=j && k>=0 && ((a[k]-a[i])^(a[j]-a[i]))<0) k=-1;
			if (k<0) continue;
			rep(j,n) res=max(res,((a[k]-a[i])^(a[j]-a[i]))/(a[k]-a[i]).len());
			ans=min(ans,res);
			}
		printf("Case %d: %.2lf\n",++Case,ans+.005);
		}
	return 0;
}
