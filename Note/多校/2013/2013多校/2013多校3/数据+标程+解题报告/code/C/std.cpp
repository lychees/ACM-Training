#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
//1..30
//1 and prime >15 are same -> everyone else is coprime with them

typedef long long int64;

int reduce(int x) {
	for (int i = 2; i * i <= x; ++i) {
		while (x % (i * i) == 0)
			x /= i;
	}
	return x;
}

bool isPrime(int x) {
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0)
			return false;
	}
	return true;
}

const int SIZE = 10000019;

struct Node {
	int64 key;
	int ret;
	Node*next;
	Node*set(int64 key, Node*next) {
		this->key = key, this->next = next;
		ret = -1;
		return this;
	}
}
;
Node nodePool[SIZE], *cur;

struct Hash {
	Node*H[SIZE];
	void clear() {
		memset(H, 0, sizeof H);
		cur = nodePool;
	}
	Hash() {
		clear();
	}
	int& find(int64 code) {
		int h = code % SIZE;
		for (Node*i = H[h]; i; i = i->next)
			if (i->key == code)
				return i->ret;
		return H[h] = (cur++)->set(code, H[h]), H[h]->ret;
	}
	int size() {
		return cur - nodePool;
	}
} H;

//2,3,5,7,11,13
//mod <= 30000
int n, mod;

const int MAX_N = 30 + 1;
int cnt[MAX_N];

int a[MAX_N], mx[MAX_N], tot;

bool can[MAX_N][MAX_N];

Hash memo;

int eval(int*c, int lst) {
//	int nc[MAX_N]; //do something cool
//	memcpy(nc, c, sizeof nc);
//	c = nc;

	int64 code = lst;
	for (int i = 0; i < tot; ++i) {
		code *= mx[i] + 1;
		code += c[i];
	}
	int&ret = memo.find(code);
	if (ret != -1)
		return ret;
	ret = 0;
	bool hasNext = false;
	for (int i = 0; i < tot; ++i) {
		if (c[i] > 0) {
			hasNext = true;
			if (can[i][lst]) {
				int tmp = c[i];
				--c[i];
				ret += eval(c, i) * tmp;
				++c[i];
			}
		}
	}
	if (!hasNext)
		++ret;
	ret %= mod;
	return ret;
}

void work() {
	cin >> n >> mod;

	memset(cnt, 0, sizeof cnt);
	++cnt[1];
	for (int i = 2; i <= n; ++i) {
		if (i > n / 2 && isPrime(i)) {
			++cnt[1];
			continue;
		}
		++cnt[reduce(i)];
	}

	int nState = 1;
	tot = 0;
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] > 0) {
			a[tot] = i;
			mx[tot++] = cnt[i];
			nState *= cnt[i] + 1;
		}
	}
//	cerr << nState << endl;

	for (int i = 0; i < tot; ++i) {
		for (int j = 0; j < tot; ++j) {
			can[i][j] = __gcd(a[i], a[j]) == 1;
		}
	}

	int c[MAX_N];
	for (int i = 0; i < tot; ++i) {
		c[i] = mx[i];
	}
	memo.clear();
	cout << eval(c, 0) << endl;
//	cout << memo.size() << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
