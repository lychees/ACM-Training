#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define mp make_pair
#define pb push_back
#define SZ(x) ((int)(x).size())
typedef long long ll;

const int K=55,N=201000;
const int mod=1000000007;
vector<int> conc[N],lp,rp,ntv;
vector<pair<int,int> > e[K],nte;
ll bi[K][K],pe[K][K],fac[N];
int x[K],y[K],w[K],vis[N],cis[N];
int n,k,c,f[N];
int l,r,ans,a[K][K];
int dp[K][(1<<18)+10],wt[(1<<18)+10];
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
void solvel(int l,int r) {
	rep(i,0,r+1) rep(j,0,(1<<l)) dp[i][j]=0;
	dp[0][0]=1;
	rep(i,0,r) rep(S,0,(1<<l)) if (dp[i][S]) {
		rep(k,0,l) if (!(S&(1<<k))) { 
			if (a[k][i]==1) upd(dp[i+1][S+(1<<k)],dp[i][S]);
			else upd(dp[i+1][S+(1<<k)],1ll*dp[i][S]*a[k][i]%mod);
		}
		upd(dp[i+1][S],dp[i][S]);
	}
	rep(S,0,(1<<l)) upd(cp[c].dp[__builtin_popcount(S)],dp[r][S]);
}
void dfs(int u) {
	pd[u][0]=info(0,0);pd[u][0].dp[0]=1;
	pd[u][1]=info(0,0);
	cis[u]=1;
	rep(j,0,SZ(e[u])) {
		int v=e[u][j].first;
		if (cis[v]) continue;
		int w=e[u][j].second;
		dfs(v);
		pd[u][1]=pd[u][1]*(pd[v][0]+pd[v][1])+pd[u][0]*(mul(pd[v][0],w)+mul(pd[v][1]));
		pd[u][0]=pd[u][0]*(pd[v][0]+pd[v][1]);
	}
	pd[u][0].r+=1; pd[u][1].r=pd[u][0].r;
	rep(j,0,2) pd[u][j]._swap();
}
void dfs(int dep,ll w,int S) {
	if (dep==SZ(nte)) {
		int c=__builtin_popcount(S);
		rep(j,0,l+r) cis[j]=vis[j];
		wt[S]=w;
		info ap(0,0); ap.dp[0]=1;
		rep(j,0,l+r) if (!cis[j]) {
			dfs(j);
			if (j>=l) rep(k,0,2) pd[j][k]._swap();
			ap=ap*(pd[j][0]+pd[j][1]);
		}
		for (int j=0;j<=ap.l&&j<=ap.r;j++) upd(dp[j+c][S],ap.dp[j]%mod);
	} else {
		int u=nte[dep].first,v=nte[dep].second;
		dfs(dep+1,w,S);
		if (!vis[u]&&!vis[v]) {
			vis[u]=1; vis[v]=1;
			dfs(dep+1,w*ntv[dep]%mod,S|(1<<dep));
			vis[u]=0; vis[v]=0;
		}
	}
}
void solver(int p) {
	for (int i=0;i<=l&&i<=r;i++) rep(j,0,(1<<p)) dp[i][j]=0;
	dfs(0,1,0);
	for (int i=0;i<=l&&i<=r;i++) rep(j,0,p) rep(k,0,(1<<p)) if (!(k&(1<<j))) {
		dp[i][k]-=dp[i][k+(1<<j)];
		if (dp[i][k]<0) dp[i][k]+=mod;
	}
	for (int i=0;i<=l&&i<=r;i++) rep(k,0,(1<<p))
		upd(cp[c].dp[i],1ll*dp[i][k]*wt[k]%mod);
}
void solve() {
	if ((l<=18||r<=18)&&(l+r<=37)) {
		if (l<=r) solvel(l,r);
		else {
			rep(i,0,l) rep(j,r+1,l) a[i][j]=0;
			rep(i,0,l) rep(j,i+1,l) swap(a[i][j],a[j][i]);
			solvel(r,l); 
		}
	} else {
		rep(i,0,l+r) f[i]=i;
		nte.clear(); ntv.clear();
		rep(i,0,l+r) e[i].clear();
		rep(i,0,l) rep(j,0,r) if (a[i][j]!=1) {
			if (find(i)!=find(j+l)) {
				f[find(i)]=f[find(j+l)];
				e[i].pb(mp(j+l,a[i][j]));
				e[j+l].pb(mp(i,a[i][j]));
			} else nte.pb(mp(i,j+l)),ntv.pb(a[i][j]);
		}
		solver(SZ(nte));
	}
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

