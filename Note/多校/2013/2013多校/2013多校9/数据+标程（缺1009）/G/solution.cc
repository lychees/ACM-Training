#include <cstdio>
#include <cstring>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

typedef __int64 llint;

const int MAXD = 19;
const int MAXS = MAXD * 9;
const int MAXN = 128;
const llint INF = 12345678901234567LL;

llint mul(llint a, llint b) {
  if (b == 0) {
    return 0;
  } else if (a <= INF / b) {
    return a * b;
  } else {
    return INF;
  }
}

llint ten[MAXD], cnt[MAXD][MAXS];

void init() {
  ten[0] = 1;
  cnt[0][0] = 1;
  for (int i = 1; i < MAXD; ++i) {
    ten[i] = ten[i - 1] * 10;
    for (int j = 0; j < MAXS; ++j) {
      for (int k = 0; k < 10 && k <= j; ++k) {
        cnt[i][j] += cnt[i - 1][j - k];
      }
    }
  }
}

int length(llint n) {
  return upper_bound(ten, ten + MAXD, n) - ten;
}

void stat(llint end, llint ret[]) {
  fill(ret, ret + MAXS, 0);
  int s = 0;
  for (int len = length(end) - 1; len >= 0; --len) {
    int d = (int)(end / ten[len]);
    for (int i = 0; i < d; ++i) {
      for (int j = i + s; j < MAXS; ++j) {
        ret[j] += cnt[len][j - i - s];
      }
    }
    end -= d * ten[len];
    s += d;
  }
}

void stat(llint begin, llint end, llint ret[]) {
  static llint a[MAXS], b[MAXS];
  stat(begin, a);
  stat(end, b);
  transform(b, b + MAXS, a, ret, minus<llint>());
}

typedef llint query(int, int);

llint dp[MAXN][MAXS], sum[MAXN][MAXS + 1];

inline llint eq(int i, int j) { return dp[i][j]; }
inline llint lt(int i, int j) { return sum[i][j]; }
inline llint le(int i, int j) { return lt(i, j) + eq(i, j); }
inline llint gt(int i, int j) { return sum[i][MAXS] - le(i, j); }
inline llint ge(int i, int j) { return sum[i][MAXS] - lt(i, j); }
inline llint ne(int i, int j) { return sum[i][MAXS] - eq(i, j); }
inline llint any(int i, int) { return sum[i][MAXS]; }

const char *op[7] = {"=", "<", "<=", ">", ">=", "!=", "~"};
const query *func[7] = {eq, lt, le, gt, ge, ne, any};
const query *rfunc[7] = {eq, gt, ge, lt, le, ne, any};
query *cmp[MAXN], *rcmp[MAXN];
llint lo[MAXN], hi[MAXN];

int index(const char s[]) {
  for (int i = 0; i < 7; ++i) {
    if (strcmp(s, op[i]) == 0) {
      return i;
    }
  }
  return -1;
}

int ds(llint n) {
  return n == 0 ? 0 : ds(n / 10) + (int)(n % 10);
}

void gao(int k, llint lo, llint hi, query *rcmp) {
  static llint tmp[MAXS];
  stat(lo, hi, tmp);
  for (int j = 0; j < MAXS; ++j) {
    dp[k][j] = mul(tmp[j], rcmp(k + 1, j));
  }
  sum[k][0] = 0;
  partial_sum(dp[k], dp[k] + MAXS, sum[k] + 1);
}

int main() {
  int n, d;
  llint m;
  char buf[80];

  init();
  while (scanf("%d%I64d", &n, &m) != EOF) {
    cmp[0] = any;
    for (int i = 0; i < n; ++i) {
      if (i > 0) {
        scanf("%s", buf);
        cmp[i] = rcmp[i - 1] = rfunc[index(buf)];
      }
      scanf("%I64d", &lo[i]);
      scanf("%I64d", &hi[i]);
    }
    rcmp[n - 1] = any;

    fill(dp[n], dp[n + 1], 0);
    dp[n][0] = 1;
    sum[n][0] = 0;
    partial_sum(dp[n], dp[n] + MAXS, sum[n] + 1);
    for (int i = n - 1; i >= 0; --i) {
      gao(i, lo[i], hi[i] + 1, rcmp[i]);
    }

    if (m > accumulate(dp[0], dp[1], 0LL)) {
      puts("OUT OF RANGE");
      continue;
    }
    d = 0;
    for (int i = 0; i < n; ++i) {
      llint ll = lo[i], rr = hi[i] + 1;
      while (ll < rr) {
        llint mm = (ll + rr) / 2;
        gao(i, lo[i], mm, rcmp[i]);
        // printf("[%I64d, %I64d): %I64d => %I64d ? %I64d\n", ll, rr, mm, cmp[i](i, d), m);
        if (cmp[i](i, d) < m) {
          ll = mm + 1;
        } else {
          rr = mm;
        }
      }
      --rr;
      gao(i, lo[i], rr, rcmp[i]);
      m -= cmp[i](i, d);
      d = ds(rr);
      printf("%I64d%c", rr, i == n - 1 ? '\n' : ' ');
    }
  }

  return 0;
}


