#include<vector>
#include<cstdlib>
#include<algorithm>
#include "Brunolib.h"
using namespace std;

#define fortodo(i, f, t) for (i = f; i <= t; i++)
#define i64 long long

static const long long INF = 3300000000000000000ll;
static const int MAXN = 333;

static long long DIST[MAXN][MAXN];
static vector<int> OS[MAXN];

static i64 RECEIVED;

void Bruno(int N, int M, int A[], int B[], long long C[], int Q, int S[], int T[], int K, int U[], int L, int X[]) {
	int i, j, k;
	fortodo(i, 0, N - 1) OS[i].clear();
	fortodo(i, 0, M - 1) OS[A[i]].push_back(i);
	fortodo(i, 0, N - 1)
		fortodo(j, 0, N - 1)
			DIST[i][j] = (i == j) ? 0 : INF;
	fortodo(i, 0, M - 1)
		DIST[A[i]][B[i]] = C[i];
	fortodo(i, 0, K - 1)
		DIST[A[U[i]]][B[U[i]]] = INF;
	int Z = A[U[0]];
	fortodo(k, 0, N - 1)
		fortodo(i, 0, N - 1)
			fortodo(j, 0, N - 1)
				DIST[i][j] = min(DIST[i][j], DIST[i][k] + DIST[k][j]);
	i64 SCHLEN[66][6];
	fortodo(k, 0, K - 1)
		fortodo(i, 0, Q - 1)
			SCHLEN[i][k] = DIST[S[i]][A[U[k]]] + DIST[B[U[k]]][T[i]];
	fortodo(i, 0, Q - 1)
		SCHLEN[i][K] = DIST[S[i]][T[i]];
	RECEIVED = 0;
	for (i = L - 1; i >= 0; i--) RECEIVED = RECEIVED * 2 + X[i];
	int typ[66], cnt[6];
	vector<pair<i64,int> > VPLI[6];
	fortodo(i, 0, Q - 1) typ[i] = 0;
	fortodo(k, 1, K)
		{
			fortodo(i, 0, k - 1)
				{
					cnt[i] = 0;
					VPLI[i].clear();
				}
			fortodo(i, 0, Q - 1)
				{
					cnt[typ[i]]++;
					VPLI[typ[i]].push_back(make_pair(SCHLEN[i][k] - SCHLEN[i][typ[i]], i));
				}
			fortodo(i, 0, k - 1)
				{
					sort(VPLI[i].begin(), VPLI[i].end());
					int v = RECEIVED % (cnt[i] + 1);
					RECEIVED /= cnt[i] + 1;
					fortodo(j, 0, v - 1) typ[VPLI[i][j].second] = k;
				}
		}
	fortodo(i, 0, Q - 1)
		{
			if (typ[i] == K)
				{
					int cur = S[i];
					while (cur != T[i])
						for (vector<int>::iterator it = OS[cur].begin(); it != OS[cur].end(); it++)
							if (DIST[cur][T[i]] == C[*it] + DIST[B[*it]][T[i]])
								{
									Answer(*it);
									cur = B[*it];
									break;
								}
				}
			else
				{
					int cur = S[i];
					while (cur != Z)
						for (vector<int>::iterator it = OS[cur].begin(); it != OS[cur].end(); it++)
							if (DIST[cur][Z] == C[*it] + DIST[B[*it]][Z])
								{
									Answer(*it);
									cur = B[*it];
									break;
								}
					Answer(U[typ[i]]);
					cur = B[U[typ[i]]];
					while (cur != T[i])
						for (vector<int>::iterator it = OS[cur].begin(); it != OS[cur].end(); it++)
							if (DIST[cur][T[i]] == C[*it] + DIST[B[*it]][T[i]])
								{
									Answer(*it);
									cur = B[*it];
									break;
								}
				}
			Answer(-1);
		}
}
