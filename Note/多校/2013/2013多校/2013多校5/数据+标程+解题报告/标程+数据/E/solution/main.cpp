#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
const int maxn = 111111;
__int64 a[maxn];

int main()
{
    int n, m, x, y;
    __int64 w, t1, t2;
    while(scanf("%d%d", &n, &m)==2) {
        for (int i = 0; i < n; ++i) {
            scanf("%I64d", &a[i]);
            a[i] *= 2;
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%I64d", &x, &y, &w);
            a[--x] += w, a[--y] += w;
        }
        sort(a, a+n, greater<__int64>());
        t1 = t2 = 0;
        for (int i = 0; i < n; ++i) {
            t1 += a[i];
            t2 += a[++i];
        }
        t1 = (t1-t2)/2;
        cout << t1 << endl;
    }
    return 0;
}
