#include<vector>
#include "Annalib.h"
using namespace std;

#define fortodo(i, f, t) for (i = f; i <= t; i++)
#define i64 long long

static const long long INF = 3300000000000000000ll;
static const int MAXN = 333;

static long long DIST[MAXN][MAXN];

static i64 TOSEND, UNIT;

void Anna(int N, int M, int A[], int B[], long long C[], int Q, int S[], int T[], int K, int U[]) {
	int i, j, k;
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
			SCHLEN[i][k] = DIST[S[i]][A[U[k]]] + C[U[k]] + DIST[B[U[k]]][T[i]];
	fortodo(i, 0, Q - 1)
		SCHLEN[i][K] = DIST[S[i]][T[i]];
	int typ[66], cnt[6], cntnew[6];
	TOSEND = 0; UNIT = 1;
	fortodo(i, 0, Q - 1) typ[i] = 0;
	fortodo(k, 1, K)
		{
			fortodo(i, 0, k - 1) cnt[i] = cntnew[i] = 0;
			fortodo(i, 0, Q - 1)
				{
					cnt[typ[i]]++;
					if (SCHLEN[i][typ[i]] > SCHLEN[i][k])
						{
							cntnew[typ[i]]++;
							typ[i] = k;
						}
				}
			fortodo(i, 0, k - 1)
				{
					TOSEND += UNIT * cntnew[i];
					UNIT *= cnt[i] + 1;
				}
		}
	while (TOSEND)
		{
			Tap(int(TOSEND & 1));
			TOSEND >>= 1;
		}
}
