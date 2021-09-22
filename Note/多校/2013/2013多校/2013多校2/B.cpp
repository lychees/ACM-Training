#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MAXN = 200010;//点数
const int MAXM = 2000010;//边数，因为是无向图，所以这个值要*2




struct Edge
{
    int to,next;
    bool cut;//是否是桥标记
    bool cong;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~block
int Index,top;
int block;//边双连通块数
bool Instack[MAXN];
int bridge;//桥的数目

void addedge(int u,int v,bool pp)
{
    edge[tot].to = v;edge[tot].next = head[u];edge[tot].cut=false;
    edge[tot].cong = pp;
    head[u] = tot++;
}

void Tarjan(int u,int pre,bool ff)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if(v == pre && (!ff))continue;
        if( !DFN[v] )
        {
            Tarjan(v,u,edge[i].cong);
            if( Low[u] > Low[v] )Low[u] = Low[v];
            if(Low[v] > DFN[u])
            {
                bridge++;
                edge[i].cut = true;
                edge[i^1].cut = true;
            }
        }
        else if( Instack[v] && Low[u] > DFN[v] )
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u])
    {
        block++;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = block;
        }
        while( v!=u );
    }
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}

int du[MAXN];//缩点后形成树，每个点的度数
vector<int>vec[MAXN];
int dep[MAXN];
void dfs(int u)
{
    for(int i = 0;i < vec[u].size();i++)
    {
        int v = vec[u][i];
        if(dep[v]!=-1)continue;
        dep[v]=dep[u]+1;
        dfs(v);
    }
}
void solve(int n)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    Index = top = block = 0;
    Tarjan(1,0,false);
    for(int i = 1;i <= block;i++)
        vec[i].clear();
    for(int i = 1;i <= n;i++)
       for(int j = head[i];j != -1;j = edge[j].next)
          if(edge[j].cut)
          {
              vec[Belong[i]].push_back(Belong[edge[j].to]);
          }
    memset(dep,-1,sizeof(dep));
    dep[1]=0;
    dfs(1);
    int k = 1;
    for(int i = 1;i <= block;i++)
        if(dep[i]>dep[k])
          k = i;
    memset(dep,-1,sizeof(dep));
    dep[k]=0;
    dfs(k);
    int ans = 0;
    for(int i = 1;i <= block;i++)
        ans = max(ans,dep[i]);
    printf("%d\n",block-1-ans);
}
struct NN
{
    int u,v;
}node[MAXM];
bool cmp(NN a,NN b)
{
    if(a.u != b.u)return a.u<b.u;
    else return a.v<b.v;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int u,v;
    while(scanf("%d%d",&n,&m)==2)
    {
        if(n==0 && m==0)break;
        init();
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d",&u,&v);
            if(u==v)continue;
            if(u>v)swap(u,v);
            node[i].u = u;
            node[i].v = v;
        }
        sort(node,node+m,cmp);
        for(int i = 0;i < m;i++)
        {
            if(i == 0 || (node[i].u!=node[i-1].u || node[i].v != node[i-1].v))
            {
                if(i < m-1 && (node[i].u==node[i+1].u && node[i].v == node[i+1].v))
                {
                    addedge(node[i].u,node[i].v,true);
                    addedge(node[i].v,node[i].u,true);
                }
                else
                {
                    addedge(node[i].u,node[i].v,false);
                    addedge(node[i].v,node[i].u,false);
                }
            }
        }
        solve(n);
    }
    return 0;
}
