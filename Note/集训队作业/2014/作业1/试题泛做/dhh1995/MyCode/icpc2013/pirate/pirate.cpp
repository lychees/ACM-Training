#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=505;
int n,m,x,y,lim,a[N][N],L[N],R[N],s[N]; long long ans;
inline void cal(int d,int a,int b){ans=max(ans,(long long)(1.*n*m*d/(n*m-a*b)-1e-6)*a*b);}
inline int min(int a,int b){return a<b?a:b;}
int main()
{
	freopen("pirate.in","r",stdin);
	freopen("pirate.out","w",stdout);
	while (scanf("%d%d%d%d",&x,&y,&n,&m)!=EOF){
		rep(i,n) rep(j,m) scanf("%d",a[i]+j);
		if (x<y) swap(x,y); lim=x,ans=0;
		rep(k,x) if (k<=n){
			if (k>y) lim=y;
			rep(i,n-k+1){
				int t=0,*A=a[i];
				rep(j,m){
					while (t && A[j]<A[s[t]]) R[s[t--]]=j;
					L[j]=s[t],R[j]=m+1,s[++t]=j;
				}
				rep(j,m) cal(A[j],k,min(R[j]-L[j]-1,lim)),A[j]=min(A[j],a[i+1][j]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
