#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MaxN = 3010, MaxM = 9010, mod = 1000000007, base = 2333;
int hash[MaxN];
int N, M;
bool mark[MaxM], vis[MaxN];
int En[MaxN], Next[MaxM], Point[MaxM], tot, ind[MaxM];
 
inline int C2(int x) { return x * (x - 1) >> 1; }
 
void Add(int x, int y, int z) {
    Next[++tot] = En[x];
    En[x] = tot;
    Point[tot] = y;
    ind[tot] = z;
}
 
int dfs_size(int now) {
    vis[now] = 1;
    int ret = 1;
    for (int i = En[now]; i; i = Next[i])
        if (!vis[Point[i]]) ret += dfs_size(Point[i]);
    return ret;
}
 
int low[MaxN], dfn[MaxN], bcnt[MaxN], btot, dcnt;
int stack[MaxN], stot;
 
void dfs(int now, int father) {
    stack[++stot] = now;
    dfn[now] = low[now] = ++dcnt;
    for (int i = En[now]; i; i = Next[i]) {
        if (mark[ind[i]]) continue;
        if (!dfn[Point[i]]) {
            dfs(Point[i], i ^ 1);
            low[now] = min(low[now], low[Point[i]]);
        } else if (i != father) low[now] = min(low[now], dfn[Point[i]]);
    }
    if (low[now] == dfn[now]) {
        int x;
        ++btot;
        do {
            x = stack[stot--];
            bcnt[x] = btot;
        } while (x != now);
    }
}
 
void tarjan() {
    memset(low, 0, sizeof low);
    memset(dfn, 0, sizeof dfn);
    btot = dcnt = stot = 0;
    for (int i = 1; i <= N; ++i)
        if (!dfn[i]) dfs(i, 0);
    for (int i = 1; i <= N; ++i) hash[i] = (1ll * hash[i] * base + bcnt[i]) % mod;
}
 
int main()
{
    tot = 1;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        Add(u, v, i);
        Add(v, u, i);
    }
    int ans = 0;
    // flow >= 1
    for (int i = 1; i <= N; ++i) 
        if (!vis[i]) {
            int size = dfs_size(i);
            ans += C2(size);
        }
    // flow >= 2
    tarjan();
    static int H[MaxN];
    memcpy(H, hash, sizeof hash);
    sort(H + 1, H + N + 1);
    for (int i = 1; i <= N; ++i) {
        int j = i;
        while (j < N && H[j + 1] == H[i]) ++j;
        ans += C2(j - i + 1);
        i = j;
    }
    // flow >= 3
    for (int i = 1; i <= M; ++i) {
        mark[i] = 1;
        tarjan();
        mark[i] = 0;
    }
    memcpy(H, hash, sizeof hash);
    sort(H + 1, H + N + 1);
    for (int i = 1; i <= N; ++i) {
        int j = i;
        while (j < N && H[j + 1] == H[i]) ++j;
        ans += C2(j - i + 1);
        i = j;
    }
 
    cout << ans << endl;
    return 0;
}
