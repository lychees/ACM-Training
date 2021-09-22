#include<cstdio>
#include<algorithm>
#include<set>
#include<cstring>

#define MAXX 100111
#define MAXN (MAXX*3)
#define inf 0xc0c0c0c0

int pre[MAXN],fa[MAXN],nxt[MAXN][2];
int max[MAXN],val[MAXN];
std::multiset<int>set[MAXN];

#define lson nxt[id][0]
#define rson nxt[id][1]

inline void checkmax(int &a,int b)
{
    a=std::max(a,b);
}

inline void up(int id)
{
    max[id]=std::max(std::max(val[id],*set[id].rbegin()),std::max(max[lson],max[rson]));
}

inline void rot(int id,int tp)
{
    static int k;
    k=pre[id];
    nxt[k][tp^1]=nxt[id][tp];
    if(nxt[id][tp])
        pre[nxt[id][tp]]=k;
    if(pre[k])
        nxt[pre[k]][k==nxt[pre[k]][1]]=id;
    pre[id]=pre[k];
    nxt[id][tp]=k;
    pre[k]=id;
    up(k);
}

inline void splay(int id)
{
    if(pre[id]) {
        static int rt;
        for(rt=pre[id]; pre[rt]; rt=pre[rt]);
        for(std::swap(fa[rt],fa[id]); pre[id]; rot(id,id==nxt[pre[id]][0]));
        up(id);
    }
}

inline int access(int id)
{
    static int to;
    for(to=0; id; id=fa[id]) {
        splay(id);
        if(rson) {
            fa[rson]=id;
            pre[rson]=0;
            set[id].insert(max[rson]);
        }
        rson=to;
        if(to) {
            fa[to]=0;
            pre[to]=id;
            set[id].erase(set[id].find(max[to]));
        }
        up(to=id);
    }
    return to;
}

int edge[MAXX],nxte[MAXX<<1],to[MAXX<<1],cnt;
int cl[MAXX];

int n;
int i,j,k;
int fat[MAXX];
void init()
{
    memset(pre,0,sizeof(pre));
    memset(fa,0,sizeof(fa));
    memset(nxt,0,sizeof(nxt));
    memset(edge,0,sizeof(edge));
    memset(nxte,0,sizeof(nxte));
    memset(to,0,sizeof(to));
    memset(cl,0,sizeof(cl));
    memset(fat,0,sizeof(fat));
    cnt = 0;
}
void make(int now,int f)
{
    fat[now]=f;
    for(int i(edge[now]); i; i=nxte[i])
        if(to[i]!=f)
            make(to[i],now);
    up(now+n);
    up(now+2*n);
    fa[j=now+(1+cl[now])*n]=now;
    set[now].insert(*set[j].rbegin());
    up(now);

    fa[now]=j=(f+(1+cl[now])*n);
    set[j].insert(max[now]);
}

inline void cut(int a,int b)
{
    access(b);
    splay(b);
    splay(a);
    set[b].erase(set[b].find(max[a]));
    fa[a]=0;
    up(b);
}

inline void link(int a,int b)
{
    access(b);
    splay(b);
    splay(a);
    fa[a]=b;
    set[b].insert(max[a]);
    up(b);
}

int q;

int main()
{
    max[0]=val[0]=inf;
   // freopen("in.txt", "r", stdin);
   // freopen("out.t", "w", stdout);
    while(~scanf("%d",&n)) {
        init();
        for (i = 0; i <= n; ++i) set[i].clear();
        for(i=1; i<n; ++i) {
            scanf("%d %d",&j,&k);
            nxte[++cnt]=edge[j];
            edge[j]=cnt;
            to[cnt]=k;

            nxte[++cnt]=edge[k];
            edge[k]=cnt;
            to[cnt]=j;
        }
        for(i=1; i<=n; ++i)
            scanf("%d",cl+i);
        ++n;
        j=n*3;
        for(i=1; i<=j; ++i) {
            set[i].insert(inf);
            val[i]=inf;
        }
        for(i=1; i<n; ++i)
            scanf("%d",val+i);
        make(1,n);
        /*
        for(i=1;i<=n*3;++i)
            printf("%d %d\n",i,*set[i].rbegin());
        puts("");
        */
        scanf("%d",&q);
        while(q--) {
            scanf("%d %d",&i,&j);
            switch(i) {
            case 0:
                for(i=access(j); nxt[i][0]; i=nxt[i][0]);
                splay(i);
                printf("%d\n",max[nxt[i][1]]);
                break;
            case 1:
                cut(j,fat[j]+(1+cl[j])*n);
                cut(j+(1+cl[j])*n,j);

                cl[j]^=1;

                link(j+(1+cl[j])*n,j);
                link(j,fat[j]+(1+cl[j])*n);
                break;
            case 2:
                access(j);
                splay(j);
                scanf("%d",val+j);
                up(j);
                break;
            }
        }
    }
    return 0;
}

