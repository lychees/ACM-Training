#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#ifndef ONLINE_JUDGE
/* #define DEBUG */
#endif
int less (int *a, int *b) {return *a < *b ? -1 : 1;}
int greater (int *a, int *b) {return *a > *b ? -1 : 1;}
typedef int (*cmp_t) (const void *, const void *);
typedef unsigned uint;
typedef long long int64;
typedef unsigned long long uint64;
#define max(i, j) ({int _ = (i), __ = (j); _ > __ ? _ : __;})
#define min(i, j) ({int _ = (i), __ = (j); _ < __ ? _ : __;})
#define swap(T, i, j) ({T _ = (i); (i) = (j); (j) = _;})
#define oo 0x3F3F3F3F
#ifdef DEBUG
#define cerr(...) fprintf (stderr, __VA_ARGS__)
#define cvar(x) cerr ("<" #x ": %d>", x)
#define evar(x) cerr ("<" #x ": %d>\n", x)
#define ctime() fprintf (stderr, "time: %.3f s\n", 1.0 * clock () / CLOCKS_PER_SEC)
void DISP (char *s, int *x, int n) {int i; cerr ("[%s: ", s); for (i = 0; i < n - 1; ++i) cerr ("%d ", x[i]); if (n) cerr ("%d", x[i]); cerr ("]\n");}
#define disp(T,n) DISP (#T " to " #n, T, n)
#else
#define cerr(...) ({})
#define cvar(...) ({})
#define evar(...) ({})
#define disp(...) ({})
#define ctime() ({})
#endif
#define CR cerr ("\n")
#ifdef WIN32
#define fmt64 "%I64d"
#else
#define fmt64 "%lld"
#endif

#define maxn 3100000

typedef struct edge {int t; struct edge *n; } edge;
typedef struct node {
    struct node *c[2], *f, *succ, *pred;
    int size;
    int64 v, d;
} node;
typedef struct BBST {
    node *root;
    int64 add;
} BBST;

node buf[maxn], *null = buf, *root;
BBST T[maxn];
edge graph[maxn << 1], *eptr = graph, *adj[maxn];
int64 f[maxn], g[maxn], d[maxn];

void show(BBST *t)
{
    node *lx = null;
    void dfs(node *t) {
        if (t->c[0] != null)
            cerr("["), dfs(t->c[0]), cerr("]<-");
        assert(t->pred == lx);
        if (lx != null) assert(lx->succ == t);
        lx = t;
        cerr("(%lld, %lld)", t->d, t->v + T->add);
        if (t->c[1] != null)
            cerr("->["), dfs(t->c[1]), cerr("]");
    }
    cerr("--------------------\n");
    dfs(t->root), CR, assert(lx->succ == null);
}

node *update(node *t)
{
    return t->size = t->c[0]->size + 1 + t->c[1]->size, t;
}

#define setc(p,d,q) (((p)->c[d] = (q))->f = (p))
void rotate(node *x)
{
    node *y = x->f, *z = y->f; int d = x == y->c[1];
    x->f = z; if (z != null) z->c[y == z->c[1]] = x;
    setc(y, d, x->c[!d]);
    setc(x, !d, update(y));
}

node *splay(node *x, node *S)
{
    if (x == null) return x;
    for (; x->f != S; rotate(x))
        if (x->f->f != S)
            rotate((x->f->f->c[1] == x) == (x->f->c[1] == x) ? x->f : x);
    if (S == null) root = x;
    return update(x);
}

node *extreme(node *x, bool d)
{
    if (x == null) return x;
    node *f = x->f;
    for (; x->c[d] != null; x = x->c[d]);
    return splay(x, f);
}

node *near(node *x, bool d)
{
    if (x->c[d] == null) return x;
    extreme(x->c[d], !d);
    return x->c[d];
}

void split(node *T, node *x, node **L, node **R)
{
    node *w = null; *L = T, *R = null;
    for (; T != null; )
        if (T->d <= x->d)
            T = T->c[1];
        else
            w = T, T = T->c[0];
    if (w != null) {
        splay(w, null);
        *L = w->c[0], *R = w;
        (*L)->f = null, (*R)->c[0] = null, update(*R);
    }
}

double turn(node *o, node *a, node *b)
{
    return (double)(a->d - o->d) * (b->v - o->v) - (double)(a->v - o->v) * (b->d - o->d);
}

node *merge(node *L, node *R)
{
    if (L == null) return R;
    if (R == null) return L;
    extreme(R, 0);
    setc(R, 0, L);
    return update(R);
}

void insert(BBST *T, node *x)
{
    x->v -= T->add;

    node *L, *R;
    split(T->root, x, &L, &R);
    L = extreme(L, 1);
    R = extreme(R, 0);

    if (L != null && R != null && turn(x, L, R) >= 0) {
        T->root = merge(L, R);
        return ;
    }
    if (L != null) {
        for (; L->pred != null && turn(x, L, L->pred) >= 0; L = L->pred);
        splay(L, null), setc(x, 0, L), L->succ = x, L->c[1] = null, update(L);
    }
    if (R != null) {
        for (; R->succ != null && turn(x, R, R->succ) <= 0; R = R->succ);
        splay(R, null), setc(x, 1, R), R->pred = x, R->c[0] = null, update(R);
    }
    x->pred = L, x->succ = R;
    T->root = update(x);
}

BBST unite(BBST *x, BBST *y)
{
    if (x->root->size < y->root->size) {
        return unite(y, x);
    }
    void dfs(node *t) {
        if (t == null) return ;
        dfs(t->c[0]);
        dfs(t->c[1]);
        t->c[0] = t->c[1] = t->f = t->pred = t->succ = null;
        t->v += y->add;
        insert(x, t);
    }
    return dfs(y->root), *x;
}

void moveup(BBST *T, int64 v)
{
    T->add += v;
}

int64 query(BBST *T, int64 d)
{
    node *t = T->root; int64 ret = ~0ull >> 1;
    for (; t != null; ) {
        if (t->succ == null || (t->succ->v - t->v) > (t->succ->d - t->d) * d) {
            int64 v = t->v - t->d * d;
            if (v < ret) ret = v;
            if (t->c[0] == null) break;
            t = t->c[0];
        }
        else {
            if (t->c[1] == null) break;
            t = t->c[1];
        }
    }
    return ret + T->add;
}

node *new(node *t)
{
    return t->c[0] = t->c[1] = t->f = t->succ = t->pred = null, t->size = 1, t;
}

void dfs(int v, int F)
{
    edge *e;
    d[v] += d[F];
    T[v].root = new(buf + v);
    T[v].root->v = d[v] * d[v], T[v].root->d = 2 * d[v];
    for (e = adj[v]; e; e = e->n) {
        if (e->t != F) {
            dfs(e->t, v);
            g[v] += f[e->t];
            T[v] = unite(T + v, T + e->t);
        }
    }
    cerr("show: %d\n", v);
    /* show(T + v); */
    f[v] = query(T + v, d[F]) + g[v] + d[F] * d[F];
    moveup(T + v, g[v] - f[v]);
}

void adde(int s, int t)
{
    *++eptr = (edge){t, adj[s]}, adj[s] = eptr;
}

int main ()
{
#ifndef ONLINE_JUDGE
    //freopen ("COT6.in" , "r", stdin);
    //freopen ("COT6.out", "w", stdout);
#endif

    int n, i;

    *null = (node){{null, null}, null, null, null};

    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf(fmt64, &d[i]);
    }
    for (i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        adde(u, v);
        adde(v, u);
    }
    dfs(1, 0);
    for (i = 1; i <= n; ++i)
        cerr("f %d: %lld\n", i, f[i]);

    /* BBST h = (BBST){null, 0}; */
    /* scanf("%d", &n); */
    /* for (i = 1; i <= n; ++i) { */
    /*  scanf("%lld%lld", &buf[i].d, &buf[i].v); */
    /*  insert(&h, new(buf + i)); */
    /*  show(h.root); */
    /* } */

    printf(fmt64 "\n", f[1]);
    fprintf(stderr, "my: %.3fms\n", 1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}
