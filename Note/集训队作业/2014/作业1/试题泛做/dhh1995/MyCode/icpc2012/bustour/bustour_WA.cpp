#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int f[1<<18][18],g[1<<18][18],c[1<<18],e[1<<18],a[18],b[18],d[25][25],Case,n,m,x,y,z,G,ans;
inline int min(int a,int b){return a<b?a:b;}
int main()
{
	freopen("bustour.in","r",stdin);
	freopen("bustour.out","w",stdout);
	c[0]=0; rep(i,1<<18) if (i) c[i]=c[i-(i&-i)]+1; rep(i,18) e[1<<i]=i;
	while (scanf("%d%d",&n,&m)!=EOF){
		rep(i,n) rep(j,n) d[i][j]=(i!=j)<<28; ans=1<<28;
		rep(i,m) scanf("%d%d%d",&x,&y,&z),
			x=(x-1+n)%n,y=(y-1+n)%n,d[x][y]=d[y][x]=min(d[x][y],z);
		rep(k,n) rep(i,n) rep(j,n) d[i][j]=min(d[i][j],d[i][k]+d[k][j]); n-=2,G=(1<<n)-1;
		if (n==1){printf("Case %d: %d\n",++Case,2*(d[2][0]+d[0][1])); continue;}
		
		rep(s,n){
			rep(i,1<<n) if (c[i]<=n-n/2) rep(j,n) f[i][j]=1<<28; f[1<<s][s]=0;
			rep(i,1<<n) if (c[i]<n-n/2) rep(j,n) if (i>>j&1) for (x=G^i;x;x-=x&-x)
				{int k=e[x&-x]; if (f[i][j]+d[j][k]<f[i|1<<k][k]) f[i|1<<k][k]=f[i][j]+d[j][k];}
			rep(i,1<<n) if (c[i]==n/2 || c[i]==n-n/2){
				g[i][s]=1<<28;
				rep(j,n) if (i>>j&1) if (f[i][j]+d[j][s]<g[i][s]) g[i][s]=f[i][j]+d[j][s];
			}
		}
		rep(i,n)
		rep(i,1<<n) if (c[i]*2==n?i<(G^i):c[i]==n/2){
			int s1=1<<28,s2=1<<28,j=G^i,L1=0,L2=0,x1,y1,x2,y2,z1,z2;
			rep(k,n) if (i>>k&1) a[L1++]=k; else b[L2++]=k;
			rep(k,L1){	x1=a[k],z1=d[n+1][x1],z2=d[n][x1];
				rep(k,L1){	y1=a[k],z=g[i][x1]-d[x1][y1];
					rep(k,L2){	x2=b[k],z+=d[y1][x2];
						rep(k,L2){	y2=b[k],z+=g[j][x2]-d[x2][y2];
							if (z1+z+d[y2][n]<s1) s1=z1+z+d[y2][n];
							if (z2+z+d[y2][n+1]<s2) s2=z2+z+d[y2][n+1];
							z-=g[j][x2]-d[x2][y2];
						}
					z-=d[y1][x2];
					}
				}
			}
			ans=min(ans,s1+s2);
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
