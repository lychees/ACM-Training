#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) ((int)(v).size())
#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 50000;
const int MOD = (int)1e9 + 7;
const int INF = (int)1e9;

int n, x[N + 1][2], y[N + 1][2], weight[N + 1];

int status[N + 1];
std::vector <int> values;
std::vector <std::pair <int, int> > events, queries;

inline void add2mod(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

struct Line {
    int a, b;

    Line() : a(0), b(0) {}
    Line(int a, int b) : a(a), b(b) {}

    Line &operator +=(const Line &o) {
        add2mod(a, o.a);
        add2mod(b, o.b);
        return *this;
    }

    Line &operator *=(int k) {
        a = (long long)a * k % MOD;
        b = (long long)b * k % MOD;
        return *this;
    }

    int at(int x) {
        if (x < 0) {
            x += MOD;
        }
        return ((long long)a * x + b) % MOD;
    }
};

Line operator +(Line a, const Line &b) {
    return a += b;
}

Line operator *(Line a, int k) {
    return a *= k;
}

int get_id(int l, int r) {
    return l + r | (l != r);
}

Line delta[N + 1 << 3], sum[N + 1 << 3];

inline int normalize(int x) {
    if (x < 0) {
        x += MOD;
    }
    if (x >= MOD) {
        x -= MOD;
    }
    return x;
}

void insert(int l, int r, int a, int b, const Line &d) {
    if (b + 1 <= values[l] || values[r + 1] <= a) {
        return;
    }
    int id = get_id(l, r);
    sum[id] += d * normalize(std::min(values[r + 1], b + 1) - std::max(values[l], a));
    if (a <= values[l] && values[r + 1] <= b + 1) {
        delta[id] += d;
    } else {
        int m = l + r >> 1;
        insert(l, m, a, b, d);
        insert(m + 1, r, a, b ,d);
    }
}

Line query(int l, int r, int a, int b) {
    if (b + 1 <= values[l] || values[r + 1] <= a) {
        return Line();
    }
    int id = get_id(l, r);
    int width = normalize(std::min(values[r + 1], b + 1) - std::max(values[l], a));
    if (a <= values[l] && values[r + 1] <= b + 1) {
        return sum[id];
    }
    Line ret = delta[id] * width;
    if (l == r) {
        return ret;
    }
    int m = l + r >> 1;
    ret += query(l, m, a, b);
    ret += query(m + 1, r, a, b);
    return ret;
}

void solve(int l, int r) {
    if (r - l > 1) {
        int m = l + r >> 1;
        solve(l, m);
        values.clear();
        for (int i = l; i < m; ++ i) {
            values.push_back(y[i][0]);
            values.push_back(y[i][1] + 1);
        }
        std::sort(ALL(values));
        values.erase(std::unique(ALL(values)), values.end());
        int size = SIZE(values) - 2;
        events.clear();
        for (int i = l; i < m; ++ i) {
            events.push_back(std::make_pair(x[i][0] - 1, i));
            events.push_back(std::make_pair(x[i][1], i));
        }
        std::sort(ALL(events));
        queries.clear();
        for (int i = m; i < r; ++ i) {
            queries.push_back(std::make_pair(x[i][0] - 1, i));
            queries.push_back(std::make_pair(x[i][1], i));
        }
        std::sort(ALL(queries));
        std::fill(status + l, status + r, 0);
        std::fill(delta, delta + (size << 1) + 1, Line());
        std::fill(sum, sum + (size << 1) + 1, Line());
        __typeof(events.begin()) e = events.begin();
//printf("[%d, %d)\n", l, r);
        foreach (q, queries) {
            while (e != events.end() && e->first <= q->first) {
                int &i = e->second;
                int x0 = normalize(e->first);
                int a = status[i] ? MOD - weight[i] : weight[i];
                insert(0, size, y[i][0], y[i][1], Line(a, MOD - (long long)a * x0 % MOD));
//printf("+ (%d x + %lld)\n", a, MOD - (long long)a * x0 % MOD);
                status[i] ^= 1;
                e ++;
            }
            int &i = q->second;
            int v = query(0, size, y[i][0], y[i][1]).at(q->first);
//printf("%d: %d\n", i, v);
            if (status[i] ^= 1) {
                v = MOD - v;
            }
            add2mod(weight[i], v);
        }
        solve(m, r);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        assert(1 <= n && n <= N);
        x[0][0] = y[0][0] = -INF;
        x[0][1] = y[0][1] = INF;
        for (int i = 1; i <= n; ++ i) {
            assert(scanf("%d%d%d%d", &x[i][0], &y[i][0], &x[i][1], &y[i][1]) == 4);
            assert(std::abs(x[i][0]) <= INF);
            assert(std::abs(x[i][1]) <= INF);
            assert(std::abs(y[i][0]) <= INF);
            assert(std::abs(y[i][1]) <= INF);
            assert(x[i][0] <= x[i][1]);
            assert(y[i][0] <= y[i][1]);
        }
        memset(weight, 0, sizeof(weight));
        weight[0] = 1;
        solve(0, n + 1);
        int answer = 0;
        for (int i = 1; i <= n; ++ i) {
            add2mod(answer, (long long)weight[i] * (x[i][1] - x[i][0] + 1) % MOD * (y[i][1] - y[i][0] + 1) % MOD);
        }
        printf("%d\n", answer);
    }
    return 0;
}
