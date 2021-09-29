#include <cstdio>
#include <cstdlib>
#include <cstring>
int gcd(int x, int y){return y ? gcd(y, x % y) : x;}
int bh[120][120];
int n, a[120], b[120], ans = 0;
int F[66666];
void dfs(int s, int d){
  int i, j, p, q;
  if (d > ans) ans = d;
  if (F[s]) return; F[s] = 1;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (b[j] > a[i] && gcd(a[i], b[j]) != 1)
	if (0 == (s & bh[i][j]))
	  for (p = 1; p <= n; p++)
	    for (q = 1; q <= n; q++)
	      if (b[p] < a[q] && gcd(a[q], b[p]) != 1)
		if (gcd(gcd(a[i], b[j]), gcd(a[q], b[p])) > 1)
		  if (0 == (s & bh[q][p]))
		    dfs(s | bh[i][j] | bh[q][p], d + 1);
}

void doit(){
  int i, j, k = 1;
  memset(bh, 0, sizeof bh);
  memset(F, 0, sizeof F);
  scanf("%d", &n);
  for (i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (i = 1; i <= n; i++) scanf("%d", &b[i]);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++){
      bh[i][j] = k; k <<= 1;
    }
  ans = 0; dfs(0, 0);
  printf("%d\n", ans);
}

int main(){
  int T;
  scanf("%d", &T);
  while (T--) doit();
  return 0;
}
