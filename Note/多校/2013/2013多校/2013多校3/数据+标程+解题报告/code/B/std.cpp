#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

typedef long long int64;

int n;
const int MAX_N = 5000 + 10;

char s[MAX_N];

const int SIZE = 100003;
const int SEED = 13331;

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
	int mark[SIZE], cmark;
	void clear() {
		++cmark;
		cur = nodePool;
	}
	Hash() {
		memset(mark, 0, sizeof mark);
		cmark = 0;
		clear();
	}
	int& find(int64 code) {
		int h = code % SIZE;
		if (h < 0)
			h += SIZE;

		if (mark[h] < cmark) {
			H[h] = 0;
			mark[h] = cmark;
		}

		for (Node*i = H[h]; i; i = i->next)
			if (i->key == code)
				return i->ret;
		return H[h] = (cur++)->set(code, H[h]), H[h]->ret;
	}
	int size() {
		return cur - nodePool;
	}
} H;

int64 pw[MAX_N];
int nId;

int getId(int64 x) {
	int&ret = H.find(x);
	if (ret == -1) {
		ret = nId++;
	}
	return ret;
}

int by[MAX_N][MAX_N], tot[MAX_N];

void put(int id, int i) {
	by[id][tot[id]++] = i;
}

int add[MAX_N][MAX_N]; //add for >=i >=j

void work() {
	scanf("%s", s);
	n = strlen(s);
	memset(add, 0, sizeof add);

	for (int L = 1; L <= n; ++L) {
		H.clear();
		int64 cd = 0;
		for (int j = 0; j < L; ++j) {
			cd = cd * SEED + s[j];
		}
		nId = 0;
		memset(tot, 0, sizeof tot);
		put(getId(cd), 0);
		for (int j = L; j < n; ++j) {
			cd = cd * SEED + s[j];
			cd -= pw[L] * s[j - L];
			put(getId(cd), j - L + 1);
		}

		for (int j = 0; j < nId; ++j) {
			int p = -1;
			int*v = by[j];
			for (int k = 0; k < tot[j]; ++k) {
				int l = v[k], r = l + L - 1;
				//the first contain is [l,r]
				//L in [p+1,l] R >= r
				add[p + 1][r] += 1;
				add[l + 1][r] -= 1;
				p = l;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			add[i][j] += add[i - 1][j] + add[i][j - 1] - add[i - 1][j - 1];
		}
	}

	int nQ;
	scanf("%d", &nQ);
	while (nQ--) {
		int l, r;
		scanf("%d%d", &l, &r);
		--l, --r;
		printf("%d\n", add[l][r]);
	}
}

bool isPrime(int x) {
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0)
			return false;
	}
	return true;
}

int main() {
	pw[0] = 1;
	for (int i = 1; i < MAX_N; ++i) {
		pw[i] = pw[i - 1] * SEED;
	}
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
