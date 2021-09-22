#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000 + 1;
const int D = 18;

struct Edge {
    int to, weight, next;
    Edge(int v = 0, int w = 0, int n = 0): to(v), weight(w), next(n) {}
} g[N << 1];
int first[N], edge_count;

void add_edge(int u, int v, int w) {
    edge_count ++;
    g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

std::vector<int> values[N], total[N][2];
int go[N][D], sum[N], depth[N], links[N], father[N];
int n, m, total_value;

int queue[N];
void bfs() {
    queue[0] = 1;
    int tail = 0;
    for (int head = 0; head <= tail; ++ head) {
        int u = queue[head];
        int p = father[u];
        go[u][0] = p;
        for (int i = 0; go[u][i]; ++ i) {
            go[u][i + 1] = go[go[u][i]][i];
        }
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            int w = g[iter].weight;
            if (v != father[u]) {
                queue[++ tail] = v;
                links[v] = w;
                father[v] = u;
                depth[v] = depth[u] + 1;
            }
        }
    }
    for (int i = tail; i >= 0; -- i) {
        int u = queue[i];
        int p = father[u];
        sum[u] = 0;
        for (int iter = first[u]; iter; iter = g[iter].next) {
            int v = g[iter].to;
            int w = g[iter].weight;
            if (v != father[u]) {
                values[u].push_back(sum[v] + w);
                sum[u] += sum[v] + w;
                links[v] = w;
            }
        }
        if (total_value - sum[u]) {
            values[u].push_back(total_value - sum[u]);
        }
        std::sort(values[u].begin(), values[u].end(), std::greater<int>());
        for (int i = 0; i < 2; ++ i) {
            total[u][i].resize(values[u].size() + 2);
            foreach (iter, total[u][i]) {
                *iter = 0;
            }
        }
        for (int i = (int)values[u].size() - 1; i >= 0; -- i) {
            total[u][i & 1][i] = total[u][i & 1][i + 2] + values[u][i];
            total[u][i & 1 ^ 1][i] = total[u][i & 1 ^ 1][i + 1];
        }
    }
}

int jump(int u, int d) {
    for (int i = D - 1; i >= 0; -- i) {
        if (1 << i <= d) {
            u = go[u][i];
            d -= 1 << i;
        }
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }
    u = jump(u, depth[u] - depth[v]);
    for (int i = D - 1; i >= 0; -- i) {
        if (go[u][i] != go[v][i]) {
            u = go[u][i];
            v = go[v][i];
        }
    }
    return u == v ? u : go[u][0];
}

int find(std::vector<int> &a, int x) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        int m = l + r >> 1;
        if (x >= a[m]) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

void solve(int o, int &a, int &b, std::vector<int> &used) {
    std::sort(used.begin(), used.end(), std::greater<int>());
    int amount = (int)used.size();
    if (amount == 0) {
        a += total[o][0][0];
        b += total[o][1][1];
    } else if (amount == 1) {
        int x = find(values[o], used[0]);
        a += total[o][0][0] - total[o][0][x] + total[o][1][x + 1];
        b += total[o][1][1] - total[o][1][x] + total[o][0][x + 1];
    } else {
        int x = find(values[o], used[0]);
        int y = find(values[o], used[1]);
        a += total[o][0][0] - total[o][0][x] + total[o][1][x + 1] - total[o][1][y] + total[o][0][y + 1];
        b += total[o][1][1] - total[o][1][x] + total[o][0][x + 1] - total[o][0][y] + total[o][1][y + 1];
    }
}

#define clr(x) memset((x), 0, sizeof(x))

void initialise() {
    clr(first), clr(go), clr(sum), clr(depth), clr(links), clr(father);
    edge_count = total_value = 0;
    for (int i = 0; i < N; ++ i) {
        values[i].clear();
        total[i][0].clear();
        total[i][1].clear();
    }
}

int main() {
    int test;
    assert(scanf("%d", &test) == 1);
    while (test --) {
        initialise();
        assert(scanf("%d%d", &n, &m) == 2);
        assert(2 <= n && n <= 100000);
        assert(1 <= m && m <= 100000);
        total_value = 0;
        for (int i = 1; i < n; ++ i) {
            int u, v, w;
            assert(scanf("%d%d%d", &u, &v, &w) == 3);
            assert(1 <= u && u <= n);
            assert(1 <= v && v <= n);
            assert(1 <= w && w <= 1000);
            add_edge(u, v, w);
            add_edge(v, u, w);
            total_value += w;
        }
        bfs();
        std::vector<int> used;
        while (m --) {
            int u, v;
            assert(scanf("%d%d", &u, &v) == 2);
            assert(1 <= u && u <= n);
            assert(1 <= v && v <= n);
            int x = lca(u, v);
            int d = depth[u] + depth[v] - depth[x] * 2;
            int id = depth[u] > depth[v] ? u : v;
            int jump_length = d / 2;
            if (d & 1 && depth[u] > depth[v]) {
                jump_length ++;
            }
            int o = jump(id, jump_length);
            int first = 0, second = 0;
            used.clear();
            if (o != x) {
                int temp = total_value - sum[o];
                used.push_back(temp);
                if (depth[u] < depth[v]) {
                    first += temp;
                } else {
                    second += temp;
                }
            }
            if (o != u) {
                int du = jump(u, depth[u] - depth[o] - 1);
                if (go[du][0] == o) {
                    int temp = sum[du] + links[du];
                    used.push_back(temp);
                    first += temp;
                }
            }
            if (o != v) {
                int dv = jump(v, depth[v] - depth[o] - 1);
                if (go[dv][0] == o) {
                    int temp = sum[dv] + links[dv];
                    used.push_back(temp);
                    second += temp;
                }
            }
            if (d & 1) {
                solve(o, second, first, used);
            } else {
                solve(o, first, second, used);
            }
            printf("%d\n", first);
        }
    }
    return 0;
}
