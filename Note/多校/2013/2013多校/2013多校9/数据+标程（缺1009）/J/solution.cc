#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef __int64 llint;

const llint MOD = 1000000007;

struct Induction {
  vector<llint> c;

  int size() const {
    return c.size();
  }

  void reduce(const Induction& unit) {
    for (int i = size() - 1 - unit.size(); i >= 0; --i) {
      llint k = c[i + unit.size()];
      for (int j = 0; j < unit.size(); ++j) {
        c[i + j] = (c[i + j] + k * unit.c[j]) % MOD;
      }
    }
    c.resize(unit.size());
  }

  llint operator()(const vector<llint>& a) {
    llint ret = 0;
    for (int i = 0; i < size(); ++i) {
      ret = (ret + c[i] * a[i]) % MOD;
    }
    return ret;
  }
};

Induction pow(const Induction& unit, llint n) {
  int m = unit.size();
  Induction ret;

  if (n < m) {
    ret.c.resize(m);
    ret.c[(int)n] = 1;
  } else if (n % 2 == 0) {
    Induction half = pow(unit, n / 2);
    ret.c.resize(m + m - 1);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        ret.c[i + j] += (half.c[i] * half.c[j]) % MOD;
      }
    }
  } else {
    ret = pow(unit, n - 1);
    ret.c.insert(ret.c.begin(), 0);
  }

  ret.reduce(unit);
  return ret;
}

int main() {
  int m;
  llint n;
  vector<int> a, b;
  vector<llint> dp;
  Induction t;

  while (scanf("%I64d", &n) != EOF) {
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

    t.c = vector<llint>(m);
    for (int i: b) {
      t.c[m - i] = dp[i];
    }
    t = pow(t, n + (m - 1));
    printf("%I64d\n", t.c.back());
  }

  return 0;
}

