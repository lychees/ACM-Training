#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 50010;
const int M = N + N;
typedef __int64 ll;

int n, c;
int val[N], trap[N];
ll f[N][4], g[N][4];
int q[N], s, t;
int en, hd[N], dep[N];
int pv[M], vo[M];

void init(int n) {
  en = 0;
  memset(hd, -1, sizeof(int) * n);
}

void add(int u, int v) {
  vo[en] = v;
  pv[en] = hd[u];
  hd[u] = en++;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &c); init(n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &val[i], &trap[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      int u, v; scanf("%d %d", &u, &v);
      add(u, v);
      add(v, u);
    }

    // build
    memset(dep, -1, sizeof(dep[0]) * n);
    dep[0] = 0;
    s = t = 0;
    q[t++] = 0;
    while (s < t) {
      int u = q[s++];
      for (int z = hd[u]; z > -1; z = pv[z]) {
        int v = vo[z];
        if (dep[v] == -1) {
          dep[v] = dep[u] + 1;
          q[t++] = v;
//        printf("%d -> %d\n", u, v);
        }
      }
    }

    for (int i = 0; i < n; i++)
      for (int k = 0; k <= c; k++)
        f[i][k] = g[i][k] = 0;

    for (int i = n - 1; i >= 0; i--) {
      int u = q[i];
      for (int k = trap[u]; k <= c; k++) {
        for (int z = hd[u]; z > -1; z = pv[z]) {
          int v = vo[z];
          if (dep[v] <= dep[u]) continue;
          if (f[v][k - trap[u]]) f[u][k] = max(f[u][k], val[u] + f[v][k - trap[u]]);
          if (g[v][k - trap[u]]) g[u][k] = max(g[u][k], val[u] + g[v][k - trap[u]]);
        }
      }
      f[u][trap[u]] = max(f[u][trap[u]], (ll)val[u]);
      if (trap[u])
        g[u][1] = max(g[u][1], (ll)val[u]);
//    for (int k = 0; k <= c; k++)
//      printf("%d %d: %d %d\n", u, k, f[u][k], g[u][k]);
    }

    ll ans = 0;
    ll ff1[4], gg1[4];
    ll ff2[4], gg2[4];
    for (int i = n - 1; i >= 0; i--) {
      int u = q[i];
      for (int k = 0; k <= c; k++) {
        if (k < c) ans = max(ans, f[u][k]);
        ans = max(ans, g[u][k]);
      }
      memset(ff1, 0, sizeof(ff1));
      memset(gg1, 0, sizeof(gg1));
      memset(ff2, 0, sizeof(ff2));
      memset(gg2, 0, sizeof(gg2));
      for (int k = 0; k <= c; k++) {
        for (int z = hd[u]; z > -1; z = pv[z]) {
          int v = vo[z];
          if (dep[v] <= dep[u]) continue;
          if (f[v][k] >= ff1[k]) {
            ff2[k] = ff1[k];
            ff1[k] = f[v][k];
          } else if (f[v][k] > ff2[k]) {
            ff2[k] = f[v][k];
          }
          if (g[v][k] >= gg1[k]) {
            gg2[k] = gg1[k];
            gg1[k] = g[v][k];
          } else if (g[v][k] > gg2[k]) {
            gg2[k] = g[v][k];
          }
        }
      }

      for (int kk = trap[u]; kk <= c; kk++) {
        for (int k = 0; k <= c; k++) {
          for (int z = hd[u]; z > -1; z = pv[z]) {
            int v = vo[z];
            if (dep[v] <= dep[u]) continue;
            int k1 = kk - trap[u] - k;
            if (k1 < 0) continue;
            if (kk < c) {
              if (f[v][k1] != ff1[k1]) {
                if (f[v][k] && ff1[k1])
                  ans = max(ans, val[u] + f[v][k] + ff1[k1]);
              } else {
                if (f[v][k] && ff2[k1])
                  ans = max(ans, val[u] + f[v][k] + ff2[k1]);
              }
            } else {
              if (g[v][k1] != gg1[k1]) {
                if (f[v][k] && gg1[k1])
                  ans = max(ans, val[u] + f[v][k] + gg1[k1]);
              } else {
                if (f[v][k] && gg2[k1])
                  ans = max(ans, val[u] + f[v][k] + gg2[k1]);
              }
            }
          }
        }
      }
    }
    printf("%I64d\n", ans);
  }
  return 0;
}
