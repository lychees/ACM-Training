#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int MAX_N = 50 + 5, MAX_NRECTS = 10000 + 10;
int n, m, nRect;
int black[MAX_N][MAX_N], white[MAX_N][MAX_N];
int id[MAX_N][MAX_N];

int ans;

typedef int Flow;
const Flow INF = ~0U >> 1; //should change with type
struct Maxflow {
//	static const Flow INF = numeric_limits<Flow>::max();
	struct Edge {
		int t;
		Flow c;
		Edge*n, *r;
		Edge(int _t, Flow _c, Edge*_n) :
				t(_t), c(_c), n(_n) {
		}
	};
	vector<Edge*> E;

	int addV() {
		E.push_back((Edge*) 0);
		return E.size() - 1;
	}

	void clear() {
		for (int i = 0; i < E.size(); ++i) {
			for (Edge*e = E[i]; e;) {
				Edge*ne = e->n;
				delete e;
				e = ne;
			}
		}
		E.clear();
	}

	Edge* makeEdge(int s, int t, Flow c) {
		return E[s] = new Edge(t, c, E[s]);
	}

	void addEdge(int s, int t, Flow c) {
		Edge*e1 = makeEdge(s, t, c), *e2 = makeEdge(t, s, 0);
		e1->r = e2, e2->r = e1;
	}

	int calcMaxFlow(int vs, int vt) {
		int nV = E.size();
		Flow totalFlow = 0;

		vector<Flow> am(nV, 0);
		vector<int> h(nV, 0), cnt(nV + 1, 0);
		vector<Edge*> prev(nV, (Edge*) 0), cur(nV, (Edge*) 0);
		cnt[0] = nV;

		int u = vs;
		Edge*e;
		am[u] = INF;
		while (h[vs] < nV) {
			for (e = cur[u]; e; e = e->n)
				if (e->c > 0 && h[u] == h[e->t] + 1)
					break;
			if (e) {
				int v = e->t;
				cur[u] = prev[v] = e;
				am[v] = min(am[u], e->c);
				u = v;
				if (u == vt) {
					Flow by = am[u];
					while (u != vs) {
						prev[u]->c -= by;
						prev[u]->r->c += by;
						u = prev[u]->r->t;
					}
					totalFlow += by;
					am[u] = INF;
				}
			} else {
				if (!--cnt[h[u]])
					break;
				h[u] = nV;
				for (e = E[u]; e; e = e->n)
					if (e->c > 0 && h[e->t] + 1 < h[u]) {
						h[u] = h[e->t] + 1;
						cur[u] = e;
					}
				++cnt[h[u]];
				if (u != vs)
					u = prev[u]->r->t;
			}
		}

		return totalFlow;
	}

	~Maxflow() {
		clear();
	}
};

Maxflow net;
int vs, vt;

const int MAX_LOG = 10;
int edgeTo[MAX_LOG][MAX_LOG][MAX_N][MAX_N];
int edgeFrom[MAX_LOG][MAX_LOG][MAX_N][MAX_N];

int log(int k) {
	int i = 0;
	while ((1 << i) <= k)
		++i;
	--i;
	return i;
}

void addTo(int r1, int c1, int r2, int c2, int u) {
	int R = (r2 - r1 + 1), C = (c2 - c1 + 1);
	int rk = log(R), ck = log(C);
	int (*w)[MAX_N] = edgeTo[rk][ck];
	net.addEdge(u, w[r1][c1], INF);
	net.addEdge(u, w[r2 - (1 << rk) + 1][c1], INF);
	net.addEdge(u, w[r1][c2 - (1 << ck) + 1], INF);
	net.addEdge(u, w[r2 - (1 << rk) + 1][c2 - (1 << ck) + 1], INF);
}
void addFrom(int r1, int c1, int r2, int c2, int u) {
	int R = (r2 - r1 + 1), C = (c2 - c1 + 1);
	int rk = log(R), ck = log(C);
	int (*w)[MAX_N] = edgeFrom[rk][ck];
	net.addEdge(w[r1][c1], u, INF);
	net.addEdge(w[r2 - (1 << rk) + 1][c1], u, INF);
	net.addEdge(w[r1][c2 - (1 << ck) + 1], u, INF);
	net.addEdge(w[r2 - (1 << rk) + 1][c2 - (1 << ck) + 1], u, INF);
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

	net.clear();
	vs = net.addV(), vt = net.addV();
	//with S -> black
	//with T -> white
	int tot = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			id[r][c] = net.addV();
			tot += black[r][c] + white[r][c];
			net.addEdge(vs, id[r][c], black[r][c]);
			net.addEdge(id[r][c], vt, white[r][c]);
		}
	}

	for (int i = 0; (1 << i) <= n; ++i) {
		for (int j = 0; (1 << j) <= m; ++j) {
			int (*to)[MAX_N] = edgeTo[i][j], (*from)[MAX_N] = edgeFrom[i][j];
			for (int r = 0; r + (1 << i) <= n; ++r) {
				for (int c = 0; c + (1 << j) <= m; ++c) {
					if (i == 0 && j == 0) {
						to[r][c] = from[r][c] = id[r][c];
						continue;
					}
					//S to them
					if (i > 0) {
						int (*pto)[MAX_N] = edgeTo[i - 1][j], (*pfrom)[MAX_N] =
								edgeFrom[i - 1][j], u;
						u = to[r][c] = net.addV();
						int go = 1 << (i - 1);
						net.addEdge(u, pto[r][c], INF);
						net.addEdge(u, pto[r + go][c], INF);
						u = from[r][c] = net.addV();
						net.addEdge(pfrom[r][c], u, INF);
						net.addEdge(pfrom[r + go][c], u, INF);

						continue;
					}

					int (*pto)[MAX_N] = edgeTo[i][j - 1], (*pfrom)[MAX_N] =
							edgeFrom[i][j - 1], u;
					u = to[r][c] = net.addV();
					int go = 1 << (j - 1);
					net.addEdge(u, pto[r][c], INF);
					net.addEdge(u, pto[r][c + go], INF);
					u = from[r][c] = net.addV();
					net.addEdge(pfrom[r][c], u, INF);
					net.addEdge(pfrom[r][c + go], u, INF);
				}
			}
		}
	}

	int cntE = 0;

	for (int i = 0; i < nRect; ++i) {
		int r1, c1, r2, c2; //r1..r2,c1..c2
		int color, score;
		cin >> r1 >> c1 >> r2 >> c2 >> color >> score;
		--r1, --c1, --r2, --c2;
		tot += score;

		int u = net.addV();

		if (color == 0) {
			net.addEdge(u, vt, score);
			addFrom(r1, c1, r2, c2, u);
		} else {
			net.addEdge(vs, u, score);
			addTo(r1, c1, r2, c2, u);
		}
	}
//	cerr << cntE << endl;
	cout << tot - net.calcMaxFlow(vs, vt) << endl;
}

//1890669795
int main() {
	int T;
	cin >> T;
	while (T--)
		work();

	return 0;
}
