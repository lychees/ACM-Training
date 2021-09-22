#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long llint;

const llint MOD = 1000000007;
const llint LIMIT = 8 * MOD * MOD;

struct Matrix {
  static const int MAXN = 200;

  int r, c;
  llint a[MAXN][MAXN];

  llint* operator[](int i) {
    return a[i];
  }

  const llint* operator[](int i) const {
    return a[i];
  }

  void init(int row, int col) {
    this->r = row;
    this->c = col;
  }

  void fill(int row, int col, llint x = 0) {
    init(row, col);
    for (int i = 0; i < r; ++i) {
      ::fill(a[i], a[i] + c, x);
    }
  }

  void eye(int n, llint x = 1) {
    fill(n, n, 0);
    for (int i = 0; i < n; ++i) {
      a[i][i] = x;
    }
  }

  void set(const Matrix& o) {
    init(o.r, o.c);
    for (int i = 0; i < r; ++i) {
      copy(o[i], o[i] + c, a[i]);
    }
  }
};

void add(const Matrix& a, const Matrix& b, llint m, Matrix& ret) {
  static Matrix c;
  c.set(a);
  for (int i = 0; i < b.r; ++i) {
    for (int j = 0; j < b.c; ++j) {
      c[i][j] += b[i][j];
      if (c[i][j] >= m) {
        c[i][j] -= m;
      }
    }
  }
  ret.set(c);
}

void mul(const Matrix& a, const Matrix& b, llint m, Matrix& ret) {
  static Matrix c;
  c.init(a.r, b.c);
  for (int i = 0; i < c.r; ++i) {
    for (int j = 0; j < c.c; ++j) {
      llint x = 0;
      for (int k = 0; k < a.c; ++k) {
        x += a[i][k] * b[k][j];
        if (x >= LIMIT) {
          x %= MOD;
        }
      }
      c[i][j] = x % m;
    }
  }
  ret.set(c);
}

void pow(const Matrix& a, llint b, llint m, Matrix& ret) {
  static Matrix c;
  c.set(a);
  ret.eye(c.r);
  while (b > 0) {
    if (b % 2 != 0) {
      mul(ret, c, m, ret);
    }
    b /= 2;
    mul(c, c, m, c);
  }
}

int main() {
  int m;
  llint n;
  vector<int> a, b;
  vector<llint> dp;
  Matrix t;

  while (scanf("%lld", &n) != EOF) {
    scanf("%d", &m);
    a.resize(m);
    for (int i = 0; i < m; ++i) {
      scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    b.resize(m);
    for (int i = 0; i < m; ++i) {
      scanf("%d", &b[i]);
    }
    m = *max_element(b.begin(), b.end());

    dp = vector<llint>(m + 1);
    dp[0] = 1;
    for (int i = 0; i <= m; ++i) {
      for (int j: a) {
        if (j <= i) {
          dp[i] += dp[i - j];
          if (dp[i] >= MOD) {
            dp[i] -= MOD;
          }
        }
      }
    }

    t.fill(m, m, 0);
    for (int i: b) {
      t[0][i - 1] = dp[i];
    }
    for (int i = 1; i < m; ++i) {
      t[i][i - 1] = 1;
    }
    pow(t, n, MOD, t);
    printf("%lld\n", t[0][0]);
    fprintf(stderr, "%d: %lld\n", m, t[0][0]);
    fflush(stderr);
  }

  return 0;
}

