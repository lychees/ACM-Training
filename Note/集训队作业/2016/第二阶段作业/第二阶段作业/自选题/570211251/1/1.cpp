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

const int N=1111,M=111111;
int l,m,n,t,C;
int f[N][N],b[N];
struct zcc{int l,r,v;}a[N];
int main(){
    //ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("L.in","r",stdin);//freopen("L.out","w",stdout);
#endif
    scanf("%d",&C);rep(_,1,C){
        scanf("%d",&n);m=0;
        rep(i,1,n)scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].v),b[++m]=a[i].l,b[++m]=a[i].r;
        sort(b+1,b+1+m);m=unique(b+1,b+1+m)-(b+1);
        rep(i,1,n)a[i].l=lower_bound(b+1,b+1+m,a[i].l)-b,a[i].r=lower_bound(b+1,b+1+m,a[i].r)-b;
        //rep(i,1,n)printf("%d %d %d\n",a[i].l,a[i].r,a[i].v);
        rep(len,1,m)rep(i,1,m-len+1){
            int j=i+len-1,Max=0,mp=0;f[i][j]=inf;
            rep(x,1,n)if(a[x].l>=i&&a[x].r<=j&&a[x].v>=Max)Max=a[x].v,mp=x;
            if(!mp)f[i][j]=0;
            else{
                rep(x,a[mp].l,a[mp].r)MIN(f[i][j],f[i][x-1]+f[x+1][j]+Max);
            }
        }
        //if(_==1){rep(i,0,m)printf("%3d ",b[i]);puts("");
        //rep(i,1,m){printf("%3d ",b[i]);rep(j,1,m)printf("%3d ",f[i][j]);puts("");}}
        printf("%d\n",f[1][m]);
    }
    return 0;
}

