#include <cstdio>
#include <cstdlib>

#define rnd (rand() * 32768 + rand())
void gen(int n, int h){
  printf("%d\n", n);
  for (int i = 1; i <= n; i++) printf("%d%c", rnd % h + 1, " \n"[i == n]);
  for (int i = 1; i <= n; i++) printf("%d%c", rnd % h + 1, " \n"[i == n]);
}
int main(){
  int s, n, t;
  freopen("s", "r", stdin); scanf("%d", &s); srand(s);
  freopen("GNUM.in", "w", stdout);
  t = 10; printf("%d\n", t);
  while (t--) gen(400, rnd % 10000 + 1);
  freopen("s", "w", stdout); printf("%d", rnd);
  return 0;
}
