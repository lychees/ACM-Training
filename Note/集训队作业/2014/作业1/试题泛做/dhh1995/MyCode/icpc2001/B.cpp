#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105;
int Case,n; double x[N],y[N],z[N],r[N],d[N][N];
#define sqr(x) (x)*(x)
int main()
{
	while (scanf("%d",&n),n>=0){
		rep(i,n) scanf("%lf%lf%lf%lf",x+i,y+i,z+i,r+i);
		rep(k,2) r[++n]=0,scanf("%lf%lf%lf",x+n,y+n,z+n);
		rep(i,n) rep(j,n) d[i][j]=max(0.,sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j]))-r[i]-r[j]);
		rep(k,n) rep(i,n) rep(j,n) if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
		printf("Cheese %d: Travel time = %d sec\n",++Case,int(round(d[n-1][n]*10)));
	}
	return 0;
}
