#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=4050;
int son[N],st[N],ed[N],next[N],data[N],cost[N],d[N],f[N*20],r[N],c[N];
int Case,n,m,S,T,L,ans,l,res,sum,A,B; bool b[N],v[N]; char s[N][N];
void add(int x,int y,int z,int c)
{
	st[++l]=x,ed[l]=y,data[l]=z,cost[l]=c,next[l]=son[x],son[x]=l;
	st[++l]=y,ed[l]=x,data[l]=0,cost[l]=-c,next[l]=son[y],son[y]=l;
}
bool spfa()
{
	int h=0,t=1; rep(i,T) d[i]=1<<25; d[f[1]=S]=0;
	while (h<t){
		int x=f[++h]; b[x]=0;
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p];
			if (d[x]+cost[p]<d[y]){
				d[y]=d[x]+cost[p];
				if (!b[y]) b[y]=1,f[++t]=y;
			}
		}
	}
	return d[T]<1<<25;
}
int dinic(int x,int low)
{
	if (x==T) return low; int w=0,res; v[x]=1;
	for (int p=son[x];p && w<low;p=next[p]) if (data[p]){
		int y=ed[p];
		if (!v[y] && d[y]==d[x]+cost[p] && (res=dinic(y,min(data[p],low-w))))
			data[p]-=res,data[p^1]+=res,w+=res;
	}
	return w;
}
int work()
{
	rep(i,T+1) son[i-1]=0; l=1; int res=n*L,sum=n*L,F;
	rep(i,n){
		add(S,i,L-r[i],0),add(n+i,T,L-c[i],0),add(i,n+i,L,1); sum-=r[i];
		rep(j,n) if (s[i][j]=='.') add(i,n+j,1,0);
	}
	v[S]=1;
	while (spfa()){rep(i,T) v[i]=0; F=dinic(S,1<<25),sum-=F,res-=F*d[T];}
	return sum?-1:res;
}
int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	while (scanf("%d%d%d",&n,&A,&B),n){
		rep(i,n) r[i]=c[i]=0; m=S=0,T=n+n+1;
		rep(i,n){scanf("%s",s[i]+1); rep(j,n) if (s[i][j]=='C') ++r[i],++c[j];}
		rep(i,n) m=max(m,max(r[i],c[i]));
		for (L=n;L>=m;--L){ans=work(); if (ans*A/B>=L) break;}
		printf("Case %d: ",++Case); rep(i,n) ans-=c[i];
		if (L<m) puts("impossible"); else printf("%d\n",ans);
	}
	return 0;
}
