#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define rep(i,n) for(int i=0;i<(n);++i)
#define repf(i,a,b) for(int i=(a);i<=(b);++i)

const int maxn = 64;

typedef pair<string, int> psi;
typedef long long int64;

vector<psi> vec;
int l[maxn], r[maxn], val[maxn];
int64 dp[maxn][128][128];
int n, cn, ans;

bool comp(psi lhs, psi rhs) {
    if (sz(lhs.first) != sz(rhs.first)) {
        return sz(lhs.first) < sz(rhs.first);
    }
    return lhs.first > rhs.first;
}

void make_huf_tree() {
    cn = n;
    int orin = n - 1;
    while (orin) {
        sort (vec.begin(), vec.end(), comp);
        l[n] = vec[orin].second;
        r[n] = vec[orin - 1].second;
        string news = vec[orin].first.substr(0, sz(vec[orin].first) - 1);
        vec.pop_back();
        vec.pop_back();
        vec.push_back(psi(news, n++));
        --orin;
    }
}

void dfs(int now, int bound) {
    if (now < cn) {
        ++ans;
        return ;
    }
    for (int x = max(1, val[now] - bound); x <= val[now] - x; ++x) {
        val[l[now]] = x;
        val[r[now]] = val[now] - x;
        dfs (now - 1, x);
    }
}

int gao() {
    ans = 0;
    val[n - 1] = 100;
    dfs (n - 1, 101);
    return ans;
}

int main() {
    freopen("huffman.in","r",stdin);
    freopen("bc.out","w",stdout);
    int Case = 1;
    while (scanf ("%d", &n), n) {
        vec.clear();
        rep (i, n) {
            string buf;
            cin >> buf;
            vec.push_back(psi(buf, i));
        }
        memset (l, -1, sizeof(l));
        memset (r, -1, sizeof(r));
        make_huf_tree();
        printf ("Case %d: %d\n", Case++, gao());
    }
    return 0;
}
