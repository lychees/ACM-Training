#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define REP(i, n) for (int i=0;i<n;++i)
#define FOR(i, a, b) for (int i=a;i<b;++i)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)

typedef long long LL;
const int N = int(5e5) + 9, Z = 26;

namespace SAM{

    int trans[N][Z], fail[N], len[N], tot;
    LL cnt[N];

    int new_node(){
        memset(trans[tot], 0, sizeof(trans[tot]));
        return tot++;
    }
    int new_node(int u){
        memcpy(trans[tot], trans[u], sizeof(trans[tot]));
        fail[tot] = fail[u];
        return tot++;
    }
#define v trans[u][c]
#define p fail[u]
#define pp fail[uu]
    int Ext(int c, int tail){
        int u = tail, uu = new_node(); len[uu] = len[u] + 1;
        while (u && !v) v = uu, u = p;
        if (!v && !v) v = uu, pp = 0;
        else{
            if (len[v] == len[u] + 1) pp = v;
            else{
                int _v = v, vv = new_node(_v); len[vv] = len[u] + 1;
                fail[_v] = pp = vv;
                while (v == _v) v = vv, u = p;
            }
        }
        return uu;
    }
#define c o[i]
    int o[Z]; void getKth(){
        LL k; scanf("%lld", &k);
        if (--k >= cnt[0]) puts("-1");
        else{
            int u = 0; while (k--){
                REP(i, Z) if (v){
                    if (k >= cnt[v]) k -= cnt[v];
                    else{
                        putchar(c+'a');
                        u = v; break;
                    }
                }
            }
        }
        puts("");
    }
#undef c
    vector<int> adj[N]; char buf[N]; int GtoM[N];
    int Q[N], C[N], cz, op; int n, qn;

    void Run(){
        REP(i, tot) C[i] = 0;
        REP(i, tot) ++C[len[i]];
        FOR(i, 1, n+1) C[i] += C[i-1];
        REP(i, tot) Q[--C[len[i]]] = i;

        for (int i=tot-1;i>=0;--i){
            int u = Q[i]; cnt[u] = 1;
            REP(c, Z) if (v) cnt[u] += cnt[v];
        }
        cout << cnt[0] << endl;
        REP(i, qn){
            scanf("%s", buf);  REP(i, Z) o[i] = buf[i]-'a';
            getKth();
        }
    }

    void Init(){
        scanf("%d %d", &n, &qn); scanf("%s", buf);
        REP(i, n) adj[i].clear();

        REP(i, n-1){
            int a, b; scanf("%d %d", &a, &b); --a, --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        tot = 0; new_node();
        GtoM[0] = Ext(buf[0]-'a', 0);
        cz = op = 0; Q[op++] = 0;
#undef v
#define v (*it)
        while(cz < op){
            int u = Q[cz++], tail = GtoM[u];
            ECH(it, adj[u]) if (!GtoM[v]){
                GtoM[v] = Ext(buf[v]-'a', tail);
                Q[op++] = v;
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    SAM::Init(); SAM::Run();
}
