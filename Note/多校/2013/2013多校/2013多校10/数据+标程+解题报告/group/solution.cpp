#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()

const int N = 50;
const int M = 100;

typedef std::vector <int> Permutation;

Permutation inverse(const Permutation &p) {
    Permutation ret(SIZE(p));
    for (int i = 0; i < SIZE(p); ++ i) {
        ret[p[i]] = i;
    }
    return ret;
}

void multiply(const Permutation &a, const Permutation &b, Permutation &c) {
    assert(SIZE(a) == SIZE(b));
    c.resize(SIZE(a));
    for (int i = 0; i < SIZE(c); ++ i) {
        c[i] = a[b[i]];
    }
}

Permutation multiply(const Permutation &a, const Permutation &b) {
    Permutation c;
    multiply(a, b, c);
    return c;
}

int fastFilter(std::vector <std::vector <Permutation> > &buckets,
               std::vector <std::vector <Permutation> > &bucketsInverse,
               std::vector <std::vector <int> > &lookupTable,
               const Permutation &g) {
    int n = SIZE(buckets);
    std::vector <Permutation> p(2, g);
    int i1 = 0;
    int i2 = 1;
    for (int i = 0; i < n; ++i) {
        int res = lookupTable[i][p[i1][i]];
        if (res == -1) {
            buckets[i].push_back(p[i1]);
            bucketsInverse[i].push_back(inverse(p[i1]));
            lookupTable[i][p[i1][i]] = SIZE(buckets[i]) - 1;
            return i;
        }
        multiply(bucketsInverse[i][res], p[i1], p[i2]);
        std::swap(i1, i2);
    }
    return -1;
}

struct BigInteger {
    std::vector <int> digits;

    BigInteger(int a) : digits(1, a) {}

    BigInteger &operator *=(int a) {
        int delta = 0;
        for (int i = 0; i < SIZE(digits); ++ i) {
            delta += digits[i] * a;
            digits[i] = delta % 10000;
            delta /= 10000;
        }
        if (delta > 0) {
            digits.push_back(delta);
        }
        return *this;
    }

    void println() {
        printf("%d", digits.back());
        for (int i = SIZE(digits) - 2; i >= 0; -- i) {
            printf("%04d", digits[i]);
        }
        puts("");
    }
};

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        assert(1 <= n && n <= N);
        assert(1 <= m && m <= M);
        std::vector <Permutation> generators(m);
        for (int i = 0; i < m; ++ i) {
            generators[i].resize(n);
            for (int j = 0; j < n; ++ j) {
                assert(scanf("%d", &generators[i][j]) == 1);
                assert(1 <= generators[i][j] && generators[i][j] <= n);
                generators[i][j] --;
                for (int k = 0; k < j; ++ k) {
                    assert(generators[i][k] != generators[i][j]);
                }
            }
        }
        std::vector <std::vector <Permutation> > buckets(n);
        std::vector <std::vector <Permutation> > bucketsInverse(n);
        std::vector <std::vector <int> > lookupTable(n);
        for (int i = 0; i < n; ++ i) {
            lookupTable[i].resize(n);
            std::fill(ALL(lookupTable[i]), -1);
        }
        Permutation id(n);
        for (int i = 0; i < n; ++ i) {
            id[i] = i;
        }
        for (int i = 0; i < n; ++ i) {
            buckets[i].push_back(id);
            bucketsInverse[i].push_back(id);
            lookupTable[i][i] = 0;
        }
        for (int i = 0; i < m; ++ i) {
            fastFilter(buckets, bucketsInverse, lookupTable, generators[i]);
        }
        std::set <std::pair <std::pair <int, int>, std::pair<int, int> > > toUpdate;
        for (int i = 0; i < n; ++ i) {
            for (int j = i; j < n; ++ j) {
                for (int k = 0; k < SIZE(buckets[i]); ++ k) {
                    for (int l = 0; l < SIZE(buckets[j]); ++ l) {
                        toUpdate.insert(std::make_pair(std::make_pair(i, k), std::make_pair(j, l)));
                    }
                }
            }
        }
        while (!toUpdate.empty()) {
            std::pair <std::pair <int, int>, std::pair<int, int> > current = *toUpdate.begin();
            toUpdate.erase(current);
            Permutation &p1 = buckets[current.first.first][current.first.second];
            Permutation &p2 = buckets[current.second.first][current.second.second];
            int res = fastFilter(buckets, bucketsInverse, lookupTable, multiply(p2, p1));
            if (res == -1) {
                continue;
            }
            std::pair<int, int> newPair(res, SIZE(buckets[res]) - 1);
            for (int i = 0; i < n; ++ i) {
                for (int j = 0; j < SIZE(buckets[i]); ++ j) {
                    if (i <= res) {
                        toUpdate.insert(std::make_pair(std::make_pair(i, j), newPair));
                    }
                    if (res <= i) {
                        toUpdate.insert(std::make_pair(newPair, std::make_pair(i, j)));
                    }
                }
            }
        }
        BigInteger answer(1);
        for (int i = 0; i < n; ++ i) {
            answer *= SIZE(buckets[i]);
        }
        answer.println();
    }
    return 0;
}
