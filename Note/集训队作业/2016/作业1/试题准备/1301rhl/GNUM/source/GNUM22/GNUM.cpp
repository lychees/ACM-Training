#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int sz = 2000020;
int node[sz], next[sz], to[sz], cap[sz], f[sz], e, S, T;
void ins(int x, int y, int c = 1){
  e++; next[e] = node[x]; node[x] = e; to[e] = y; cap[e] = c; f[e] = 0;
  e++; next[e] = node[y]; node[y] = e; to[e] = x; cap[e] = 0; f[e] = 0;
}

int q[sz], inq[sz], d[sz], R[sz];
int bfs(){
  int i, j, k, l, r;
  for (i = 1; i <= T; i++) inq[i] = 0, d[i] = 1000000000, R[i] = node[i];
  q[l = r = 0] = S; inq[S] = 1; d[S] = 0;
  while (l <= r){
    k = q[l++];
    for (j = node[k]; j; j = next[j])
      if (cap[j] > f[j] && d[to[j]] > d[k] + 1){
	if (!inq[to[j]]) inq[q[++r] = to[j]] = 1;
	d[to[j]] = d[k] + 1;
      }
  }
  return inq[T];
}

int dfs(int x, int a){
  if (x == T) return a;
  int F, fl = 0;
  for (int &j = R[x]; j; j = next[j])
    if (cap[j] > f[j] && d[to[j]] == d[x] + 1){
      F = dfs(to[j], min(a, cap[j] - f[j]));
      fl += F; a -= F; f[j] += F; f[j & 1 ? j + 1 : j - 1] -= F;
      if (a == 0) return fl;
    }
  return fl;
}

int gcd(int x, int y){return y ? gcd(y, x % y) : x;}
int bh[402][402];
int n, N, M;
int a[402], b[402];

void doit(){
  int i, j, k, l;
  for (i = 1; i <= e; i++) next[i] = to[i] = cap[i] = f[i] = 0;
  for (i = 1; i <= T; i++) node[i] = 0;
  for (i = 1; i <= n; i++) for (j = 1; j <= n; j++) bh[i][j] = 0;
  N = M = e = T = 0;

  cin >> n;
  for (i = 1; i <= n; i++) cin >> a[i];
  for (i = 1; i <= n; i++) cin >> b[i];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (a[i] < b[j] && gcd(a[i], b[j]) > 1) bh[i][j] = ++N;
      else if (a[i] > b[j] && gcd(a[i], b[j]) > 1) bh[i][j] = ++M;
  S = 1; T = N + M + 2;

  for (i = 1; i <= N; i++) ins(S, i + 1);
  for (i = 1; i <= M; i++) ins(N + 1 + i, T);

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (a[i] < b[j] && bh[i][j])
	for (k = 1; k <= n; k++)
	  for (l = 1; l <= n; l++)
	    if (a[k] > b[l] && bh[k][l])
	      if (gcd(gcd(a[i], b[j]), gcd(a[k], b[l])) > 1)
		ins(bh[i][j] + 1, bh[k][l] + N + 1);

  l = 0;
  while (bfs()) l += dfs(S, 1000000000);
  printf("%d\n", l);
}

int main(){
  int T;
  scanf("%d", &T);
  while (T--) doit();
  return 0;
}
