#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=1010,u[4]={1,0,-1,0},v[4]={0,1,0,-1};
int Case,n,m,x[N],y[N],z[N],d[N][N],f[N*N*4],g[N*N*4]; bool a[N][N],b[N][N];
void dis(int *x)
{
	rep(i,n) z[i]=x[i]; sort(z,z+n),m=unique(z,z+n)-z;
	rep(i,n) x[i]=lower_bound(z,z+m,x[i])-z+1;
}
int bfs(int x,int y,int tx,int ty)
{
	n+=2; rep(i,n) rep(j,n) d[i][j]=10000; d[x][y]=0; int h=n*n*2,t=h+1; f[t]=x,g[t]=y;
	while (h<t){
		x=f[++h],y=g[h]; if (d[x][y]>=d[tx][ty]) return d[tx][ty];
		rep(k,4){
			int i=x+u[k],j=y+v[k];
			if (i>=0 && i<n && j>=0 && j<n){
				if (k&1?b[x][min(y,j)]:a[min(x,i)][y])
					{if (d[x][y]+1<d[i][j]) d[i][j]=d[x][y]+1,f[++t]=i,g[t]=j;}
				else if (d[x][y]<d[i][j]) d[i][j]=d[x][y],f[h]=i,g[h--]=j;
			}
		}
	}
}
int main()
{
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	while (scanf("%d",&n),n){
		n=n*2+2; rep(i,n) scanf("%d%d",x+i,y+i); dis(x),dis(y); printf("City %d\n",++Case);
		rep(i,n-2) if (i&1)
			if (x[i]==x[i^1]){
				if (y[i]>y[i^1]) swap(y[i],y[i^1]);
				for (int j=y[i];j<y[i^1];++j) a[x[i]][j+1]=1;
			}else{
				if (x[i]>x[i^1]) swap(x[i],x[i^1]);
				for (int j=x[i];j<x[i^1];++j) b[j+1][y[i]]=1;
			}
		printf("Peter has to cross %d streets\n",bfs(x[n-2],y[n-2],x[n-1],y[n-1]));
		rep(i,n) rep(j,n) a[i][j]=b[i][j]=0;
	}
	return 0;
}
