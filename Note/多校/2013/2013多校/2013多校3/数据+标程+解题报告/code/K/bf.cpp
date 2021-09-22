#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

//100003,1000003,10000019
const int MAX_N = int(1e5) + 10;
typedef long long int64;

void readVector(int n, int x[]) {
	int64 cur = 0;
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
	for (int i = 0; i < n; ++i) {
		cur = (cur * a + b) % c;
		x[i] = cur;
	}
}

int n, x[MAX_N], y[MAX_N];

void work() {
	cin >> n;
	readVector(n, x);
	readVector(n, y);

	int64 ans = 1LL << 60, sum = 0;

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			int64 dx = x[i] - x[j], dy = y[i] - y[j];
			ans = min(ans, dx * dx + dy * dy);
		}
		sum += ans;
	}

	cout << sum << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
