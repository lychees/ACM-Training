#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <bitset>

using namespace std;

#define rep(i,n) for (int i = 0; i < (n); ++i)
#define For(i,s,t) for (int i = (s); i <= (t); ++i)
#define foreach(i,c) for (__typeof(c.begin()) i = c.begin(); i != c.end(); ++i)

typedef long long LL;
typedef pair<int, int> Pii;

const int inf = 0x3f3f3f3f;
const LL infLL = 0x3f3f3f3f3f3f3f3fLL;

const int T = 100;
const int MaxN[] = {6, 1000};
const int MaxV[] = {100, 1000};

int diff;

namespace solver {
    const long double eps = 1e-12;
    const long double pi = acos(-1);
    int sgn(long double x) { return x < -eps? -1: x > eps; }
    
    struct Point3 {
        long double x, y, z;
        Point3(long double x = 0, long double y = 0, long double z = 0):
        x(x), y(y), z(z) {}
    };
    typedef Point3 Vector3;
    Vector3 operator-(Vector3 v)
    { return Vector3(-v.x, -v.y, -v.z); }
    Vector3 operator+(Vector3 u, Vector3 v)
    { return Vector3(u.x + v.x, u.y + v.y, u.z + v.z); }
    Vector3 operator-(Vector3 u, Vector3 v)
    { return Vector3(u.x - v.x, u.y - v.y, u.z - v.z); }
    Vector3 operator*(Vector3 u, long double k)
    { return Vector3(u.x * k, u.y * k, u.z * k); }
    Vector3 operator/(Vector3 u, long double k)
    { return Vector3(u.x / k, u.y / k, u.z / k); }
    
    long double dot(Vector3 u, Vector3 v)
    { return u.x * v.x + u.y * v.y + u.z * v.z; }
    Vector3 cross(Vector3 u, Vector3 v)
    { return Vector3(u.y * v.z - u.z * v.y,
                     u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x); }
    bool zero(Vector3 v) { return !sgn(v.x) && !sgn(v.y) && !sgn(v.z); }
    long double abs(Vector3 v) { return sqrt(dot(v, v)); }
    Vector3 unit(Vector3 v) { return v / abs(v); }
    
    inline long double safe_sqrt(long double x) { return sgn(x) > 0? sqrt(x): 0; }
    inline long double cosf(long double a, long double b, long double c)
    { return (a * a + b * b - c * c) / (2 * a * b); }
    
    const int maxn = 1000 + 5;
    
    int n;
    long double a, h, r;
    Vector3 v[maxn];
    
    Vector3 vz, vx;
    bool cmp(const pair<Vector3, int> &a, const pair<Vector3, int> &b)
    {
        if (zero(a.first - b.first)) return a.second > b.second;
        if (zero(-a.first - vx)) return true;
        if (zero(-b.first - vx)) return false;
        int s1 = sgn(dot(cross(a.first, vx), vz)),
        s2 = sgn(dot(cross(b.first, vx), vz));
        if (s1 != s2) return s1 > s2;
        return sgn(dot(cross(a.first, b.first), vz)) > 0;
    }
    
    int solve()
    {
        int ret = 0;
        For(i,1,n) {
            vector<pair<Vector3, int> > event;
            For(j,1,n) if (j != i) {
                long double d = abs(v[j] - v[i]) / 2;
                if (sgn(d - h * r) > 0) continue;
                long double l = cosf(1, safe_sqrt(h * h - d * d),
                                     safe_sqrt(r * r - d * d));
                Vector3 p = unit(v[i] + v[j]) * l,
                u = unit(cross(v[i], v[j])) * safe_sqrt(1 - l * l);
                event.push_back(make_pair(p - u - v[i], +j));
                event.push_back(make_pair(p + u - v[i], -j));
            }
            vz = v[i], vx = (event.empty()? 0: event.front().first);
            sort(event.begin(), event.end(), cmp);
            int k = 1;
            bitset<maxn> mrk;
            foreach(it,event) {
                if (it->second < 0) k += !mrk[-it->second];
                else mrk[it->second] = true;
            }
            ret = max(ret, k);
            foreach(it,event) ret = max(ret, k += (it->second < 0? -1: 1));
        }
        return ret;
    }
}

struct test_case_t {
    int n, a;
    vector<vector<int> > p;
    
    test_case_t(int n = 0, int a = 0): n(n), a(a) {}
    test_case_t(int n, int a, const vector<vector<int> > &p): n(n), a(a), p(p) {}
    
    void print_input() const {
        printf("%d %d\n", n, a);
        rep(i,p.size()) rep(j,p[i].size())
        printf("%d%c", p[i][j], " \n"[j==p[i].size()-1]);
    }
    
    void print_output(int cas) const {
        solver::n = n;
        solver::a = a * solver::pi / 180,
        solver::h = cos(solver::a), solver::r = sin(solver::a);
        solver::Point3 o(p[0][0], p[0][1], p[0][2]);
        For(i,1,n) solver::v[i] = solver::unit(
                                               solver::Vector3(p[i][0], p[i][1], 0) - o) * solver::h;
        fprintf(stderr, "Case #%d: %d\n", cas, solver::solve());
    }
};
vector<test_case_t> test_cases;

inline int rand_int(int l, int r) { return l + rand() % (r - l + 1); }

void generate_muanl_test_cases()
{
    test_cases.push_back(
                         test_case_t(
                                     2, 45,
                                     {{0, 0, 3}, {1, -2}, {-5, 2}}));
    test_cases.push_back(
                         test_case_t(
                                     4, 89,
                                     {{1, 1, 1}, {30, 0}, {0, 50}, {-70, 0}, {0, -90}}));
    if (!diff) return;
    int z = 1000;
    vector<vector<int> > p;
    p.push_back({0, 0, z});
    For(i,1,z) {
        int j = sqrt(z * z - i * i + 1e-10);
        if (i * i + j * j == z * z) {
            p.push_back({i, j});
            p.push_back({-j, i});
            p.push_back({-i, -j});
            p.push_back({j, -i});
        }
    }
    test_cases.push_back(test_case_t(p.size() - 1, 45, p));
    int x = rand_int(-100, 100), y = rand_int(-100, 100); z = 800;
    p.clear();
    p.push_back({x, y, z});
    For(i,1,z) {
        int j = sqrt(z * z - i * i + 1e-10);
        if (i * i + j * j == z * z) {
            p.push_back({x + i, y + j});
            p.push_back({x - j, y + i});
            p.push_back({x - i, y - j});
            p.push_back({x + j, y - i});
        }
    }
    test_cases.push_back(test_case_t(p.size() - 1, 45, p));
}

void generate_random_test_case(bool small_data_set)
{
    int d = small_data_set? 0: diff;
    set<vector<int> > st;
    vector<vector<int> > p;
    p.push_back({rand_int(-MaxV[d], MaxV[d]),
        rand_int(-MaxV[d], MaxV[d]), rand_int(1, MaxV[d])});
    while (p.size() <= MaxN[d]) {
        vector<int> v = {rand_int(-MaxV[d], MaxV[d]), rand_int(-MaxV[d], MaxV[d])};
        if (st.count(v)) continue;
        st.insert(v);
        p.push_back(v);
    }
    test_cases.push_back(test_case_t(
                                     MaxN[d], d? rand_int(30, 60): rand_int(1, 89), p));
}

int main(int argc, char* argv[])
{
    if (argc == 3) {
        diff = atoi(argv[1]);
        srand(atoi(argv[2]));
    } else {
        diff = 0;
        srand((int)time(NULL));
    }
    
    generate_muanl_test_cases();
    
    int remain_tests = T - test_cases.size();
    for (int i = 0; i < remain_tests; i++) {
        generate_random_test_case(i < 88);
    }
    
    printf("%lu\n", test_cases.size());
    int cas = 0;
    for (const auto& test_case : test_cases) {
        test_case.print_input();
        test_case.print_output(++cas);
    }
    
    return 0;
}