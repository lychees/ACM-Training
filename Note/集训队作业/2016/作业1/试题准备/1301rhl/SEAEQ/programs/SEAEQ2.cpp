#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int ljz = 1000000007;
int Tm(int x, int y){long long a = x, b = y; return (a * b) % ljz;}
int fpm(int x, int y){int p = 1, s = x; for (; y; y >>= 1){if (y & 1) p = Tm(p, s); s = Tm(s, s); } return p;}
void MOD(int &x){if (x >= ljz) x -= ljz; if (x < 0) x += ljz;}

int fact[1000];
int cnt[100][5000];
int p[100], _n;
void prepare(int n){
  int i, j, k;
  for (i = 1; i <= n; i++) p[i] = i;
  do {
    i = 0;
    for (j = 1; j <= n; j++)
      for (k = 1; k < j; k++)
	if (p[j] < p[k]) i++;
    cnt[n][i]++;
  } while (next_permutation(p + 1, p + n + 1));
}

int main(){
  int T, n, E, ans = 0;
  for (int i = fact[0] = 1; i < 1000; i++) fact[i] = Tm(fact[i - 1], i);
  _n = 0;
  freopen("SEAEQ.in", "r", stdin); freopen("SEAEQ.out", "w", stdout);
  scanf("%d", &T);
  while (T--){
    scanf("%d %d", &n, &E); ans = 0;
    while (_n < n){_n++; prepare(_n);}
    for (int x = 1; x <= n; x++){
      int tmp = Tm(fact[n], fpm(fact[x], ljz - 2)), s = 0;
      for (int i = 0; i <= E; i++) MOD(s += cnt[x][i]);
      MOD(ans += Tm(Tm(n - x + 1, s), Tm(tmp, tmp)));
    }
    printf("%d\n", ans);
  }
  return 0;
}
