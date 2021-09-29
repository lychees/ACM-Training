#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=1005;
int Case,n,m,t,ans,L[9],x[N],y[N],z[N],p[N],b[9][N];
bool cmp(const int i,const int j){return y[i]<y[j];}
void dfs(int w,int e,int v,int s)
{
	if (e+1==1<<n) ans=min(ans,s);
	rep(j,n) if (!(e>>j&1)){
		int u=v,t=s,r=w,k=0;
		for (int i=w;i<=m;++i){
			while (b[j][k]) u-=b[j][k++]; if (k==L[j]){r=i; break;}
			u+=b[x[i]][y[i]]=z[i]; if (x[i]!=j || y[i]!=k) t=max(t,u);
		}
		dfs(r,e|1<<j,u,t);
		for (int i=w;i<r;++i) b[x[i]][y[i]]=0;
	}
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		ans=0; rep(i,n) scanf("%d",&t),ans+=t;
		rep(i,m) scanf("%d%d%d",x+i,y+i,z+i),--x[i],z[i]-=y[i]-1;
		rep(i,n){
			L[i]=0; rep(j,m) if (x[j]==i) p[L[i]++]=j;
			sort(p,p+L[i],cmp); rep(j,L[i]) y[p[j]]=j;
		}
		dfs(0,0,0,0); printf("Case %d: %d\n\n",++Case,ans);
	}
	return 0;
}
