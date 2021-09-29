#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=100005;
int Case,n,D,C,t,id[N],d[N],p[N],r[N],g[N],q[N]; long long f[N],ans; double a[N];
bool cmp(const int i,const int j){return g[i]<g[j];}
#define get(i,j) (f[i]-f[j]+0.)/(g[j]-g[i]+0.)
int main()
{
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	while (scanf("%d%lld%d",&n,f,&D),n&&*f&&D){
		rep(i,n) scanf("%d%d%d%d",d+i,p+i,r+i,g+i),id[i]=i;
		q[t=1]=0,ans=*f; sort(id+1,id+n+1,cmp);
		rep(k,n){
			int i=id[k],j=q[upper_bound(a,a+t,d[i]-1)-a]; f[i]=f[j]+(d[i]-1LL)*g[j];
			if (f[i]<p[i]) continue; f[i]-=p[i]-r[i],f[i]-=1LL*d[i]*g[i];
			while (t>1 && get(q[t-1],i)<=get(q[t-1],q[t])) --t; a[t]=get(q[t],i);
			q[++t]=i; ans=max(ans,f[i]+1LL*D*g[i]);
		}
		printf("Case %d: %lld\n",++Case,ans);
	}
	return 0;
}
