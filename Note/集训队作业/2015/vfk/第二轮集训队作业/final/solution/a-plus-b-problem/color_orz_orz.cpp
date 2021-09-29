#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#include <climits>
using namespace std;

const int MaxN = 20;

int main()
{
	int n;
	static int a[MaxN],b[MaxN],w[MaxN],c[MaxN],l[MaxN],r[MaxN];
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i] >> b[i] >> w[i] >> l[i] >> r[i] >> c[i];
	int res = INT_MIN;
	int sol;
	for(int i = 0; i < (1 << n); i++)
	{
		int cur = 0;
		for(int j = 0; j < n; j++)
		{
			if((i>>j)&1)
			{
				cur += b[j];
				for(int k = 0; k < j; k++)
					if(l[j] <= a[k] && a[k] <= r[j] && (~(i >> k) & 1))
					{
						cur -= c[j];
						break;
					}
			}
			else
				cur += w[j];
		}
		if (cur > res)
			res = cur, sol = i;
	}

	bool ok = false;
	for (int i = 0; i < n; i++)
	{
		if ((sol >> i & 1) == 0)
			continue;
		int cnt = 0;
		for(int j = 0; j < i; j++)
			if (l[i] <= a[j] && a[j] <= r[i] && (~(sol >> j) & 1))
				cnt++;
		ok |= cnt >= 2;
	}
	if (ok)
		cerr << "Yes" << endl;
	else
		cerr << "No" << endl;
	for (int i = 0; i < n; i++)
		cerr << (sol >> i & 1) << " ";
	cerr << endl;

	cout << res << endl;
	return 0;
}
