#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
const int MAX_N = 20;

double dp[1 << MAX_N];
int mask[MAX_N][MAX_N];

int main() {
	int n;
	cin >> n;
	dp[0] = 0;

	for (int l = 0; l < n; ++l) {
		for (int r = l; r < n; ++r) {
			mask[l][r] = 1 << r;
			if (r > l)
				mask[l][r] |= mask[l][r - 1];
		}
	}

	for (int i = 1; i < (1 << n); ++i) {
		double stay = 0;
		double p = 1.0 / (n * (n + 1) / 2);
		double exp = 0;
		for (int l = 0; l < n; ++l) {
			for (int r = l; r < n; ++r) {
				int ni = i & (~mask[l][r]);
				if (ni == i) {
					stay += p;
				} else {
					exp += p * dp[ni];
				}
			}
		}
		dp[i] = (exp + 1) / (1 - stay);
	}
	printf("%0.10lf\n", dp[(1 << n) - 1]);
}
