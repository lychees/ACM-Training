#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=25;
int Case,n,m,x[N],y[N]; double eps=1e-8,z,t,d[N][N],f[N];
double D(int i,int j){return sqrt(0.+(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) scanf("%d%d",x+i,y+i),f[i]=i+1<n?1e9:0; rep(i,n) rep(j,n) d[i][j]=D(i,j);
		for (;;){
			int i=-1; double z=3e6; rep(j,n) if (f[j]>=0 && f[j]<z) i=j,z=f[j];
			if (i<=0 || z>2e6) break; f[i]=-1;
			rep(j,n) if (f[j]>=0){
				if (z+d[i][j]*2<m+eps) f[j]=min(f[j],z+d[i][j]);
				if (d[i][j]*3<m)
					t=max(1.,ceil((z-d[i][j])/(m-d[i][j]*3)))*2-1,
					f[j]=min(f[j],z+t*d[i][j]);
			}
		}
		if (f[0]<1+eps) printf("1 unit of food\n");
		else if (f[0]<1e6+eps) printf("%.0lf units of food\n",ceil(f[0]-eps));
			else puts("Impossible");
	}
	return 0;
}
