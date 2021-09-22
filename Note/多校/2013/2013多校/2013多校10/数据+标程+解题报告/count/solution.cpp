#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) (int)((v).size())

const int MOD = (int)1e9 + 7;
const int N = (int)1e9;
const int K = 1000;
const int M = K + 1 << 1;

int n, m, k, x[K], y[K], height[M], order[K], children[M][2], scale[M], answer;
std::vector <int> x_values, y_values;

bool by_x(int i, int j) {
    return x[i] < x[j];
}

int choose(int n) {
    return (long long)n * (n + 1) / 2 % MOD;
}

void search(int u, int l, int r) {
    if (u != -1) {
        scale[u] = (choose(r - l) - choose(y_values[u] - l) - choose(r - y_values[u + 1])) % MOD;
        search(children[u][0], l, y_values[u]);
        search(children[u][1], y_values[u + 1], r);
    }
}

void solve(int delta) {
    memset(children, -1, sizeof(children));
    std::vector <int> stack;
    for (int i = 0; i + 1 < SIZE(y_values); ++ i) {
        int left = -1;
        while (!stack.empty() && height[stack.back()] > height[i]) {
            int u = stack.back();
            stack.pop_back();
            children[u][1] = left;
            left = u;
        }
        children[i][0] = left;
        stack.push_back(i);
    }
    int root = -1;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        children[u][1] = root;
        root = u;
    }
    search(root, 0, m);
    for (int i = 0; i + 1 < SIZE(y_values); ++ i) {
        (answer -= ((long long)choose(height[i] + delta - 1) - choose(height[i] - 1)) * scale[i] % MOD) %= MOD;
        height[i] += delta;
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        assert(1 <= n && n <= N);
        assert(1 <= m && m <= N);
        assert(0 <= k && k <= K);
        for (int i = 0; i < k; ++ i) {
            assert(scanf("%d%d", x + i, y + i) == 2);
            assert(1 <= x[i] && x[i] <= n);
            assert(1 <= y[i] && y[i] <= m);
            x[i] --, y[i] --;
            order[i] = i;
        }
        x_values.clear();
        y_values.clear();
        std::sort(order, order + k, by_x);
        x_values.push_back(0);
        x_values.push_back(n);
        y_values.push_back(0);
        y_values.push_back(m);
        for (int i = 0; i < k; ++ i) {
            x_values.push_back(x[i]);
            x_values.push_back(x[i] + 1);
            y_values.push_back(y[i]);
            y_values.push_back(y[i] + 1);
        }
        std::sort(ALL(x_values));
        x_values.erase(std::unique(ALL(x_values)), x_values.end());
        std::sort(ALL(y_values));
        y_values.erase(std::unique(ALL(y_values)), y_values.end());
        memset(height, 0, sizeof(height));
        answer = (long long)choose(n) * choose(m) % MOD;
        for (int i = 0; i + 1 < SIZE(y_values); ++ i) {
            height[i] = 1;
        }
        for (int i = 0, j = 0; i + 1 < SIZE(x_values); ++ i) {
            while (j < k && x[order[j]] <= x_values[i]) {
                height[std::lower_bound(ALL(y_values), y[order[j]]) - y_values.begin()] = 0;
                j ++;
            }
            solve(x_values[i + 1] - x_values[i]);
        }
        printf("%d\n", (answer + MOD) % MOD);
    }
    return 0;
}
