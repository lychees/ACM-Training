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

const int N=211111,M=5111111;
int l,m,n,t,C,q;
int b[N];
struct zcc{int l,r,v;}a[N];
vector<int>E[N];
inline bool cmpv(const zcc &a,const zcc &b){return a.v<b.v;}
queue<int>Q;
int pt[N],ans[N];

namespace pre{
struct lct{
    ll m,d;int sz,rev,x;lct *f,*c[2];
    int dir(){return f->c[1]==this;}
    int isr(){return !f||f->c[0]!=this&&f->c[1]!=this;}
    void sc(lct* x,int d){if(x)x->f=this;c[d]=x;}
    void upd(){sz=1;m=d;if(c[0])sz+=c[0]->sz,MAX(m,c[0]->m);if(c[1])sz+=c[1]->sz,MAX(m,c[1]->m);}
    void push(){if(rev)swap(c[0],c[1]);if(c[0])c[0]->rev^=rev;if(c[1])c[1]->rev^=rev;rev=0;}
}nd[N];
stack<lct*>S;
void rot(lct* x){
    lct *y=x->f;int d=x->dir();
    if(y->isr())x->f=y->f;else y->f->sc(x,y->dir());
    y->sc(x->c[!d],d);x->sc(y,!d);y->upd();
}
void splay(lct *x){
    for(lct *p=x,*q=NULL;!(q&&q->isr());q=p,p=p->f)S.push(p);
    for(;!S.empty();S.pop())S.top()->push();
    while(!x->isr()){if(!x->f->isr())if(x->dir()==x->f->dir())rot(x->f);else rot(x);rot(x);}x->upd();
}
lct* expose(lct* x){lct* q=NULL;for(;x;x=x->f)splay(x),x->push(),x->c[1]=q,(q=x)->upd();return q;}
void expose(lct* x,lct* y){expose(x);splay(x);x->rev^=1;expose(y);splay(x);}
void merge(lct* x,lct* y){expose(x);splay(x);x->rev^=1;x->f=y;}
void split(lct* x,lct* y){expose(x,y);x->c[1]=y->f=NULL;x->upd();}
lct* rt(lct* x){if(x->isr())return x;return rt(x->f);}
lct* fm(lct* x){
    if(x->d==x->m)return x;if(!x->c[0])return fm(x->c[1]);
    if(x->c[0]->m==x->m)return fm(x->c[0]);return fm(x->c[1]);
}
void pre(){
    rep(i,1,2*n-1)nd[i].d=nd[i].m=nd[i].rev=0,nd[i].sz=1,nd[i].c[0]=nd[i].c[1]=nd[i].f=NULL;
    while(Q.size())Q.pop();rep(i,n+1,2*n-1)Q.push(i);
    dep(i,m,1){
        expose(&nd[a[i].l],&nd[a[i].r]);if(rt(&nd[a[i].r])==&nd[a[i].l]){
            lct* p=fm(&nd[a[i].l]);split(p,&nd[a[pt[p->x]].l]);split(p,&nd[a[pt[p->x]].r]);Q.push(p->x);
            ans[pt[p->x]]=i;
        }int p=Q.front();Q.pop();nd[p].x=p;nd[p].d=nd[p].m=a[i].v;
        merge(&nd[a[i].l],&nd[p]);merge(&nd[a[i].r],&nd[p]);pt[p]=i;
    }
}
}

int tot,root[N];
struct EDGE {int a,b,l,r,s;} e[M];
int creat(int l,int r){
    if(l>r)return 0;e[++tot].a=l;e[tot].b=r;e[tot].s=0;int k=tot;if(l==r)return k;
    e[k].l=creat(l,(l+r)/2);e[k].r=creat((l+r)/2+1,r);return k;
}
int mdf(int root,int x,int y){
    int k=++tot;e[k]=e[root];e[k].s+=y;if(e[root].a==x&&e[root].b==x)return k;
    int mid=(e[root].a+e[root].b)/2;if(x<=mid)e[k].l=mdf(e[root].l,x,y);else e[k].r=mdf(e[root].r,x,y);
    return k;
}
int ask(int x,int y,int t){
    if(e[x].a==e[x].b)return e[x].s-e[y].s;int mid=e[x].a+e[x].b>>1;
    if(t<=mid)return ask(e[x].l,e[y].l,t);return ask(e[x].r,e[y].r,t)+e[e[x].l].s-e[e[y].l].s;
}
int que(int l,int r){return ask(root[r],root[l-1],l-1);}
int main(){
    //ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("J.in","r",stdin);freopen("J.out","w",stdout);
#endif
    read(C);rep(_,1,C){
        read(n,m);rep(i,1,m)read(a[i].l,a[i].r,a[i].v);
        sort(a+1,a+1+m,cmpv);rep(i,1,m)b[i]=a[i].v;tot=0;CLR(ans);
        rep(i,1,n)E[i].clear(),vector<int>(E[i]).swap(E[i]);
        rep(i,1,m){
            E[a[i].l].pb(i);E[a[i].r].pb(i+m);a[i+m]=a[i];swap(a[i+m].l,a[i+m].r);
        }
        pre::pre();
        int lans=0;
        //rep(i,1,m)printf("%d %d %d %d %d\n",i,a[i].l,a[i].r,a[i].v,ans[i]);
        root[0]=creat(0,m);rep(i,1,m)root[i]=mdf(root[i-1],ans[i],a[i].v);
        read(q);while(q--){
            read(l,t);l-=lans;t-=lans;
            printf("%d\n",lans=que(upper_bound(b+1,b+1+m,l-1)-b,upper_bound(b+1,b+1+m,t)-b-1));
        }
    }
    return 0;
}

