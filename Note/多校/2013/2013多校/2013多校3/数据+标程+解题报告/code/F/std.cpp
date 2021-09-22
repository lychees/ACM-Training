#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include <cassert>
using namespace std;

const int MAX_N = int(1e5) + 10;
const int MAX_LETTER = 20;

typedef long long int64;

int n;
char str[MAX_N];
//1..20
int cnt[1 << MAX_LETTER];

void ASSERT(bool a, string w = "wrong input format!") {
	if (!a)
		cerr << w << endl;
}

void work() {
	scanf("%s", str);
	n = strlen(str);
	int s = 0;
	memset(cnt, 0, sizeof cnt);
	cnt[s]++;
	for (int i = 0; i < n; ++i) {
		ASSERT(str[i] - 'a' < MAX_LETTER);
		s ^= 1 << (str[i] - 'a');
		cnt[s]++;
	}

	for (int i = 0; i < MAX_LETTER; ++i) {
		for (int j = 0; j < (1 << MAX_LETTER); ++j)
			if (j >> i & 1) {
				cnt[j - (1 << i)] += cnt[j];
			}
	}

	int nQ;
	cin >> nQ;
	while (nQ--) {
		int k; //k<=5
		scanf("%d", &k);
		ASSERT(k <= 5);
		int v[5];
		for (int i = 0; i < k; ++i) {
			char ch;
			scanf(" ");
			scanf("%c", &ch);
			v[i] = ch - 'a';
			ASSERT(v[i] < MAX_LETTER);
		}
		for (int i = 0; i < k; ++i) {
			for (int j = i + 1; j < k; ++j) {
				ASSERT(v[i] != v[j]);
			}
		}

		int dp[1 << 5];
		for (int i = 0; i < (1 << k); ++i) {
			int mask = 0;
			for (int j = 0; j < k; ++j)
				if (i >> j & 1) {
					mask |= 1 << v[j];
				}
			dp[i] = cnt[mask];
		}

		int super = (1 << k) - 1;
		for (int i = (1 << k) - 1; i >= 0; --i) {
			for (int j = i; j <= super; (++j) |= i)
				if (j > i)
					dp[i] -= dp[j];
		}

		int64 ans = 0;

		for (int i = 0; i < (1 << k); ++i) {
			ans += 1LL * dp[i] * (dp[i] - 1) / 2;
		}

		cout << ans << endl;
	}
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
}
