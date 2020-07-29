#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;
namespace Zeonfai
{
    inline int getInt()
    {
        int a = 0, sgn = 1; char c;
        while(! isdigit(c = getchar())) if(c == '-') sgn *= -1;
        while(isdigit(c)) a = a * 10 + c - '0', c = getchar();
        return a * sgn;
    }
}
const int N = (int)1e5, M = (int)2e5, INF = (int)2e9, T = (int)1e5;
int n, m;
int ans[T + 1];
struct edge
{
    int u, v, L, R;
    inline int operator <(const edge &a) const {return L == a.L ? R < a.R : L < a.L;}
}edg[M];
struct linkCutTree
{
    int tp;
    struct node
    {
        int pre, suc[2], isRoot, rev;
        int w, mn, sz;
        inline node() {pre = -1; for(int i = 0; i < 2; ++ i) suc[i] = -1; isRoot = 1; rev = 0; sz = 1;}
    }nd[N + 1 + M];
    inline void initialize()
    {
        for(int i = 1; i <= n; ++ i) nd[i].w = INF, nd[i].mn = i;
        tp = n + 1;
    }
    inline void pushDown(int u)
    {
        if(! nd[u].isRoot) pushDown(nd[u].pre);
        if(nd[u].rev)
        {
            for(int i = 0; i < 2; ++ i) if(~ nd[u].suc[i])
                swap(nd[nd[u].suc[i]].suc[0], nd[nd[u].suc[i]].suc[1]), nd[nd[u].suc[i]].rev ^= 1;
            nd[u].rev = 0;
        }
    }
    inline int getRelation(int u) {return u == nd[nd[u].pre].suc[1];}
    inline void update(int u)
    {
        nd[u].mn = u; nd[u].sz = 1;
        for(int i = 0; i < 2; ++ i) if(~ nd[u].suc[i])
        {
            if(nd[nd[nd[u].suc[i]].mn].w < nd[nd[u].mn].w) nd[u].mn = nd[nd[u].suc[i]].mn;
            nd[u].sz += nd[nd[u].suc[i]].sz;
        }
    }
    inline void rotate(int u)
    {
        int pre = nd[u].pre, prepre = nd[pre].pre, k = getRelation(u);
        nd[pre].suc[k] = nd[u].suc[k ^ 1]; if(~ nd[u].suc[k ^ 1]) nd[nd[u].suc[k ^ 1]].pre = pre;
        nd[u].pre = prepre; if(! nd[pre].isRoot) nd[prepre].suc[getRelation(pre)] = u;
        nd[pre].pre = u; nd[u].suc[k ^ 1] = pre;
        if(nd[pre].isRoot) nd[pre].isRoot = 0, nd[u].isRoot = 1;
        update(pre); update(u);
    }
    inline void splay(int u)
    {
        pushDown(u);
        while(! nd[u].isRoot)
        {
            if(! nd[nd[u].pre].isRoot) rotate(getRelation(u) == getRelation(nd[u].pre) ? nd[u].pre : u);
            rotate(u);
        }
    }
    inline void access(int u)
    {
        splay(u);
        if(~ nd[u].suc[1])
        {
            nd[nd[u].suc[1]].isRoot = 1;
            nd[u].suc[1] = -1; update(u);
        }
        while(~ nd[u].pre)
        {
            int pre = nd[u].pre;
            splay(pre);
            if(~ nd[pre].suc[1])
            {
                nd[nd[pre].suc[1]].isRoot = 1;
                nd[pre].suc[1] = -1; update(pre);
            }
            nd[pre].suc[1] = u; nd[u].isRoot = 0; update(pre);
            splay(u);
        }
    }
    inline void makeRoot(int u)
    {
        access(u); swap(nd[u].suc[0], nd[u].suc[1]); nd[u].rev ^= 1;
    }
    inline int get(int u)
    {
        access(u);
        while(~ nd[u].suc[0]) u = nd[u].suc[0];
        return u;
    }
    inline int newNode(int w) {nd[tp].w = w; nd[tp].mn = tp; return tp ++;}
    inline void link(int id)
    {
        int u = edg[id].u, v = edg[id].v;
        if(get(u) == get(v))
        {
            makeRoot(u); access(v);
            int x = nd[v].mn;

            cout << nd[x].w << endl;

            if(nd[x].w > edg[id].L && nd[v].sz + 1 >> 1 & 1) for(int i = edg[id].L + 1; i <= min(nd[x].w, edg[id].R); ++ i) ans[i] = 1;



            if(nd[x].w > edg[id].R) return;
            access(x); nd[nd[x].suc[0]].pre = -1; nd[nd[x].suc[0]].isRoot = 1; nd[x].suc[0] = -1;
            makeRoot(v); access(x); nd[nd[x].suc[0]].pre = -1; nd[nd[x].suc[0]].isRoot = 1; nd[x].suc[0] = -1;
        }
        makeRoot(u); makeRoot(v);
        int x = newNode(edg[id].R); nd[x].pre = u; nd[v].pre = x;
        return;
    }
}LCT;
int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif


    using namespace Zeonfai;
    n = getInt(), m = getInt(); int T = getInt();
    LCT.initialize();
    for(int i = 0; i < m; ++ i) edg[i].u = getInt(), edg[i].v = getInt(), edg[i].L = getInt(), edg[i].R = getInt();
    sort(edg, edg + m);
    for(int i = 0; i < m; ++ i) LCT.link(i);
    for(int i = 1; i <= T; ++ i) puts(! ans[i] ? "Yes" : "No");
}
