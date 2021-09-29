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

#include<vector>

const int MAXN = 3010;
const double PI = acos(-1.0);

int N;
int X[MAXN], Y[MAXN], C[MAXN];

i64 ans;

int FRONT[3], BACK[3];

void COLLECT(int color1, int color2)
{
	int nxcolor1 = (color1 + 1) % 3, nxcolor2 = (color2 + 1) % 3;
	ans += FRONT[nxcolor1] * FRONT[3 ^ color1 ^ nxcolor1] * 1LL * BACK[nxcolor2] * BACK[3 ^ color2 ^ nxcolor2];
	ans += FRONT[nxcolor2] * FRONT[3 ^ color2 ^ nxcolor2] * 1LL * BACK[nxcolor1] * BACK[3 ^ color1 ^ nxcolor1];
}

int main()
{
	scanf("%d", &N);
	int i, j;
	fortodo(i, 1, N) scanf("%d%d%d", &X[i], &Y[i], &C[i]);
	ans = 0;
	fortodo(i, 1, N)
		{
			vector<pair<double,int> > VPDI;
			VPDI.clear();
			fortodo(j, 1, N)
				if (i != j)
					{
						VPDI.push_back(make_pair(atan2(Y[j] - Y[i], X[j] - X[i]), C[j]));
						VPDI.push_back(make_pair(atan2(Y[i] - Y[j], X[i] - X[j]),-C[j] - 1));
					}
			sort(VPDI.begin(), VPDI.end());
			fortodo(j, 0, 2) FRONT[j] = BACK[j] = 0;
			fortodo(j, 1, N - 2)
				if (VPDI[j].second >= 0)
					FRONT[VPDI[j].second]++;
				else
					BACK[VPDI[j + N - 1].second]++;
			COLLECT(C[i], (VPDI[0].second >= 0) ? (VPDI[0].second) : (-1 - VPDI[0].second));
			fortodo(j, 1, N - 2)
				{
					if (VPDI[j - 1].second >= 0)
						BACK[VPDI[j - 1].second]++;
					else
						FRONT[VPDI[j - 1 + N - 1].second]++;
					if (VPDI[j].second >= 0)
						FRONT[VPDI[j].second]--;
					else
						BACK[VPDI[j + N - 1].second]--;
					COLLECT(C[i], (VPDI[j].second >= 0) ? (VPDI[j].second) : (-1 - VPDI[j].second));
				}
		}
	ans /= 4;
	cout << ans << endl;
	return 0;
}

