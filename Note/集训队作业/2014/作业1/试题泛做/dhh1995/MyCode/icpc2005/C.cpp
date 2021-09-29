#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,m,T,s,ans,cnt,o,x,y,z,p[25],a[25],D[25],fa[25],d[25][25]; bool b[25];
int work(int c,int y)
{
	int L=0,sum=0; rep(i,n) if (i!=T && y>>i&1) a[++L]=i,D[i]=d[T][i],fa[i]=T; --c;
	while (c--){
		int opt=1<<20,k=-1;
		rep(i,L) if (D[a[i]]>=0 && D[a[i]]<opt) opt=D[a[i]],k=a[i];
		if (k<0) return 1<<20; sum+=D[k],D[k]=-1;
		rep(i,L) if (d[k][a[i]]<D[a[i]]) D[a[i]]=d[k][a[i]],fa[a[i]]=k;
	}
	return sum;
}
void dfs(int x,int c,int y)
{
	if (x>n){
		int res=work(c,y);
		if (res==ans?c<cnt:res<ans) ans=res,cnt=c,o=y;
		return;
	}
	dfs(x+1,c+1,y|1<<x); if (!b[x]) dfs(x+1,c,y);
}
int main()
{
	while (scanf("%d",&n),n>=0){
		scanf("%d%d",&T,&m); rep(i,n) rep(j,n) d[i][j]=(i!=j)<<20;
		rep(i,m) scanf("%d%d%d",&x,&y,&z),d[x][y]=d[y][x]=z;
		rep(i,n) b[i]=0; b[T]=1,scanf("%d",&s); rep(i,s) scanf("%d",p+i),b[p[i]]=1;
		ans=1<<20,dfs(1,0,0),work(cnt,o); printf("Case %d: distance = %d\n",++Case,ans);
		rep(i,s){printf("   "); for (x=p[i];x!=T;x=fa[x]) printf("%d-",x); printf("%d\n",T);}
		puts("");
	}
	return 0;
}
