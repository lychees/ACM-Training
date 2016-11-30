#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <algorithm>
using namespace std;

int getc() {
    static const int L = 1 << 15;
    static char buf[L], *S = buf, *T = buf;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, L, stdin);
        if (S == T)
            return EOF;
    }
    return *S++;
}
int getint() {
    int c;
    while (!isdigit(c = getc()));
    int x = c - '0';
    while (isdigit(c = getc()))
        x = (x << 1) + (x << 3) + c - '0';
    return x;
}

struct Node {
    int ch[2], s;
}S[10000010];
#define son(x, c) (S[(x)].ch[(c)])
#define siz(x) (S[(x)].s)
int cnt;
int insert(int last, int dep, int x) {
    int q = ++cnt;
    S[q] = S[last];
    ++S[q].s;
    if (dep < 0)
        return q;
    S[q].ch[(x >> dep) & 1] = insert(S[last].ch[(x >> dep) & 1], dep - 1, x);
    return q;
}
int root[500010];

int queryMaxXor(int lnode, int rnode, int dep, int x) {
    if (dep < 0 || !rnode)
        return 0;
    int c = (x >> dep) & 1;
    if (siz(son(rnode, c ^ 1)) > siz(son(lnode, c ^ 1)))
        return (1 << dep) + queryMaxXor(son(lnode, c ^ 1), son(rnode, c ^ 1), dep - 1, x);
    else
        return queryMaxXor(son(lnode, c), son(rnode, c), dep - 1, x);
}

int queryLessOrEqual(int root, int dep, int x) {
    if (dep < 0 || !root)
        return siz(root);
    int c = (x >> dep) & 1;
    if (c == 0)
        return queryLessOrEqual(son(root, 0), dep - 1, x);
    else
        return siz(son(root, 0)) + queryLessOrEqual(son(root, 1), dep - 1, x);
}

int queryKthElement(int lnode, int rnode, int dep, int k) {
    if (dep < 0 || !rnode)
        return 0;
    int lsize = siz(son(rnode, 0)) - siz(son(lnode, 0));
    if (k <= lsize)
        return queryKthElement(son(lnode, 0), son(rnode, 0), dep - 1, k);
    else
        return (1 << dep) + queryKthElement(son(lnode, 1), son(rnode, 1), dep - 1, k - lsize);
}

int main() {
    //freopen("tt.in", "r", stdin);
    int m = getint(), n = 0;
    int type, l, r, x, k;
    while (m--) {
        type = getint();
        if (type == 0) {
            root[n + 1] = insert(root[n], 18, getint());
            ++n;
        }
        else if (type == 1) {
            l = getint();
            r = getint();
            x = getint();
            printf("%d\n", x ^ queryMaxXor(root[l - 1], root[r], 18, x));
        }
        else if (type == 2)
            n -= getint();
        else if (type == 3) {
            l = getint();
            r = getint();
            x = getint();
            printf("%d\n", queryLessOrEqual(root[r], 18, x) - queryLessOrEqual(root[l - 1], 18, x));
        }
        else if (type == 4) {
            l = getint();
            r = getint();
            k = getint();
            printf("%d\n", queryKthElement(root[l - 1], root[r], 18, k));
        }
    }
    
    return 0;
}