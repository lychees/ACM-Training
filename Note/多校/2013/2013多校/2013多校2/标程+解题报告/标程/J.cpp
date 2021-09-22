#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
using namespace std;


const int MAXN = 50;
const int MAXM = 300;

int n, m, w, best;
int mrk[MAXN], used[MAXM], ans[MAXN];
int fruitleft[MAXN];
int fid[MAXM][MAXN], fidn[MAXM];
int p[MAXN], pn;

struct Cut {
    int f[MAXM], n, t, id;
    bool operator < (const Cut& rhs) const {
        if (t != rhs.t) return t < rhs.t;
        return id < rhs.id;
    }
} cut[MAXN];

int check(int x) {
    return fruitleft[x] >= 3;
}

int estimate(int start) {
    int i, tot = 0, last = start;
    pn = 0;
    for (i = start + 1; i < n && cut[i].t - cut[last].t <= w; ++i) {
        if (check(i)) {
            ++tot;
            p[pn++] = i;
            last = i;
        }
    }
    return tot;
}

void mrkcut(int x) {
    mrk[x] = true;
    for (int i = 0; i < cut[x].n; ++i) {
        used[cut[x].f[i]]++;
        if (used[cut[x].f[i]] == 1)
        for (int j = 0; j < fidn[cut[x].f[i]]; ++j) {
            fruitleft[fid[cut[x].f[i]][j]]--;
        }
    }
}

void unmrkcut(int x) {
    mrk[x] = false;
    for (int i = 0; i < cut[x].n; ++i) {
        used[cut[x].f[i]]--;
        if (used[cut[x].f[i]] == 0) 
        for (int j = 0; j < fidn[cut[x].f[i]]; ++j) {
            fruitleft[fid[cut[x].f[i]][j]]++;
        }
    }
}


void dfs(int cur, int dep) {
    if (cur > best) {
        best = cur;
        memcpy(ans, mrk, sizeof(mrk));
    }
    if (dep+1 >=n) {
        return;
    }
    int i, j;
    for (i=dep+1; i <n && cut[i].t - cut[dep].t <= w; ++i) {
        if (!check(i)) {
            continue;
        }
        mrkcut(i);
        if (estimate(i) + cur + 1 > best) {
            dfs(cur + 1, i);
        }
        unmrkcut(i);
    }   
}

int main() {
    int t, i, j;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &w);
        assert(n<=30);
        assert(m<=200);
        assert(w<=100);
        for (i=0;i<n;++i) {
            scanf("%d%d", &cut[i].n, &cut[i].t);
            assert(cut[i].n<=10);
            assert(cut[i].t<=2000);
            for (j=0;j<cut[i].n;++j) {
                scanf("%d", &cut[i].f[j]);
            }
            cut[i].id = i+1;
        }
        sort(cut, cut+n);
        best = 0;
        memset(mrk, 0, sizeof(mrk));
        memset(used, 0, sizeof(used));
        for (i=0;i<n;++i) fruitleft[i] = cut[i].n;
        
        memset(fidn, 0, sizeof(fidn));
        for (i=0;i<n;++i) {
            for (j=0;j<cut[i].n;++j) {
                fid[cut[i].f[j]][fidn[cut[i].f[j]]++] = i;
            }
        }
        
        for (i=0;i<n;++i) {
            mrkcut(i);
            dfs(1, i);      
            unmrkcut(i);
        }
        
        printf("%d\n", best);
        memcpy(mrk, ans, sizeof(ans));
        j = 0;
        for (i=0;i<n;++i) {
            if (mrk[i]) ans[j++] = cut[i].id;
        }
        sort(ans, ans+j);
        if (j) {
            printf("%d", ans[0]);
        }
        for (i=1;i<j;++i) {
            printf(" %d", ans[i]);
        }
        puts("");
    }
    return 0;
}