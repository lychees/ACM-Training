#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int sz = 1020;
int link[sz], used[sz];
int node[sz * sz], next[sz * sz], to[sz * sz], e;
void ins(int x, int y){e++; next[e] = node[x]; node[x] = e; to[e] = y;}
int bh[sz][sz], g[sz][sz];
int a[sz], b[sz], n, N, M;
int gcd(int x, int y){return y ? gcd(y, x % y) : x;}

int find(int x){
  int j;
  for (j = node[x]; j; j = next[j])
    if (!used[to[j]]){
      used[to[j]] = 1;
      if (link[to[j]] == 0 || find(link[to[j]])){
	link[to[j]] = x;
	return 1;
      }
    }
  return 0;
}

void doit(){
  int i, j, p, q;
  //Clearing arrays
  for (i = 1; i <= N; i++) node[i] = 0;
  for (i = 1; i <= M; i++) link[i] = 0;
  for (i = 1; i <= e; i++) next[i] = to[i] = 0;
  N = M = e = 0;

  cin >> n;
  for (i = 1; i <= n; i++) cin >> a[i];
  for (i = 1; i <= n; i++) cin >> b[i];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      g[i][j] = gcd(a[i], b[j]);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (a[i] < b[j] && g[i][j] > 1) bh[i][j] = ++N;
      else if (a[i] > b[j] && g[i][j] > 1) bh[i][j] = ++M;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (bh[i][j] && a[i] < b[j])
	for (p = 1; p <= n; p++)
	  for (q = 1; q <= n; q++)
	    if (bh[q][p] && a[q] > b[p])
	      if (gcd(g[i][j], g[q][p]) > 1)
		ins(bh[i][j], bh[q][p]);

  p = 0;
  for (i = 1; i <= N; i++){
    for (j = 1; j <= M; j++) used[j] = 0;
    p += find(i);
  }
  cout << p << endl;
}

int main(){
  int T;
  cin >> T;
  while (T--) doit();
  return 0;
}
