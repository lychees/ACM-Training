#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
#define N 53
#define eps 1e-5
#define inf 1e10

struct POINT {
    double x, y;
    POINT() {};
    POINT(double _x, double _y): x(_x), y(_y) {};
}c[N], b[N];
int n, m;


inline double dist(POINT &x, POINT &y) {
    return ((x.x-y.x)*(x.x-y.x) + (x.y-y.y)*(x.y-y.y));
}
int belong(POINT &x) {
    double r = inf, d;
    int k = 0;
    for (int i=0; i<m; i++) {
        d = dist(x, b[i]);
        if (d < r) { r = d; k = i; }
    }
    return k;
}
int work(POINT &x, POINT &y) {
    int la = belong(x), lb = belong(y);
    if (la == lb) return 0;
    if (sqrt(dist(x, y)) < eps) return 1;
    POINT t((x.x+y.x)/2.0, (x.y+y.y)/2.0);
    return work(x, t) + work(t, y);
}
int main() {
    int k, x, y;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i=0; i<n; i++) scanf("%lf%lf", &c[i].x, &c[i].y);
        for (int i=0; i<m; i++) scanf("%lf%lf", &b[i].x, &b[i].y);
        scanf("%d", &k);
        while (k--)  {
            scanf("%d%d", &x, &y);
            printf("%d\n", work(c[x-1], c[y-1]));
        }
    }

    return 0;
}
