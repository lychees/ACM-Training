#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=20005;
int Case,n,m,l,ans,S,T,x,y,z,son[N],ed[N],next[N],data[N],d[N],f[N];
bool build()
{
	int h=0,t=1; f[1]=S; rep(i,n) d[i]=-1; d[S]=0;
	while (h<t){
		int x=f[++h];
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p]; if (d[y]<0) d[y]=d[x]+1,f[++t]=y; if (y==T) return 1;
		}
	}
	return 0;
}
int dinic(int x,int low)
{
	if (x==T) return low; int res,w=0;
	for (int p=son[x];p && w<low;p=next[p]) if (data[p]){
		int y=ed[p];
		if (d[y]==d[x]+1 && (res=dinic(y,min(data[p],low-w))))
			data[p]-=res,data[p^1]+=res,w+=res;
	}
	if (!w) d[x]=-1; return w;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) son[i]=0; l=1; ans=0;
		scanf("%d%d%d",&S,&T,&m);
		rep(i,m) scanf("%d%d%d",&x,&y,&z),
			ed[++l]=y,data[l]=z,next[l]=son[x],son[x]=l,
			ed[++l]=x,data[l]=z,next[l]=son[y],son[y]=l;
		while (build()) ans+=dinic(S,1<<20);
		printf("Network %d\nThe bandwidth is %d.\n",++Case,ans);
	}
	return 0;
}
