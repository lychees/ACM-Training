#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=205;
int Case=0,n,m,l,x,y,a[N],b[N],q[N],f[N],g[N],ed[N],next[N],son[N];
bool cmp(const int i,const int j){return g[i]-f[i]<g[j]-f[j];}
void dfs(int x,int fa)
{
	for (int p=son[x];p;p=next[p]) if (ed[p]!=fa) dfs(ed[p],x);
	m=0,f[x]=a[x],g[x]=b[x];
	for (int p=son[x];p;p=next[p]) if (ed[p]!=fa) q[++m]=ed[p];
	sort(q+1,q+m+1,cmp);
	rep(i,m) f[x]=max(f[x],g[x]+f[q[i]]),g[x]+=g[q[i]]; f[x]=max(f[x],g[x]);
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) scanf("%d%d%d",a+i,b+i,&x),b[i]+=x,son[i]=0; l=0;
		rep(i,n-1) scanf("%d%d",&x,&y),
			ed[++l]=y,next[l]=son[x],son[x]=l,
			ed[++l]=x,next[l]=son[y],son[y]=l;
		int ans=1<<25; rep(i,n) dfs(i,0),ans=min(ans,f[i]);
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
