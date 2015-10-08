#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#define REP(i, n) for (int i=0;i<n;++i)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin();it!=A.end();++it)

using namespace std;

const int N = int(1e5) + 9, Z = 26;

char cmd[N]; int ans[N];
int cn, qn;

int low_bit(int x){
    return x & -x;
}

namespace BIT{

    int C[N], n;

    void Add(int x, int d){
        for (;x<=n;x+=low_bit(x)) C[x] += d;
    }
    int Sum(int x){
        int z = 0; for (;x;x^=low_bit(x)) z += C[x];
        return z;
    }
    int Sum(int l, int r){
        return Sum(r) - Sum(l-1);
    }
} using namespace BIT;

namespace ACM{
    int trans[N][Z], fail[N], cnt[N], Q[N], cz, op, tot;
    int L[N], R[N], pos[N], par[N];
    vector<int> adj[N]; vector<pair<int, int> > qry[N];

    int new_node(){
        memset(trans[tot], 0, sizeof(trans[tot]));
        fail[tot] = 0;
        return tot++;
    }

#define v trans[u][c]
#define f trans[fail[u]][c]

    void dfs(int u = 0){
        L[u] = ++n; ECH(it, adj[u]) dfs(*it); R[u] = n;
        //cout << u << " " << L[u] << endl;
    }

    void Build(){
        cz = op = 0;
        int u = 0; for (int c=0;c<Z;++c)
            if (v) Q[op++] = v;

        while (cz < op){
            int u = Q[cz++]; for (int c=0;c<Z;++c){
                if (v) fail[Q[op++] = v] = f;
                else v = f;
            }
        }

        for (int u=1;u<tot;++u){
            adj[fail[u]].push_back(u);
        }
        n = 0, dfs();
    }

#define p par[u]
#define c (cmd[i] - 'a')

    void Init(){
        tot = 0; new_node(); int u = 0;
        scanf("%s", cmd); cn = strlen(cmd);

        REP(i, cn) switch(cmd[i]){
            case 'P':
                pos[n++] = u;
                break;
            case 'B':
                u = p;
                break;
            default:
                if (!v) v = new_node();
                par[v] = u, u = v;
        }

        Build(); scanf("%d", &qn);
        REP(i, qn){
            int pi, ti; scanf("%d %d", &pi, &ti); --pi, --ti;
            qry[ti].push_back(make_pair(i, pi));
        }
    }

} using namespace ACM;



int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    Init(); int ti = 0, u = 0;

    REP(i, cn) switch(cmd[i]){
        case 'P':
            ECH(it, qry[ti]){
                ans[it->first] = Sum(L[pos[it->second]], R[pos[it->second]]);
            }
            ++ti;
            break;
        case 'B':
            //cout << u << " " << L[u] << endl;
            Add(L[u], -1);
            u = p;
            break;
        default:
            //cout << "   " << u << " " << 1 << endl;
            Add(L[u = v], 1);
            //cout << "   " << Sum(L[u]) << endl;
    }

    REP(i, qn) printf("%d\n", ans[i]);
}
