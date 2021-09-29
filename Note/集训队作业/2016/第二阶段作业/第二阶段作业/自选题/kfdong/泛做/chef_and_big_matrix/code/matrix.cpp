#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define ll long long
#define mkp make_pair
#define fir first
#define sec second
using namespace std;

const int MaxN = 200010, Log = 10;
int fac[MaxN], facpow[MaxN][Log], facinv[MaxN];
int factor[Log], ftot;
int mod;

void exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int get_inv(int a) {
	int x, y;
	exgcd(a, mod, x, y);
	return ((x % mod) + mod) % mod;
}
int power(ll x, int l) {
	ll ret = 1;
	for (; l; l >>= 1, x = x * x % mod)
		if (l & 1) ret = ret * x % mod;
	return ret;
}
void init(int n) {
	ftot = 0;
	int x = mod;
	for (int i = 2; i * i <= mod; ++i) 
		if (x % i == 0) {
			factor[ftot++] = i;
			while (x % i == 0) x /= i;
		}
	if (x != 1) factor[ftot++] = x;

	fac[0] = facinv[0] = 1;
	for (int i = 1; i <= n; ++i) {
		int x = i;
		memcpy(facpow[i], facpow[i - 1], sizeof facpow[i]);
		for (int j = 0; j < ftot; ++j)
			while (x % factor[j] == 0) {
				x /= factor[j];
				++facpow[i][j];
			}
		fac[i] = 1ll * fac[i - 1] * x % mod;
		facinv[i] = get_inv(fac[i]);
	}
}

int comb(int n, int m) {
	int ret = 1ll * fac[n] * facinv[m] % mod * facinv[n - m] % mod;
	for (int j = 0; j < ftot; ++j)
		ret = 1ll * ret * power(factor[j], facpow[n][j] - facpow[m][j] - facpow[n - m][j]) % mod;
	return ret;
}

const int MaxC = 210;
int n, m, c, d;
int f[MaxC][MaxC], g[MaxC][MaxC], ways[MaxC][MaxC];
bool mark[MaxC][MaxC];
int a[2][2][MaxC], ans[MaxC];
pair <int, int> car[MaxN];

inline bool tless(pair <int, int> a, pair <int, int> b) {
	return (a.fir <= b.fir) && (a.sec <= b.sec);
}

void init_car() {
	memset(ways, 0, sizeof(ways));
	memset(f, 0, sizeof(f));
	memset(mark, 0, sizeof(mark));
	for (int i = 1; i <= c; ++i)
		for (int j = i; j <= c; ++j) 
			if (tless(car[i], car[j])) {
				ways[i][j] = comb(car[j].fir - car[i].fir + car[j].sec - car[i].sec, car[j].fir - car[i].fir);
				mark[i][j] = 1;
			}
	for (int i = 1; i <= c; ++i)
		for (int j = 1; j <= c; ++j) 
			if (mark[i][j]) {
				f[i][j] = ways[i][j];
				for (int k = i + 1; k < j; ++k)
					if (mark[i][k] && mark[k][j] && f[i][k]) {
						f[i][j] = (f[i][j] - 1ll * f[i][k] * ways[k][j]) % mod;
					}
			}
}

void calc(int a[], int sx, int sy, int tx, int ty) {
	fill(a, a + c + 1, 0);
	car[0] = mkp(sx, sy);
	car[c + 1] = mkp(tx, ty);
	if (!tless(car[0], car[c + 1])) return;
	//init f[0][], f[][c + 1]
	for (int i = 0; i <= c + 1; ++i)
		if (tless(car[0], car[i])) {
			f[0][i] = ways[0][i] = comb(car[i].fir - sx + car[i].sec - sy, car[i].fir - sx);			
			mark[0][i] = 1;
			for (int j = 1; j < i; ++j)
				if (mark[0][j] && mark[j][i] && f[0][j])
					f[0][i] = (f[0][i] - 1ll * f[0][j] * ways[j][i]) % mod;
		} else {
			f[0][i] = ways[0][i] = mark[0][i] = 0;
		}
	for (int i = c + 1; i >= 0; --i)
		if (tless(car[i], car[c + 1])) {
			f[i][c + 1] = ways[i][c + 1] = comb(tx - car[i].fir + ty - car[i].sec, tx - car[i].fir);
			mark[i][c + 1] = 1;
			for (int j = i + 1; j <= c; ++j)
				if (mark[i][j] && mark[j][c + 1] && f[i][j]) {
					f[i][c + 1] = (f[i][c + 1] - 1ll * f[i][j] * ways[j][c + 1]) % mod;
				}
		} else {
			f[i][c + 1] = ways[i][c + 1] = mark[i][c + 1] = 0;
		}

	memset(g, 0, sizeof(g));
	g[0][0] = 1;
	for (int i = 1; i <= c + 1; ++i)
		for (int j = 1; j <= d + 1; ++j)
			for (int k = 0; k < i; ++k) {
				g[i][j] = (g[i][j] + 1ll * g[k][j - 1] * f[k][i]) % mod;
			}
	for (int i = 0; i <= d + 1; ++i) a[i] = g[c + 1][i + 1];
//	for (int i = 0; i <= d + 1; ++i) printf("%d ", a[i]); puts(";");
}

void Main() {
	scanf("%d%d%d%d%d", &n, &m, &c, &d, &mod);
	init(n + m);
	for (int i = 1; i <= c; ++i) 
		scanf("%d%d", &car[i].fir, &car[i].sec);
	sort(car + 1, car + c + 1);
	init_car();
	calc(a[0][0], 1, 2, n - 1, m);
	calc(a[0][1], 1, 2, n, m - 1);
	calc(a[1][0], 2, 1, n - 1, m);
	calc(a[1][1], 2, 1, n, m - 1);
	int ret = 0;
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i <= d; ++i) {
		for (int j = 0; j <= i; ++j) 
			ans[i] = (ans[i] + 1ll * a[0][0][j] * a[1][1][i - j] - 1ll * a[0][1][j] * a[1][0][i - j]) % mod;
		ret += (ans[i] < 0 ? ans[i] += mod : ans[i]);
		ret >= mod ? ret -= mod : ret;
	}
	cout << ret << endl;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) Main();
	return 0;
}
