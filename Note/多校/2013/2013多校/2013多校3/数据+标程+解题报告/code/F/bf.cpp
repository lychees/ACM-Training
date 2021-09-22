#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;

const int MAX_N = int(1e5) + 10;
const int MAX_LETTER = 20;
int n;
char str[MAX_N];
//1..20

void work() {
	scanf("%s", str);
	n = strlen(str);

	int nQ;
	cin >> nQ;
	while (nQ--) {
		int mp[20];
		memset(mp, -1, sizeof mp);
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j) {
			char ch;
			scanf(" ");
			scanf("%ch", &ch);
			mp[ch - 'a'] = j;
		}
		int cnt[1 << 5] = { };

		int cur = 0;
		cnt[0]++;
		for (int i = 0; i < n; ++i) {
			int x = mp[str[i] - 'a'];
			if (x >= 0)
				cur ^= 1 << x;
			cnt[cur]++;
		}

		long long ans = 0;
		for (int i = 0; i < (1 << k); ++i) {
			ans += 1LL * cnt[i] * (cnt[i] - 1) / 2;
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
