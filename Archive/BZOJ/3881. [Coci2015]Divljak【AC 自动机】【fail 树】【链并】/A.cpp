#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define REP(i, n) for (int i=0;i<n;++i)
#define ECH(it, A) for (__typeof(A.begin()) it=A.begin(); it != A.end(); ++it)

int low_bit(int x){return x & -x;}
int lg2(int x){return !x ? -1 : 31 - __builtin_clz(x);}

const int N = int(2e6) + 9; //#

namespace BIT{
    int C[N], n;
    void Add(int x, int d){
        for (;x<=n;x+=low_bit(x)) C[x] += d;
    }
    int Sum(int x){
        int z = 0; for(;x;x^=low_bit(x)) z += C[x];
        return z;
    }
    void Init(){
        fill(C+1, C+n+1, 0);
    }
    int Sum(int l, int r){
        return Sum(r) - Sum(l-1);
    }
}
namespace ACM{
    const int Z = 26, LV = 23;
    int trans[N][Z], fail[N], Q[N], cz, op, u, tot;
    char buf[N]; int pos[N];
    vector<int> adj[N]; int L[N], R[N], depth[N];
    int st[N], ST[LV][N*2], nn;

    int new_node(){
        memset(trans[tot], 0, sizeof(trans[tot]));
        fail[tot] = 0;
        return tot++;
    }
#define v trans[u][c]
#define f trans[fail[u]][c]
    void Build(){
        cz = op = u = 0;
        REP(c, Z) if (v) Q[op++] = v;
        while (cz < op){
            u = Q[cz++];
            REP(c, Z){
                if (v) fail[Q[op++] = v] = f;
                else v = f;
            }
        }
    }

#define c (*cur -'a')
    int Insert(){
        scanf("%s", buf);
        u = 0; for (char*cur=buf;*cur;++cur){
            if (!v) v = new_node();
            u = v;
        }
        return u;
    }
    bool cmpByDepth(int a, int b){
        return depth[a] < depth[b];
    }
    int lca(int l, int r){
        l = st[l], r = st[r];
        if (l > r) swap(l, r); ++r;
        int lv = lg2(r-l);
        return min(ST[lv][l], ST[lv][r-(1<<lv)], cmpByDepth);
    }
    void dfs(int u = 0){
        L[u] = ++BIT::n;
        ST[0][st[u] = ++nn] = u;
        ECH(it, adj[u]){
            depth[*it] = depth[u] + 1;
            dfs(*it);
            ST[0][++nn] = u;
        }
        R[u] = BIT::n;
    }
    void Init(){
        tot = 0; new_node(); int n; scanf("%d", &n); REP(i, n){
            pos[i] = Insert();
        }
        Build(); for(int u=1;u<tot;++u){
            adj[fail[u]].push_back(u);
        }
        BIT::n = nn = 0; dfs();
        BIT::Init();
        for (int lv=1;(1<<lv)<=nn;++lv){
            for (int i=1;i+(1<<lv)<=nn+1;++i){
                ST[lv][i] = min(ST[lv-1][i], ST[lv-1][i+(1<<(lv-1))], cmpByDepth);
            }
        }
    }

    int Query(){
        int x; scanf("%d", &x); --x; x = pos[x];
        return BIT::Sum(L[x], R[x]);
    }

    bool cmpByL(int a, int b){
        return L[a] < L[b];
    }

    void AddText(){
        scanf("%s", buf);
        u = 0;
        vector<int> P;
        for(char*cur=buf;*cur;++cur){
            u = v;
            P.push_back(u);
        }

        sort(P.begin(), P.end(), cmpByL); P.erase(unique(P.begin(), P.end()), P.end());
        BIT::Add(L[P[0]], 1);

        for(int i=1;i<P.size();++i){
            BIT::Add(L[P[i]], 1);
            BIT::Add(L[lca(P[i-1],P[i])], -1);
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif

    ACM::Init(); int Q; cin >> Q; while (Q--){
        int cmd; scanf("%d", &cmd);
        if (cmd == 1){
            ACM::AddText();
        }
        else{
            printf("%d\n", ACM::Query());
        }
    }
}

