#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=60005;
int son[N],st[N],ed[N],next[N],data[N],cost[N],d[N],f[N*20],pre[N];
int Case,n,m,S,T,l,x,y,z,ans,a[15][55],s[15],u[55],w[55],v[15][55]; bool b[N];
void add(int x,int y,int z,int c)
{
	st[++l]=x,ed[l]=y,cost[l]=c,data[l]=z,next[l]=son[x],son[x]=l;
	st[++l]=y,ed[l]=x,cost[l]=-c,data[l]=0,next[l]=son[y],son[y]=l;
}
bool spfa()
{
	int h=0,t=1; rep(i,T) d[i]=1<<20; d[f[1]=S]=0;
	while (h<t){
		int x=f[++h]; b[x]=0;
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p];
			if (d[x]+cost[p]<d[y]){
				d[y]=d[x]+cost[p],pre[y]=p;
				if (!b[y]) b[y]=1,f[++t]=y;
			}
		}
	}
	if (d[T]==1<<20) return 0;
	for (int p=T;p!=S;p=st[p]) p=pre[p],--data[p],++data[p^1];
	return ans+=d[T],1;
}
int main()
{
	while (scanf("%d%d",&m,&n)!=EOF){
		rep(i,m) scanf("%d",s+i); S=0,T=n+n*m+1,l=1; rep(i,T+1) son[i-1]=0;
		rep(j,n){
			rep(i,m) a[i][j]=-1; scanf("%d",&z);
			while (z--){scanf("%d%d",&x,&y); rep(i,m) if (s[i]>=x) a[i][j]=y;}
		}
		rep(i,m) rep(j,n) if (a[i][j]>=0) for (int k=n;k;--k) add(i*n-n+k,j+n*m,1,a[i][j]*k);
		rep(i,m) for (int k=n;k;--k) add(S,i*n-n+k,1,0); rep(j,n) add(j+n*m,T,1,0);
		ans=0,l=1; while (spfa()); printf("%.2lf\n",ans*1./n);
		rep(i,m) rep(j,n+1) v[i][j]=0;
		rep(i,m) rep(j,n) if (a[i][j]>=0) for (int k=n;k;--k)
			if (data[l+=2]) v[i][k]=a[i][j],u[j]=i,w[j]=k;
		rep(i,m) for (int k=n;k;--k) v[i][k]+=v[i][k+1];
		rep(j,n) printf("%d %d %d\n",u[j],v[u[j]][w[j]+1],v[u[j]][w[j]]);
	}
	return 0;
}
