#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
#define in inline
#define re register
namespace Mer{
  int x = 986504542, X = 104857601 ^ 1073741824;
  in int ran(){
    x <<= 1;
    if (x > 1073741823) x ^= X;
    return x;
  }
};
const int p = 23333;
const int sz = 3214567;
class Hash{
public:
  int node[sz], next[sz], e;
  int X[sz];
  in void clr()
  {for (re int i = 1; i <= e;i++){int s = X[i] % sz; if (s < 0) s = -s; node[s] = 0; next[i] = X[i] = 0;}e = 0;}
  in void add(re int x){re int s = x % sz; if (s < 0) s = -s; e++; next[e] = node[s]; node[s] = e; X[e] = x;}
  in int has(re int x){re int s = x % sz, j; if (s < 0) s = -s; for (j = node[s]; j; j = next[j]) if (X[j] == x) return 1; return 0;}
} H1, H2;
int h[17][17][17][17], P[300];
int n, m, CrLf = 1013, ANS = 0;
int check(int a[17][17]){
  re int i, j, k, l;
  ANS = 0; H1.clr();
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++){
      h[i][j][i][j] = a[i][j] + 1;
      for (k = j + 1; k <= m; k++){
    h[i][j][i][k] = h[i][j][i][k - 1] + (a[i][k] + 1) * P[k - j];
    h[i][j][i][k] += CrLf * P[k - j + 1];
      }
    }
  for (i = n; i; i--)
    for (j = 1; j <= m; j++)
      for (k = i + 1; k <= n; k++)
    for (l = j; l <= m; l++)
      h[i][j][k][l] = h[i + 1][j][k][l] * P[l - j + 2] + h[i][j][i][l];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
      for (k = i; k <= n; k++)
    for (l = j; l <= m; l++)
      if (!H1.has(h[i][j][k][l])){
        ANS++;
        H1.add(h[i][j][k][l]);
      }
  return ANS;
}
int K, Q[17][17], BEST[17][17], BESTANS;
void update(int X[17][17], int A){
  BESTANS = A;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) BEST[i][j] = X[i][j];
}
void load(int X[17][17], int &A){
  A = BESTANS;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) X[i][j] = BEST[i][j];
}
void NEXT(int &i, int &j){j++; if (j > m) j = 1, i++;}
void find1(){
  int i, j, t = 0, li, lj, r = (n * m) >> 1, nowa = n * m;
  li = lj = 1;
  for (i = 1; i <= n; i++) for (j = 1; j <= m; j++) Q[i][j] = 0;
  for (i = j = 1; i <= n; NEXT(i, j)){
    t++; Q[i][j] = 1;
    if (t == r){
      t = 0; r >>= 1; if (r < 1) r = 1;
      check(Q);
      if (abs(ANS - K) > abs(nowa - K)){
    for (; li < i || (li == i && lj <= j); NEXT(li, lj)) Q[li][lj] = 0;
    ANS = nowa;
      } else {nowa = ANS; li = i; lj = j; NEXT(li, lj);}
    }
  }
  if (abs(nowa - K) < abs(BESTANS - K)) update(Q, nowa);
}
void find2(){
  int i, j, t = 0, li, lj, r = (n * m) >> 1, nowa = n * m;
  li = lj = 1;
  for (i = 1; i <= n; i++) for (j = 1; j <= m; j++) Q[i][j] = 0;
  for (i = j = 1; i <= n; NEXT(i, j)){
    t++; Q[i][j] = Mer::ran() & 3;
    if (t == r){
      t = 0; r >>= 1; if (r < 1) r = 1;
      check(Q);
      if (abs(ANS - K) < abs(BESTANS - K)) update(Q, ANS);
      if (ANS > K){
    for (; li < i || (li == i && lj <= j); NEXT(li, lj)) Q[li][lj] = 0;
      } else {nowa = ANS; li = i; lj = j; NEXT(li, lj);}
    }
  }
  if (abs(nowa - K) < abs(BESTANS - K)) update(Q, nowa);
  ANS = nowa;
}
int x, y, a[17][17];
void insert(int debug){
  int i, j;
  H2.clr();
  h[x][y][x][y] = a[x][y] + 1 + p * CrLf;
  for (j = y - 1; j; j--)
    h[x][j][x][y] = a[x][j] + 1 + p * h[x][j + 1][x][y];
  for (i = x - 1; i; i--)
    for (j = y; j; j--)
      h[i][j][x][y] = h[i + 1][j][x][y] * P[y - j + 2] + h[i][j][i][y];
  for (i = x; i; i--)
    for (j = y; j; j--)
      if (!H1.has(h[i][j][x][y]) && !H2.has(h[i][j][x][y])){
    ANS++;
    if (debug) H2.add(h[i][j][x][y]);
    else H1.add(h[i][j][x][y]);
      }
  y++; if (y > m){y = 1; x++;}
}
void find22(){
  int i, j, ox, oy, oa, b, _ = 0, lll = 0;
  double sc = 0, bc = 0;
  x = y = 1; ANS = 0; H1.clr();
  for (i = 1; i <= n; i++) for (j = 1; j <= m; j++) lll += i * j;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++){
       _ += i * j; sc = 1.0 * _ * K / lll; bc = 1000000000;
      for (a[i][j] = 0; a[i][j] < 4; a[i][j]++){
    ox = x; oy = y; oa = ANS;
    insert(1);
    if (abs(ANS - sc) < bc){
      bc = abs(ANS - sc); b = a[i][j];
    }
    x = ox; y = oy; ANS = oa;
      }
      a[i][j] = b; insert(0);
    }
  if (abs(ANS - K) < abs(BESTANS - K)) update(a, ANS);
}
int tot_cases;
int S[17][17], PS;
void find3(){
  int i, j, d, r = 50000000 / (n * m * n * m * tot_cases), q, P, k, b;
  while (r--){
    i = rand() % n + 1; j = rand() % m + 1;
    q = Q[i][j]; P = ANS; k = q; b = ANS;
    for (Q[i][j] = 0; Q[i][j] <= 3; Q[i][j]++){
      if (Q[i][j] == q) d = P;
      else d = check(Q);
      if (abs(d - K) < abs(b - K)) b = d, k = Q[i][j];
    }
    ANS = b; Q[i][j] = k;
  }
  update(Q, ANS);
}
void find4(int r){
  double e = 0.05;
  int i, j, d, q, P, k, b;
  while (r--){
    if (BESTANS == K) return;
    i = Mer::ran() % n + 1; j = Mer::ran() % m + 1; q = Q[i][j]; b = ANS;
    do{Q[i][j] = Mer::ran() & 3;} while (Q[i][j] == q);
    P = check(Q);
    if (abs(P - K) < abs(b - K) || rand() < e * RAND_MAX){
      if (abs(P - K) < abs(BESTANS - K)) update(Q, P);
    } else {ANS = b; Q[i][j] = q;}
  }
}
double score = 0;
void doit(){
  int i, j;
  scanf("%d %d %d", &n, &m, &K);
  if (K <= n * m){
    for (i = 1; i <= n; i++){
      for (j = 1; j <= m; j++)
    putchar('A');
      putchar('\n');
    }
#ifndef ONLINE_JUDGE
    fprintf(stderr, "%d\n", n * m - K);
#endif
    score += 1.0 * (n * m - K) / K;
    return;
  }
  BESTANS = 1 << 28;
  //find1();
  for (i = 1; i <= n; i++) for (j = 1; j <= m; j++) Q[i][j] = 0; ANS = n * m;
  find2();
  if (BESTANS != K) find22();
  load(Q, ANS);
  int r = 17000000 / (n * m * n * m * tot_cases);
  if (n * m > 10)
    if (n * m <= 81 || K <= 500)
      r = 130000000 / (n * m * n * m * tot_cases);
  if (K > 10000) r *= 0.5;
  find4(r);
  for (i = 1; i <= n; i++){
    for (j = 1; j <= m; j++)
      putchar(BEST[i][j]["ACTG"]);
    putchar('\n');
  }
#ifndef ONLINE_JUDGE
  fprintf(stderr, "%d\n", abs(BESTANS - K));
#endif
  score += 1.0 * abs(BESTANS - K) / K;
}
int main(){
  int t, i;
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
  freopen("TAT.txt", "w", stderr);
#endif
  for (i = P[0] = 1; i < 300; i++) P[i] = P[i - 1] * p;
  scanf("%d", &t); tot_cases = t;
  while (t--) doit();
#ifndef ONLINE_JUDGE
  fprintf(stderr, "%.10lf\n", score);
#endif
  return 0;
}
