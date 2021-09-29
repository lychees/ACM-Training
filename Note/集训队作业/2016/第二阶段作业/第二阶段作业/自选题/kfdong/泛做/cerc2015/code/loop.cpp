#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define ll long long
#define mkp(a, b) (node){a, b}
using namespace std;
 
struct node {
    int fir, sec;
    node() {}
    node(int x, int y) : fir(x), sec(y) {}
    bool operator < (const node &a) const {
        return fir != a.fir ? fir < a.fir : sec < a.sec;
    }
    bool operator == (const node &a) const {
        return (fir == a.fir) && (sec == a.sec);
    }
};
 
inline int cmod(int a, int mod) {
    return (a %= mod) < 0 ? a += mod : a;
}
 
const int MaxN = 110, MaxQ = 2000000;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
vector <node> vis[MaxN][MaxN];
char Map[MaxN][MaxN];
int type;
int N, M;
node dir;
 
class hash {
public:
    static const int Mod = 3000017, Base = 1000000009;
    int En[Mod], Next[Mod], tot;
    long long val[Mod];
    bool find(node y) {
        ll x = 1ll * y.fir * Base + y.sec;
        int u = cmod(x, Mod);
        for (int i = En[u]; i; i = Next[i])
            if (val[i] == x) return 1;
        return 0;
    }
    bool insert(node y) {
        if (find(y)) return 0;
        ll x = 1ll * y.fir * Base + y.sec;
        int u = cmod(x, Mod);
        Next[++tot] = En[u];
        En[u] = tot;
        val[tot] = x;
        return 1;
    }
}   Hash;
 
void init() {
    static node Q[MaxQ];
    int l = 0, r = 0;
    Q[++r] = mkp(0, 0);
    vis[0][0].push_back(Q[r]);
    Hash.insert(Q[r]);
    while (l != r) {
        ++l;
        if (int(vis[0][0].size()) > N + M) break;
        for (int i = 0; i < 4; ++i) {
            node nxt = mkp(Q[l].fir + dx[i], Q[l].sec + dy[i]);
            int x = cmod(nxt.fir, N), y = cmod(nxt.sec, M);
            if (Map[x][y] != '.') continue;
            if (Hash.insert(nxt)) {
                Q[++r] = nxt;
                vis[x][y].push_back(nxt);
            }
        }
    }
    if (vis[0][0].size() == 1) return;
    vector <node> delta, &s = vis[0][0];
    sort(s.begin(), s.end());
    for (uint i = 1; i < s.size(); ++i) {
        delta.push_back(mkp(s[i].fir - s[i - 1].fir, s[i].sec - s[i - 1].sec));
    }
    sort(delta.begin(), delta.end());
    int size = unique(delta.begin(), delta.end()) - delta.begin();
    if (size > 1) type = 2;
    else {
        type = 1;
        dir = *(delta.begin());
    }
}
 
bool get(node s) {
    int x = cmod(s.fir, N), y = cmod(s.sec, M);
    if (type == 0) return Hash.find(s);
    else if (type == 2) return vis[x][y].size();
    else {
        int k = (s.fir - x + s.sec - y) / (dir.fir + dir.sec);
        node nxt(s.fir - k * dir.fir, s.sec - k * dir.sec);
        return Hash.find(nxt);
    }
}
 
int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; ++i) scanf("%s", Map[i]);
    init();
 
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (get(mkp(u, v))) puts("yes");
        else puts("no");
    }
    return 0;
}
