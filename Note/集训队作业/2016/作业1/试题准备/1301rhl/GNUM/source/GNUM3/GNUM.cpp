#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int sz = 4000020;
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
int n, N, M, G, pr[8044];
int a[402], b[402], g[402][402], pra[402][12], prb[402][12];
map <int, int> p_have, emp;

void getp(int x, int *q){
  int i;
  q[0] = 0;
  for (i = 2; i * i <= x; i++)
    if (x % i == 0){
      while (x % i == 0) x /= i;
      q[++q[0]] = i;
    }
  if (x != 1) q[++q[0]] = x;
}

void doit(){
  int i, j, k, l;
  for (i = 1; i <= e; i++) next[i] = to[i] = cap[i] = f[i] = 0;
  for (i = 1; i <= T; i++) node[i] = 0;
  for (i = 1; i <= n; i++) for (j = 1; j <= n; j++) bh[i][j] = 0;
  N = M = G = T = e = 0; p_have = emp;

  cin >> n;
  for (i = 1; i <= n; i++){
    cin >> a[i];
    getp(a[i], pra[i]);
    for (j = 1; j <= pra[i][0]; j++)
      if (!p_have[pra[i][j]]){
	p_have[pra[i][j]] = ++G;
	pr[G] = pra[i][j];
      }
  }
  for (i = 1; i <= n; i++){
    cin >> b[i];
    getp(b[i], prb[i]);
    for (j = 1; j <= prb[i][0]; j++)
      if (!p_have[prb[i][j]]){
	p_have[prb[i][j]] = ++G;
	pr[G] = prb[i][j];
      }
  }

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++){
      g[i][j] = gcd(a[i], b[j]);
      if (a[i] < b[j] && g[i][j] > 1) bh[i][j] = ++N;
      else if (a[i] > b[j] && g[i][j] > 1) bh[i][j] = ++M;
    }
  S = 1; T = N + M + G + 2;

  for (i = 1; i <= N; i++) ins(S, i + 1);
  for (i = 1; i <= M; i++) ins(N + 1 + i, T);

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (g[i][j] > 1){
	l = 1;
	for (k = 1; k <= pra[i][0]; k++){
	  for (; l <= prb[j][0] && prb[j][l] < pra[i][k]; l++);
	  if (l <= prb[j][0] && prb[j][l] == pra[i][k])
	    if (a[i] < b[j]) ins(bh[i][j] + 1, p_have[prb[j][l]] + N + M + 1);
	    else if (a[i] > b[j])
	      ins(p_have[prb[j][l]] + N + M + 1, bh[i][j] + N + 1);
	}
      }

  l = 0;
  while (bfs()) l += dfs(S, 1000000000);
  printf("%d\n", l);
  fprintf(stderr, "%d %d %d %d\n", N, M, G, e);
  //for (int i = 1; i <= 100000000; i++);
}

int main(){
  int T;
  scanf("%d", &T);
  while (T--) doit();
  return 0;
}
