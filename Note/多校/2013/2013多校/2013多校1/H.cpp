#include <string.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
const int MAXN=100010;
const int INF=0x3f3f3f3f;
struct Node
{
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int dep[MAXN];
void dfs(int u)
{
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(dep[v]!=-1)continue;
        dep[v] = dep[u]+1;
        dfs(v);
    }
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int main()
{
    int n,m;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        int u,v,w;
        init();
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        memset(dep,-1,sizeof(dep));
        dep[1] = 0;
        dfs(1);
        int Max = 0;
        int k = 1;
        for(int i = 2;i <= n;i++)
            if(Max < dep[i])
        {
            k = i;
            Max = dep[i];
        }
        memset(dep,-1,sizeof(dep));
        dep[k] = 0;
        dfs(k);
        for(int i = 2;i <= n;i++)
            if(Max < dep[i])
        {
            Max = dep[i];
        }
        while(m--)
        {
            scanf("%d",&u);
            if(u <= Max+1)printf("%d\n",u-1);
            else printf("%d\n", Max+2*(u-Max-1));
        }
    }
    return 0;
}
