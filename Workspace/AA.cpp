#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX 1010000
inline int read()
{
    int x=0;bool t=false;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=true,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return t?-x:x;
}
int n,m;char ch[MAX];
long long ans;
struct Node
{
    int son[26];
    int len,ff;
}t[MAX];
int last=1,tot=1,lt[MAX];
void extend(int c)
{
    int p=last,np=++tot;last=tot;
    t[np].len=t[p].len+1;
    while(p&&!t[p].son[c])t[p].son[c]=np,p=t[p].ff;
    if(!p)t[np].ff=1;
    else
    {
        int q=t[p].son[c];
        if(t[q].len==t[p].len+1)t[np].ff=q;
        else
        {
            int nq=++tot;
            t[nq]=t[q];t[nq].len=t[p].len+1;
            t[q].ff=t[np].ff=nq;
            while(p&&t[p].son[c]==q)t[p].son[c]=nq,p=t[p].ff;
        }
    }
}
struct Line{int v,next;}e[MAX];
int h[MAX],cnt=1;
inline void Add(int u,int v){e[cnt]=(Line){v,h[u]};h[u]=cnt++;}
int dfn[MAX],low[MAX],dep[MAX],fa[MAX],tim,size[MAX],hson[MAX],top[MAX];
void dfs1(int u,int ff)
{
    size[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
    for(int i=h[u];i;i=e[i].next)
    {
        int v=e[i].v;
        dfs1(v,u);size[u]+=size[v];
        if(size[v]>size[hson[u]])hson[u]=v;
    }
}
void dfs2(int u,int tp)
{
    dfn[u]=++tim;top[u]=tp;
    if(hson[u])dfs2(hson[u],tp);
    for(int i=h[u];i;i=e[i].next)
        if(e[i].v!=hson[u])dfs2(e[i].v,e[i].v);
    low[u]=tim;
}
int LCA(int u,int v)
{
    while(top[u]^top[v])(dep[top[u]]<dep[top[v]])?v=fa[top[v]]:u=fa[top[u]];
    return dep[u]<dep[v]?u:v;
}
int p[MAX],S[MAX];
bool vis[MAX];
bool cmp(int a,int b){return dfn[a]<dfn[b];}
int dp(int u)
{
    int ret=0;if(vis[u])ret=1;
    for(int i=h[u];i;i=e[i].next)
    {
        int d=dp(e[i].v);
        ans+=1ll*t[u].len*d*ret;
        ret+=d;
    }
    return ret;
}
int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif

    n=read();m=read();
    scanf("%s",ch+1);reverse(&ch[1],&ch[n+1]);
    for(int i=1;i<=n;++i)extend(ch[i]-97),lt[i]=last;
    for(int i=1;i<=tot;++i)if(t[i].ff)Add(t[i].ff,i);
    dfs1(1,0);dfs2(1,1);memset(h,0,sizeof(h));cnt=1;
    while(m--)
    {
        int t=read(),top=0;cnt=0;
        for(int i=1;i<=t;++i)vis[p[i]=lt[n-read()+1]]=true;
        sort(&p[1],&p[t+1],cmp);
        for(int i=t;i>1;--i)p[++t]=LCA(p[i],p[i-1]);
        sort(&p[1],&p[t+1],cmp);t=unique(&p[1],&p[t+1])-p-1;
        for(int i=1;i<=t;++i)
        {
            while(top&&low[S[top]]<dfn[p[i]])--top;
            Add(S[top],p[i]);S[++top]=p[i];
        }
        ans=0;dp(p[1]);printf("%lld\n",ans);
        for(int i=1;i<=t;++i)h[p[i]]=0,vis[p[i]]=false;
    }
    return 0;
}
