#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=105,M=6005,oo=-1<<25;
int Case,n,l,r,m,x,y,z,son[N],ed[N],data[N],next[N],g[M],h[M],u[M],v[M],f[N][M];
void trans(int *f,int *fy,int z)
{
	rep(i,0,m) h[i]=oo,g[i]=oo; rep(i,0,m-z) g[i+z]=fy[i]+z;
	u[0]=f[0],v[0]=g[0]; rep(i,1,m) u[i]=max(u[i-1],f[i]),v[i]=max(v[i-1],g[i]);
	rep(i,0,m){
		int j=min(i,m-i);
		if (u[i]+v[j]>=-m) h[i]=max(h[i],min(u[i],v[j]));
		if (u[j]+v[i]>=-m) h[i]=max(h[i],min(u[j],v[i]));
	}
	if (z){
		z-=60; rep(i,0,m) g[i]=oo; rep(i,0,m) if (i+z>=-m) g[max(0,i+z)]=fy[i]+z;
		v[0]=g[0]; rep(i,1,m) v[i]=max(v[i-1],g[i]);
		rep(i,0,m){
			int j=min(i,m-i);
			if (u[i]+v[j]>=-m) h[i]=max(h[i],min(u[i],v[j]));
			if (u[j]+v[i]>=-m) h[i]=max(h[i],min(u[j],v[i]));
		}
	}
	rep(i,-m,m) f[i]=h[i];
}
void dfs(int x,int fa)
{
	rep(i,1,m) f[x][i]=oo; f[x][0]=0;
	for (int p=son[x];p;p=next[p]) if (ed[p]!=fa) dfs(ed[p],x),trans(f[x],f[ed[p]],data[p]);
}
bool check(){dfs(1,0); rep(i,0,m) if (f[1][i]>=-m) return 1; return 0;}
int main()
{
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
