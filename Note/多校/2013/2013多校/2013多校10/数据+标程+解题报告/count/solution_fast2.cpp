#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const long long mod = 1000000007;
const int MAXN = 1100;

long long n, m, len, k;
struct node {
	long long x, y;
}p[MAXN], q[MAXN];

vector<long long> vecx;

long long ans = 0;

long long Y[MAXN], X[MAXN];
int top;
long long res, sum;

void insert(long long x, long long y) {
	while(top > 1 && X[top] < x) {
		sum -= (X[top] * (Y[top] - Y[top - 1])) % mod;
		sum = (sum + mod) % mod;
		top--;
	}
	++top;
	X[top] = x;
	Y[top] = y;
	sum += (Y[top] - Y[top - 1]) * X[top] % mod;
	sum %= mod;
}

long long calc(long long h) {
	len = 0;
	for(int i = 1; i <= k; i++) {
		if (p[i].x <= h)
			q[++len] = p[i];
	}
	top = 0; res = 0; sum = 0;
	X[++top] = h; Y[top] = 0;
	q[len + 1].y = m + 1;
	for(int i = 1; i <= len; i++) {
		insert(q[i].x, q[i].y);
		res = res + (sum * (q[i + 1].y - q[i].y)) % mod;
		res = res % mod;
	}
	return res;
}

int cmpy(node a, node b) {
	return a.y < b.y;
}

int main() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for(int i = 1; i <= k; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y), vecx.push_back(p[i].x);
	sort(p + 1, p + k + 1, cmpy);
	sort(vecx.begin(), vecx.end());
	vecx.resize(unique(vecx.begin(), vecx.end()) - vecx.begin());
	for(int i = 0; i < vecx.size(); i++) {
		long long tmp = calc(vecx[i]) % mod;
		if (i == vecx.size() - 1)
			tmp = tmp * (n - vecx[i] + 1) % mod;
		else
			tmp = tmp * (vecx[i + 1] - vecx[i]) % mod;
		ans = (ans + tmp) % mod;
	}
	cout << ans << endl;
	return 0;
}
