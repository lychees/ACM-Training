#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define mp make_pair
#define pb push_back
#define SZ(x) ((int)(x).size())
#define TWO(x) (1<<(x))
typedef long long ll;
typedef vector<int> VI;

const int K=55,N=201000;
const int mod=1000000007;
vector<int> conc[N],lp,rp;
vector<pair<int,int> > e[K];
ll bi[K][K],pe[K][K],fac[N];
int x[K],y[K],w[K],vis[N],cis[N];
int n,k,c,f[N];
int l,r,ans,a[K][K];
VI dp[K][K];

map<pair<int,int>,int> hs;

int find(int x) { return f[x]==x?x:f[x]=find(f[x]); }
inline void upd(int &a,int b) { a+=b; if (a>=mod) a-=mod; }

struct info {
	int l,r;
	int dp[K];
	info () {}
	info (int _l,int _r) { l=_l; r=_r; memset(dp,0,sizeof(dp)); }
	void _swap() { swap(l,r); }
};

info ap,cp[K],pd[K][2];

info operator * (const info &a,const info &b) {
	info c(a.l+b.l,a.r+b.r);
	for (int j=0;j<=a.l&&j<=a.r;j++) for (int k=0;k<=b.l&&k<=b.r;k++) 
		for (int pl=0;pl+k<=b.l&&pl+j<=a.r;pl++) for (int pr=0;pr+k<=b.r&&pr+j<=a.l;pr++) {
			upd(c.dp[j+k+pl+pr],1ll*a.dp[j]*b.dp[k]%mod*bi[b.l-k][pl]%mod*pe[a.r-j][pl]%mod
				*bi[b.r-k][pr]%mod*pe[a.l-j][pr]%mod);
		}
	return c;
}
info mul(const info &a,const ll &b) {
	info c(a.l,a.r+1);
	for (int j=0;j<=a.l&&j<=a.r;j++) c.dp[j+1]=a.dp[j]*(b+a.l-1-j)%mod;
	return c;
}
info mul(const info &a) {
	info c(a.l,a.r+1);
	for (int j=0;j<=a.l&&j<=a.r;j++) c.dp[j+1]=1ll*a.dp[j]*(a.l-j)%mod;
	return c;
}

info operator + (const info &a,const info &b) {
	info c(max(a.l,b.l),max(a.r,b.r));
	for (int j=0;j<=c.l&&j<=c.r;j++) c.dp[j]=(a.dp[j]+b.dp[j])%mod;
	return c;
}
void upd(int &a,ll b) { a=(a+b)%mod;}
////////////////////////////////
int pos[K],p[K],od[K],id[K][K];
ll cost[K];
vector<int> _e[K],pnt[K];
ll calc(int t=0) {
	rep(i,0,l+r) pos[p[i]]=i,cost[i]=1;
	rep(i,0,l+r) {
		int ms=i;
		rep(j,0,SZ(_e[p[i]])) ms=max(ms,pos[_e[p[i]][j]]);
		rep(j,i,ms+1) cost[j]*=2;
	}
	ll ret=0;
	rep(i,0,l+r) ret+=cost[i];
	return ret;
}
void solve() {
	rep(i,0,l+r) _e[i].clear();
	rep(i,0,l) rep(j,0,r) if (a[i][j]!=1) _e[i].pb(j+l), _e[j+l].pb(i);
	rep(i,0,l+r) p[i]=i,od[i]=i;
	ll ans=calc();
	rep(k,0,500*(l+r)) {
		int u=rand()%(l+r),v=rand()%(l+r);
		rep(i,0,l+r) p[i]=od[i];
		swap(p[u],p[v]);
		ll c=calc();
		if (c<ans) {
			ans=c;
			rep(i,0,l+r) od[i]=p[i];
		}
	}
	int cl=0,cr=0;
	rep(i,0,l+r) p[i]=od[i],pnt[i].clear();;
	rep(i,0,l+r) pos[p[i]]=i;
	rep(i,0,l+r) rep(j,0,l+r) id[i][j]=-1;
	rep(i,0,l+r) {
		int ms=i;
		rep(j,0,SZ(_e[p[i]])) ms=max(ms,pos[_e[p[i]][j]]);
		rep(j,i,ms+1) pnt[j].pb(i);
	}
	rep(i,0,l+r) rep(j,0,SZ(pnt[i])) id[i][pnt[i][j]]=j;
	dp[0][0].clear();
	dp[0][0].resize(2); dp[0][0][0]=1;
	if (p[0]<l) cl++; else cr++;
	rep(i,1,l+r) {
		int u=p[i];
		rep(k,0,min(cl,cr)+2) {
			dp[i][k].clear();
			dp[i][k].resize(TWO(SZ(pnt[i])));
		}
		rep(oS,0,TWO(SZ(pnt[i-1]))) {
			int S=0,pl=cl,pr=cr;
			rep(w,0,SZ(pnt[i-1])) if (oS&TWO(w)) {
				int ps=id[i][pnt[i-1][w]];
				if (ps!=-1) S|=1<<ps;
			}
			rep(w,0,SZ(pnt[i])-1) if (!(S&TWO(w))) {
				int v=p[pnt[i][w]];
				if (v<l) pl--; else pr--;
			}
			rep(k,0,min(cl,cr)+1) if (dp[i-1][k][oS]) {
				ll ret=dp[i-1][k][oS];
				upd(dp[i][k][S],ret);
				rep(w,0,SZ(pnt[i])-1) if (!(S&TWO(w))) {
					int v=p[pnt[i][w]];
					if (((u<l)^(v<l))==0) continue;
					upd(dp[i][k+1][S|TWO(SZ(pnt[i])-1)|TWO(w)],ret*((u<l)?a[u][v-l]:a[v][u-l]));
				}
				if (u<l) upd(dp[i][k+1][S|TWO(SZ(pnt[i])-1)],ret*(pr-k));
				else upd(dp[i][k+1][S|TWO(SZ(pnt[i])-1)],ret*(pl-k));
			}
		}
		if (p[i]<l) cl++; else cr++;
	}
	rep(j,0,min(cl,cr)+1) rep(k,0,TWO(SZ(pnt[l+r-1]))) upd(cp[c].dp[j],dp[l+r-1][j][k]);
}

ll perm(int a,int b) {
	ll s=1;
	rep(j,1,b+1) s=s*(a+1-j)%mod;
	return s;
}
void init() {
	rep(i,0,k+1) {
		bi[i][0]=bi[i][i]=1;
		rep(j,1,i) bi[i][j]=(bi[i-1][j-1]+bi[i-1][j])%mod;
		pe[i][0]=1;
		rep(j,1,i+1) pe[i][j]=pe[i][j-1]*(i+1-j)%mod;
	}
	fac[0]=1;
	rep(i,1,n+1) fac[i]=fac[i-1]*i%mod;
}
void read() {
	scanf("%d%d",&n,&k);
	rep(i,0,2*n) f[i]=i;
	rep(i,0,k) {
		scanf("%d%d%d",x+i,y+i,w+i);
		if (w[i]==1) {
			--i; --k;
			continue;
		}
		--x[i]; --y[i];
		hs[mp(x[i],y[i])]=w[i];
		y[i]+=n;
		f[find(x[i])]=find(y[i]);
	}
	rep(i,0,2*n) conc[find(i)].pb(i);
}
void step1() {
	c=0;
	rep(i,0,2*n) if (SZ(conc[i])>1) {
		lp.clear(); rp.clear();
		rep(j,0,SZ(conc[i])) {
			int u=conc[i][j];
			if (u<n) lp.pb(u); else rp.pb(u-n);
		}
		cp[c]=info(SZ(lp),SZ(rp));
		rep(j,0,SZ(lp)) rep(k,0,SZ(rp))
			if (hs.count(mp(lp[j],rp[k]))) a[j][k]=hs[mp(lp[j],rp[k])];
			else a[j][k]=1;
		l=SZ(lp); r=SZ(rp);
		solve();
		++c;
	}
}
void step2() {
	ap=info(0,0); ap.dp[0]=1;
	rep(i,0,c) ap=ap*cp[i];
	for (int j=0;j<=ap.l&&j<=ap.r;j++) {
		if (ap.l+ap.r-j>n) continue;
		upd(ans,ap.dp[j]*perm(n-ap.r,ap.l-j)%mod*perm(n-ap.l,ap.r-j)%mod*fac[n-ap.r-ap.l+j]%mod);
	}
	printf("%d\n",ans);
}
int main() {
	read();
	init();
	step1();
	step2();
}

