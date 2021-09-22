#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <climits>
#include <cassert>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000 + 1;

struct Query_Data {
    int u, x;
    Query_Data() {}
    Query_Data(int u, int x): u(u), x(x) {}
};
std::vector<Query_Data> queries;
std::vector<int> tables[N];
int answer[N][2];

int count[N], children[N][2], weight[N];
int n;

const int M = N << 2;

int size[M], number[M], args[M], key[M], indices[M][2];
int node_count;

void update(int u) {
    size[u] = size[indices[u][0]] + size[indices[u][1]] + number[u];
}

void rotate(int &u, int d) {
    int v = indices[u][d];
    indices[u][d] = indices[v][d ^ 1];
    indices[v][d ^ 1] = u;
    update(u);
    update(v);
    u = v;
}

void insert(int &u, int k) {
    if (u == 0) {
        u = ++ node_count;
        size[u] = number[u] = 1;
        key[u] = k;
        args[u] = rand();
        indices[u][0] = indices[u][1] = 0;
    } else if (k == key[u]) {
        number[u] ++;
    } else {
        int d = k > key[u];
        int &v = indices[u][d];
        insert(v, k);
        if (args[v] < args[u]) {
            rotate(u, d);
        }
    }
    update(u);
}

void erase(int &u, int k) {
    if (u == 0) {
        size[u] = number[u] = indices[u][0] = indices[u][1] = 0;
    } else if (k == key[u]) {
        if (number[u] > 1) {
            number[u] --;
        } else {
            int d = args[indices[u][1]] < args[indices[u][0]];
            rotate(u, d);
            erase(u, k);
        }
    } else {
        int d = k > key[u];
        int &v = indices[u][d];
        erase(v, k);
        if (args[v] < args[u]) {
            rotate(u, d);
        }
    }
    update(u);
}

bool find(int u, int k) {
    while (u > 0) {
        if (key[u] == k) {
            return true;
        }
        u = indices[u][k > key[u]];
    }
    return false;
}

int find_greater(int u, int k) {
    int result = 0;
    while (u > 0) {
        if (k < key[u]) {
            result += size[indices[u][1]] + number[u];
        }
        u = indices[u][k > key[u]];
    }
    return result;
}

int steps[2], roots[2];
void dfs(int u, int first) {
    foreach(iter, tables[u]) {
        int id = (*iter);
        int x = queries[id].x;
        if (find(roots[0], x) || find(roots[1], x)) {
            answer[id][0] = -1;
        } else if (u == 0) {
            answer[id][0] = answer[id][1] = 0;
        } else {
            int a = find_greater(roots[0], x);
            int b = find_greater(roots[1], x);
            answer[id][1] += a + (steps[0] - a) * 3;
            answer[id][1] += b + (steps[1] - b) * 3;
            answer[id][0] += steps[1] - b;
        }
    }
    for (int i = 0; i < count[u]; ++ i) {
        int v = children[u][i];
        insert(roots[i], weight[u]);
        steps[i] ++;
        dfs(v, first == -1 ? i : first);
        steps[i] --;
        erase(roots[i], weight[u]);
    }
}

#define clr(x) memset((x), 0, sizeof(x))

void initialise() {
    clr(steps), clr(roots), clr(count);
    clr(answer), clr(children), clr(weight);
    clr(size), clr(number), clr(args), clr(key);
    clr(indices);
    node_count = 0;
    args[0] = INT_MAX;
    queries.clear();
    for (int i = 0; i < n; ++ i) {
        tables[i].clear();
    }
}

int main() {
    int test_count;
    assert(scanf("%d", &test_count) == 1);
    while (test_count --) {
        assert(scanf("%d", &n) == 1);
        initialise();

        for (int i = 0; i < n; ++ i) {
            assert(scanf("%d", &weight[i]) == 1);
        }

        int m;
        assert(scanf("%d", &m) == 1);
        while (m --) {
            int u, a, b;
            assert(scanf("%d%d%d", &u, &a, &b) == 3);
            u --, a --, b --;
            children[u][0] = a;
            children[u][1] = b;
            count[u] = 2;
        }

        assert(scanf("%d", &m) == 1);
        for (int i = 0; i < m; ++ i) {
            int u, x;
            assert(scanf("%d%d", &u, &x) == 2);
            u --;
            tables[u].push_back(i);
            queries.push_back(Query_Data(u, x));
        }

        dfs(0, -1);

        for (int i = 0; i < m; ++ i) {
            if (answer[i][0] == -1) {
                puts("0");
            } else {
                printf("%d %d\n", answer[i][0], answer[i][1]);
            }
        }
    }
    return 0;
}
