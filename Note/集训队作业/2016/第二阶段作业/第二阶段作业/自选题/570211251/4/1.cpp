#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include<map>
#include<set>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define ph push
#define pb push_back
#define REP(i,a,n) for(int _tmp=n,i=a;i<=_tmp;++i)
#define DEP(i,a,n) for(int _tmp=n,i=a;i>=_tmp;--i)
#define rep(i,a,n) for(int i=(a);i<=(n);++i)
#define dep(i,a,n) for(int i=(a);i>=(n);--i)
#define ALL(x,S) for(__typeof((S).end()) x=S.begin();x!=S.end();x++)
#define eps 1e-8
#define pi 3.1415926535897
#define sqr(x) ((x)*(x))
#define MAX(a,b) a=max(a,b)
#define MIN(a,b) a=min(a,b)
#define SZ(x) ((int)(x).size())
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define POSIN(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=m)
#define all(x) (x).begin(),(x).end()
#define COUT(S,x) cout<<fixed<<setprecision(x)<<S<<endl
typedef long long ll;
typedef long long LL;
typedef double lf;
typedef pair<int,int> pii;
typedef pair<ll,ll> PLL;
typedef pair<lf,lf> pff;
typedef complex<double> CD;
const int inf=0x20202020;
const int mod=1000000007;
template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar());if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
template<class T> inline void read(T&x,T&y,T&z,T&q){read(x);read(y);read(z);read(q);}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************
namespace FC {
    const int N=5010000;
    ll C,fac[10010],n,mut,a[5001000];
    int T,cnt,i,l,prime[N],p[N],psize,_cnt,tot=0;
    ll _e[100],_pr[100];
    vector<ll> d;
    inline ll mul(ll a,ll b,ll p) {
        if (p<=1000000000) return a*b%p;
        else if (p<=1000000000000ll) return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
        else {
            ll d=(ll)floor(a*(long double)b/p+0.5);
            ll ret=(a*b-d*p)%p;
            if (ret<0) ret+=p;
            return ret;
        }
    }
    void prime_table(){
        int i,j,t1;
        for (i=1;i<=psize;i++) p[i]=i;
        for (i=2,tot=0;i<=psize;i++){
            if (p[i]==i) prime[++tot]=i;
            for (j=1;j<=tot && (t1=prime[j]*i)<=psize;j++){
                p[t1]=prime[j];
                if (i%prime[j]==0) break;
            }
        }
    }
    void init(int ps) {
        psize=ps;
        prime_table();
    }
    ll powl(ll a,ll n,ll p) {
        ll ans=1;
        for (;n;n>>=1) {
            if (n&1) ans=mul(ans,a,p);
            a=mul(a,a,p);
        }
        return ans;
    }
    bool witness(ll a,ll n) {
        int t=0;
        ll u=n-1;
        for (;~u&1;u>>=1) t++;
        ll x=powl(a,u,n),_x=0;
        for (;t;t--) {
            _x=mul(x,x,n);
            if (_x==1 && x!=1 && x!=n-1) return 1;
            x=_x;
        }
        return _x!=1;
    }
    bool miller(ll n) {
        if (n<2) return 0;
        if (n<=psize) return p[n]==n;
        if (~n&1) return 0;
        for (int j=0;j<=7;j++) if (witness(rand()%(n-1)+1,n)) return 0;
        return 1;
    }
    ll gcd(ll a,ll b) {
        ll ret=1;
        while (a!=0) {
            if ((~a&1) && (~b&1)) ret<<=1,a>>=1,b>>=1;
            else if (~a&1) a>>=1; else if (~b&1) b>>=1;
            else {
                if (a<b) swap(a,b);
                a-=b;
            }
        }
        return ret*b;
    }
    ll rho(ll n) {
        for (;;) {
            ll X=rand()%n,Y,Z,T=1,*lY=a,*lX=lY;
            int tmp=20;
            C=rand()%10+3;
            X=mul(X,X,n)+C;*(lY++)=X;lX++;
            Y=mul(X,X,n)+C;*(lY++)=Y;
            for(;X!=Y;) {
                ll t=X-Y+n;
                Z=mul(T,t,n);
                if(Z==0) return gcd(T,n);
                tmp--;
                if (tmp==0) {
                    tmp=20;
                    Z=gcd(Z,n);
                    if (Z!=1 && Z!=n) return Z;
                }
                T=Z;
                Y=*(lY++)=mul(Y,Y,n)+C;
                Y=*(lY++)=mul(Y,Y,n)+C;
                X=*(lX++);
            }
        }
    }
    void _factor(ll n) {
        for (int i=0;i<cnt;i++) {
            if (n%fac[i]==0) n/=fac[i],fac[cnt++]=fac[i];}
        if (n<=psize) {
            for (;n!=1;n/=p[n]) fac[cnt++]=p[n];
            return;
        }
        if (miller(n)) fac[cnt++]=n;
        else {
            ll x=rho(n);
            _factor(x);_factor(n/x);
        }
    }
    void dfs(ll x,int dep) {
        if (dep==_cnt) d.pb(x);
        else {
            dfs(x,dep+1);
            for (int i=1;i<=_e[dep];i++) dfs(x*=_pr[dep],dep+1);
        }
    }
    void norm() {
        sort(fac,fac+cnt);
        _cnt=0;
        rep(i,0,cnt-1) if (i==0||fac[i]!=fac[i-1]) _pr[_cnt]=fac[i],_e[_cnt++]=1;
            else _e[_cnt-1]++;
    }
    vector<ll> getd() {
        d.clear();
        dfs(1,0);
        return d;
    }
    vector<ll> factor(ll n) {
        cnt=0;
        _factor(n);
        norm();
        return getd();
    }
    vector<PLL> factorG(ll n) {
        cnt=0;
        _factor(n);
        norm();
        vector<PLL> d;
        rep(i,0,_cnt-1) d.pb(mp(_pr[i],_e[i]));
        return d;
    }
    bool is_primitive(ll a,ll p) {
        //assert(miller(p));
        vector<PLL> D=factorG(p-1);
        rep(i,0,SZ(D)-1) if (powmod(a,(p-1)/D[i].X,p)==1) return 0;
        return 1;
    }
    vector<int> pows(ll n) {
        vector<PLL> w = factorG(n);
        vector<int> ret;
        ret.clear();
        for (vector<PLL>::iterator it = w.begin(); it != w.end(); it++)
            ret.push_back(it->second);
        return ret;
    }
}
const int N=111111,M=111111;
int l,m,n,t,C;
int check(ll x){
    vector<ll>p=FC::factor(x);
    sort(p.begin(),p.end());
    ll sum=0;
    rep(i,0,SZ(p)-1){
        if(p[i]>sum+1)return 0;sum+=p[i];
    }return 1;
}
void pfen(ll x){
	vector<PLL>p=FC::factorG(x);
	printf("%d",SZ(p));rep(i,0,SZ(p)-1)printf(" %I64d %I64d",p[i].X,p[i].Y);puts("");
}
void pfen(ll x,ll y){
	vector<PLL>p1=FC::factorG(x),p2=FC::factorG(y),ans;
	int q1=0,q2=0;
	while(q1<SZ(p1)&&q2<SZ(p2)){
		if(p1[q1].X==p2[q2].X){
			ans.pb(mp(p1[q1].X,p1[q1].Y+p2[q2].Y));q1++;q2++;
		}else if(p1[q1].X<p2[q2].X){
			ans.pb(p1[q1]);q1++;
		}else {
			ans.pb(p2[q2]);q2++;
		}
	}
	while(q1<SZ(p1))ans.pb(p1[q1]),++q1;
	while(q2<SZ(p2))ans.pb(p2[q2]),++q2;
	printf("%d",SZ(ans));rep(i,0,SZ(ans)-1)printf(" %I64d %I64d",ans[i].X,ans[i].Y);puts("");
}
ll biu[111],btot=0;
void gcd(ll a,ll b,ll &d,ll &x,ll &y){
	if(!b){d=a;x=1;y=0;}
	else{gcd(b,a%b,d,y,x);y-=x*(a/b);} 
}
int main(){
	//ios::sync_with_stdio(false);
#ifdef LOCAL
	//freopen("1008.in","r",stdin);freopen("1008.out","w",stdout);
#endif
	FC::init(5000000);
	biu[0]=50;
	while(biu[btot]<=1000000000){
		++btot;for(biu[btot]=int(biu[btot-1]*0.8)*2;!check(biu[btot])||!check(biu[btot]+2);biu[btot]-=2);
	}
	//rep(i,1,btot)printf("%d %lld\n",i,biu[i]);
	//rep(i,6,20)fprintf(stderr,"%d %d\n",i,check(i));return 0;
	ll n;int cnt=0,sm=0;
	while(scanf("%I64d",&n)!=EOF){
		if(n==2)puts("YES\n1 1\n0\n0");
		//if((++cnt)%100==0)fprintf(stderr,"%d %.2lf\n",cnt,1.0*sm/cnt);
		if(n<=10000){
			rep(i,1,n/2-1)if(check(i*2)&&check(n-i*2)){
				puts("YES");printf("%I64d %I64d\n",ll(i*2),n-i*2);
				pfen(i*2);pfen(n-i*2);sm+=i;break;
			}
		}else{
			int bo=0;
			rep(i,1,btot){
				ll m=biu[i];
				if(4*m*m<n)continue;
				//printf("%d",i);
				//am+b(m+2)=n
				ll x=((-n/2)%(2*(m+2))+2*(m+2))%(2*(m+2));
				rep(_,-1,1){
					ll xx=x+_*(m+2);if(xx<1||xx>2*m)continue;
					if((n-xx*m)%(m+2))continue;
					if(n-xx*m<=0)continue;
					ll yy=(n-xx*m)/(m+2);
					if(yy<1||yy>2*m)continue;
					bo=1;
					printf("YES\n%I64d %I64d\n",xx*m,yy*(m+2));
					//if(!check(xx*m)||!check(yy*(m+2)))fprintf(stderr,"biubiu");
					//if(xx*m+yy*(m+2)!=n)fprintf(stderr,"biubiu");
					pfen(xx,m);pfen(yy,m+2);
					break;
				}
				if(bo)break;
			}if(!bo)puts("NO");
		}
	}
	return 0;
}
