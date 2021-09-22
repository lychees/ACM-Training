#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-6;
inline int sign(double x) { return x < -eps ? -1 : x > eps; }
inline double sqr(double x) { return x * x; }

struct point {
  double x, y, z;
  void read() {
    scanf("%lf %lf %lf", &x, &y, &z);
  }
  bool zero() {
    return !sign(x) && !sign(y) && !sign(z);
  }
  double len() {
    return sqrt(sqr(x) + sqr(y) + sqr(z));
  }
};

typedef point vt;

point operator-(point a, point b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

vt operator*(vt a, vt b) {
  vt c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x;
  return c;
}

struct cylinder {
  point p;
  vt v;
  double r;
};

double dot(vt a, vt b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double dist(point a, point b) {
  return (a - b).len();
}

double c_angle(vt a, vt b) {
  return dot(a, b) / (a.len() * b.len());
}

const int N = 35;
int n;
cylinder cy[N];

double solve(cylinder a, cylinder b) {
  vt l = a.v * b.v;
  if (l.zero()) {
    vt vd = b.p - a.p;
    double d;
    if (vd.zero()) {
      d = 0;
    } else {
      double c_theta = c_angle(vd, a.v);
      d = dist(b.p, a.p) * sqrt(1 - sqr(c_theta));
    }
    d -= a.r + b.r;
    return d;
  } else {
    double d = dot(l, a.p);
    double de = fabs(dot(l, b.p) - d) / l.len();
    return de - a.r - b.r;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      point p, a, b;
      p.read(); a.read(); b.read();
      cy[i].p = p;
      cy[i].r = dist(p, a);
      cy[i].v = (a - p) * (b - p);
    }

    double ans = 1e100;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        ans = min(ans, solve(cy[i], cy[j]));

    if (sign(ans) <= 0)
      puts("Lucky");
    else
      printf("%.2lf\n", ans);
  }
  return 0;
}
