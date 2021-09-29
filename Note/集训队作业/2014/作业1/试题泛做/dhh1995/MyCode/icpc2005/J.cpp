#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,l,x,y,ans,res,a[25],b[15],c[15];
void dfs(int x,int y,int z,int s)
{
	if (y==m){
		rep(i,l) if (z&b[i]) s+=c[i];
		if (s>ans) ans=s,res=z; return;
	}
	if (n-x+y<m || x>=n) return;
	dfs(x+1,y+1,z|1<<x,s+a[x]),dfs(x+1,y,z,s);
}
int main()
{
	while (scanf("%d%d",&n,&m),n){
		rep(i,n) scanf("%d",a+i); scanf("%d",&l); ans=-1;
		rep(i,l){
			scanf("%d",&y); b[i]=0; while (y--) scanf("%d",&x),b[i]|=1<<x-1;
			scanf("%d",c+i); rep(j,n) if (b[i]>>j&1) a[j]-=c[i];
		}
		dfs(0,0,0,0);
		printf("Case Number  %d\n",++Case);
		printf("Number of Customers: %d\n",ans);
		printf("Locations recommended:");
		rep(i,n) if (res>>i&1) printf(" %d",i+1); puts("\n");
	}
	return 0;
}
