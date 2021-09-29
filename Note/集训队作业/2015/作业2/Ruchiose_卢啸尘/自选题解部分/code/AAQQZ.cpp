// Author: Ruchiose
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define fortodo(i, f, t) for (i = f; i <= t; i++)
#define i64 long long
#define d64 long double
using namespace std;

const int MAXN = 3010;

int N, S, A[MAXN], cnt[MAXN];
int C[MAXN][MAXN];

int ans = 0;

void Rev()
{
	int i, _A[MAXN];
	fortodo(i, 1, N) _A[N + 1 - i] = S + 1 - A[i];
	fortodo(i, 1, N) A[i] = _A[i];
}

void calcSigC()
{
	A[0] = -1; A[N + 1] = -2;
	int i, j;
	fortodo(i, 0, N)
		for (j = N + 1; j >= i; j--)
			if (A[i] == A[j])
				C[i][j] = C[i - 1][j + 1] + 1;
			else
				C[i][j] = 0;
}

int UnivScanProc(int LR, int RL, int MI)
{
	if ((LR < 1) || (RL > N)) return 0;
	int LL = LR;
	while ((LL) && (A[LL - 1] >= A[LL])) LL--;
	int mi = 0; // Ò»º½‘é¤ÎÕF¤ê¡¢¤³¤ó¤Ê¤È¤³¤í¤ÇÊ§¤¦¤ï¤±¤Ë¤Ï¡­£¡
	int ans = 0;
	#define LRV(x) A[LR - (x)]
	int MATCH = 0, RST = LR - LL + 1;
	int RR, i;
	int need[MAXN], free[MAXN];
	fortodo(i, 1, S) need[i] = free[i] = 0;
	fortodo(i, LL, LR) need[A[i]]++;
	fortodo(RR, RL, N)
		{
			if (MI == A[RR])
				mi++;
			else
				{
					free[A[RR]]++;
					need[A[RR]]--;
					if (need[A[RR]] < 0)
						while ((RST) && (LRV(RST - 1) > A[RR]))
							RST--;
					while ((MATCH < LR - LL + 1) && (free[LRV(MATCH)]))
						{
							free[LRV(MATCH)]--;
							MATCH++;
						}
				}
			ans = max(ans, min(MATCH, RST) * 2 + mi + ((MATCH + mi == RR - RL + 1) ? (C[LR - MATCH][RR + 1] * 2) : 0));
		}
	return ans;
}

void ScanProcMk1()
{
	for (int dC = 2; dC <= 2 * N; dC++)
		{
			int LR, RL;
			LR = dC / 2;
			RL = dC - LR;
			int d = C[LR][RL];
			LR -= d;
			RL += d;
			ans = max(ans, UnivScanProc(LR, RL, -1) + (RL - LR - 1));
		}
}

void ScanProcMk2()
{
	for (int i = 1; i < N; i++)
		{
			int MI = -1;
			for (int j = i + 1; j <= N; j++)
				if (A[j] < A[i])
					{
						MI = A[j];
						break;
					}
			ans = max(ans, UnivScanProc(i, i + 1, MI));
		}
}

void Analyse()
{
	ScanProcMk1();
	ScanProcMk2();
}

int main()
{
	scanf("%d%d", &N, &S);
	int i;
	fortodo(i, 1, N) scanf("%d", &A[i]);
	fortodo(i, 1, S) cnt[i] = 0;
	fortodo(i, 1, N) cnt[A[i]]++;
	fortodo(i, 1, S) ans = max(ans, cnt[i]);
	calcSigC();
	Analyse();
	Rev();
	calcSigC();
	Analyse();
	cout << ans << endl;
	return 0;
}

