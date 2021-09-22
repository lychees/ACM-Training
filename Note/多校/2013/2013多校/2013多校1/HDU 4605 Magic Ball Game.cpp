#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;




const int MAXN = 400010;
int next[MAXN][2];
int n;
int root;
int w[MAXN];
struct QQ
{
    int v;
    int X;
    int ans1,ans2;
}Query[MAXN];
vector<int>vec[MAXN];
bool used[MAXN];
int a[MAXN];
map<int,int>mp;

int c1[MAXN];
int c2[MAXN];
int t;
int lowbit(int x)
{
    return x&(-x);
}
void add1(int i,int val)
{
    while(i <= t)
    {
        c1[i] += val;
        i += lowbit(i);
    }
}
int sum1(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += c1[i];
        i -= lowbit(i);
    }
    return s;
}
void add2(int i,int val)
{
    while(i <= t)
    {
        c2[i] += val;
        i += lowbit(i);
    }
}
int sum2(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += c2[i];
        i -= lowbit(i);
    }
    return s;
}

void dfs(int u)
{
    int sz = vec[u].size();
    for(int i = 0;i < sz;i++)
    {
        int id = vec[u][i];
        int X = mp[Query[id].X];
        if(sum1(X)-sum1(X-1)!=0 || sum2(X)-sum2(X-1)!=0)
        {
            Query[id].ans1 = Query[id].ans2 = -1;
        }
        else
        {
            Query[id].ans1 = Query[id].ans2 = 0;
            Query[id].ans2 += 3*sum1(X-1)+sum1(t)-sum1(X);
            Query[id].ans1 += sum2(X-1);
            Query[id].ans2 += 3*sum2(X-1)+sum2(t)-sum2(X);
        }
    }
    if(next[u][0]==0 && next[u][1]==0)return;
    add1(mp[w[u]],1);
    dfs(next[u][0]);
    add1(mp[w[u]],-1);
    add2(mp[w[u]],1);
    dfs(next[u][1]);
    add2(mp[w[u]],-1);
}



int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int m;
    int u,x,y;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
        {
            used[i] = false;
            next[i][0] = next[i][1] = 0;
            vec[i].clear();
        }
        t = 0;
        for(int i = 1;i <= n;i++)
        {
            scanf("%d",&w[i]);
            a[t++] = w[i];
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d%d",&u,&x,&y);
            used[x] = true;
            used[y] = true;
            next[u][0] = x;
            next[u][1] = y;
        }
        scanf("%d",&m);
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d",&u,&x);
            Query[i].v = u;
            Query[i].X = x;
            a[t++] = x;
            vec[u].push_back(i);
        }
        for(int i = 1;i <= n;i++)
            if(!used[i])
            {
                root = i;
                break;
            }
        sort(a,a+t);
        t = unique(a,a+t)-a;
        mp.clear();
        for(int i = 0;i < t;i++)
            mp[a[i]]=i+1;
        memset(c1,0,sizeof(c1));
        memset(c2,0,sizeof(c2));
        dfs(root);
        for(int i = 0;i < m;i++)
        {
            if(Query[i].ans1 == -1)
                printf("0\n");
            else printf("%d %d\n",Query[i].ans1,Query[i].ans2);
        }
    }
    return 0;
}



