#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<cmath>
using namespace std;

typedef long long LL;
const int SZ = 100010;
const int INF = 1000000010;

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    //fread->read
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
            //{printf("IO error!\n");system("pause");for (;;);exit(0);}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline int read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return 0;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
        return 1;
    }
    inline int read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return 0;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
        return 1;
    }
    inline int read(double &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return 0;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (ch=='.'){
            double tmp=1; ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
        }
        if (sign)x=-x;
        return 1;
    }
    inline int read(char *s){
        char ch=nc();
        for (;blank(ch);ch=nc());
        if (IOerror)return 0;
        for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
        *s=0;
        return 1;
    }
    inline void read(char &c){
        for (c=nc();blank(c);c=nc());
        if (IOerror){c=-1;return;}
    }
    //fwrite->write
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(double x,int y){
            static ll mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
                1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
                100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
            if (x<-1e-12)out('-'),x=-x;x*=mul[y];
            ll x1=(ll)floor(x); if (x-floor(x)>=0.5)++x1;
            ll x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
            if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
        }
        void println(double x,int y){print(x,y);out('\n');}
        void print(char *s){while (*s)out(*s++);}
        void println(char *s){while (*s)out(*s++);out('\n');}
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    inline void println(int x){Ostream.println(x);}
    inline void print(char x){Ostream.out(x);}
    inline void println(char x){Ostream.out(x);Ostream.out('\n');}
    inline void print(ll x){Ostream.print(x);}
    inline void println(ll x){Ostream.println(x);}
    inline void print(double x,int y){Ostream.print(x,y);}
    inline void println(double x,int y){Ostream.println(x,y);}
    inline void print(char *s){Ostream.print(s);}
    inline void println(char *s){Ostream.println(s);}
    inline void println(){Ostream.out('\n');}
    inline void flush(){Ostream.flush();}
};
using namespace fastIO;



int n,m,head[SZ],nxt[SZ  * 2],tot = 1;

struct edge
{
    int t,id;
}l[SZ * 2];

void build(int f,int t,int id)
{
    l[++ tot] = (edge){t,id};
    nxt[tot] = head[f];
    head[f] = tot;
}

int bcnt = 0,bri[SZ];
int dfn[SZ],low[SZ],dfs_clock1 = 0;

void tarjan(int u,int fa)
{
    dfn[u] = low[u]= ++ dfs_clock1;
    for(int i = head[u];i;i = nxt[i])
    {
        int v = l[i].t;
        if(fa == v) continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v] > dfn[u]) bcnt ++,bri[l[i].id] = 1;
        }
        else if(dfn[v] < dfn[u])
        {
            low[u] = min(low[u],dfn[v]);
        }
    }
}

int c[SZ],ccnt;

void dfs(int u,int color)
{
    c[u] = color;
    for(int i = head[u];i;i = nxt[i])
    {
        int v = l[i].t;
        if(!bri[l[i].id] && !c[v])
        {
            dfs(v,color);
        }
    }
}


int deep[SZ],inseg[SZ],intre[SZ];
int sz[SZ],top[SZ],son[SZ],fa[SZ];
void dfs_1(int u,int f)
{
    fa[u] = f;
    deep[u] = deep[f] + 1;
    sz[u] = 1;
    for(int i = head[u];i;i = nxt[i])
    {
        int v = l[i].t;
        if(v == f) continue;
        dfs_1(v,u);
        sz[u] += sz[v];
        if(!son[u] || sz[son[u]] < sz[v]) son[u] = v;
    }
}
int dfs_clock = 0;
void dfs_2(int u,int topu)
{
    top[u] = topu;
    inseg[u] = ++ dfs_clock;
    intre[dfs_clock] = u;
    if(!son[u]) return ;
    dfs_2(son[u],topu);
    for(int i = head[u];i;i = nxt[i])
    {
        int v = l[i].t;
        if(v == fa[u] || v == son[u]) continue;
        dfs_2(v,v);
    }
}

int Fa[SZ];
int find(int x) { return x == Fa[x] ? x : Fa[x] = find(Fa[x]); }

int bits[SZ];

void add(int x,int d)
{
    for(int i = x;i <= ccnt;i += i & -i)
        bits[i] += d;
}

int ask(int x)
{
    int ans = 0;
    for(int i = x;i > 0;i -= i & -i)
        ans += bits[i];
    return ans;
}

void merge(int l,int r)
{
//    printf("%d %d\n",l,r);
//    for(int i = l;i <= r;i ++) add(i,-1);
    while(find(r) != find(l - 1))
    {
        add(find(r),-1);
        Fa[find(r)] = Fa[find(r) - 1];
    }
}

int ask_sum(int x,int y)
{
    int fx = top[x],fy = top[y],ans = 0;
    while(fx != fy)
    {
    //    puts("233");
        if(deep[fx] < deep[fy]) swap(fx,fy),swap(x,y);
        ans += ask(inseg[x]) - ask(inseg[fx] - 1);
        x = fa[fx],fx = top[x];
    }
    if(x != y) //若是把边权放到点上，则有这一句
    {
        if(deep[x] > deep[y]) swap(x,y);
        ans += ask(inseg[y]) - ask(inseg[x] + 1 - 1); //若边权，则要+1
    }
    return ans;
}
void change(int x,int y)
{
    int fx = top[x],fy = top[y];
    while(fx != fy)
    {
        if(deep[fx] < deep[fy]) swap(fx,fy),swap(x,y);
        merge(inseg[fx],inseg[x]);
        x = fa[fx],fx = top[x];
    }
    if(x != y)
    {
        if(deep[x] > deep[y]) swap(x,y);
        merge(inseg[x] + 1,inseg[y]);
    }
}

int ff[SZ],tt[SZ];

void init()
{
    tot = 1; memset(head,0,sizeof(head));
    memset(bits,0,sizeof(bits));
    memset(son,0,sizeof(son));
    memset(bri,0,sizeof(bri));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(c,0,sizeof(c));
    dfs_clock = dfs_clock1 = ccnt = bcnt = 0;
}

int main()
{
    int T,cc = 0; read(T);
    while(T --)
    {
        init();
        read(n),read(m);
        for(int i = 1;i <= m;i ++)
        {
            read(ff[i]),read(tt[i]);
            build(ff[i],tt[i],i); build(tt[i],ff[i],i);
        }
        for(int i = 1;i <= n;i ++)
            if(!dfn[i])
                tarjan(i,0);
        ccnt = 0;
        for(int i = 1;i <= n;i ++)
            if(!c[i])
                dfs(i,++ ccnt);
        tot = 1; memset(head,0,sizeof(head));
        for(int i = 1;i <= m;i ++)
            if(c[ff[i]] != c[tt[i]])
            {
                int x = c[ff[i]],y = c[tt[i]];
                build(x,y,i); build(y,x,i);
            }
        dfs_1(1,0); dfs_2(1,1);
        for(int i = 0;i <= ccnt;i ++) Fa[i] = i;
        for(int i = 2;i <= ccnt;i ++) add(i,1);

    //    for(int i = 1;i <= n;i ++) printf("%d ",c[i]); puts("");
    //    for(int i = 1;i <= ccnt;i ++) printf("%d ",inseg[i]); puts("");

        int q; read(q);
        print("Case #");print(++ cc);println(':');
        for(int i = 1;i <= q;i ++)
        {
            int opt,x,y;
            read(opt),read(x),read(y);
            x = c[x]; y = c[y];
            if(opt == 1)
                change(x,y);
            else
                println(ask_sum(x,y));
        }
    }
    return 0;
}
