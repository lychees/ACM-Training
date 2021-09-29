#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=305; const double eps=1e-8;
int Case,n,m,x,y; double w[N][3],a[N][N],g[N][N];
bool solve()
{
	memcpy(g,a,sizeof(g)); int p=0;
	rep(i,n){
		while (p<m && fabs(g[i][p])<eps){
			for (int j=i+1;fabs(g[i][p])<eps && j<n;++j) if (fabs(g[j][p])>eps)
				for (int k=p;k<=m;++k) swap(g[i][k],g[j][k]);
			if (fabs(g[i][p])<eps) ++p;
		}
		if (p>=m){if (fabs(g[i][m])>eps) return 0; continue;}
		for (int k=m;k>=p;--k) g[i][k]/=g[i][p];
		rep(j,n) if (i!=j && fabs(g[j][p])>eps)
			for (int k=m;k>=p;--k) g[j][k]-=g[j][p]*g[i][k];
	}
	return 1;
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,n) rep(j,3) scanf("%lf",w[i]+j);
		memset(a,0,sizeof(a)); rep(i,n) if (w[i][2]>eps) a[i*3+2][m]=1;
		rep(i,m){
			scanf("%d%d",&x,&y),--x,--y;
			rep(j,3){
				if (w[x][2]>eps) a[x*3+j][i]+=w[y][j]-w[x][j];
				if (w[y][2]>eps) a[y*3+j][i]+=w[x][j]-w[y][j];
			}
		}
		n*=3,printf("Sculpture %d: ",++Case);
		if (!solve()) puts("NON-STATIC");
		else{rep(i,n) if (w[i/3][2]) a[i][m]=sin(i); puts(solve()?"STABLE":"UNSTABLE");}
	}
	return 0;
}
