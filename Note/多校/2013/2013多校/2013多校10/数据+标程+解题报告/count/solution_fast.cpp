#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

typedef __int64 LL;

const LL mod = 1000000007;
const int maxn = 1111;

int n, m, k;

set<int>sakura;

int val[maxn];

struct rec{
    int x, y;
    bool operator<(const rec &o)const {
        return x < o.x;
    }
}p[maxn];

set<int>::iterator it;


int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i){
        scanf("%d%d", &p[i].x, &p[i].y);
        val[i - 1] = p[i].x;
    }
    sort(p + 1, p + k + 1);
    sort(val, val + k);
    int tot = unique(val, val + k) - val;
    LL ans = 0;
    for (int i = 0, r = 1; i < tot; ++i){
        LL T = 0;
        sakura.clear();
        r = 1;
        while (r <= k && p[r].x < val[i])r++;
        int gxx = i == 0 ? val[i] : val[i] - val[i - 1];
        for (int j = i; j < tot; ++j){
            while (r <= k && p[r].x == val[j]){
                it = sakura.lower_bound(p[r].y);
                int a;
                int b;
                if (it == sakura.end())
                    b = m + 1;
                else
                    b = *it;
                if (it == sakura.begin())
                    a = 0;
                else
                    a = *(--it);
                T = (T + (LL)(p[r].y - a) * (b - p[r].y) % mod) % mod;
                sakura.insert(p[r].y);
                r++;
            }
            int ls = j == tot - 1 ? n - val[j] + 1 : val[j + 1] - val[j];
            ans = (ans + (LL)T * ls % mod * gxx % mod) % mod;
        }
    }
    cout<<ans<<endl;
}
