#include <cstdio>
#include <cstdlib>
#include <ctime>

int n, e, t, mode;
int main(int ac, char *av[]){
  srand(time(0));
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
    if (mode == 2) {
      t = rand() % t + 1; n = rand() % n + 1; e = rand() % e + 1;
      fprintf(stderr, "%d %d %d\n", t, n, e);
    }
    printf("%d\n", t);
    while (t--) printf("%d %d\n", rand() % n + 1, rand() % (e + 1));
  }
  return 0;
}
