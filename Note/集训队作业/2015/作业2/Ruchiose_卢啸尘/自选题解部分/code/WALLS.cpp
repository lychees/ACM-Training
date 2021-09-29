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

#include<set>
#include<vector>

const int MAXN = 200010;
const int MAXM = 200010;
const int INF = 0x3FFFFFFF;

int N, M;

int L[MAXN], R[MAXN], A[MAXM];
i64 ANS[MAXN];
set<pair<int,int> > segs, smallgaps;
vector<pair<int,int> > queries;
int A0;
i64 sumgap;

void addgap(int s, int l)
{
	segs.insert(make_pair(l, s));
	smallgaps.insert(make_pair(abs(s), l));
	sumgap += abs(s);
}

void erasegap(int l)
{
	set<pair<int,int> >::iterator it = segs.lower_bound(make_pair(l, -INF));
	sumgap -= abs(it->second);
	smallgaps.erase(make_pair(abs(it->second), it->first));
	segs.erase(it);
}

int simulate(int &L, int &R, int x)
{
	if (x < L)
		{
			int d = L - x;
			L -= d; R -= d;
			return d;
		}
	if (x > R)
		{
			int d = x - R;
			L += d; R += d;
			return d;
		}
	return 0;
}

int main()
{
	scanf("%d%d", &N, &M);
	int i;
	fortodo(i, 1, N) scanf("%d%d", &L[i], &R[i]);
	fortodo(i, 1, M) scanf("%d", &A[i]);
	queries.clear();
	segs.clear();
	smallgaps.clear();
	sumgap = 0;
	A0 = A[1];
	int laslen = 0;
	fortodo(i, 2, M)
		if (A[i] != A[i - 1])
			{
				if (laslen == 0)
					{
						laslen += A[i] - A[i - 1];
						continue;
					}
				if ((laslen > 0) ^ (A[i] - A[i - 1] > 0))
					{
						addgap(laslen, i - 1);
						laslen = A[i] - A[i - 1];
					}
				else
					laslen += A[i] - A[i - 1];
			}
	if (laslen) addgap(laslen, M);
	fortodo(i, 1, N)
		queries.push_back(make_pair(R[i] - L[i], i));
	sort(queries.begin(), queries.end());
	fortodo(i, 1, N)
		{
			int Q = queries[i - 1].second;
			int Len = R[Q] - L[Q];
			while ((smallgaps.size() > 1) && (smallgaps.begin()->first <= Len))
				{
					int LOC = smallgaps.begin()->second;
					if (LOC == segs.begin()->first)
						{
							A0 += segs.begin()->second;
							erasegap(LOC);
						}
					else
						if (LOC == segs.rbegin()->first)
							erasegap(LOC);
						else
							{
								set<pair<int,int> >::iterator it = segs.lower_bound(make_pair(LOC, -INF)), lit, rit;
								lit = it; lit--;
								rit = it; rit++;
								int nxgap = lit->second + it->second + rit->second;
								int nxloc = rit->first;
								erasegap(lit->first);
								erasegap(it->first);
								erasegap(rit->first);
								addgap(nxgap, nxloc);
							}
				}
			int l = L[Q], r = R[Q]; ANS[Q] = 0;
			if (segs.size() == 0) // 这只可能出现在A全相等时
				ANS[Q] += simulate(l, r, A0);
			else
				if (segs.size() == 1)
					{
						ANS[Q] += simulate(l, r, A0);
						ANS[Q] += simulate(l, r, A0 + segs.begin()->second);
					}
				else
					{
						ANS[Q] += simulate(l, r, A0);
						if (((r == A0) && (segs.begin()->second < 0)) || (l == A0) && (segs.begin()->second > 0))
							ANS[Q] += sumgap - segs.size() * 1LL * Len;
						else
							{
								ANS[Q] += simulate(l, r, A0 + segs.begin()->second);
								ANS[Q] += sumgap - abs(segs.begin()->second) - (segs.size() - 1LL) * 1LL * Len;
							}
					}

		}
	fortodo(i, 1, N)
		printf("%I64d\n", ANS[i]);
	return 0;
}

