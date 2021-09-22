#include <cstdio>
#include <cstring>
#include <algorithm>

const int MOD = (int)1e9 + 7;

const int N = 100000;

int n, x[N][2], y[N][2], weight[N];

void add2mod(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

int intersect(int x1, int x2, int x3, int x4) {
    return std::max(0, std::min(x2, x4) - std::max(x1, x3) + 1);
}

int main() {
	printf("%d\n",MOD);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d%d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]);
    }
    memset(weight, 0, sizeof(weight));
    int answer = 0;
    for (int i = 0; i < n; ++ i) {
        int area = (__int64)(x[i][1] - x[i][0] + 1) * (y[i][1] - y[i][0] + 1) % MOD;
        weight[i] = area;
        for (int j = 0; j < i; ++ j) {
            add2mod(weight[i], (__int64)weight[j] * intersect(x[i][0], x[i][1], x[j][0], x[j][1]) % MOD * intersect(y[i][0], y[i][1], y[j][0], y[j][1]) % MOD);
        }
        add2mod(answer, (__int64)weight[i] * area % MOD);
    }
    printf("%d\n", answer);
    return 0;
}
