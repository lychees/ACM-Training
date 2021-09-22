#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

typedef long long int64;
int64 solve(int n) {
	assert(n>=2);
	assert(n <= int(1e9));
	int64 ans = 0;
	for (int i = n / 2; i >= 0; --i) {
		int j = n - i;
		if (1LL * i * j <= ans)
			break;
		ans = max(ans, 1LL * i / __gcd(i, j) * j);
	}
	return ans;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << solve(n) << endl;
	}
	return 0;
}
