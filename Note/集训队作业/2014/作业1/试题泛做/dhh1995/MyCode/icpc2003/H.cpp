#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55,inf=1<<25;
int Case,n,T,x,z,e[N],d[N],m[3],t[3][N*5],f[N*5][N][3];
inline void Min(int &x,int y){if (y<x) x=y;}
int main()
{
	while (scanf("%d",&n),n){
		scanf("%d",&T); rep(i,n) if (i) scanf("%d",e+i),d[i]=e[i]+d[i-1];
		rep(i,3) if (i){
			scanf("%d",m+i); rep(j,251) t[i][j]=0;
			rep(j,m[i]) scanf("%d",&x),t[i][x]=1;
		}
		rep(i,T+1) rep(j,n) rep(k,3) f[i][j][k]=inf; f[0][0][0]=0;
		rep(i,T+1) rep(j,n){
			Min(f[i][j][0],min(f[i][j][1],f[i][j][2])); Min(f[i+1][j][0],f[i][j][0]+1);
			if ((z=f[i][j][0])<inf){
				if (i>=d[j] && t[1][i-d[j]]) Min(f[i][j][1],z);
				if (i>=d[n-1]-d[j] && t[2][i-d[n-1]+d[j]]) Min(f[i][j][2],z);
			}
			if (j+1<n && f[i][j][1]<inf) Min(f[i+e[j+1]][j+1][1],f[i][j][1]);
			if (j && f[i][j][2]<inf) Min(f[i+e[j]][j-1][2],f[i][j][2]);
		}
		printf("Case Number %d: ",++Case);
		if (f[T][n-1][0]<inf) printf("%d\n",f[T][n-1][0]); else puts("impossible");
	}
	return 0;
}
