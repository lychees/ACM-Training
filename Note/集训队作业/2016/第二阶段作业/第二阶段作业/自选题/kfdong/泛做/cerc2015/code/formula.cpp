#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define ll long long
#define cmod(a) (a >= Mod ? a -= Mod : a)
using namespace std;
 
const int MaxN = 200010, Mod = 1000003, MaxF = 1 << 19;
 
long long Power(ll x, int L, int Mod) {
    ll ret = 1;
    for (; L; L >>= 1, x = x * x % Mod)
        if (L & 1) ret = ret * x % Mod;
    return ret;
}
 
class fast_fourier_transform {
public:
    int Mod, G;
    int w[MaxF];
     
    void init(int _Mod, int _G) { Mod = _Mod, G = _G; }
 
    void get_w(int N) {
        int M = N >> 1, e = Power(G, (Mod - 1) / N, Mod);
        w[M] = 1;
        for (int i = 1; i < M; i++) 
            w[i + M] = 1ll * e * w[i + M - 1] % Mod;
        for (int i = M - 1; i; i--) w[i] = w[i << 1];
    }
 
    void DFT(int N, int a[]) {
        for (int i = 0, j = 0; i < N; i++) {
            if (i > j) swap(a[i], a[j]);
            for (int l = N >> 1; (j ^= l) < l; l >>= 1);
        }
        for (int s = 2, m = 1; s <= N; m = s, s <<= 1) { 
            for (int i = 0; i < N; i += s) 
                for (int j = 0; j < m; j++) {
                    int tmp = 1ll * a[i + j + m] * w[j + m] % Mod;
                    a[i + j + m] = a[i + j] - tmp + Mod;
                    cmod(a[i + j + m]);
                    a[i + j] = a[i + j] + tmp;
                    cmod(a[i + j]);
                }
        }
    }
 
    void convolution(int N, int a[], int b[], int ans[]) {
        int tn = 1;
        while (tn < (N << 1)) tn <<= 1;
        get_w(tn);
        DFT(tn, a);
        DFT(tn, b);
        for (int i = 0; i < tn; ++i) ans[i] = 1ll * a[i] * b[i] % Mod;
        reverse(ans + 1, ans + tn);
        DFT(tn, ans);
        int inv = Power(tn, Mod - 2, Mod);
        for (int i = 0; i < tn; ++i) 
            ans[i] = 1ll * ans[i] * inv % Mod;
    }
}   F0, F1;
 
int N, a, b, c;
int fac[MaxN << 1], invfac[MaxN << 1], inv[MaxN << 1];
int powa[MaxN], powb[MaxN], sa[MaxF], sb[MaxF];
 
inline int comb(int N, int M) {
    return 1ll * fac[N] * invfac[M] % Mod * invfac[N - M] % Mod;
}
 
void convolution(int N, int a[], int b[], int ans[]) {
    static int ta[MaxF], tb[MaxF], ans0[MaxF], ans1[MaxF];
    memcpy(ta, a, sizeof ta);
    memcpy(tb, b, sizeof tb);
    F0.convolution(N, ta, tb, ans0);
    memcpy(ta, a, sizeof ta);
    memcpy(tb, b, sizeof tb);
    F1.convolution(N, ta, tb, ans1);
    int inv = Power(F0.Mod, F1.Mod - 2, F1.Mod);
    for (int i = 0; i < N * 2 - 1; ++i) {
        int delta = (ans1[i] - ans0[i]) % F1.Mod;
        if (delta < 0) delta += F1.Mod;
        ans[i] = (ans0[i] + 1ll * delta * inv % F1.Mod * F0.Mod) % Mod;
    }
}
 
int main()
{
    F0.init(1004535809, 3);
    F1.init(998244353, 3);
 
    scanf("%d%d%d%d", &N, &a, &b, &c);
    //init
    fac[0] = invfac[0] = inv[1] = 1;
    for (int i = 2; i <= (N << 1); ++i) inv[i] = Mod - 1ll * inv[Mod % i] * (Mod / i) % Mod;
    for (int i = 1; i <= (N << 1); ++i) {
        fac[i] = 1ll * fac[i - 1] * i % Mod;
        invfac[i] = 1ll * invfac[i - 1] * inv[i] % Mod;
    }
    powa[0] = powb[0] = 1;
    for (int i = 1; i <= N; ++i) {
        powa[i] = 1ll * powa[i - 1] * a % Mod;
        powb[i] = 1ll * powb[i - 1] * b % Mod;
    }
    int ans = 0, x;
    scanf("%*d");
    for (int i = 2; i <= N; ++i) {
        scanf("%d", &x);
        ans = (1ll * x * comb(N - 2 + N - i, N - 2) % Mod * powa[N - 1] % Mod * powb[N - i] + ans) % Mod;
    }
    scanf("%*d");
    for (int i = 2; i <= N; ++i) {
        scanf("%d", &x);
        ans = (1ll * x * comb(N - 2 + N - i, N - 2) % Mod * powa[N - i] % Mod * powb[N - 1] + ans) % Mod;
    }
 
    for (int i = 0; i <= N - 2; ++i) 
        sa[i] = 1ll * powa[i] * invfac[i] % Mod;
    for (int i = 0; i <= N - 2; ++i)
        sb[i] = 1ll * powb[i] * invfac[i] % Mod;
    convolution(N - 1, sa, sb, sa);
    int plus = 0;
    for (int i = 0; i <= N * 2 - 4; ++i) 
        plus = (plus + 1ll * fac[i] * sa[i]) % Mod;
    ans = (ans + 1ll * c * plus) % Mod;
    cout << ans << endl;
    return 0;
}
