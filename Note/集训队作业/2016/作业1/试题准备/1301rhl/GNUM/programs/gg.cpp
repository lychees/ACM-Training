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
  int i, j, k = 1;
  printf("%d\n", n);
  for (i = 1; i <= n + n; i++){
    if (i == n + 1) swap(x, y);
    k = ran % (X / x) + 1;
    printf("%d%c", k * x, " \n"[i % n == 0]);
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

int main(){
  int T, n;
  srand(1999031603);
  freopen("GNUM.in", "w", stdout);
  printf("6\n");
  do {n = rand() % 27113;} while (735134400 % n != 0);
  gen1(400, 1, 10000);
  gen2(400, 2);
  gen2(400, 3214567);
  gen3(400, p, 9);
  gen4(400, n, 735134400 / n);
  int i, j;
  do {i = rand() % 100000 + 1; j = rand() % 100000 + 1;} while (gcd(i, j) > 1);
  gen4(400, 26775, 27456);
  return 0;
}
