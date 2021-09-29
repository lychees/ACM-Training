#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=105,M=125,oo=-1<<25;
int Case,n,l,r,m,x,y,z,son[N],ed[N*2],data[N*2],next[N*2],h[M],f[N][M];
void trans(int *f,int *g)
{
	rep(i,0,m) h[i]=oo;
	rep(i,0,m) rep(j,0,m-i) if (f[i]+g[j]>=-m){
		int k=max(i,j),z=min(f[i],g[j]); if (z>h[k]) h[k]=z;
	}
	rep(i,0,m) f[i]=h[i];
}
void dfs(int x,int fa,int z)
{
	rep(i,1,m) f[x][i]=oo; f[x][0]=0;
	for (int p=son[x];p;p=next[p]) if (ed[p]!=fa) dfs(ed[p],x,data[p]),trans(f[x],f[ed[p]]);
	rep(i,0,m) h[i]=oo;
	rep(i,0,m){
		if (i+z<=m) h[i+z]=max(h[i+z],f[x][i]+z);
		if (z && i+z-60>=-m) h[max(0,i+z-60)]=max(h[max(0,i+z-60)],f[x][i]+z-60);
	}
	rep(i,0,m) f[x][i]=h[i];
}
bool check(){dfs(1,0,0); rep(i,0,m) if (f[1][i]>=-m) return 1; return 0;}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,1,n) son[i]=0; l=0;
		rep(i,2,n) scanf("%d%d%d",&x,&y,&z),z%=60,
			ed[++l]=y,data[l]=z,next[l]=son[x],son[x]=l,
			ed[++l]=x,data[l]=z,next[l]=son[y],son[y]=l;
		l=0,r=118;
		while (l<r) m=l+r>>1,check()?r=m:l=m+1;
		printf("Case %d: %d\n",++Case,l);
	}
	return 0;
}
