//Í·ÎÄ¼þ{{{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<complex>
#include<tr1/unordered_set>
#include<tr1/unordered_map>
using namespace std;
using namespace tr1;

const int inf=0x0f0f0f0f;

#define uset unordered_set
#define umap unordered_map
#define pqueue priority_queue

typedef long long ll;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef complex<double> point;

typedef vector<int> vint;

#define PB push_back

template<class S,class T> inline pair<S,T> MP(S a,T b){return make_pair(a,b);}
template<class S,class T> inline S& LX(pair<S,T> &X){return X.first;}
template<class S,class T> inline const S& LX(const pair<S,T> &X){return X.first;}
template<class S,class T> inline T& RX(pair<S,T> &X){return X.second;}
template<class S,class T> inline const T& RX(const pair<S,T> &X){return X.second;}

template<class T> inline void RST(T &a){memset(a,0,sizeof(a));}
template<class T> inline void RST1(T &a){memset(a,-1,sizeof(a));}
template<class T> inline void SINF(T &a){memset(a,0x0f,sizeof(a));}
template<class S,class T> inline void RST(S &a,T b){fill((T*)a,(T*)a+(sizeof(a)/sizeof(b)),b);}
template<class T> inline void CLR(T &a){a.clear();}
template<class S,class T> inline void CPY(S &a,T &b){memcpy(a,b,sizeof(a));}
template<class S,class T> inline bool chkmin(S &a,T b){return b<a?a=b,1:0;}
template<class S,class T> inline bool chkmax(S &a,T b){return a<b?a=b,1:0;}
template<class T> inline T sqr(T x){return x*x;}
template<class T> inline int SZ(T &a){return (int)(a.size());}
template<class T> inline bool EPT(T &a){return a.empty();}
//}}}
const ll oo=1e13;
inline int bit(int x)
{
    return x?31-__builtin_clz(x):-1;
}
struct Tnode
{
    int low,high,dx;
    ll ly,ry,dy;
    char i;
    Tnode *l,*r,*tl,*tr,*prev,*succ;
    Tnode();
};
Tnode *tp;
Tnode::Tnode():r(tp){tp=this;}
inline Tnode* newnode()
{
    if(!tp)new Tnode[10000];
    Tnode *ret=tp;
    return tp=tp->r,/*memset(ret,0,sizeof(Tnode)),*/ret->l=ret->r=ret->prev=ret->succ=0,ret;
}
const int base=100000000;
inline Tnode* getnew(int x,ll y)
{
    x+=base;
    Tnode *ret=newnode();
    return ret->low=ret->high=x,ret->ly=ret->ry=y,ret->dx=1,ret->dy=oo,ret->i=-1,ret->tl=ret->tr=ret,ret;
}
inline Tnode* getnew(Tnode *a,Tnode *b)
{
    if(!a||!b)return a?a:b;
    Tnode *ret=newnode();
    return a->tr->succ=b->tl,b->tl->prev=a->tr,a->tr->dx=b->low-a->high,a->tr->dy=b->ly-a->ry,ret->low=a->low,ret->high=b->high,ret->ly=a->ly,ret->ry=b->ry,ret->i=bit(ret->low^ret->high),ret->l=a,ret->r=b,ret->tl=a->tl,ret->tr=b->tr,ret;
}
inline void drop(Tnode *R)
{
    if(R->l)
        R->l->tr->succ=R->r->tl->prev=0,R->l->tr->dx=1,R->l->tr->dy=oo,R->l->ry+=R->ly-R->l->ly,R->l->ly=R->ly,R->r->ly+=R->ry-R->r->ry,R->r->ry=R->ry;
    R->r=tp,tp=R;
}
inline Tnode* erase(Tnode *R,int x)
{
    if(R->i==-1)return drop(R),(Tnode*)0;
    Tnode *p=R->l,*q=R->r;
    int i=R->i;
    drop(R);
    return ~x&(1<<i)?getnew(erase(p,x),q):getnew(p,erase(q,x));
}
inline ll cross(ll ax,ll ay,ll bx,ll by)
{
    return ax*by-ay*bx;
}
inline Tnode* do_merge(Tnode *a,Tnode *b)
{
    for(;;)
    {
        bool t=1;
        while(a->i!=-1)
            if(cross(a->tr->prev->dx,a->tr->prev->dy,a->tr->prev->dx+b->low-a->high,a->tr->prev->dy+b->ly-a->ry)<=0)a=erase(a,a->high),t=0;
            else break;
        while(b->i!=-1)
            if(cross(b->low-a->high,b->ly-a->ry,b->tl->dx+b->low-a->high,b->tl->dy+b->ly-a->ry)<=0)b=erase(b,b->low),t=0;
            else break;
        if(t)break;
    }
    return getnew(a,b);
}
Tnode* merge(Tnode *a,Tnode *b)
{
    if(!a||!b)return a?a:b;
    if(a->i==-1&&b->i==-1&&a->low==b->low)
        if(a->ly<b->ly)return drop(b),a;
        else return drop(a),b;
    if(a->low>b->low)swap(a,b);
    int I=bit(a->low^max(a->high,b->high));
    if(I!=a->i&&I!=b->i)return do_merge(a,b);
    Tnode *p,*q,*x,*y;
    if(a->i==b->i)return p=a->l,q=a->r,x=b->l,y=b->r,drop(a),drop(b),do_merge(merge(p,x),merge(q,y));
    if(a->i<b->i)swap(a,b);
    x=a->l,y=a->r;
    drop(a);
    return ~b->low&(1<<I)?do_merge(merge(b,x),y):do_merge(x,merge(b,y));
}
inline int getint()
{
    int ret=0;bool ok=0,neg=0;
    for(;;)
    {
        int c=getchar();
        if(c>='0'&&c<='9')ret=(ret<<3)+ret+ret+c-'0',ok=1;
        else if(ok)return neg?-ret:ret;
        else if(c=='-')neg=1;
    }
}
const double eps=1e-9;
ll mindot(Tnode *R,ll a,ll b)
{
    if(R->i==-1)return a*R->low+b*R->ly;
    if((double)R->l->tr->dy/R->l->tr->dx+eps>=(double)-a/b)return b*(R->ly-R->l->ly)+mindot(R->l,a,b);
    else return b*(R->ry-R->r->ry)+mindot(R->r,a,b);
}
const int maxn=1200010;
int n;
struct edge
{
    int v;
    edge *n;
};
edge EPool[maxn*2],*ep=EPool,*g[maxn];
inline void addedge(int u,int v)
{
    ep->v=v,ep->n=g[u],g[u]=ep++;
}
int w[maxn];
ll sw[maxn];
ll dp[maxn];
Tnode *dp2[maxn];
void dfs(int u,int fa)
{
    sw[u]=sw[fa]+w[u];
    ll x=0;
    for(edge *i=g[u];i;i=i->n)if(i->v!=fa)dfs(i->v,u),x+=dp[i->v];
    dp2[u]=getnew(sw[u],x+sqr(sw[u]));
    for(edge *i=g[u];i;i=i->n)if(i->v!=fa)
    {
        int v=i->v;
        ll t=x-dp[v];
        dp2[v]->ly+=t,dp2[v]->ry+=t;
        dp2[u]=merge(dp2[u],dp2[v]);
    }
    dp[u]=sqr(sw[fa])+mindot(dp2[u],-2*sw[fa],1)+2*sw[fa]*base;
}
int main()
{
//  freopen("in.txt","r",stdin);
    n=getint();
    for(int i=1;i<=n;i++)w[i]=getint();
    for(int i=1;i<n;i++)
    {
        int u=getint(),v=getint();
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    printf("%lld\n",dp[1]);
    return 0;
}
