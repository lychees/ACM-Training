#include <lastweapon/io>
using namespace lastweapon;

const int N = int(2e3) + 9, QN = int(2e5) + 9;
vector<array<int,2>> adj[N];
vector<array<int,3>> qry[N];
int par[N], in[N], out[N];
LL dep[N], pre[N], suf[N], ans[QN], ww;
int n, t, qn;

void dfs(int u, int p) {
    in[u] = t++;
    for (auto [v, w]: adj[u]) if (v != p) {
        par[v] = u; dep[v] = dep[u] + w;
        dfs(v, u);
    }
    out[u] = t;
}

bool anc(int u, int v) {
    return in[u] <= in[v] && in[v] < out[u];
}


int main(){

#ifndef ONLINE_JUDGE
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

	RD(n, qn); DO(n-1) {
	    int u, v, w; RD(u, v, w); --u; --v;
	    adj[u].PB({v,w});
	    adj[v].PB({u,w});
	    ww += w;
	}
	ww *= 2;

	REP(i, qn) {
	    int s, k, t; RD(s, k, t); --s; --k; --t;
	    qry[s].PB({k, t, i});
	}

	REP(s, n) {
        t = 0; dep[s] = 0; dfs(s, -1);
        REP(i, n) pre[in[i]+1] = suf[in[i]] = dep[i];
        REP_1(i, n) checkMax(pre[i], pre[i-1]);
        DWN(i, n, 0) checkMax(suf[i], suf[i+1]);
        for (auto [k, t, id]: qry[s]) {
            if (anc(t, k)) continue;
            LL &z = ans[id]; z = INFF;
            LL e = max(pre[in[k]],suf[in[k]]);
            while (1) {
                checkMin(z, ww + 2*dep[k] - e);
                if (anc(k, t)) break;
                e = max(pre[in[k]],suf[out[k]]);
                k = par[k];
            }
            z -= 2*dep[k];
        }
	}

	REP(i, qn) {
	    if (!ans[i]) puts("impossible");
	    else printf("%lld\n", ans[i]);
	}
}
