#include <set>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define mkp make_pair
#define fir first
#define sec second
using namespace std;
 
const int MaxN = 200010, MC = 1000002;
 
template <int MaxN, int MaxM> class Graph {
public:
    int En[MaxN], Next[MaxM], Point[MaxM], tot;
    void Add(int x, int y) {
        Next[++tot] = En[x];
        En[x] = tot;
        Point[tot] = y;
    }
};
Graph <MaxN << 1, MaxN << 1> Tr, Tc;
template <int MaxN> class Fenwick {
public:
    int c[MaxN];
    void insert(int x, int val) {
        ++x;
        for (; x < MaxN; x += (x & -x)) c[x] += val;
    }
    int query(int x) { int ret = 0;
        ++x;
        for (; x; x -= (x & -x)) ret += c[x];
        return ret;
    }
};
 
struct rectangle {
    int x1, y1, x2, y2;
    void read() { 
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        ++x2, ++y2;
    }
}   rect[MaxN];
struct segment {
    int p, l, r, val;
}   seg[MaxN << 1], qry[MaxN << 1];
int stot, qtot;
int val[MaxN << 1];
struct point {
    int x, y;
    void read() { scanf("%d%d", &x, &y); }
}   flower[MaxN], cow[MaxN];
 
int N, M, F;
 
void input() {
    scanf("%d", &F);
    for (int i = 1; i <= F; ++i) rect[i].read();
    rect[++F] = (rectangle){0, 0, MC, MC};
    scanf("%d", &M);
    for (int i = 1; i <= M; ++i) flower[i].read();
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) cow[i].read();
}
 
struct event {
    int x, y, type, pos;
}   H[MaxN << 3];
int Htot;
set < pair <int, int> > s;
bool cmp_c(const event &a, const event &b) {
    return (a.y == b.y) ? a.type > b.type : a.y < b.y;
}
 
void dfs_c(int now) {
    for (int i = Tc.En[now]; i; i = Tc.Next[i]) {
        dfs_c(Tc.Point[i]);
        val[now] += val[Tc.Point[i]];
    }
}
 
void build_tree_c() {
    static bool root[MaxN];
    fill(root + 1, root + F + 1, 1);
    s.clear();
    Htot = 0;
    for (int i = 1; i <= F; ++i) {
        H[++Htot] = (event){rect[i].x1, rect[i].y1, 1, i + F};
        H[++Htot] = (event){rect[i].x1, rect[i].y2, 2, i + F};
        H[++Htot] = (event){rect[i].x2, rect[i].y1, 1, i};
        H[++Htot] = (event){rect[i].x2, rect[i].y2, 2, i};
        if (i != F) H[++Htot] = (event){rect[i].x1 - 1, rect[i].y1 - 1, 0, i};
    }
    for (int i = 1; i <= M; ++i) 
        H[++Htot] = (event){flower[i].x, flower[i].y, 0, i + F};
    sort(H + 1, H + Htot + 1, cmp_c);
    for (int i = 1; i <= Htot; ++i) {
        event now = H[i];
//      printf("%d %d %d %d\n", now.x, now.y, now.type, now.pos);
        if (now.type == 1) s.insert(mkp(-now.x, now.pos));
        else if (now.type == 2) s.erase(mkp(-now.x, now.pos));
        else {
            pair <int, int> ask = *s.lower_bound(mkp(-now.x, 0));
            int father = ask.sec;
            if (father <= F) {
                Tc.Add(father, now.pos);
                if (now.pos <= F) {
                    root[now.pos] = 0;
//                  printf("%d -> %d(rect)\n", father, now.pos);
                }
//              else printf("%d -> %d(flower)\n", father, now.pos - F);
            }
            seg[++stot] = (segment){now.y, -ask.fir, now.x, now.pos};
        }
    }
    for (int i = F + 1; i <= F + M; ++i) val[i] = 1;
    for (int i = 1; i <= F; ++i)
        if (root[i]) dfs_c(i);
    for (int i = 1; i <= stot; ++i) seg[i].val = val[seg[i].val];
//  for (int i = 1; i <= stot; ++i) printf("%d, [%d %d] = %d\n", seg[i].p, seg[i].l, seg[i].r, seg[i].val);
}
 
bool root[MaxN];
bool cmp_r(const event &a, const event &b) {
    return (a.x == b.x) ? a.type > b.type : a.x > b.x;
}
void build_tree_r() {
    fill(root + 1, root + F + 1, 1);
    s.clear();
    Htot = 0;
    for (int i = 1; i <= F; ++i) {
        H[++Htot] = (event){rect[i].x1 - 1, rect[i].y1, 2, i};
        H[++Htot] = (event){rect[i].x2 - 1, rect[i].y1, 1, i};
        H[++Htot] = (event){rect[i].x1 - 1, rect[i].y2, 2, i + F};
        H[++Htot] = (event){rect[i].x2 - 1, rect[i].y2, 1, i + F};
        if (i != F) H[++Htot] = (event){rect[i].x2, rect[i].y1, 0, i};
    }
    for (int i = 1; i <= N; ++i) 
        H[++Htot] = (event){cow[i].x, cow[i].y, 0, i + F};
    sort(H + 1, H + Htot + 1, cmp_r);
    for (int i = 1; i <= Htot; ++i) {
        event now = H[i];
//      printf("%d %d %d %d\n", now.x, now.y, now.type, now.pos);
        if (now.type == 1) s.insert(mkp(now.y, now.pos));
        else if (now.type == 2) s.erase(mkp(now.y, now.pos));
        else {
            pair <int, int> ask = *s.lower_bound(mkp(now.y + 1, 0));
            int father = ask.sec;
            if (father <= F) {
                Tr.Add(father, now.pos);
                if (now.pos <= F) {
                    root[now.pos] = 0;
//                  printf("%d -> %d(rect)\n", father, now.pos);
                }
//              else printf("%d -> %d(cow)\n", father, now.pos - F);
            }
            qry[++qtot] = (segment){now.x, now.y, ask.fir - 1, now.pos};
        }
    }
//  for (int i = 1; i <= qtot; ++i) printf("%d, [%d %d] = %d\n", qry[i].p, qry[i].l, qry[i].r, qry[i].val);
}
 
bool cmp_i(const event &a, const event &b) {
    return (a.x == b.x) ? a.type < b.type : a.x < b.x;
}
Fenwick <MC + 2> tree;
void intersect() {
    memset(val, 0, sizeof(val));
    Htot = 0;
    for (int i = 1; i <= qtot; ++i) {
        H[++Htot] = (event){qry[i].p, qry[i].r, 1, qry[i].val};
        H[++Htot] = (event){qry[i].p, qry[i].l - 1, 2, qry[i].val};
    }
    for (int i = 1; i <= stot; ++i) {
        H[++Htot] = (event){seg[i].l, seg[i].p, 0, seg[i].val};
        H[++Htot] = (event){seg[i].r + 1, seg[i].p, 0, -seg[i].val};
    }
    sort(H + 1, H + Htot + 1, cmp_i);
    for (int i = 1; i <= Htot; ++i) {
        event now = H[i];
        if (now.type >= 1) {
            int k = ((now.type == 2) ? -1 : 1);
            val[now.pos] += k * tree.query(now.y);
        } else {
            tree.insert(now.y, now.pos);
        }
    }
//  for (int i = 1; i <= N + F; ++i) printf("%d ", val[i]); puts("");
}
 
void dfs_dp(int now, int sum) {
    val[now] += sum;
    for (int i = Tr.En[now]; i; i = Tr.Next[i]) {
        dfs_dp(Tr.Point[i], val[now]);
    }
}
 
void tree_dp() {
    for (int i = 1; i <= F; ++i)
        if (root[i]) dfs_dp(i, 0);
}
 
void output() {
    for (int i = 1; i <= N; ++i)
        printf("%d\n", val[i + F]);
}
 
int main()
{
    input();
    build_tree_c();
    build_tree_r();
    intersect();
    tree_dp();
    output();
    return 0;
}
