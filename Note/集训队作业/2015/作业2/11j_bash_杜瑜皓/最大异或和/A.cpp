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

typedef bitset<2000> number;

vector<number> nd[4010];
VI vec[4010];
number ZERO,d[2010],Pre[2010],base[2010];
int l,r,n,m,q,mt,bs[2010],zr[2010],pre[2010],ty,pty,qt[2010];
char s[2010];
int add(number d) {
	for (int k=m-1;k>=0;k--) if (d[k]) {
		if (bs[k]) d=d^base[k];
		else {
			bs[k]=1; base[k]=d;
			return k;
		}
	}
	return -1;
}
void add(int p,int tl,int tr,int l,int r,number &c) {
/*
	if (tl==1&&tr==1000) {
		printf("%d %d ",l,r);
		for (int k=m-1;k>=0;k--) if (c[k]) putchar('1'); else putchar('0');
		puts("");
	}*/
	if (tl==l&&tr==r) nd[p].pb(c);
	else {
		int md=(tl+tr)>>1;
		if (r<=md) add(p+p,tl,md,l,r,c);
		else if (l>md) add(p+p+1,md+1,tr,l,r,c);
		else add(p+p,tl,md,l,md,c),add(p+p+1,md+1,tr,md+1,r,c);
	}
}
void modify(int x,number c) {
	if (!zr[x]) { if (pre[x]<mt) add(1,1,1000,pre[x]+1,mt,Pre[x]);}
	pre[x]=mt; Pre[x]=c;
}
void query(int p,int tl,int tr) {
	if (tl>mt) return;
	vec[p].clear();
	for (auto c:nd[p]) {
		int r=add(c);
		if (r!=-1) vec[p].pb(r);
	}
	if (tl!=tr) {
		int md=(tl+tr)>>1;
		query(p+p,tl,md);
		query(p+p+1,md+1,tr);
	} else {
		number c=ZERO;
		for (int k=m-1;k>=0;k--) if (!c[k]&&bs[k]) c^=base[k];
		rep(i,0,m) s[i]=c[i]+'0';
		reverse(s,s+m);
		rep(i,0,qt[tl]) puts(s);
	}
	for (auto c:vec[p]) bs[c]=0;
}

int main() {
	scanf("%d%d%d",&n,&m,&q);
	rep(i,1,n+1) {
		scanf("%s",s);
		reverse(s,s+m);
		rep(j,0,m) d[i][j]=(s[j]=='1');
	}
	rep(i,1,n+1) zr[i]=1;
	mt=0;
	per(i,1,n+1) modify(i,d[i]^d[i-1]),zr[i]=0;
	rep(k,0,q) {
		scanf("%d",&ty);
		if (ty==3) {
			if (pty!=3) mt++;
			qt[mt]++;
		} else {
			scanf("%d%d%s",&l,&r,s);
			reverse(s,s+m);
			number c;
			rep(j,0,m) c[j]=(s[j]=='1');
			if (ty==2) {
				rep(i,l,r+1) d[i]=c;
				modify(l,d[l]^d[l-1]),zr[l]=0;
				rep(i,l+1,r+1) if (!zr[i]) {
					modify(i,ZERO); zr[i]=1;
				}
				if (r+1<=n) modify(r+1,d[r+1]^d[r]),zr[r+1]=0;
			} else if (ty==1) {
				rep(i,l,r+1) d[i]^=c;
				modify(l,d[l]^d[l-1]),zr[l]=0;
				if (r+1<=n) modify(r+1,d[r+1]^d[r]),zr[r+1]=0;
			}
		}
		pty=ty;
	}
	rep(i,1,n+1) modify(i,ZERO);
	query(1,1,1000);
}
