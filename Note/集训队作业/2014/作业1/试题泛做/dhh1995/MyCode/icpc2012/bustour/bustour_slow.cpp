#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int f[18][1<<18][18],c[1<<18],e[1<<18],a[18],b[18],d[25][25],Case,n,m,x,y,z,G,ans;
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
			rep(i,1<<n) if (c[i]<=n-n/2) rep(j,n) f[s][i][j]=1<<28; f[s][1<<s][s]=0;
			rep(i,1<<n) if (c[i]<n-n/2) rep(j,n) if ((z=f[s][i][j])<1<<28){
				for (x=G^i;x;x-=x&-x){
					int k=e[x&-x];
					if (z+d[j][k]<f[s][i|1<<k][k]) f[s][i|1<<k][k]=z+d[j][k];
				}
			}
		}
		rep(i,1<<n) if (c[i]*2==n?i<(G^i):c[i]==n/2){
			int s1=1<<28,s2=1<<28,j=G^i,L1=0,L2=0,x1,y1,x2,y2;
			rep(k,n) if (i>>k&1) a[L1++]=k; else b[L2++]=k;
			rep(k,L1){	x1=a[k];
				rep(k,L1){	y1=a[k];
					rep(k,L2){	x2=b[k];
						rep(k,L2){	y2=b[k];
							z=f[x1][i][y1]+d[y1][x2]+f[x2][j][y2];
							s1=min(s1,d[n+1][x1]+z+d[y2][n]);
							s2=min(s2,d[n][x1]+z+d[y2][n+1]);
						}
					}
				}
			}
			ans=min(ans,s1+s2);
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
