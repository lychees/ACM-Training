#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105,M=N*N*N,u[5]={0,1,0,-1,0},v[5]={0,0,1,0,-1};
int Case,n,m,x1,y1,x2,y2,a[N][N],b[N][N],d[N][N][5][2],f[M],g[M],p[M],z[M];
int cost(int x1,int y1,int x2,int y2)
{
	if (x1==x2) return a[x1][min(y1,y2)];
	return b[min(x1,x2)][y1];
}
int main()
{
	while (scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2),n){
		rep(i,n){
			rep(j,m-1) scanf("%d",a[i]+j);
			if (i<n) rep(j,m) scanf("%d",b[i]+j);
		}
		memset(d,6,sizeof(d)); int h=0,t=0;
		rep(i,4) d[x1][y1][i][1]=0,f[++t]=x1,g[t]=y1,p[t]=i,z[t]=1;
		while (h<t){
			int x=f[++h],y=g[h],dir=p[h],turn=z[h],x1=x+u[dir],y1=y+v[dir];
			int C=cost(x,y,x1,y1),D=d[x][y][dir][turn];
			if (x1 && x1<=n && y1 && y1<=m && C) rep(k,4)
				if (k==dir){
					if (C*(1+turn)+D<d[x1][y1][k][0])
						d[x1][y1][k][0]=C*(1+turn)+D,f[++t]=x1,g[t]=y1,p[t]=k,z[t]=0;
				}else{
					if (C*2+D<d[x1][y1][k][1])
						d[x1][y1][k][1]=C*2+D,f[++t]=x1,g[t]=y1,p[t]=k,z[t]=1;
				}
		}
		int ans=1<<26; rep(i,4) ans=min(ans,d[x2][y2][i][1]);
		printf("Case %d: ",++Case);
		if (ans<1<<26) printf("%d\n",ans); else puts("Impossible");
	}
	return 0;
}
