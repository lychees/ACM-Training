#include "kth.h"
#include <algorithm>

int query_kth(int n_a, int n_b, int n_c, int k)
{
	int vl = 1, vr = 1000000000;
	while (vl != vr)
	{
		int vm = (vl + vr) >> 1;
		
		int c = 0;
		int l, r;
		l = 0, r = n_a;
		while (l != r)
		{
			int m = (l + r) >> 1;
			if (get_a(m) <= vm)
				l = m + 1;
			else
				r = m;
		}
		c += l;

		l = 0, r = n_b;
		while (l != r)
		{
			int m = (l + r) >> 1;
			if (get_b(m) <= vm)
				l = m + 1;
			else
				r = m;
		}
		c += l;

		l = 0, r = n_c;
		while (l != r)
		{
			int m = (l + r) >> 1;
			if (get_c(m) <= vm)
				l = m + 1;
			else
				r = m;
		}
		c += l;

		if (c < k)
			vl = vm + 1;
		else
			vr = vm;
	}
	return vl;
}
