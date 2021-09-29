#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=16;
int Case,n,ans,x,y,c,d[N]; bool a[N][N],b[N];
void dfs(int i){b[i]=1; rep(j,n) if (a[i][j] && !b[j]) dfs(j);}
bool check()
{
	rep(j,n) if (!b[j]) rep(k,n) if (!b[k] && a[j][k]) ++d[j];
	rep(j,n) if (d[j]>2) return 0;
	int e=0; rep(j,n) if (!b[j] && d[j]<=1) dfs(j),++e;
	rep(j,n) if (!b[j]) return 0; return e<=c+1;
}
int main()
{
	while (scanf("%d",&n),n){
		rep(i,n) rep(j,n) a[i][j]=0; ans=n;
		while (scanf("%d%d",&x,&y),x>=0) --x,--y,a[x][y]=a[y][x]=1;
		rep(i,1<<n){c=0; rep(j,n) d[j]=0,c+=b[j]=i>>j&1; if (c<ans && check()) ans=c;}
		printf("Set %d: Minimum links to open is %d\n",++Case,ans);
	}
	return 0;
}
