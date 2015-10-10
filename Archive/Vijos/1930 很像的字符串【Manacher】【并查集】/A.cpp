#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#define REP(i, n) for (int i=0;i<n;++i)

using namespace std;
typedef long long LL;

const int MOD = int(1e9) + 7;
const int N = int(2e6) + 9;

namespace DSU{
    int P[N];
    int Find(int x){
        return x == P[x] ? x : P[x] = Find(P[x]);
    }
    void Union(int x, int y){
        x = Find(x), y = Find(y);
        if (x == y) return;
        P[y] = x; //#
    }
    void Init(int n){
        REP(i, n) P[i] = i;
    }
}

char _s[N], s[N]; int r[N], deg[N];
int _n, n;

set<pair<int, int> > hashEdge;
void addEdge(int x, int y){
    x = DSU::Find(x); y = DSU::Find(y);
    if (x == y) return;
    if (x > y) swap(x, y);
    if (x == 0) return;
    if (hashEdge.find(make_pair(x, y)) != hashEdge.end()) return;
    hashEdge.insert(make_pair(x, y));
    ++deg[y];
}

void init(){
    static char _s[N]; int _n;
    scanf("%s", &_s);
    _n = strlen(_s);
    s[n++] = '$';
    s[n++] = '#';
    REP(i, _n){
        s[n++] = _s[i];
        s[n++] = '#';
    }
    DSU::Init(n);
}

void manacher(){
    int mx = 0, mi = 0; for (int i=1;i<n;++i){
        if (mx > i) r[i] = min(r[2*mi-i], mx - i);
        else r[i] = 1;

        while (s[i-r[i]] == s[i+r[i]]){
            DSU::Union(i-r[i], i+r[i]);
            ++r[i];
        }
        if (i+r[i]>mx){
            mx = i+r[i];
            mi = i;
        }
    }
    for (int i=1;i<n;++i){
        addEdge(i-r[i],i+r[i]);
    }
}

int main(){

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif

    init(); manacher();
    LL z = 1; for(int i=2;i<n;++i) if (DSU::Find(i) == i){
        z = z * (26 - deg[i]) % MOD;
    }
    cout << z << endl;
}


