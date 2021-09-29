#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=105,M=6005,oo=-1<<25;
int Case,n,l,r,m,x,y,z,son[N],ed[N],data[N],next[N],A[N][M+M+5],*f[N],*g,*h,*u;
void trans(int *f,int *fy,int z)
{
	printf("%d\n",m);
	u[-m]=f[-m]; rep(i,1-m,m) u[i]=max(u[i-1],f[i]);
	rep(i,-m,m) h[i]=oo,g[i]=oo; rep(i,-m,m-z) g[i+z]=fy[i]+z;
	rep(i,1-m,m) g[i]=max(g[i-1],g[i]);
	rep(i,-m,m){
		int j=min(i,m-i);
		if (u[i]+g[j]>=-m) h[i]=max(h[i],min(u[i],g[j]));
		if (i!=j && u[j]+g[i]>=-m) h[i]=max(h[i],min(u[j],g[i]));
	}
	if (z){
		z-=60; rep(i,-m,m) g[i]=oo; rep(i,-m-z,m) g[i+z]=fy[i]+z;
		rep(i,1-m,m) g[i]=max(g[i-1],g[i]);
		rep(i,-m,m){
			int j=min(i,m-i);
			if (u[i]+g[j]>=-m) h[i]=max(h[i],min(u[i],g[j]));
			if (i!=j && u[j]+g[i]>=-m) h[i]=max(h[i],min(u[j],g[i]));
		}
	}
	rep(i,-m,m) f[i]=h[i];
}
void dfs(int x,int fa)
{
	rep(i,1,m) f[x][i]=oo; f[x][0]=0;
	for (int p=son[x];p;p=next[p]) if (ed[p]!=fa) dfs(ed[p],x),trans(f[x],f[ed[p]],data[p]);
}
bool check(){dfs(1,0); rep(i,-m,m) if (f[1][i]>=-m) return 1; return 0;}
int main()
{
	g=A[0]+M,h=A[1]+M,u=A[2]+M; rep(i,0,100) f[i]=A[i+3]+M;
	while (scanf("%d",&n),n){
		rep(i,1,n) son[i]=0; l=0;
		rep(i,2,n) scanf("%d%d%d",&x,&y,&z),z%=60,
			ed[++l]=y,data[l]=z,next[l]=son[x],son[x]=l,
			ed[++l]=x,data[l]=z,next[l]=son[y],son[y]=l;
		l=0,r=59*n;
		while (l<r) m=l+r>>1,check()?r=m:l=m+1;
		printf("Case %d: %d\n",++Case,l);
	}
	return 0;
}
