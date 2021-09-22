#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

#define SIZE(v) ((int)((v).size()))
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 100;

int n, cut[N][N], graph[N][N];

bool check(std::vector <int> vs) {
    if (SIZE(vs) <= 1) {
        return true;
    }
    int bridge = INT_MAX;
    foreach (u, vs) {
        foreach (v, vs) {
            bridge = std::min(bridge, cut[*u][*v]);
        }
    }
    int u0 = vs.front();
    std::vector <int> v0, v1;
    foreach (iter, vs) {
        int v = *iter;
        if (cut[u0][v] > bridge) {
            v0.push_back(v);
        } else {
            v1.push_back(v);
        }
    }
    if (v0.empty() || v1.empty()) {
        return false;
    }
    graph[v0.front()][v1.front()] = graph[v1.front()][v0.front()] = bridge;
    foreach (u, v0) {
        foreach (v, v1) {
            if (cut[*u][*v] != bridge) {
                return false;
            }
        }
    }
    return check(v0) && check(v1);
}

int main() {
//	freopen("1005.in","r",stdin);
//	freopen("10050.out","w",stdout);
    while (scanf("%d", &n) == 1) {
    //	printf("%d\n",n);
        assert(1 <= n && n <= N);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                assert(scanf("%d", &cut[i][j]) == 1);
             //   if(j!=n-1)printf("%d ",cut[i][j]);
             //   else printf("%d",cut[i][j]);
                if (i == j) {
                    assert(cut[i][j] == -1);
                    cut[i][j] = INT_MAX;
                } else {
                    assert(0 <= cut[i][j] && cut[i][j] <= 1000000000);
                }
            }
        //    puts("");
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                assert(cut[i][j] == cut[j][i]);
            }
        }
        std::vector <int> vertices;
        for (int i = 0; i < n; ++ i) {
            vertices.push_back(i);
        }
        memset(graph, 0, sizeof(graph));
        for (int i = 0; i < n; ++ i) {
            graph[i][i] = -1;
        }
        if (check(vertices)) {
            puts("YES");
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < n; ++ j) {
                    //printf("%d%c", i == j ? -1 : 0, j == n - 1 ? '\n' : ' ');
                    printf("%d%c", graph[i][j], j == n - 1 ? '\n' : ' ');
                }
            }
        } else {
            puts("NO");
        }
    }
    //puts(check(vertices) ? "YES" : "NO");
    return 0;
}
