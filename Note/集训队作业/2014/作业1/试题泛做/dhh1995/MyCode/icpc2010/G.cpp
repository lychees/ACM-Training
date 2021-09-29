#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=205;
int Case,n,b1,b2,A,B,u,v,a[N],b[N],x[N],y[N],g[N][N]; double ans,d[N][N],f[N][N];
int main()
{
	while (scanf("%d%d%d",&n,&b1,&b2),n){
		rep(i,n) scanf("%d%d",x+i,y+i); ans=1e9;
		rep(i,n) rep(j,i) d[i][j]=d[j][i]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+0.);
		rep(i,n) rep(j,n) f[i][j]=1e9; if (b1!=1) f[0][1]=d[0][1]; if (b2!=1) f[1][0]=d[1][0];
		rep(i,n) if (i>1) rep(j,i){
			if (i!=b2){
				if (f[i-1][j]+d[i][i-1]<f[i][j]) f[i][j]=f[i-1][j]+d[i][i-1],g[i][j]=i-1;
				if (f[j][i-1]+d[i][j]<f[i][i-1]) f[i][i-1]=f[j][i-1]+d[i][j],g[i][i-1]=j;
			}
			if (i!=b1){
				if (f[j][i-1]+d[i][i-1]<f[j][i]) f[j][i]=f[j][i-1]+d[i][i-1],g[j][i]=i-1;
				if (f[i-1][j]+d[i][j]<f[i-1][i]) f[i-1][i]=f[i-1][j]+d[i][j],g[i-1][i]=j;
			}
		}
		rep(j,n){
			if (f[n-1][j]+d[j][n-1]<ans) ans=f[n-1][j]+d[j][n-1],u=n-1,v=j;
			if (f[j][n-1]+d[j][n-1]<ans) ans=f[j][n-1]+d[j][n-1],u=j,v=n-1;
		}
		A=B=0;
		for (int i=n-1;i;--i)
			if (u==i) a[A++]=i,u=g[u][v]; else b[B++]=i,v=g[u][v];
		a[A++]=b[B++]=0; reverse(a,a+A);
		rep(i,B) a[A++]=b[i]; if (a[1]!=1) reverse(a,a+A);
		printf("Case %d: %.2lf\n",++Case,ans);
		rep(i,A) printf("%d%s",a[i],i+1<A?" ":"\n");
	}
	return 0;
}
