#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=105;
double f[N][25],ans; int Case,T,x,n,m=21,g[N][25],d[N],L[N],R[N];
int main()
{
	for (scanf("%d",&T);T--;){
		scanf("%d",&n),ans=1e9;
		rep(i,n) scanf("%d%d%d",d+i,L+i,R+i);
		rep(j,m) f[n][j]=0;
		for (int i=n-1;i>=0;--i){
			rep(j,m){
				f[i][j]=f[i+1][j]+d[i]/(400+(L[i]+(R[i]-L[i])/20.*j))*(2000+abs(j-10)*10);
				g[i][j]=j; if (j && f[i][j-1]<f[i][j]) f[i][j]=f[i][j-1],g[i][j]=g[i][j-1];
			}
			for (int j=m-1;j;--j){
				if (f[i][j]+50<f[i][j-1]) f[i][j-1]=f[i][j]+50,g[i][j-1]=g[i][j];
			}
		}
		rep(j,21) if (f[0][j]+j*50<ans) ans=f[0][j]+j*50,x=j;
		printf("Flight %d: ",++Case);
		rep(i,n) x=g[i][x],printf("%d ",x+20); printf("%.0lf\n",50*20+ans+.5-1e-8);
	}
	return 0;
}
