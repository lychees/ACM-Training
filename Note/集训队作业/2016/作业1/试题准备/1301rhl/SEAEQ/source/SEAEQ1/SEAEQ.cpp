#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int sz = 222222;
const int ljz = 1000000007;//这个模数是纪念一个已退役的神犇
int T;
int n, p1[sz], p2[sz];

int C(int *p, int l, int r, int x){
  int s = 0;
  for (int i = l; i <= r; i++)
    if (p[i] < x) s++;
  return s;
}
int check(int l, int r){
  for (int i = l; i <= r; i++)
    if (C(p1, l, r, p1[i]) != C(p2, l, r, p2[i])) return 0;
  return 1;
}

int inv(int l, int r){
  int s = 0;
  for (int i = l; i <= r; i++)
    for (int j = l; j < i; j++)
      if (p1[i] < p1[j]) s++;
  return s;
}

void doit(){
  int n, E, i, j, ans = 0;
  scanf("%d %d", &n, &E);
  for (i = 1; i <= n; i++) p1[i] = i;
  do {
    for (i = 1; i <= n; i++) p2[i] = i;
    do {
      for (i = 1; i <= n; i++)
	for (j = i; j <= n; j++)
	  if (inv(i, j) <= E)
	    if (check(i, j)){
	      ans++;
	      if (ans == ljz) ans = 0;
	    }
    } while (next_permutation(p2 + 1, p2 + n + 1));
  } while (next_permutation(p1 + 1, p1 + n + 1));
  printf("%d\n", ans);
}

int main(){
  int T;
  scanf("%d", &T);
  while (T--) doit();
  return 0;
}
