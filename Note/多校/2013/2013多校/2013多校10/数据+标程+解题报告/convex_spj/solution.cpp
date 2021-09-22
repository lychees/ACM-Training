#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()
#define SIZE(v) ((int)(v).size())

const int N = 50;
const int T = 1e4;
const double EPS = 1e-9;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

template <class T>
struct Point {
    T x, y;

    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    Point <T> &operator -=(const Point <T> &o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Point <T> &operator +=(const Point <T> &o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point <T> &operator *=(T k) {
        x *= k;
        y *= k;
        return *this;
    }
};

template <class T>
Point <T> operator +(Point <T> a, const Point <T> &b) {
    return a += b;
}

template <class T>
Point <T> operator -(Point <T> a, const Point <T> &b) {
    return a -= b;
}

template <class T>
Point <T> operator +(Point <T> a, T k) {
    return a *= k;
}

template <class T>
T det(const Point <T> &a, const Point <T> &b) {
    return a.x * b.y - a.y * b.x;
}

int n, t;
int order[N];
Point <int> p[N], v[N];
Point <double> q[N];

template <class T> 
void get_coef(T &a, T &b, T &c, T d, T k_1, T b_1, T k_2, T b_2) {
    // (k_1 x + b_1) * (k_2 x + b_2)
    a += d * (k_1 * k_2);
    b += d * (k_1 * b_2 + k_2 * b_1);
    c += d * b_1 * b_2;
}

bool by_q(int i, int j) {
    if (q[i].x != q[j].x) {
        return q[i].x < q[j].x;
    }
    return q[i].y < q[j].y;
}

bool check_convex(int i, int j, int k) {
    return signum(det(q[j] - q[i], q[k] - q[j])) > 0;
}

int main() {
	freopen("1002.in","r",stdin);
	freopen("10020.out","w",stdout);
    while (scanf("%d%d", &n, &t) == 2) {
    	printf("%d %d\n",n,t);
        assert(1 <= n && n <= N);
        assert(1 <= t && t <= T);
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d%d", &p[i].x, &p[i].y, &v[i].x, &v[i].y);
            printf("%d %d %d %d\n",p[i].x, p[i].y, v[i].x, v[i].y);
        }
        std::vector <double> events;
        events.push_back(0);
        events.push_back(t);
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < i; ++ j) {
                for (int k = 0; k < j; ++ k) {
                    Point <int> va(v[i] - v[j]);
                    Point <int> vb(v[i] - v[k]);
                    Point <int> pa(p[i] - p[j]);
                    Point <int> pb(p[i] - p[k]);
                    int a = 0, b = 0, c = 0;
                    get_coef(a, b, c,  1, va.x, pa.x, vb.y, pb.y);
                    get_coef(a, b, c, -1, va.y, pa.y, vb.x, pb.x);
                    if (a == 0) {
                        if (b != 0) {
                            events.push_back(-(double)c / b);
                        }
                    } else {
                        int d = b * b - 4 * a * c;
                        if (d >= 0) {
                            events.push_back(0.5 * (-b - sqrt(d)) / a);
                            events.push_back(0.5 * (-b + sqrt(d)) / a);
                        }
                    }
                }
            }
        }
        std::sort(ALL(events));
        double answer = 0;
        for (int k = 1; k < SIZE(events); ++ k) {
            double t_1 = events[k - 1];
            double t_2 = events[k];
            double t_0 = 0.5 * (t_1 + t_2);
            if (t_0 < 0 || t_0 > t) {
                continue;
            }
            for (int i = 0; i < n; ++ i) {
                q[i] = Point <double>(p[i].x + v[i].x * t_0, p[i].y + v[i].y * t_0);
                order[i] = i;
            }
            std::sort(order, order + n, by_q);
            std::vector <int> stack;
            for (int i = 0; i < n; ++ i) {
                while (SIZE(stack) >= 2 && !check_convex(stack[SIZE(stack) - 2], stack.back(), order[i])) {
                    stack.pop_back();
                }
                stack.push_back(order[i]);
            }
            int end = SIZE(stack);
            for (int i = n - 1; i >= 0; -- i) {
                while (SIZE(stack) > end && !check_convex(stack[SIZE(stack) - 2], stack.back(), order[i])) {
                    stack.pop_back();
                }
                stack.push_back(order[i]);
            }
            for (int _ = 1; _ < SIZE(stack); ++ _) {
                int a = 0, b = 0, c = 0;
                int i = stack[_ - 1];
                int j = stack[_];
                get_coef(a, b, c,  1, v[i].x, p[i].x, v[j].y, p[j].y);
                get_coef(a, b, c, -1, v[j].x, p[j].x, v[i].y, p[i].y);
                answer += a * (t_2 * t_2 * t_2 - t_1 * t_1 * t_1) / 3 + b * (t_2 + t_1) * (t_2 - t_1) / 2 + c * (t_2 - t_1);
            }
        }
        printf("%.10f\n", std::abs(0.5 * answer / t));
    }
    return 0;
}
