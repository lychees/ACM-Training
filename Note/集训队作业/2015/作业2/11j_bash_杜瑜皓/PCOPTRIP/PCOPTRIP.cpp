#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

const ll N=100000;
int pr[N/5],p[N+100],tot,mu[N+100];
ll mul(ll a,ll b) { return (a%mod)*(b%mod)%mod;}
void init() {
	mu[1]=1;p[1]=1;
	rep(i,2,N+1) {
		if (!p[i]) p[i]=i,pr[++tot]=i,mu[i]=-1;
		for (int j=1;j<=tot&&pr[j]*i<=N;j++) {
			p[i*pr[j]]=pr[j];
			if (p[i]==pr[j]) break;
			else mu[i*pr[j]]=-mu[i];
		}
	}
}

int n,T;
int de[N+10];
pair<PII,int> E[N*10];
vector<PII> e[N+10];
ll ans;
int main() {
	init();
	for (scanf("%d",&T);T;T--) {
		scanf("%d",&n);
		rep(d,1,n+1) de[d]=0,e[d].clear();
		tot=0; ans=0;
		rep(d,1,n+1) for (int a=1;a*d<=n;a++) if (mu[a*d]) 
			for (int b=a+1;1ll*a*b*d<=n;b++) if (mu[b*d]&&__gcd(a,b)==1) {
				de[a*d]++; de[b*d]++;
				E[tot++]=mp(mp(a*d,b*d),n/(a*b*d));
			}
		rep(d,1,n+1) de[d]++,e[d].pb(mp(d,n/d));
		rep(i,0,tot) {
			int a=E[i].fi.fi,b=E[i].fi.se;
			if (mp(de[a],a)<=mp(de[b],b)) e[a].pb(mp(b,E[i].se));
			else e[b].pb(mp(a,E[i].se));
		}
		rep(a,1,n+1) if (mu[a]) rep(j,0,SZ(e[a])) rep(k,j,SZ(e[a])) {
			int b=e[a][j].fi,c=e[a][k].fi,r=mu[a]*mu[b]*mu[c];
			if (a!=b&&b!=c&&a!=c) r*=6; else if (!(a==b&&b==c)) r*=3;
			ll s=n/c/(b/__gcd(b,c));
			ans+=r*s*e[a][j].se*e[a][k].se;
		}
		printf("%I64d\n",ans);
	}
}
