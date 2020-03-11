#include <cstdio>
const int N=6e4+10;
int head[N],to[N<<1],Next[N<<1],cnt;
void add(int u,int v)
{
    to[++cnt]=v,Next[cnt]=head[u],head[u]=cnt;
}
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
const int inf=0x3f3f3f3f;
int n,m,dp[N][2],dfn[N],low[N],dfsclock,fa[N];
void cal(int rt,int now)
{
    int t=now,s0=0,s1=0;
    while(now!=rt)
    {
        int tmp=s0;
        s0=max(s0,s1)+dp[now][0];
        s1=tmp+max(dp[now][1],dp[now][0]);
        now=fa[now];
    }
    dp[rt][0]+=max(s0,s1);
    s0=-inf,s1=0,now=t;
    while(now!=rt)
    {
        int tmp=s0;
        s0=max(s0,s1)+dp[now][0];
        s1=tmp+max(dp[now][1],dp[now][0]);
        now=fa[now];
    }
    dp[rt][1]+=s0;
}
void dfs(int now)
{
    dp[now][1]=1;
    dfn[now]=low[now]=++dfsclock;
    for(int v,i=head[now];i;i=Next[i])
        if((v=to[i])!=fa[now])
        {
            if(!dfn[v]) fa[v]=now,dfs(v),low[now]=min(low[now],low[v]);
            else low[now]=min(low[now],dfn[v]);
            if(dfn[now]<low[v])//正常树边
                dp[now][0]+=max(dp[v][0],dp[v][1]),dp[now][1]+=dp[v][0];
        }
    for(int v,i=head[now];i;i=Next[i])
        if(fa[v=to[i]]!=now&&dfn[v]>dfn[now])
            cal(now,v);
}
int main()
{


#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    scanf("%d%d",&n,&m);
    for(int u,v,i=1;i<=m;i++) scanf("%d%d",&u,&v),add(u,v),add(v,u);
    dfs(1);
    printf("%d\n",max(dp[1][0],dp[1][1]));
    return 0;
}
