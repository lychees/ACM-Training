#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>

#define REP(i, n) for (int i=0;i<n;++i)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin();it!=A.end();++it)
#define fi first
#define se second
using namespace std;

const int N = int(2e5) + 9, Z = 26;

namespace SAM{

    int trans[N][Z], len[N], fail[N], cnt[N], tail, tot;
    char str[N]; int st[N];

    inline int new_node(){
        memset(trans[tot], 0, sizeof(*trans));
        fail[tot] = 0;
        cnt[tot] = 0;
        tail = tot;
        return tot++;
    }

    inline int new_node(int u){
        memcpy(trans[tot], trans[u], sizeof(*trans));
        fail[tot] = fail[u];
        cnt[tot] = cnt[u];
        return tot++;
    }

    #define v trans[u][c]
    #define p fail[u]
    #define pp fail[uu]

    int Ext(int c){
        int u = tail, uu = new_node(); len[uu] = len[u] + 1;
        while (u && !v) v = uu, u = p; // 向上遍历没有 c-转移 的祖先 ..
        if (!u && !v) v = uu, pp = 0;
        else{
            if (len[v] == len[u] + 1) pp = v;
            else{
                int _v = v, vv = new_node(_v); len[vv] = len[u] + 1;
                fail[_v] = pp = vv;
                while (v == _v) v = vv, u = p;
                if (!u && v == _v) v = vv;
            }
        }
        return uu;
    }

#define c (*cur - 'A')

    void Init(char *cur){
        tot = 0; new_node(); for (;*cur;++cur) Ext(c);
        for (int u = tail; u; u = p) cnt[u] = 1;
    }

    int Query(char *cur){
        int u = 0, i = 0, z = 0; for (;*cur;++cur){
            if (!v) break;
            ++i; u = v;
            if (cnt[u]) z = i;
        }
        return z;
    }

} using namespace SAM;

vector<pair<int, int> > qry[N];
int ans[N]; int n, m;

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    while (~scanf("%d %d", &n, &m)){

        REP(i, n){
            scanf("%s", str + st[i]);
            st[i+1] = st[i] + strlen(str + st[i]) + 1;
            qry[i].clear();
        }

        REP(i, m){
            int l, r; scanf("%d %d", &l, &r); --l, --r;
            qry[l].push_back(make_pair(r, i));
        }

        REP(l, n) if (qry[l].size()){
            unordered_map<int, int> cache;
            Init(str + st[l]);
            ECH(it, qry[l]){
                int r = it->fi, id = it->se;
                if (cache.find(r) != cache.end()) ans[id] = cache[r];
                else{
                    ans[id] = Query(str + st[r]);
                    cache[r] = ans[id];
                }
            }
        }

        REP(i, m) printf("%d\n", ans[i]);
    }
}
