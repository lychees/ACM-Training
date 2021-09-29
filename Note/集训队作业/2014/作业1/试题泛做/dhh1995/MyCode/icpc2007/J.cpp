#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55,M=N*N;
int Case,n,m,l,x,y,v[N],f[N],d[N],son[N],ed[M],data[M],next[M]; bool b[N];
bool build(int x)
{
	int h=0,t=1; rep(i,n) d[i]=-1; d[f[1]=x]=0;
	while (h<t){
		x=f[++h];
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p]; if (d[y]<0 && b[y]) d[y]=d[x]+1,f[++t]=y; if (!y) return 1;
		}
	}
	return 0;
}
int dinic(int x,int low)
{
	if (!x) return low; int w=0,res;
	for (int p=son[x];p && w<low;p=next[p]) if (data[p]){
		int y=ed[p];
		if (d[y]==d[x]+1 && (res=dinic(y,min(data[p],low-w))))
			data[p]-=res,data[p^1]+=res,w+=res;
		}
	if (!w) d[x]=-1; return w;
}
int maxflow(int i)
{
	rep(j,m*2) data[j+2]=1; int res=0;
	while (build(i)) res+=dinic(i,1<<20); return res;
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		++n,l=1; rep(i,n) son[i]=0,b[i]=1;
		rep(i,m) scanf("%d%d",&x,&y),
			ed[++l]=y,next[l]=son[x],son[x]=l,
			ed[++l]=x,next[l]=son[y],son[y]=l;
		rep(i,n) if (i) v[i]=maxflow(i); 
		for (;;){
			int opt=1<<20; rep(i,n) if (i && b[i] && v[i]<opt) opt=v[i];
			if (opt==1<<20) break; rep(i,n) if (i && b[i] && v[i]==opt) b[i]=0;
			rep(i,n) if (i && b[i]) v[i]=min(v[i],opt+maxflow(i));
		}
		printf("Case %d: %d\n\n",++Case,v[1]);
	}
	return 0;
}
