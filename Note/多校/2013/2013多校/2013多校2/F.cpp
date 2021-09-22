#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
const int MAXN = 50010;
const long long INF = 1LL<<61;
struct Edge
{
    int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int val[MAXN];
int trap[MAXN];
long long ans,dp[MAXN][4][2];
int N,C;
void dfs(int u,int pre)
{
    dp[u][trap[u]][trap[u]] = val[u];
    for(int i = head[u];i!=-1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)continue;
        dfs(v,u);
        for(int j = 0;j <= C;j++)
            for(int k = 0;k+j <= C;k++)
            {
                if(k+j < C)
                    ans = max(ans,dp[u][j][0] + dp[v][k][0]);
                if(j != C)ans = max(ans,dp[u][j][0] + dp[v][k][1]);
                if(k != C)ans = max(ans,dp[u][j][1] + dp[v][k][0]);
            }
        for(int j = 0;j < C;j++)
        {
            dp[u][j+trap[u]][0] = max(dp[u][j+trap[u]][0],dp[v][j][0]+val[u]);
            dp[u][j+trap[u]][1] = max(dp[u][j+trap[u]][1],dp[v][j][1]+val[u]);
        }
        if(!trap[u])
            dp[u][C][1] = max(dp[u][C][1],dp[v][C][1]+val[u]);

    }

}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);

    while(T--)
    {
        scanf("%d%d",&N,&C);
        init();
        for(int i = 0;i < N;i++)
        {
            scanf("%d%d",&val[i],&trap[i]);
        }
        int u,v;
        for(int i = 0;i < N-1;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        ans = 0;
        for(int i = 0;i < N;i++)
            for(int j = 0;j < 4;j++)
                for(int k = 0;k < 2;k++)
                  dp[i][j][k] = -INF;
        dfs(0,-1);
        printf("%I64d\n",ans);
    }
    return 0;
}







