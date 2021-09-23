/*
    This code has been written by MinakoKojima, feel free to ask me question. Blog: http://www.shuizilong.com/house
    Template Date: 2015.10.12
    Note: ...
*/

#pragma comment(linker, "/STACK:36777216")
//#pragma GCC optimize ("O2")
#define LOCAL
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

//#include <tr1/unordered_set>
//#include <tr1/unordered_map>
//#include <array>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
const int mod = 998244353, N = 262144;

int wn[N], lim, s, rev[N], w[N];
void reduce(int &x) { x += x >> 31 & mod; }
int pow(int x, int y, int ans = 1) {
	for (; y; y >>= 1, x = (LL) x * x % mod)
		if (y & 1) ans = (LL) ans * x % mod;
	return ans;
}
void fftinit(int len) {
	wn[0] = lim = 1, s = -1; while (lim < len) lim <<= 1, ++s;
	for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
	const int g = pow(3, (mod - 1) / lim);
	for (int i = 1; i < lim; ++i) wn[i] = (LL) wn[i - 1] * g % mod;
}
void fft(int *A, int typ) {
	static ULL tmp[N];
	for (int i = 0; i < lim; ++i) tmp[rev[i]] = A[i];
	for (int i = 1; i < lim; i <<= 1) {
		for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
		for (int j = 0; j < lim; j += i << 1)
			for (int k = 0; k < i; ++k) {
				const ULL x = tmp[k + j + i] * w[k] % mod;
				tmp[k + j + i] = tmp[k + j] + mod - x, tmp[k + j] += x;;
			}
	}
	for (int i = 0; i < lim; ++i) A[i] = tmp[i] % mod;
	if (!typ) {
		const int il = pow(lim, mod - 2); std::reverse(A + 1, A + lim);
		for (int i = 0; i < lim; ++i) A[i] = (LL) A[i] * il % mod;
	}
}

int inv[N];
int f[N], g[N], n;
int a[N], b[N];

void init(int n) {
	inv[0] = 1, inv[1] = 1;
	for (int i = 2; i < n; ++i)
		inv[i] = (LL) (mod - mod / i) * inv[mod % i] % mod;
}

void solve(int l, int r) {
	if (r - l <= 32) {
		for (int i = l; i < r; ++i) {
			for (int j = l; j < i; ++j) {
				f[i] = (f[i] + (LL) f[j] * g[i - j]) % mod;
				if (l > 1) f[i] = (f[i] + (LL) g[j] * f[i - j]) % mod;
			}
			f[i] = (LL) f[i] * inv[i - 1] % mod;
			int v = (LL) f[i] * i % mod;
			for (int p = i; p <= n; p += i) reduce(g[p] += v - mod);
		}
		return;
	}
	int mid = l + r + 1 >> 1;
	solve(l, mid), fftinit(r - l);
	auto update = [&] (int *f, int la, int *g, int lb) {
		std::memcpy(a, f, la << 2), std::memset(a + la, 0, lim - la << 2);
		std::memcpy(b, g, lb << 2), std::memset(b + lb, 0, lim - lb << 2);
		fft(a, 1), fft(b, 1);
		for (int i = 0; i < lim; ++i) a[i] = (LL) a[i] * b[i] % mod;
		fft(a, 0);
		for (int i = mid; i < r; ++i) reduce(::f[i] += a[i - l] - mod);
	};
	if (l > 1) update(f + l, mid - l, g, r - l);
	update(g + l, mid - l, f, l == 1 ? mid : r - l);
	solve(mid, r);
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

	std::ios::sync_with_stdio(0), std::cin.tie(0);
	std::cin >> n, f[1] = 1, init(n), solve(1, n + 1);
	int ans = f[n];
	for (int i = n / 2 + 1; i < n; ++i)
		ans = (ans + (LL) (mod - f[i]) * f[n - i]) % mod;
	if (n % 2 == 0) ans = (ans + mod - (LL) f[n / 2] * (f[n / 2] - 1) / 2 % mod) % mod;
	std::cout << ans << '\n';
	return 0;
}
