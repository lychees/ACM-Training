#include <cstdio>
#include <cstdlib>
#include <ctime>
#define rnd (rand() * 32768 + rand())

int n, e, t, mode, s;
int main(int ac, char *av[]){
  freopen("s", "r", stdin); scanf("%d", &s); srand(s);
  freopen("SEAEQ.in", "w", stdout);
  sscanf(av[1], "%d", &t);
  sscanf(av[2], "%d", &n);
  sscanf(av[3], "%d", &e);
  sscanf(av[4], "%d", &mode);
  if (mode == 1){
    t = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 0; j + j <= (i * (i - 1)); j++)
	t++;
    printf("%d\n", t);
    for (int i = 1; i <= n; i++)
      for (int j = 0; j + j <= (i * (i - 1)); j++)
	printf("%d %d\n", i, j);
  } else{
    printf("%d\n", t);
    while (t--) printf("%d %d\n", rnd % n + 1, rnd % (e + 1));
  }
  freopen("s", "w", stdout); printf("%d", rnd);
  return 0;
}
