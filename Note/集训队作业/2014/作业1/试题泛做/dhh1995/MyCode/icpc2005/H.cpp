#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=35;
int Case,n,ans,res,l,S,T;
int x[N],y[N],c[N],d[N],pre[N],f[N*N],son[N],st[N*N],ed[N*N],next[N*N],data[N*N],cost[N*N];
void add(int x,int y,int z)
{
	st[++l]=x,ed[l]=y,data[l]=1,cost[l]=z,next[l]=son[x],son[x]=l;
	st[++l]=y,ed[l]=x,data[l]=0,cost[l]=-z,next[l]=son[y],son[y]=l;
}
bool spfa()
{
	int h=0,t=1; f[1]=S; rep(i,T) d[i]=1<<20; d[S]=0;
	while (h<t){
		int x=f[++h];
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p];
			if (d[x]+cost[p]<d[y])
				d[y]=d[x]+cost[p],pre[y]=p,f[++t]=y;
		}
	}
	if (d[T]==1<<20) return 0;
	for (int p=T;p!=S;p=st[p]) p=pre[p],--data[p],++data[p^1];
	return res+=d[T],1;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%d%d",x+i,y+i); ans=1<<20,S=0,T=n+n+1;
		rep(i,n){
			res=0; rep(j,n) c[j]=-1;
			rep(j,n) res+=abs(i-x[j]),++c[y[j]];
			rep(j,n) res+=abs(c[j]),c[j+1]+=c[j];
			ans=min(ans,res);
			res=0; rep(j,n) c[j]=-1;
			rep(j,n) res+=abs(i-y[j]),++c[x[j]];
			rep(j,n) res+=abs(c[j]),c[j+1]+=c[j];
			ans=min(ans,res);
		}
		rep(i,T+1) son[i-1]=0; l=1; res=0;
		rep(i,n) add(S,i,0),add(i+n,T,0);
		rep(i,n) rep(j,n) add(i,n+j,abs(i-x[j])+abs(i-y[j]));
		while (spfa()); ans=min(ans,res);
		rep(i,T+1) son[i-1]=0; l=1; res=0;
		rep(i,n) add(S,i,0),add(i+n,T,0);
		rep(i,n) rep(j,n) add(i,n+j,abs(i-x[j])+abs(n+1-i-y[j]));
		while (spfa()); ans=min(ans,res);
		printf("Board %d: %d moves required.\n\n",++Case,ans);
	}
	return 0;
}
