#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <cassert>

using namespace std;

typedef long long LL;

const int maxn = 2333;
int tests, m, nxt[maxn];
char text[maxn], patt[maxn];
vector<pair<string, int> > segs;

void preprocess() {
	memset(nxt, 0, sizeof(nxt));
	nxt[1] = 0;
	int j = 0;
	for (int i = 2; i <= m; ++i) {
		while (j > 0 && patt[j + 1] != patt[i]) j = nxt[j];
		if (patt[j + 1] == patt[i]) j += 1;
		nxt[i] = j;
	}
}

vector<int> kmp(const char *text) {
	int n = strlen(text + 1), j = 0;
	vector<int> ans;
	for (int i = 1; i <= n; ++i) {
		while (j > 0 && patt[j + 1] != text[i]) j = nxt[j];
		if (patt[j + 1] == text[i]) j = j + 1;
		if (j == m) {
			ans.push_back(i - m);
			j = nxt[j];
		}
	}
	return ans;
}

void parse(const char *text) {
	segs.clear();
	int n = strlen(text + 1);
	string cur;
	for (int i = 1; i <= n; ) {
		if (isalpha(text[i])) {
			int j = i; cur = "";
			while (j <= n && isalpha(text[j])) {
				cur += text[j++];
			}
			i = j;
			segs.push_back(make_pair(cur, 1));
		} else if (text[i] == '[') {
			int j = i + 1; cur = "";
			while (j <= n && text[j] != ']') {
				cur += text[j++];
			}
			int num = 0;
			j += 1;
			while (j <= n && isdigit(text[j])) {
				num = num * 10 + text[j++] - '0';
			}
			i = j;
			segs.push_back(make_pair(cur, num));
		} else assert(false);
	}
}

LL count(const pair<string, int> &psl) {
	string str = psl.first, tmp;
	int times = psl.second;
	LL ans = 0;
	int n = str.length();
	while (tmp.length() <= m) tmp += str;
	tmp += tmp;
	vector<int> occur = kmp(tmp.c_str() - 1);
	for (vector<int>::iterator it = occur.begin(); it != occur.end(); ++it) {
		int pos = *it + 1;
		if (pos > n) continue;
		LL k = (LL)times * n - pos - m + 1;
		if (k >= 0) ans += k / n + 1;
	}
	return ans;
} 

int main() {
	while (scanf("%s%s", text + 1, patt + 1) != EOF) {
		m = strlen(patt + 1);
		parse(text); preprocess();
		LL ans = 0;
		for (int i = 0; i < segs.size(); ++i) {
			ans += count(segs[i]);
		}
		string prefix, suffix;
		for (int i = 0; i < segs.size(); ++i) {
			LL times = segs[i].second;
			suffix = "";
			while (times--) {
				suffix += segs[i].first;
				if (suffix.length() >= m) break;
			}
			if (suffix.length() >= m) suffix = suffix.substr(0, m - 1);
			ans += kmp((prefix + suffix).c_str() - 1).size();
			times = segs[i].second;
			if (times * segs[i].first.length() < m) {
				while (times--) {
					prefix += segs[i].first;
				}
				if (prefix.length() >= m) prefix = prefix.substr(prefix.length() - (m - 1), m - 1);
			} else {
				prefix = "";
				while (times--) {
					prefix += segs[i].first;
					if (prefix.length() >= m) break;
				}
				if (prefix.length() >= m) prefix = prefix.substr(prefix.length() - (m - 1), m - 1);
			}
		}
		cout << ans << endl;
	}
	return 0;
}