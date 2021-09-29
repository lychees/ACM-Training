#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105;
int Case,n,m,x,y,d[N][N],a[N][N],f[N*N*N],g[N*N*N]; bool b[N][N];
int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	while (scanf("%d%d",&n,&m),n&&m){
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<25;
		rep(i,m) scanf("%d%d",&x,&y),d[x][y]=x!=y;
		rep(k,n) rep(i,n) rep(j,n) if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
		int h=0,t=1; f[1]=1,g[1]=1; rep(i,n) rep(j,n) a[i][j]=1<<25; a[1][1]=1;
		while (h<t){
			x=f[++h],y=g[h]; b[x][y]=0; if (a[x][y]>=a[2][2]) continue;
			rep(i,n) if (x!=i) rep(j,n) if (y!=j){
				int z=d[x][i]+d[j][y]+d[i][j]-1;
				if (a[x][y]+z<a[j][i])
					{a[j][i]=a[x][y]+z; if (!b[j][i]) b[j][i]=1,f[++t]=j,g[t]=i;}
			}
		}
		printf("Network %d\n",++Case);
		if (a[2][2]<1<<20) printf("Minimum number of nodes = %d\n\n",a[2][2]);
		else puts("Impossible\n");
	}
	return 0;
}
