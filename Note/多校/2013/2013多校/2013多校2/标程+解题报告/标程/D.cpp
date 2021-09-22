#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

inline int id(int u, int v) { return (u + v) | (u < v); }
inline int md(int u, int v) { return (u + v) >> 1; }

const int N = 50010;
int h[N << 1];
int g[N << 1];

void down(int u, int v) {
  int d = md(u, v);
  int t = id(u, v);
  int l = id(u, d);
  int r = id(d + 1, v);

  if (!g[t]) {
    g[t] = 1;
    if (h[t] == 0) {
      h[l] = h[r] = 0;
    } else if (h[t] == v - u + 1) {
      h[l] = d - u + 1;
      h[r] = v - (d + 1) + 1;
    }
    g[l] = g[r] = 0;
  }
}

void set(int u, int v, int a, int b) {
  int d = md(u, v);
  int t = id(u, v);
  int l = id(u, d);
  int r = id(d + 1, v);

  if (u == a && v == b) {
    h[t] = v - u + 1;
    g[t] = 0;
    return;
  }

  down(u, v);

  if (b <= d) 
    set(u, d, a, b);
  else if (d + 1 <= a)
    set(d + 1, v, a, b);
  else {
    set(u, d, a, d);
    set(d + 1, v, d + 1, b);
  }

  h[t] = h[l] + h[r];
}

void clear(int u, int v, int a, int b) {
  int d = md(u, v);
  int t = id(u, v);
  int l = id(u, d);
  int r = id(d + 1, v);

  if (u == a && v == b) {
    h[t] = 0;
    g[t] = 0;
    return;
  }

  down(u, v);

  if (b <= d) 
    clear(u, d, a, b);
  else if (d + 1 <= a)
    clear(d + 1, v, a, b);
  else {
    clear(u, d, a, d);
    clear(d + 1, v, d + 1, b);
  }

  h[t] = h[l] + h[r];
}

int find(int u, int v, int a, int b) {
  int d = md(u, v);
  int t = id(u, v);
  int l = id(u, d);
  int r = id(d + 1, v);

  if (!g[t]) {
    if (h[t] == v - u + 1)
      return b - a + 1;
    else if (h[t] == 0)
      return 0;
  }

  if (u == a && v == b) {
    return h[t];
  }

  if (b <= d) 
    return find(u, d, a, b);
  else if (d + 1 <= a)
    return find(d + 1, v, a, b);
  else
    return find(u, d, a, d) + find(d + 1, v, d + 1, b);
}

int n, q;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &q);
    memset(h, 0, sizeof(h));
    memset(g, 0, sizeof(g));
    while (q--) {
      int c, u, v, f;
      int l, r, d, first, second;
      scanf("%d %d %d", &c, &u, &v);
      f = v;
      switch (c) {
        case 1:
          l = u - 1, r = n;
          while (l + 1 < r) {
//          printf("[%d %d]\n", l, r);
            d = (l + r) >> 1;
            if (find(0, n - 1, u, d) < d - u + 1)
              r = d;
            else
              l = d;
          }
          first = r;

          if (first >= n || !f) {
            puts("Can not put any one.");
          } else {
            u = first;
            l = u, r = n;
            while (l + 1 < r) {
              d = (l + r) >> 1;
              if (d - u + 1 - find(0, n - 1, u, d) <= f)
                l = d;
              else
                r = d;
            }
            v = l;

            l = u, r = v + 1;
            while (l + 1 < r) {
              d = (l + r) >> 1;
              if (find(0, n - 1, d, v) < v - d + 1)
                l = d;
              else
                r = d;
            }
            second = l;

            printf("%d %d\n", first, second);
            set(0, n - 1, first, second);
          }
          break;
        case 2:
          printf("%d\n", find(0, n - 1, u, v));
          clear(0, n - 1, u, v);
          break;
      }
    }
    puts("");
  }
  return 0;
}
