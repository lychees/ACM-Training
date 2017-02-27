#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <vector>
#include "testlib.h"
using namespace std;
const int N = 300005;

vector<vector<string> > TestCases;

int totallen = 0;

void print(const vector<string> &Cases) {
    printf("%d\n", (int)Cases.size());
    assert(Cases.size() <= 50000);
    int len = 0;
    // set<int> Hash;
    for (auto &str : Cases) {
        puts(str.c_str());
        len += str.size();
        int x = 0;
        for (auto &c : str) {
            x = x * 61 + (c - 'a' + 1);
        }
        // assert(!Hash.count(x));
        // Hash.insert(x);
    }
    totallen += len;
    assert(len <= 250000);
}

namespace solve {
    int n, id[N], suf[N], len;
    int s[N];
    
    int sa[N], t1[N], t2[N], c[N];
    int Rank[N], height[N];
    void buildsa(int *s, int n, int m) {
        int i, k, p, a1, a2, *x = t1, *y = t2;
        memset(c, 0, m << 2);
        for (i = 0; i < n; ++i) ++c[x[i] = s[i]];
        for (i = 1; i < m; ++i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (k = 1, p = 0; k < n; k <<= 1, p = 0) {
            for (i = n - k; i < n; ++i) y[p++] = i;
            for (i = 0; i < n; ++i)
                if (sa[i] >= k) y[p++] = sa[i] - k;
            memset(c, 0, m << 2);
            for (i = 0; i < n; ++i) ++c[x[y[i]]];
            for (i = 1; i < m; ++i) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for (i = 1; i < n; ++i) {
                a1 = sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1;
                a2 = sa[i] + k < n ? y[sa[i] + k] : -1;
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && a1 == a2) ? p - 1 : p++;
            }
            if (p >= n) break;
            m = p;
        }
        for (i = 0; i < n; ++i) Rank[sa[i]] = i;
        for (i = 0, k = 0; i < n; ++i) {
            if (k) --k;
            if (!Rank[i]) continue;
            int j = sa[Rank[i] - 1];
            while (s[i + k] == s[j + k]) ++k;
            height[Rank[i]] = k;
        }
    }
    
    int begin;
    bool check(int v) {
        for (int i = n, x = n; i < len; ++i) {
            if (i + 1 == len || height[i + 1] < v) {
                // printf("%d %d\n" , x , i);
                int flag = 0, beg = -1;
                for (int j = x; j <= i; ++j) {
                    if (id[sa[j]]) {
                        flag |= 1;
                        break;
                    } else if (suf[sa[j]] >= v && beg == -1) {
                        flag |= 2;
                        beg = sa[j];
                    }
                }
                if (flag == 2) {
                    begin = beg;
                    return 1;
                }
                x = i + 1;
            }
        }
        return 0;
    }
    
    void work(const vector<string> &Cases) {
        n = Cases.size();
        len = 0;
        int det;
        for (int i = 0; i < n; ++i) {
            static char str[N];
            strcpy(str, Cases[i].c_str());
            int l = strlen(str);
            if (!i) det = l;
            for (int j = len; j < len + l; ++j) {
                s[j] = str[j - len] + n + 1;
                id[j] = !!i;
                suf[j] = l - j + len;
            }
            len += l;
            id[len] = -1;
            s[len++] = 1 + i;
        }
        s[len] = 0;
        
        buildsa(s, len, 255 + n);
        
        int L = 1, R = det + 1;
        while (L < R) {
            int mid = (L + R) >> 1;
            if (check(mid)) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
        static int ca = 0;
        fprintf(stderr, "Case #%d: ", ++ca);
        if (R > det) {
            fprintf(stderr, "Impossible\n");
        } else {
            for (int i = begin; i < begin + R; ++i) {
                fprintf(stderr, "%c", s[i] - n - 1);
            }
            fprintf(stderr, "\n");
        }
    }
}

int perm[N], length[N];

void gena(int n, int total, int c) {
    for (int i = 0; i < total - 1; ++i) {
        perm[i] = i + 1;
    }
    shuffle(perm, perm + total - 1);
    sort(perm, perm + n - 1);
    perm[n - 1] = total;
    vector<string> V;
    
    for (int i = 0; i < n; ++i) {
        if (!i)
            length[i] = perm[i];
        else
            length[i] = perm[i] - perm[i - 1];
        // printf("%d%c" , length[i] , " \n"[i + 1 == n]);
        string str;
        while (length[i]--) {
            str += (char)(rnd.next('a','a'+c-1));
        }
        V.push_back(str);
    }
    TestCases.push_back(V);
}
void genb(int n, int len, int ww = 3) {
    string str;
    for (int i = 0; i < n; ++i) {
        str += (char)(rnd.next('a','z'));
    }
    vector<string> V;
    V.push_back(str);
    int tot = n;
    while (V.size() < 50000) {
        int l = rnd.next(1,n*2/3);
        if (tot + l > len) break;
        int p = rnd.next(1,n-l);
        string s = str.substr(p, l);
        for (int k = rnd.next(0,ww-1); k >= 0; --k) {
            s[rnd.next(0,l-1)] = rnd.next('a','z');
        }
        V.push_back(s);
        tot += l;
    }
    
    TestCases.push_back(V);
}
void genc(int n, int len) {
    string str;
    for (int i = 0; i < n; ++i) {
        str += (char)(rnd.next('a','z'));
    }
    vector<string> V;
    V.push_back(str);
    V.push_back(str.substr(0, n - 1));
    V.push_back(str.substr(1, n - 1));
    TestCases.push_back(V);
}
void antihash() {
    string str = "a";
    int len = 1;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < len; ++j) {
            str += (str[j] == 'a' ? 'b' : 'a');
        }
        len <<= 1;
    }
    vector<string> V;
    V.push_back(str);
    for (int i = 0; i < len; ++i) {
        str[i] = (str[i] == 'a' ? 'b' : 'a');
    }
    V.push_back(str);
    TestCases.push_back(V);
}

int main(int argc, char **argv) {
    int diff = atoi(argv[1]);
    registerGen(argc,argv,1);
    
    if (diff == 1) {
        for (int i = 0; i < 14; ++i) {
            // random with short total length
            gena(40, 5000, 5);
        }
        gena(100, 5000, 1);
        for (int i = 0; i < 5; ++i) {
            // make the answer string very long
            for (int j = 0; j < 2; ++j) {
                genb(400, 20000);
            }
            genb(1000, 20000);
        }
        gena(100, 250000, 2);
        genb(10000, 250000, 1);
        for (int i = 0; i < 3; ++i) {
            // full dataset
            gena(100, 200000, 3);
            genb(15000, 250000, 2);
        }
        genb(50000, 250000, 2);
        gena(200, 250000, 10);
        genc(80000, 250000);
        antihash();
    } else {
        for (int i = 0; i < 14; ++i) {
            gena(5, 200, 5);
        }
        for (int i = 0; i < 5; ++i) {
            // make the answer string very long
            genb(30, 2000);
        }
        genc(10 , 1000);
    }
    
    printf("%d\n", (int)TestCases.size());
    for (auto &T : TestCases) {
        solve::work(T);
        print(T);
    }
    assert(totallen <= 3000000);
    // printf("%d\n" , totallen);
}
