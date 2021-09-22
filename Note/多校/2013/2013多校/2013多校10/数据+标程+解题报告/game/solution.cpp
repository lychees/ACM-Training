#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <algorithm>

const int N = 1000000;
const long long INF = 1000000000000000000LL;

int n, a, b, c[N];
long long sum[N + 1], least[N + 1];

int main() {
    while (scanf("%d%d%d", &n, &a, &b) == 3) {
        assert(1 <= n && n <= N);
        assert(0 <= a && a <= 1000000000);
        assert(0 <= b && b <= 1000000000);
        for (int i = 0; i < n; ++ i) {
            assert(scanf("%d", c + i) == 1);
            assert(0 <= c[i] && c[i] <= 1000000000);
        }
        sum[n] = 0;
        for (int i = n - 1; i >= 0; -- i) {
            sum[i] = sum[i + 1] + c[i];
        }
        least[n] = INF;
        long long minimum = INF;
        for (int i = n; i >= 0; -- i) {
            if (i < n) {
                least[i] = sum[i] + minimum;
            }
            minimum = std::min(minimum, std::max(-sum[i], (long long)a + b - sum[0] - least[i] + 1));
        }
        puts(a >= least[0] ? "ALICE" : "BOB");
    }
    return 0;
}
