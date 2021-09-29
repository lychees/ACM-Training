#include <algorithm>
#include <cstdio>

#ifdef _WIN32
#define LLFORMAT "I64"
#else
#define LLFORMAT "ll"
#endif

const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

struct Point
{
    long long x, y;

    Point() {}
    Point(long long x_, long long y_) : x(x_), y(y_) {}

    Point get_rotate_cw() const
    {
        return Point(x + y, -x);
    }

    void rotate_cw()
    {
        *this = get_rotate_cw();
    }
};

struct InState
{
    long long x, y;
    int d2, d1, b;
};

struct OutState
{
    long long ans;
};

InState in;
OutState out;

void input()
{
    scanf("%"LLFORMAT"d%"LLFORMAT"d%d%d%d", &in.x, &in.y, &in.d2, &in.d1, &in.b);
}

long long getans4(long long x, long long y, int p)
{
    long long c = (x + 2 * p - 1) / (2 * p);
    long long s1 = c * 6;
    long long r = (x + y) / 2;
    int t = std::min(p, 6);
    long long s2 = std::max(r / p * t + std::min(int(r % p), 6) - c * t, 0LL);
    long long s = x + s1 + s2;
    return s;
}

long long getans3(Point a, int b)
{
    while (!(a.x >= 0 && a.y >= 0)) {
        a.rotate_cw();
    }
    return getans4(a.x + a.y, llabs(a.x - a.y), b - 1);
}

long long getans2(Point a, int d, int b, bool isfirst)
{
    if (d == 5 && !isfirst) return getans3(a, b);
    long long ans = INFLL;
    for (int i = 1; i <= b; i++) {
        a.x--;
        ans = std::min(ans, i + getans2(a.get_rotate_cw(), (d + 5) % 6, b, false));
    }
    return ans;
}

long long getans(Point a, int d2, int d1, int b)
{
    for (int i = 0; i < d1; i++) {
        a.rotate_cw();
    }
    return getans2(a, (d2 - d1 + 6) % 6, b, true);
}

void solve()
{
    if (in.x == 0 && in.y == 0 && in.d1 == in.d2) {
        out.ans = 0;
        return;
    }
    long long ans1 = getans(Point(in.x, in.y), in.d2, in.d1, in.b);
    long long ans2 = getans(Point(in.x, in.y), in.d2, (in.d1 + 1) % 6, in.b);
    out.ans = std::min(ans1, ans2);
}

void output()
{
    printf("%"LLFORMAT"d\n", out.ans);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("419.in", "r", stdin);
    freopen("419.out", "w", stdout);
#endif

    input();
    solve();
    output();

#ifndef ONLINE_JUDGE
    fclose(stdin); fclose(stdout);
#endif
    return 0;
}
