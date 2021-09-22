#include <cstdio>
#include <algorithm>

using namespace std;

typedef __int64 llint;

const llint MOD = 1000000007LL;

struct Matrix {
  static const int MAXN = 5;

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
        x += a[i][k] * b[k][j] % m;
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
  llint n, a0, ax, ay, b0, bx, by;
  Matrix t;

  while (scanf("%I64d", &n) != EOF) {
    scanf("%I64d%I64d%I64d", &a0, &ax, &ay);
    scanf("%I64d%I64d%I64d", &b0, &bx, &by);
    t.fill(5, 5, 0);
    t[0][0] = ax * bx % MOD;
    t[0][1] = ax * by % MOD;
    t[0][2] = bx * ay % MOD;
    t[0][3] = ay * by % MOD;
    t[1][1] = ax % MOD;
    t[1][3] = ay % MOD;
    t[2][2] = bx % MOD;
    t[2][3] = by % MOD;
    t[3][3] = 1;
    t[4][0] = 1;
    t[4][4] = 1;
    pow(t, n, MOD, t);
    printf("%I64d\n", (a0 * b0 % MOD * t[4][0] + a0 * t[4][1] + b0 * t[4][2] + t[4][3]) % MOD);
  }

  return 0;
}

