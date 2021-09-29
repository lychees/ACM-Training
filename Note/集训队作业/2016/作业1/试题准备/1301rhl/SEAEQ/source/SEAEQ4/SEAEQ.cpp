#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int ljz = 1000000007;
int Tm(int x, int y){long long a = x, b = y; return (a * b) % ljz;}
int fpm(int x, int y){int p = 1, s = x; for (; y; y >>= 1){if (y & 1) p = Tm(p, s); s = Tm(s, s); } return p;}
void MOD(int &x){if (x >= ljz) x -= ljz; if (x < 0) x += ljz;}

int fact[1000], ifact[1000];
int scnt[502][124752];
int p[100], _n;
#define Scnt(a, b) (b < 0 ? 0 : scnt[a][min(((a) * (a - 1)) >> 1, b)])
void prepare(int i){
  int j;
  scnt[i][0] = 1;
  for (j = 1; j <= ((i * (i - 1)) >> 1); j++){
    MOD(scnt[i][j] = scnt[i][j - 1] + Scnt(i - 1, j));
    MOD(scnt[i][j] = scnt[i][j] - Scnt(i - 1, j - i));
  }
}

int main(){
  int T, n, E, ans = 0;
  for (int i = fact[0] = 1; i < 1000; i++) fact[i] = Tm(fact[i - 1], i);
  for (int i = 0; i < 1000; i++) ifact[i] = fpm(fact[i], ljz - 2);
  _n = 0;
  scanf("%d", &T);
  while (T--){
    scanf("%d %d", &n, &E); ans = 0;
    while (_n < n){_n++; prepare(_n);}
    for (int x = 1; x <= n; x++){
      int tmp = Tm(fact[n], ifact[x]), s = Scnt(x, E);
      MOD(ans += Tm(Tm(n - x + 1, s), Tm(tmp, tmp)));
    }
    printf("%d\n", ans);
  }
  return 0;
}
