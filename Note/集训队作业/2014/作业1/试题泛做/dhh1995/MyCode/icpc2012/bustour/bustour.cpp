#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int f[616666][20],c[1<<20],e[1<<20],d[25][25],p[1<<20],q[616666],Case,L,n,m,x,y,z,G,ans;
inline int min(int a,int b){return a<b?a:b;}
int main()
{
	freopen("bustour.in","r",stdin);
	freopen("bustour.out","w",stdout);
	rep(i,1<<20) c[i]=i?c[i-(i&-i)]+1:0; rep(i,20) e[1<<i]=i;
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<28; ans=1<<28;
		rep(i,m) scanf("%d%d%d",&x,&y,&z),d[x][y]=d[y][x]=min(d[x][y],z);
		rep(k,n) rep(i,n) rep(j,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]); G=(1<<n)-1;
		if (n==3){printf("Case %d: %d\n",++Case,2*(d[0][1]+d[1][2])); continue;}
		L=0; rep(i,1<<n) if (c[i]<=n-n/2) q[L]=i,p[i]=L++;
		rep(i,L) rep(j,n) f[i][j]=1<<28; f[p[1]][0]=f[p[1<<n-1]][n-1]=0;
		rep(i,L) if (c[q[i]]<n-n/2) rep(j,n) if (q[i]>>j&1) for (x=G^q[i];x;x-=x&-x)
			{int k=e[x&-x]; if (f[i][j]+d[j][k]<f[p[q[i]|1<<k]][k]) f[p[q[i]|1<<k]][k]=f[i][j]+d[j][k];}
		rep(k,L) if (c[q[k]]*2==n?q[k]<(G^q[k]):c[q[k]]==n/2){
			int i=q[k],j=G^i,s1=1<<28,s2=1<<28;
			rep(x,n) if (i>>x&1) rep(y,n) if (j>>y&1)
				s1=min(s1,f[k][x]+f[p[j]][y]+d[x][y]),
				s2=min(s2,f[p[j^1^(1<<n-1)]][y]+f[p[i^1^(1<<n-1)]][x]+d[x][y]);
			ans=min(ans,s1+s2);
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
