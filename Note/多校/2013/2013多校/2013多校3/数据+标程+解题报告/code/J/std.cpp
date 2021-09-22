#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = int(1e5) + 10;

int a[MAX_N], n;
vector<int> divs[MAX_N];

int last[MAX_N] = { };

vector<pair<int, int> > by[MAX_N]; //l,id

struct TA {
	int a[MAX_N], n;

	void init(int n) {
		this->n = n;
		memset(a, 0, sizeof a);
	}

	int query(int p) {
		int ret = 0;
		for (p++; p; p -= p & -p)
			ret = max(ret, a[p - 1]);
		return ret;
	}

	void modify(int p, int x) {
		for (p++; p <= n; p += p & -p)
			a[p - 1] = max(a[p - 1], x);
	}
} ta;

int ans[MAX_N];

void work() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		by[i].clear();
	}
	int nQ;
	cin >> nQ;
	for (int i = 0; i < nQ; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		--l, --r;
		by[r].push_back(make_pair(l, i));
	}

	memset(last, -1, sizeof last);
	ta.init(n);

	for (int i = 0; i < n; ++i) {
		int x = a[i];
		for (vector<int>::iterator e = divs[x].begin(); e != divs[x].end(); ++e) {
			int p = last[*e];
			if (p != -1) {
				ta.modify(n - 1 - p, *e);
			}
			last[*e] = i;
		}
		for (vector<pair<int, int> >::iterator e = by[i].begin();
				e != by[i].end(); ++e) {
			ans[e->second] = ta.query(n - 1 - e->first);
		}
	}

	for (int i = 0; i < nQ; ++i) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	for (int i = 1; i < MAX_N; ++i) {
		for (int j = i; j < MAX_N; j += i)
			divs[j].push_back(i);
	}

	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
