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

int N;
int X[MAXN], Y[MAXN], S[MAXN], Z[MAXN];

i64 ans;

void discritize()
{
	int i;
	fortodo(i, 1, N) S[i] = X[i];
	sort(S + 1, S + N + 1);
	fortodo(i, 1, N) X[i] = lower_bound(S + 1, S + N + 1, X[i]) - S;
	fortodo(i, 1, N) S[i] = Y[i];
	sort(S + 1, S + N + 1);
	fortodo(i, 1, N) Y[i] = lower_bound(S + 1, S + N + 1, Y[i]) - S;
}

int Zp[MAXN];
set<int> Zs;
vector<pair<int,int> > Sp;

int V[MAXN];

void Init()
{
	int i;
	fortodo(i, 1, N) V[i] = 0;
}

void Ins(int x, int v)
{
	for (; x <= N; x += x & -x) V[x] += v;
}

int Qry(int x)
{
	int v = 0;
	for (; x; x -= x & -x) v += V[x];
	return v;
}

int Qry(int x, int y)
{
	return Qry(y) - Qry(x - 1);
}

void Analyse(int L, int R)
{
	if (L == R) return;
	int Lr = (L + R) / 2;
	int Rl = Lr + 1;
	Analyse(L, Lr);
	Analyse(Rl, R);
	Zs.clear(); Zs.insert(N + 1);
	for (int i = Lr; i >= L; i--)
		{
			set<int>::iterator it = Zs.lower_bound(Z[i]);
			Zp[i] = (*it) - 1;
			Zs.insert(Z[i]);
		}
	Zs.clear(); Zs.insert(0);
	int i;
	fortodo(i, Rl, R)
		{
			set<int>::iterator it = Zs.upper_bound(Z[i]);
			it--;
			Zp[i] = (*it) + 1;
			Zs.insert(Z[i]);
		}
	Sp.clear();
	fortodo(i, L, Lr) Sp.push_back(make_pair(Z[i], -i));
	fortodo(i, Rl, R) Sp.push_back(make_pair(Zp[i], -i));
	sort(Sp.begin(), Sp.end());
	for (vector<pair<int,int> >::iterator it = Sp.begin(); it != Sp.end(); it++)
		if (-it->second >= Rl)
			Ins(Z[-it->second], 1);
		else
			ans += Qry(Z[-it->second], Zp[-it->second]);
	fortodo(i, Rl, R) Ins(Z[i], -1);
}

int main()
{
	scanf("%d", &N);
	int i;
	fortodo(i, 1, N) scanf("%d%d", &X[i], &Y[i]);
	discritize();
	fortodo(i, 1, N) Z[X[i]] = Y[i];
	ans = 0;
	Init();
	Analyse(1, N);
	cout << ans << endl;
	return 0;
}

