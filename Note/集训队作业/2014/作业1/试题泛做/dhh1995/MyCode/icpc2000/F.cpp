#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=105;
int Case,n,x,y,ans,id[N],d[N][N];
int get(int x){if (!id[x]) id[x]=++n; return id[x];}
int main()
{
	rep(i,100) rep(j,100) d[i][j]=(i!=j)<<20;
	while (scanf("%d%d",&x,&y),x||y){
		rep(i,100) id[i]=0; n=ans=0;
		do{x=get(x),y=get(y),d[x][y]=1,scanf("%d%d",&x,&y);}while (x||y);
		rep(k,n) rep(i,n) rep(j,n) if (d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
		rep(i,n) rep(j,n) ans+=d[i][j];
		printf("Case %d: average length between pages = %.3lf clicks\n",++Case,ans/(n-1.)/n);
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<20;
	}
	return 0;
}
