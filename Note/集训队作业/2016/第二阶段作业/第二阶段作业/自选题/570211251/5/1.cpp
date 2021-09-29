#include<bits/stdc++.h>
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
typedef double lf;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N=111111,M=3333333;
int l,m,n,t,tot,cnt,moyue;
int enc(pii x){if(x.X==1)x.X=14;return (x.X<<2)+x.Y;}
pii dec(int x){return mp(x>>2,x&3);}
struct zcc{int a,ty,c1,c2;
void st(){int c[6];rep(i,1,5)c[i]=a&63,a>>=6;sort(c+1,c+1+5);a=0;dep(i,5,1)a=(a<<6)+c[i];}
void work(){
	int c[6];rep(i,1,5)c[i]=a&63,a>>=6;sort(c+1,c+1+5);a=0;dep(i,5,1)a=(a<<6)+c[i];
	pii a[6];rep(i,1,5)a[i]=dec(c[i]);
	int c1S=0,c2S=0,c1F=0,c2F=0,c1N=0,c2N=0,S=0,F=0,tmp;
	dep(i,5,1)c1N=(c1N<<6)+a[i].X,c2N=(c2N<<6)+a[i].Y;
	tmp=1;rep(i,2,5)if(a[i].X!=a[i-1].X+1)tmp=0;S=tmp;
	dep(i,5,1)c1S=(c1S<<6)+a[(i+3)%5+1].X,c2S=(c2S<<6)+a[(i+3)%5+1].Y;
	tmp=1;rep(i,1,4)if(a[i].X!=i+1)tmp=0;
	if(tmp&&a[5].X==14)S=1;else c1S=c1N,c2S=c2N;
	tmp=1;rep(i,2,5)if(a[i].Y!=a[1].Y)tmp=0;F=tmp;
	int sum[6];sum[0]=0;
	rep(i,1,5)if(a[i].X==a[i-1].X)sum[i]=sum[i-1]+1;else sum[i]=1;
	dep(i,4,1)if(a[i].X==a[i+1].X)MAX(sum[i],sum[i+1]);
	pair<int,pii> p[6];rep(i,1,5)p[i]=mp(sum[i],a[i]);sort(p+1,p+1+5);
	dep(i,5,1)c1F=(c1F<<6)+p[i].Y.X,c2F=(c2F<<6)+p[i].Y.Y;
	
	if(S&&F){ty=9;c1=c1S;c2=c2S;return;}
	if(p[5].X==4){ty=8;c1=c1F;c2=c2F;return;}
	if(p[5].X==3&&p[1].X==2){ty=7;c1=c1F;c2=c2F;return;}
	if(F){ty=6;c1=c1N;c2=c2N;return;}
	if(S){ty=5;c1=c1S;c2=c2S;return;}
	if(p[5].X==3&&p[1].X==1){ty=4;c1=c1F;c2=c2F;return;}
	if(p[5].X==2&&p[3].X==2){ty=3;c1=c1F;c2=c2F;return;}
	if(p[5].X==2&&p[3].X==1){ty=2;c1=c1F;c2=c2F;return;}
	if(p[5].X==1){ty=1;c1=c1F;c2=c2F;return;}
}
bool exi(int *v,int n){int B=a;rep(i,1,5){if(v[B&63])--n;B>>=6;}return n==0;}
friend bool operator<(const zcc &a,const zcc &b){return a.ty<b.ty||a.ty==b.ty&&a.c1<b.c1||a.ty==b.ty&&a.c1==b.c1&&a.c2<b.c2;}
}p1,p2,a[M];
void dfs(int x,int y,int z){
	if(x>5){a[++tot].a=z;a[tot].work();return;}
	rep(i,y,63){
		if(2<=(i>>2)&&(i>>2)<=14)dfs(x+1,i+1,(z<<6)+i);
	}
}
//unordered_map<int,int>MA;
int tt;
int MA[11111111];
vector<pii>vec[1111111];
ll ans,fm,gd;
char con1[5]={4,5,3,6};
char con2[15]={0,0,'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
void print(int *a){rep(i,1,5)printf("%c%c ",con1[dec(a[i]).Y],con2[dec(a[i]).X]);puts("");}
#include<ctime>
int ca1[66],ca2[66];
ll C[88][88];
int find(int x){
	int y=x%1000033;
	rep(i,0,SZ(vec[y])-1)if(vec[y][i].X==x)return vec[y][i].Y;
	vec[y].pb(mp(x,++tt));return tt;
}
int main(){
	//ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("A1344.in","r",stdin);//freopen("A1344.out","w",stdout);
#endif
	C[0][0]=1;rep(i,1,77){C[i][0]=C[i-1][0];rep(j,1,10)C[i][j]=C[i-1][j-1]+C[i-1][j];}
	scanf("%d",&n);int tmp;
	rep(i,1,n)scanf("%d%d",&l,&t),tmp=enc(mp(l,4-t)),ca1[tmp]=1,p1.a=(p1.a<<6)+tmp;p1.st();
	rep(i,1,n-1)scanf("%d%d",&l,&t),tmp=enc(mp(l,4-t)),ca2[tmp]=1,p2.a=(p2.a<<6)+tmp;p2.st();
	dfs(1,1,0);sort(a+1,a+1+tot);
	//printf("%d\n",clock());
	rep(i,1,tot){
		if(a[i].exi(ca1,n)){
			//puts("orz1");
			int b[6],B=a[i].a;rep(i,1,5)b[i]=B&63,B>>=6;
			rep(mask,0,31){
                int ty=1,a=0;rep(i,1,5)if(mask&1<<i-1)ty*=-1,a=(a<<6)+b[i];
                ans+=ty*MA[find(a)];
			}
		}
		if(a[i].exi(ca2,n-1)){
			//puts("orz2");++cnt;
			int b[6],B=a[i].a;rep(i,1,5)b[i]=B&63,B>>=6;
			rep(mask,0,31){
                int a=0;rep(i,1,5)if(mask&1<<i-1)a=(a<<6)+b[i];
                MA[find(a)]++;
			}
		}
	}fm=C[52-(2*n-1)][10-(2*n-1)]*C[10-(2*n-1)][5-n];
	gd=gcd(fm,ans);ans/=gd;fm/=gd;
	printf("%lld/%lld\n",ans,fm);
	//printf("%d\n",clock());
	//printf("%d\n",moyue);
	return 0;
}
