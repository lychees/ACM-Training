#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef __int64 LL;

const int MAXL = (1 << 18) + 100;
const double PI = acos(-1.);
int N = 1 << 18,id = 0;
int n;
LL cnt[MAXL];
int a[MAXL],p[MAXL];
pair<double,double> P[MAXL],PB[MAXL],tmp[MAXL];

void fill(int s[],int m,int d)
{
    if (m == N)
        P[d] = make_pair(s[id++],0.);
    else 
    {
        fill(s,m<<1,d);
        fill(s,m<<1,d+m);
    }
}

void fill2(int m,int d)
{
    if (m == N) P[d] = tmp[id++];
    else
    {
        fill2(m<<1,d);
        fill2(m<<1,d+m);
    }
}

inline void FFT(double oper)
{
    for (int d = 0;(1 << d) < N;++d)
    {
        int m = (1 << d);
        double p0 = PI / m * oper;
        double sinp0 = sin(p0);
        double cosp0 = cos(p0);
        for (int i = 0;i < N;i += (m << 1))
        {
            double sinp = 0;
            double cosp = 1;
            for (int j = 0;j < m;++j)
            {
                double ta = cosp * P[i+j+m].first - sinp*P[i+j+m].second;
                double tb = cosp * P[i+j+m].second + sinp * P[i+j+m].first;
                P[i+j+m].first = P[i+j].first - ta;
                P[i+j+m].second = P[i+j].second - tb;
                P[i+j].first += ta;
                P[i+j].second += tb;
                double tsinp = sinp;
                sinp = sinp * cosp0 + cosp * sinp0;
                cosp = cosp * cosp0 -tsinp * sinp0;
            }
        }
    }
}

void Mul()
{
    id = 0;
    fill(p,1,0);
    FFT(1.);
    for (int i = 0;i < N;++i)
        PB[i] = P[i];
    id = 0;
    fill(p,1,0);
    FFT(1.);
    for (int i = 0;i < N;++i)
    {
        tmp[i].first = P[i].first * PB[i].first - P[i].second * PB[i].second;
        tmp[i].second = P[i].first * PB[i].second + P[i].second * PB[i].first;
    }
    id = 0;
    fill2(1,0);
    FFT(-1.);
    for (int i = 0;i < N;++i)
        cnt[i] = LL(P[i].first / N + 0.1);
    for (int i = 0;i < n;++i)
        cnt[a[i]+a[i]]--;
    for (int i = 0;i < N;++i)
        cnt[i] >>= 1;
}

void work()
{
    N = 1 << 18;
    scanf("%d",&n);
    LL tot = (LL)n * (n-1) * (n-2) / 6;
    LL ans = tot;
    for (int i = 0;i < n;++i)
        scanf("%d",a+i);
    sort(a,a+n);
    while ((N >> 2) > a[n-1]) N >>= 1;
    for (int i = 0;i < N;++i)
        p[i] = 0;
    for (int i = 0;i < n;++i)
        p[a[i]]++;
    Mul();
    for (int i = 0,k = 0;i < N;++i)
        if (cnt[i])
        {
            while (k < n && a[k] < i) ++k;
            if (k == n) break;
            ans -= cnt[i] * (n - k);
        }
    printf("%.7f\n",(double)ans / tot);
}

int main()
{
    int times;
    scanf("%d",&times);
    while (times--) work();
    return 0;
}

