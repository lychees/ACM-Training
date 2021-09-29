//ACM/ICPC World Finals 1999 A Bee Breeding
#include <cstdio>
#include <cstring>

#define MAX 10000
#define N 10300
#define M 61000
struct edge {
	int next, node;
} e[M + 1];
int head[N + 1], tot = 0;

inline void addedge(int a, int b) {
	e[++tot].next = head[a];
	head[a] = tot, e[tot].node = b;
	e[++tot].next = head[b];
	head[b] = tot, e[tot].node = a;
}

int d[N + 1];

void bfs(int S) {
	static int q[N + 1];
	int h = 0, t = 0;
	memset(d, 0, sizeof d);
	q[t++] = S, d[S] = 1;
	while (h < t) {
		int cur = q[h++];
		for (int i = head[cur]; i; i = e[i].next) {
			int node = e[i].node;
			if (d[node]) continue;
			d[node] = d[cur] + 1;
			q[t++] = node;
		}
	}
}

int main(int argc, char* argv[]) {
#ifdef KANARI
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	for (int last = 1, step = 1, now = 7; last <= MAX; last = now, now += 6 * (++step)) {
		int p = last, q = now + 1;
		addedge(last + 1, now);
		for (int i = last + 2; i <= now; ++i) addedge(i - 1, i);
		for (int row = 6; row > 0; --row) {
			addedge(p, --q);
			for (int i = 1; i < step; ++i) {
				addedge(p, --q);
				if (--p <= last - 6 * (step - 1)) p = last;
				addedge(p, q);
			}
		}
	}
	
	int a, b;
	while (scanf("%d%d", &a, &b), a != 0 && b != 0) {
		bfs(a);
		printf("The distance between cells %d and %d is %d.\n", a, b, d[b] - 1);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

