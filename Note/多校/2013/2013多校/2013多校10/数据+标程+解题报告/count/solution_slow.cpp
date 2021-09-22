#include<cstdio>
#include<vector>
#include<string>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

const int N = 1e3 + 10;
long long MOD = 1e9 + 7;
long long n, m, k;
pair<long long, long long> a[N];
#define X first
#define Y second

set<int> T;
set<int> :: iterator J, K;
long long sum = 0;

long long choose(long long n) {
	long long rec = n * (n - 1) / 2 + n;
	if (rec >= MOD) rec %= MOD;
	return rec;
}

void Insert2(int y) {
	K = T.lower_bound(y);
	if (K != T.end() && *K == y) return ;
	J = K; J--;
	int L = *J + 1;
	int R = *K - 1;
	sum -= choose(R - L + 1);
	if (L < y) 
		sum += choose(y - L);
	if (y < R) 
		sum += choose(R - y);
	T.insert(y);
}

vector<pair<long long, long long> > seg;

void update(long long &a, long long b) {
	a += b % MOD;
	if (a >= MOD) a %= MOD;
	while (a < 0) a += MOD;
}

int main() {
	cin >> n >> m >> k;
	vector<int> px;
	for (int i = 1; i <= k; i++) {
		cin >> a[i].X >> a[i].Y;
		px.push_back(a[i].X);
		px.push_back(a[i].X - 1);
	}
	px.push_back(0);
	px.push_back(n);
	sort(px.begin(), px.end());
	px.erase(unique(px.begin(), px.end()), px.end());
	for (int i = 1; i < (int) px.size(); i++) 
		seg.push_back(make_pair(px[i - 1] + 1, px[i]));
	sort(a + 1, a + 1 + k);

	long long ans = 0;
	ans = choose(n) * choose(m) % MOD;
	for (int Li = 0; Li < (int) seg.size(); Li++) {
		sum = 0;
		T.clear();		
		sum = choose(m);
		T.insert(0);
		T.insert(m + 1);
		int ptr = 1;
		long long lenL = seg[Li].Y - seg[Li].X + 1;
		for (int Ri = Li; Ri < (int) seg.size(); Ri++) {
			long long lenR = seg[Ri].Y - seg[Ri].X + 1;
			while (ptr <= k && a[ptr].X <= seg[Ri].Y) {
				if (a[ptr].X >= seg[Ri].X) Insert2(a[ptr].Y);
				ptr++;
			}
			if (Ri == Li) 
				update(ans, -sum * choose(lenL) % MOD);
			else 
				update(ans, -sum * lenL % MOD * lenR % MOD);
		}
	}
	cout << ans << endl;
}
