#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000;
struct node{
    int v;
    node* next;
} Edge[4*MAXN+10], *adj[MAXN+10], *ecnt = Edge;

int n, m;
int A[2*MAXN+10], Q[2*MAXN+10], sum[MAXN+10];
int ans, num, f[MAXN+10], fa[MAXN+10], low[MAXN+10], dfn[MAXN+10];

inline void addedge(int u, int v)
{
    node* p = ++ecnt;
    p->v = v; p->next = adj[u]; adj[u] = p;
}

void dp(int rt, int ed)
{
    int n = sum[ed] - sum[rt] + 1;
    for (int i = ed; i != rt; i = fa[i])
    {
        A[n--] = f[i];
    }
    A[n] = f[rt]; n = sum[ed] - sum[rt] + 1;
    //expand
    for (int i=n+1; i<=n+n; i++)
        A[i] = A[i-n];
    int l = 1, r = 1;
    Q[l] = 1;
    for (int i = 2; i<=n + n/2; i++)
    {
        while (l <= r && Q[l] < i - n/2)
            l++;
        ans = max(ans, A[Q[l]] + A[i] + i - Q[l]);
        while (l <= r && A[Q[r]] - Q[r] <= A[i] - i)
            r--;
        Q[++r] = i;
    }
    for (int i=2; i<=n; i++)
    {
        f[rt] = max(f[rt], A[i] + min(i-1, n-i+1));
    }
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++num;
    for (node* p = adj[u]; p; p = p->next)
    {
        int v = p->v;
        if (v != fa[u])
        {
            if (!dfn[v])
            {
                fa[v] = u;
                sum[v] = sum[u] + 1;
                tarjan(v);
            }
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v])
            {
                ans = max(ans, f[u] + f[v] + 1);
                f[u] = max(f[u], f[v] + 1);
            }

        }
    }
    for (node* p = adj[u]; p; p = p->next)
    {
        int v = p->v;
        if (fa[v] != u && dfn[u] < dfn[v])
        {
            dp(u, v);
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif

    int k;
    scanf("%d%d", &n, &m);
    for (int i=1; i<=m; i++)
    {
        scanf("%d", &k);
        for (int j=1; j<=k; j++)
            scanf("%d", &A[j]);
        for (int j=2; j<=k; j++)
            addedge(A[j], A[j-1]), addedge(A[j-1], A[j]);
    }
    tarjan(1);
    printf("%d\n", ans);
}
