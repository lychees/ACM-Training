#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000;

int n, q;

int main() {
    while (scanf("%d%d", &n, &q) == 2) {
        assert(1 <= n && n <= N);
        assert(1 <= q && q <= N);
        for (int i = 0; i < n; ++ i) {
            int t;
            assert(scanf("%d", &t) == 1);
            assert(1 <= t && t <= N);
        }
        bool has1 = false;
        for (int i = 0; i < n; ++ i) {
            int c;
            assert(scanf("%d", &c) == 1);
            assert(1 <= c && c <= 2);
            has1 |= c == 1;
        }
        while (q --) {
            int m;
            assert(scanf("%d", &m) == 1);
            assert(std::abs(m) <= 1000000000);
            if (m <= 0) {
                puts("NO");
            } else {
                puts(has1 || m % 2 == 0 ? "YES" : "NO");
            }
        }
    }
    return 0;
}
