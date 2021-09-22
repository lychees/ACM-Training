#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef __int64 llint;

llint gao(int n, const char s[]) {
  vector<vector<llint> > cur;

  vector<vector<llint> >(n + 1, vector<llint>(n + 1)).swap(cur);
  cur[0][0] = 1;
  for (int k = 0; k < n; ++k) {
    vector<vector<llint> > pre(cur);
    fill(cur.begin(), cur.end(), vector<llint>(n + 1));
    if (s[k] == '+') {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          cur[i + 1][j + 1] += pre[i][j];
          if (j > 0) {
            cur[i][j] += pre[i][j] * j;
          }
        }
      }
    } else {
      for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
          cur[i][j] += pre[i][j] * i;
          if (j > 0) {
            cur[i - 1][j - 1] += pre[i][j] * i * j;
          }
        }
      }
    }
  }

  return cur[0][0];
}

int main() {
  char buf[80];

  while (scanf("%s", buf) != EOF) {
    printf("%I64d\n", gao(strlen(buf), buf));
  }

  return 0;
}

