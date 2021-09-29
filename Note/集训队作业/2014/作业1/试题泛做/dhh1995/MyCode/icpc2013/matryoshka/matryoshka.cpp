#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=505,inf=1<<28;
int n,z,a[N],c[N][N],d[N][N],f[N][N],g[N]; bool b[N][N],v[N];
int get(int i,int k,int j)
{
	int x=d[i][k],y=d[k+1][j];
	if (x<y) return c[k][y]-c[i-1][y];
	return c[j][x]-c[k][x];
}
int main()
{
	freopen("matryoshka.in","r",stdin);
	freopen("matryoshka.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		rep(i,1,n) rep(j,1,n) c[i][j]=0,f[i][j]=inf; g[0]=0;
		rep(i,1,n) scanf("%d",a+i),g[i]=inf,++c[i][a[i]],f[i][i]=0;
		rep(i,1,n){
			rep(j,1,n) v[j]=0,c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
			v[a[i]]=1,d[i][i]=a[i],b[i][i]=a[i]<=n;
			rep(j,i+1,n)
				b[i][j]=b[i][j-1]&&!v[a[j]]&&a[j]<=n,v[a[j]]=1,d[i][j]=min(d[i][j-1],a[j]);
			}
		rep(l,1,n-1) rep(i,1,n-l) if (b[i][i+l]){
			int j=i+l;
			rep(k,i,j) if (f[i][k]<inf && f[k+1][j]<inf)
				if ((z=f[i][k]+f[k+1][j]+j-i+1-get(i,k,j))<f[i][j]) f[i][j]=z;
			}
		rep(i,1,n){
			int m=0;
			rep(j,i,n) if (j-i+1==(m=max(m,a[j]))) if (b[i][j])
				if (g[i-1]+f[i][j]<g[j]) g[j]=g[i-1]+f[i][j];
			}
		if (g[n]<inf) printf("%d\n",g[n]); else puts("Impossible");
	}
	return 0;
}
