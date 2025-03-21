#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
#define ran (rand() * 32768 + rand())
const int X = 1000000000;

void gen1(int n, int l, int r){
  printf("%d\n", n);
  for (int i = 1; i <= n + n; i++)
    printf("%d%c", ran % (r - l + 1) + l, " \n"[i % n == 0]);
}

void gen2(int n, int p){
  printf("%d\n", n);
  int T = X / p;
  for (int i = 1; i <= n + n; i++)
    printf("%d%c", p * (ran % T + 1), " \n"[i % n == 0]);
}

void gen3(int n, int *p, int k){
  int P = 1, i, j, T;
  printf("%d\n", n);
  for (i = 1; i <= k; i++) P *= p[i];
  for (int x = 1; x <= n + n; x++){
    i = ran % k + 1;
    T = X / (P / p[i]);
    do {j = ran % T + 1;} while (j % p[i] == 0);
    printf("%d%c", j * (P / p[i]), " \n"[x % n == 0]);
  }
}

int gcd(int x, int y){return y ? gcd(y, x % y) : x;}
void gen4(int n, int x, int y){
  int i, j, k;
  printf("%d\n", n);
  for (i = 1; i <= n + n; i++){
    if (i == n + 1) swap(x, y);
    k = (ran % (X / x) + 1) * x;
    printf("%d%c", k, " \n"[i % n == 0]);
  }
}

int p[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23};
int q[20] = {0, 7, 11, 13, 17};
int N[100] = {4, 4, 4, 4, 4,
	      15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	      30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	      50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	      100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	      200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
	      300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
	      400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
char cmd[20];
int l[10] = { 1,    1,      1,        1,          1, 30000000};
int r[10] = {10, 1000, 100000, 10000000, 1000000000, 50000000};
int P[5] = {2, 7, 40, 10000, 10000000};
int _[2] = {26775, 19008};

int main(){
  int T, n;
  srand(1999031603);
  for (int cs = 98; cs < 100; cs++){
    fprintf(stderr, "Gen data %d\n", cs);
    for (int i = 1; i <= 10000; i++) rand();
    freopen("GNUM.in", "w", stdout);
    printf("%d\n", T = 10);
    while (T--){
      n = N[cs];
      if (0 && rand() % 4 == 0){
	int x = rand() % 6;
	gen1(n, l[x], r[x]); fprintf(stderr, "1");
      } else if (0 && rand() % 3 == 0){
	gen2(n, rand() % (P[rand() % 5] - 1) + 2); fprintf(stderr, "2");
      } else if (rand() % 2 == 0){
	if (rand() & 1) gen3(n, p, 9);
	else gen3(n, q, 4);
	fprintf(stderr, "3");
      } else {
	int x;
	if (rand() % 3 == 0){
	  do {do {x = rand() % 735134399 + 1;} while (735134400 % x != 0);}
	  while (gcd(x, 735134400 / x) != 1);
	} else x = _[rand() & 1];
	gen4(n, x, 735134400 / x);
	fprintf(stderr, "4");
      }
    }
    fprintf(stderr, "\n");
    fclose(stdout);
    system("GNUM4");
    sprintf(cmd, "copy GNUM.in GNUM%d.in", cs);
    system(cmd);
    sprintf(cmd, "copy GNUM.out GNUM%d.out", cs);
    system(cmd);
  }
  return 0;
}
