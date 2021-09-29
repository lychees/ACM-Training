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

const int N=2010;
int u[N],v[N],w[N],dis[N],tot,sp[N];
int ww,x;
char s[N];
void add(int x,int y,int l,int r) {
	u[tot]=x; v[tot]=y; w[tot]=r; tot++;
	u[tot]=y; v[tot]=x; w[tot]=-l; tot++;
}
bool check(int p,int s) {
	sp[p]=s;
	tot=0;
	rep(i,0,x) if (i<=p) add(2*i,2*i+1,-sp[i],-sp[i]);
		else add(2*i,2*i+1,-1,0);
	rep(i,0,x) add(2*i+1,2*(2*i%x),0,0),add(2*i+1,2*(2*i%x+1),1,1);
	rep(i,0,2*x) dis[i]=1<<30;
	dis[0]=0;
	bool fg=0;
	rep(i,0,2*x+1) {
		fg=0;
		rep(j,0,tot) if (dis[u[j]]>dis[v[j]]+w[j]) {
			dis[u[j]]=dis[v[j]]+w[j];
			fg=1;
		}
	}
	return !fg;
}
void dfs(int p,int f) {
	if (p==x) {
		rep(i,0,p) putchar(sp[i]+'0');
		puts("");
		throw 0;
	} else {
		rep(i,f==0?(s[p]-'0'):0,2) if (check(p,i))
			dfs(p+1,f|(i!=s[p]-'0'));
	}
}
int main() {
	freopen("idtire.in","r",stdin);
	freopen("idtire.out","w",stdout);
	scanf("%d",&ww);
	scanf("%s",s);
	x=1<<(2*ww+1);
	try {
		dfs(0,0);
	} catch(int e) {
		return 0;
	}
	puts("no");
}
