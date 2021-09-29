#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <ctime>
#include <map>
#include <queue>
#include <set>
using namespace std;
 
const int maxn=50000+15;
int n,m;
vector <int> edge[maxn];
bool vis[maxn];
int fa[maxn],u[maxn];
double rat[maxn],b[maxn],sumb[maxn];
int dfs(int now)
{
    vis[now]=true;
    rat[now]=edge[now].size();
    for (int i=0;i<edge[now].size();i++)
     if (!vis[edge[now][i]])
      {
        fa[edge[now][i]]=now;
        dfs(edge[now][i]);
        rat[now]-=rat[edge[now][i]];
      }
    rat[now]=1/rat[now];
    return 0;
}
int change(int x,int w)
{
    u[x]-=w;
    u[fa[x]]+=w;
    for (;x;x=fa[x])
    {
        sumb[fa[x]]-=b[x];
        b[x]=(sumb[x]+u[x])*rat[x];
        sumb[fa[x]]+=b[x];
    }
    return 0;
}
double solve(int x)
{
    if (!x) return 0;
    return solve(fa[x])*rat[x]+b[x];
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    for (int i=1;i<=n;i++)
     if (edge[i].size()==1)
      if (edge[0].size()) edge[i].push_back(i);
       else edge[i].push_back(0),edge[0].push_back(i);
    dfs(0);
    while (m--)
    {
        char st[5];
        scanf("%s",st);
        if (st[0]=='C')
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            if (fa[u]==v) change(u,w);
             else change(v,-w);
        }
        else
        if (st[0]=='Q')
        {
            int x;
            scanf("%d",&x);
            printf("%.10lf ",solve(x));
        }
    }
    printf("\n");
    return 0;
}
