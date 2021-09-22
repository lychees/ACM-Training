#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = 50, MAX_NRECTS = 10000 + 10;
int n, m, nRect;
int black[MAX_N][MAX_N], white[MAX_N][MAX_N];

int which[MAX_N][MAX_N];
int cnt[MAX_N][MAX_N];
struct Rect {
	int r1, c1, r2, c2; //r1..r2,c1..c2
	int color, score;
	void read() {
		cin >> r1 >> c1 >> r2 >> c2 >> color >> score;
		--r1, --c1, --r2, --c2;
	}

	bool check() {
		for (int r = r1; r <= r2; ++r) {
			for (int c = c1; c <= c2; ++c) {
				if (cnt[r][c] > 0 && which[r][c] != color)
					return false;
			}
		}
		return true;
	}

	void put() {
		for (int r = r1; r <= r2; ++r) {
			for (int c = c1; c <= c2; ++c) {
				++cnt[r][c];
				which[r][c] = color;
			}
		}
	}

	void unput() {
		for (int r = r1; r <= r2; ++r) {
			for (int c = c1; c <= c2; ++c) {
				--cnt[r][c];
			}
		}
	}
};

Rect rect[MAX_NRECTS];
int ans;

void dfs(int i, int ret) {
	if (i == nRect) {
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				if (cnt[r][c] == 0) {
					ret += max(black[r][c], white[r][c]);
				} else {
					if (which[r][c] == 0)
						ret += white[r][c];
					else
						ret += black[r][c];
				}
			}
		}
		ans = max(ans, ret);
		return;
	}

	Rect&r = rect[i];
	if (r.check()) {
		r.put();
		dfs(i + 1, ret + r.score);
		r.unput();
	}
	dfs(i + 1, ret);
}

void work() {
	cin >> n >> m >> nRect;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> black[r][c];
		}
	}
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> white[r][c];
		}
	}
	for (int i = 0; i < nRect; ++i) {
		rect[i].read();
	}
	memset(cnt, 0, sizeof cnt);
	memset(which, -1, sizeof which);
	ans = 0;
	dfs(0, 0);
	cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
