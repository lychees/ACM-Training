#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define uns short
#define R(x, L) (x >= L ? (x) - L : x)
const int msc = 40;
using namespace std;

string s;
char q[110], S[110];
int E[50][50][50], d[50], t[50];
int main()
{
  freopen("inse.in", "r", stdin);
	freopen("inse.out", "w", stdout);

	for (int i = 1; i <= msc; ++i)
		for (int j = 0; j < msc; ++j)  {
			memset(t, 0, sizeof(t));

			int N = 0, L = i;  E[i][j][1] = 0;  t[0] = 1;
			for (int k = 2; k <= i; ++k)  {
				int remain = j + 1;
				while (remain)  {
					while (t[N = R(N + 1, L)]);
					remain--;
				}

				E[i][j][k] = N;  t[N] = 1;
			}
		}
	
	int test = 0;
	while (cin >> s)  {
		if (!s.compare("X"))  break;
		++ test;
    printf("Code %d: ", test);

		memset(S, 0, sizeof(S));
		int L = s.length(), i, w = 0;

		for (i = L >> 1; i  &&  !w; --i)  
			for (uns j = 0; j < L; ++j)
				for (uns k = 0; k < L; ++k)  {
					memset(t, 0, sizeof(t));
					int *G = E[L][k];

					for (uns p = 1; p <= i; ++p)
						q[p] = s[R(G[p] + j, L)], t[R(G[p] + j, L)] = 1;

					bool v = 0;
					for (uns p = 1; p <= i; ++p)
						if (q[p] != S[p])  {  v = 1;  break;  }

					if (!v)  continue;

					int m = 0, res = 0;
					for (uns p = 0; p < L; ++p)
						if (!t[p])  d[m++] = p;
          
					for (uns p = 0; p < m  &&  !res; ++p)
						if (s[d[p]] == q[1])
							for (uns h = k + 1; h < L  &&  !res; ++h)  {
								int *Q = E[m][h];  bool u = 1;
								for (uns r = 1; r <= i; ++r)
									if (s[d[R(Q[r] + p, m)]] != q[r])  {  u = false;  break;  }
								
								if (u)  res = 1;
							}
					
					if (res)  {
						for (int p = 1; p <= i; ++p)  S[p] = q[p];
						++ w;
					}

					if (w > 1)  goto fail;
				}
		
    for (int j = 0; j++ <= i; )  
      printf("%c", S[j]);
    printf("\n");
		continue;
		
	fail:
		printf("Codeword not unique\n");
	}
}
