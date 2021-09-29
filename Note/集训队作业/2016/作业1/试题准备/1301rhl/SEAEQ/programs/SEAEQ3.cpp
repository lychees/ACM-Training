#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int ljz = 1000000007;
int Tm(int x, int y){long long a = x, b = y; return (a * b) % ljz;}
int fpm(int x, int y){int p = 1, s = x; for (; y; y >>= 1){if (y & 1) p = Tm(p, s); s = Tm(s, s); } return p;}
void MOD(int &x){if (x >= ljz) x -= ljz; if (x < 0) x += ljz;}

int fact[1000], ifact[1000];
int cnt[502][124752];
int p[100], _n;
void prepare(int n){
  int i, j, k;
  cnt[1][0] = 1;
  for (i = 2; i <= n; i++)
    for (j = 0; j <= ((i * (i - 1)) >> 1); j++){
      cnt[i][j] = 0;
      for (k = 0; k < i && k <= j; k++)
	MOD(cnt[i][j] += cnt[i - 1][j - k]);
    }
}

int main(){
  int T, n, E, ans = 0;
  for (int i = fact[0] = 1; i < 1000; i++) fact[i] = Tm(fact[i - 1], i);
  for (int i = 0; i < 1000; i++) ifact[i] = fpm(fact[i], ljz - 2);
  _n = 0;
  freopen("SEAEQ.in", "r", stdin); freopen("SEAEQ.ans", "w", stdout);
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
