#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105,M=N*N;
int Case,S,T,n,m,l,c[N],f[M*10],pre[N],son[N],st[M],ed[M],next[M],data[M];
double a[N][N],cost[M],d[N],ans; bool b[N];
void add(int x,int y,int z,double c)
{
	st[++l]=x,ed[l]=y,data[l]=z,cost[l]=c,next[l]=son[x],son[x]=l;
	st[++l]=y,ed[l]=x,data[l]=0,cost[l]=-c,next[l]=son[y],son[y]=l;
}
bool spfa()
{
	int h=0,t=1; f[1]=S; rep(i,T) d[i]=1e9; d[S]=0;
	while (h<t){
		int x=f[++h]; b[x]=0;
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p];
			if (d[x]+cost[p]+1e-9<d[y]){
				d[y]=d[x]+cost[p],pre[y]=p;
				if (!b[y]) b[y]=1,f[++t]=y;
			}
		}
	}
	if (d[T]>1e8) return 0; int F=1<<20;
	for (int p=T;p!=S;p=st[p]) p=pre[p],F=min(F,data[p]);
	for (int p=T;p!=S;p=st[p]) p=pre[p],data[p]-=F,data[p^1]+=F;
	return ans+=d[T]*F,1;
}
double work(int flag)
{
	rep(i,T+1) son[i-1]=0; l=1;
	rep(i,n+m) if (i<=n) add(S,i,c[i],0); else add(i,T,c[i],0);
	rep(i,n) rep(j,m) if (a[i][j]>-.5) add(i,n+j,1<<20,a[i][j]*flag);
	ans=0; while (spfa()); return ans*flag;
}
int main()
{
	while (scanf("%d%d",&n,&m),n&&m){
		S=0,T=n+m+1; rep(i,n+m) scanf("%d",c+i);
		rep(i,n) rep(j,m) scanf("%lf",a[i]+j);
		printf("Problem %d: %.2lf to %.2lf\n",++Case,work(1),work(-1));
	}
	return 0;
}
