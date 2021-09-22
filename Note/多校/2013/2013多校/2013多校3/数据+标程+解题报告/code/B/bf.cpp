#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>
using namespace std;

const int MAX_N = 5000 + 10;
struct State {
	State*suf, *go[26];
	int val;
	void clear() {
		suf = 0;
		val = 0;
		memset(go, 0, sizeof go);
	}
	int calc() {
		if (suf == 0)
			return 0;
		return val - suf->val;
	}
}*root, *last;
State statePool[MAX_N * 2], *cur;

void init() {
	cur = statePool;
	root = last = cur++;
	root->clear();
}

int tot;
void extend(int w) {
	State*p = last, *np = cur++;
	np->clear();
	np->val = p->val + 1;
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p) {
		np->suf = root, tot += np->calc();
	} else {
		State*q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q, tot += np->calc();
		} else {
			State*nq = cur++;
			nq->clear();
			memcpy(nq->go, q->go, sizeof q->go);
			tot -= p->calc() + q->calc();
			nq->val = p->val + 1;
			nq->suf = q->suf;
			q->suf = nq;
			np->suf = nq;
			tot += p->calc() + q->calc() + np->calc() + nq->calc();
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	last = np;
}

int ans[MAX_N][MAX_N];
char s[MAX_N];
void work() {
	scanf("%s", s);
	int n = strlen(s);

	for (int i = 0; i < n; ++i) {
		init();
		tot = 0;
		for (int j = i; j < n; ++j) {
			extend(s[j] - 'a');
			ans[i][j] = tot;

//			int ret = 0;
//			for (State*k = statePool; k != cur; ++k)
//				ret += k->calc();
//			ans[i][j] = ret;
		}
	}

	int nQ;
	scanf("%d", &nQ);
	while (nQ--) {
		int l, r;
		scanf("%d%d", &l, &r);
		--l, --r;
		printf("%d\n", ans[l][r]);
	}
}

int main() {
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
