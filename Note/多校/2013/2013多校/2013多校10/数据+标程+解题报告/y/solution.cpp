#pragma comment(linker, "/STACK:16777216")
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100000;

int n, edge_count, first_edge[N], to[N << 1], next_edge[N << 1], parent[N];

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

bool merge(int a, int b) {
    if (find(a) == find(b)) {
        return false;
    }
    parent[find(a)] = find(b);
    return true;
}

long long answer;
int size[N];

void solve(int p, int u) {
    size[u] = 1;
    int sum = 0;
    for (int iter = first_edge[u]; iter != -1; iter = next_edge[iter]) {
        int v = to[iter];
        if (v != p) {
            solve(u, v);
            size[u] += size[v];
            answer -= (long long)sum * size[v];
            sum += size[v];
        }
    }
    answer -= (long long)sum * (n - size[u]);
}


void add_edge(int u, int v) {
    to[edge_count] = v;
    next_edge[edge_count] = first_edge[u];
    first_edge[u] = edge_count ++;
}

int main() {
    while (scanf("%d", &n) == 1) {
        assert(1 <= n && n <= N);
        edge_count = 0;
        memset(first_edge, -1, sizeof(first_edge));
        for (int i = 0; i < n; ++ i) {
            parent[i] = i;
        }
        for (int i = 0; i < n - 1; ++ i) {
            int a, b;
            assert(scanf("%d%d", &a, &b) == 2);
            assert(1 <= a && a <= n && 1 <= b && b <= n);
            a --, b --;
            add_edge(a, b);
            add_edge(b, a);
            assert(merge(a, b));
        }
        answer = (long long)n * (n - 1) * (n - 2) / 6;
        solve(-1, 0);
        std::cout << answer << std::endl;
    }
    return 0;
}
