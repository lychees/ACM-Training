//For Tsinsen
#include <cstdio>
#include <cstdlib>
#include <cmath>

typedef long long int ll;
typedef long double lf;
const ll ljz = 135435435ll << 25 | 1;
ll Tm(ll x, ll y){
  lf D = lf(x) * lf(y) / lf(ljz);
  ll r = x * y - ll(D) * ljz;
  while (r >= ljz) r -= ljz; while (r < 0) r += ljz;
  return r;
}
const ll p = 172846192823333ll;
void MOD(ll &x){if (x >= ljz) x -= ljz; if (x < 0) x += ljz;}

const int sz = 3214567;
int node[sz], next[sz], e;
ll X[sz];
void clr()
{for (int i = 1; i <= e; i++) {node[X[i] % sz] = 0; next[i] = X[i] = 0;} e = 0;}
void add(ll x){int s = x % sz; e++; next[e] = node[s]; node[s] = e; X[e] = x;}
int has(ll x){int s = x % sz, j; for (j = node[s]; j; j = next[j]) if (X[j] == x) return 1; return 0;}

int a[17][17];
ll h[17][17][17][17], P[300];
int n, m, CrLf = 1013;
int check(){
  int i, j, k, l, ANS = 0;
  clr();
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++){
      h[i][j][i][j] = a[i][j] + 1;
      for (k = j + 1; k <= m; k++){
	MOD(h[i][j][i][k] = h[i][j][i][k - 1] + Tm(a[i][k] + 1, P[k - j]));
	MOD(h[i][j][i][k] += Tm(CrLf, P[k - j + 1]));
      }
    }
  for (i = n; i; i--)
    for (j = 1; j <= m; j++)
      for (k = i + 1; k <= n; k++)
	for (l = j; l <= m; l++)
	  MOD(h[i][j][k][l] = Tm(h[i + 1][j][k][l], P[l - j + 2]) + h[i][j][i][l]);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
      for (k = i; k <= n; k++)
	for (l = j; l <= m; l++)
	  if (!has(h[i][j][k][l])){
	    ANS++;
	    add(h[i][j][k][l]);
	  }
  return ANS;
}

FILE *fin, *fout, *fans, *flog;
void report(char *s){fprintf(flog, s); exit(0);}

char s[22][22];
int main(int ac, char *av[]){
  int i, j, t, K;
  double TAT = 0, mine;
  for (i = P[0] = 1; i < 300; i++) P[i] = Tm(P[i - 1], p);
  fin = fopen(av[1], "r"); fout = fopen(av[2], "r"); fans = fopen(av[3], "r");
  flog = fopen(av[4], "w");
  fscanf(fin, "%d", &t);
  while (t--){
    fscanf(fin, "%d %d %d", &n, &m, &K);
    for (i = 1; i <= n; i++){
      if (fscanf(fout, "%s", s[i] + 1) != 1)
	report("0 Output too short!");
      for (j = 1; j <= m; j++)
	if (s[i][j] != 'A' && s[i][j] != 'C' && s[i][j] != 'G' && s[i][j] != 'T') report("0 Strange character or output too short!");
      if (s[i][m + 1]) report("0 output too long!");
    }
    for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++)
	if (s[i][j] == 'A') a[i][j] = 0;
	else if (s[i][j] == 'C') a[i][j] = 1;
	else if (s[i][j] == 'T') a[i][j] = 2;
	else a[i][j] = 3;
    TAT += fabs(check() - K) / K;
  }
  fscanf(fans, "%lf", &mine);
  fprintf(flog, "%.10lf", pow(mine / TAT, 23.33));
  return 0;
}
