#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=55;
int Case,n,a[N][N],m[N],p[N],q[N],F[N],G[N],*f=F,*g=G;
int main()
{
	freopen("stacking.in","r",stdin);
	freopen("stacking.out","w",stdout);
	while (scanf("%d",&n)!=EOF){
		rep(i,n){scanf("%d",m+i),p[i]=f[i]=0; rep(j,m[i]) scanf("%d",a[i]+j);}
		rep(j,10001){
			int L=0;
			rep(i,n) while (p[i]<m[i] && a[i][p[i]]==j) ++p[q[L++]=i];
			L=unique(q,q+L)-q;
			
			if (!L) continue;
			
			rep(k,n) g[k]=1<<20;
			rep(i,L){
				int x=q[i];
				rep(k,n) if (f[k]+(k!=x)<g[x]) g[x]=f[k]+(k!=x);
			}
			swap(f,g);
			
			if (L==1) continue;
			
			rep(k,n) g[k]=1<<20;
			rep(i,L){
				int x=q[i];
				rep(k,n) if (k!=x && f[k]+L-1<g[x]) g[x]=f[k]+L-1;
			}
			swap(f,g);
		}
		int ans=1<<20; rep(i,n) ans=min(ans,f[i]);
		printf("Case %d: %d\n",++Case,ans*2-n+1);
	}
	return 0;
}
