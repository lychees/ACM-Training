#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int N = int(5e5) + 9, L = int(1e6) + 9, Z = 26;

namespace ACM{
    int trans[N][Z], fail[N], cnt[N], Q[N], cz, op, tot;
    char str[L]; bool vis[N];

    int new_node(){
        memset(trans[tot], 0, sizeof(trans[tot]));
        fail[tot] = 0;
        cnt[tot] = 0;
        return tot++;
    }

#define v trans[u][c]
#define p fail[u]
#define f trans[p][c]

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
    }

    void Insert(){
        scanf("%s", str);
        int u = 0;
        for (char *cur=str;*cur;++cur){
            int c = *cur - 'a';
            if (!v) v = new_node();
            u = v;
        }
        ++cnt[u];
    }

    void Init(){
        tot = 0; new_node();
        int T; cin >> T; while (T--) Insert();
        Build();
    }

    int Run(){
        scanf("%s", str); fill(vis, vis+tot, false);
        int res = 0, u = 0;
        for (char* cur=str;*cur;++cur){
            int c = *cur - 'a'; u = v;
            for (int t = u; t && !vis[t]; t = fail[t]){
                res += cnt[t];
                vis[t] = true;
            }
        }
        return res;
    }

#undef f
#undef p
#undef v
} using namespace ACM;

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int T; cin >> T; while (T--){
        Init(); cout << Run() << endl;
    }
}
