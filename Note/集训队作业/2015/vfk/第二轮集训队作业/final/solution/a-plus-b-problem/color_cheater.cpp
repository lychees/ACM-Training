#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

const int MaxN = 5000;

// getint
inline int getint()
{
    char c;
    while (c = getchar(), ('0' > c || c > '9') && c != '-');
    
    if (c != '-')
    {
        int res = c - '0';
        while (c = getchar(), '0' <= c && c <= '9')
            res = res * 10 + c - '0';
        return res;
    }
    else
    {
        int res = 0;
        while (c = getchar(), '0' <= c && c <= '9')
            res = res * 10 + c - '0';
        return -res;
    }
}

// adjust
template <class T>
inline bool relax(T &a, const T &b)
{
	if (b > a)
	{
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool tension(T &a, const T &b)
{
	if (b < a)
	{
		a = b;
		return true;
	}
	return false;
}

inline int lowbit(const int &t)
{
	return t & -t;
}

int n;
int a[MaxN + 1];
int bVal[MaxN], wVal[MaxN + 1];
int qL[MaxN + 1], qR[MaxN + 1];
int penalty[MaxN + 1];

int seqA_n;
int seqA[MaxN];

bool col[MaxN + 1];

int bit[MaxN + 1];
inline void bit_init()
{
	fill(bit + 1, bit + seqA_n + 1, 0);
}
inline void bit_add(const int &pos)
{
	for (int j = pos; j <= seqA_n; j += lowbit(j))
		bit[j]++;
}
inline int bit_query(const int &pos)
{
	int res = 0;
	for (int j = pos; j >= 1; j -= lowbit(j))
		res += bit[j];
	return res;
}

inline int eval()
{
	int res = 0;
	bit_init();
	for (int i = 1; i <= n; i++)
	{
		if (col[i])
		{
			if (qL[i] <= qR[i])
			{
				int cnt = bit_query(qR[i]) - bit_query(qL[i] - 1);
				if (cnt > 0)
					res -= penalty[i];
			}
			res += bVal[i];
		}
		else
			res += wVal[i], bit_add(a[i]);
	}
	return res;
}

inline void adjust()
{
	static int bestVal = eval();
	static bool best[MaxN + 1];

	copy(col + 1, col + n + 1, best + 1);

	int first = min(4, n);
	for (int status = 0; status < (1 << first); status++)
	{
		copy(best + 1, best + n + 1, col + 1);
		for (int i = 0; i < first; i++)
			col[i] = status >> i & 1;

		int cur = eval();
		for (int times = 0; times <= 100; times++)
		{
			int x = rand() % n + 1, y = rand() % n + 1;
			int t;

			col[x] = !col[x];
			t = eval();
			if (t > cur)
				cur = t;
			else
				col[x] = !col[x];
	
			col[x] = !col[x], col[y] = !col[y];
			t = eval();
			if (t > cur)
				cur = t;
			else
				col[x] = !col[x], col[y] = !col[y];
		}

		if (cur > bestVal)
		{
			bestVal = cur;
			copy(col + 1, col + n + 1, best + 1);
		}
	}

	copy(best + 1, best + n + 1, col + 1);
}

inline int cheat1()
{
	for (int i = 1; i <= n; i++)
		col[i] = bVal[i] > wVal[i];
	adjust();
	return eval();
}
inline int cheat2()
{
	bit_init();
	for (int i = 1; i <= n; i++)
	{
		int tb = bVal[i], tw = wVal[i];
		if (qL[i] <= qR[i])
		{
			int cnt = bit_query(qR[i]) - bit_query(qL[i] - 1);
			if (cnt > 0)
				tb -= penalty[i];
		}
		
		if (tb > tw)
			col[i] = true;
		else
			col[i] = false, bit_add(a[i]);
	}
	adjust();
	return eval();
}
inline int cheat3()
{
	for (int i = 1; i <= n; i++)
		col[i] = bVal[i] - penalty[i] > wVal[i];
	adjust();
	return eval();
}
inline int cheat4()
{
	bit_init();
	for (int i = 1; i <= n; i++)
	{
		int tb = bVal[i], tw = wVal[i];
		if (qL[i] <= qR[i])
		{
			int cnt = bit_query(qR[i]) - bit_query(qL[i] - 1);
			if (cnt > 0)
				tb = INT_MIN;
		}
		
		if (tb > tw)
			col[i] = true;
		else
			col[i] = false, bit_add(a[i]);
	}
	adjust();
	return eval();
}
inline int cheat5()
{
	static int f[MaxN + 1];
	static int g[MaxN + 1];

	int sumW;
	for (int i = 1; i <= n; i++)
	{
		f[i] = INT_MIN;

		bool ok = true;
		sumW = 0;
		int cur;
		for (int j = i - 1; j >= 1; j--)
		{
			cur = f[j] + sumW;
			if (!ok)
				cur -= penalty[i];
			if (cur > f[i])
				f[i] = cur, g[i] = j;

			sumW += wVal[j];
			if (qL[i] <= a[j] && a[j] <= qR[i])
				ok = false;
		}

		cur = sumW;
		if (!ok)
			cur -= penalty[i];
		if (cur > f[i])
			f[i] = cur, g[i] = 0;

		f[i] += bVal[i];
	}

	fill(col + 1, col + n + 1, false);

	sumW = 0;
	for (int i = n; i >= 1; i--)
	{
		f[i] += sumW;
		sumW += wVal[i];
	}
	f[0] += sumW;

	for (int i = max_element(f + 1, f + n + 1) - f; i; i = g[i])
		col[i] = true;
	adjust();
	return eval();
}

inline int cheat6()
{
	fill(col + 1, col + n + 1, true);
	adjust();
	return eval();
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		a[i] = getint(), bVal[i] = getint(), wVal[i] = getint(), qL[i] = getint(), qR[i] = getint(), penalty[i] = getint();

	seqA_n = 0;
	for (int i = 1; i <= n; i++)
		seqA[seqA_n++] = a[i];
	sort(seqA, seqA + seqA_n);
	seqA_n = unique(seqA, seqA + seqA_n) - seqA;

	for (int i = 1; i <= n; i++)
	{
		a[i] = lower_bound(seqA, seqA + seqA_n, a[i]) - seqA + 1;
		qL[i] = lower_bound(seqA, seqA + seqA_n, qL[i]) - seqA + 1;
		qR[i] = upper_bound(seqA, seqA + seqA_n, qR[i]) - seqA;
	}

	int res = 0;
	relax(res, cheat1());
	relax(res, cheat2());
	relax(res, cheat3());
	relax(res, cheat4());
	relax(res, cheat5());
	relax(res, cheat6());

	cout << res << endl;

	return 0;
}
