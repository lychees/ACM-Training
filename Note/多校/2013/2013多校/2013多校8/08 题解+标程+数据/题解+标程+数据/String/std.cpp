#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXLEN = 1000;

char a[MAXLEN + 1], b[MAXLEN + 1], c[MAXLEN + 1];;
int lcs[MAXLEN + 1][MAXLEN + 1], rlcs[MAXLEN + 1][MAXLEN + 1];
int nxta[MAXLEN][26], nxtb[MAXLEN][26];
int mina[MAXLEN], minb[MAXLEN];

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas)
    {
        scanf("%s%s%s", a, b, c);
        int n = strlen(a), m = strlen(b), w = strlen(c);
        for (int i = 0; i < n; ++ i)
            rlcs[i][m] = 0;
        for (int j = 0; j <= m; ++ j)
            rlcs[n][j] = 0;
        for (int i = n - 1; i >= 0; -- i)
            for (int j = m - 1; j >= 0; -- j)
            {
                if (a[i] == b[j])
                    rlcs[i][j] = rlcs[i + 1][j + 1] + 1;
                else
                    rlcs[i][j] = max(rlcs[i + 1][j], rlcs[i][j + 1]);
            }
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
            {
                lcs[i][j] = (a[i] == b[j]);
                if (i && j && a[i] == b[j])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                if (i)
                    lcs[i][j] = max(lcs[i][j], lcs[i - 1][j]);
                if (j)
                    lcs[i][j] = max(lcs[i][j], lcs[i][j - 1]);
            }
        for (int i = 0; i < n; ++ i)
        {
            memset(nxta[i], -1, 4 * 26);
            for (int j = i; j < n; ++ j)
                if (nxta[i][a[j] - 'a'] == -1)
                    nxta[i][a[j] - 'a'] = j;
        }
        for (int i = 0; i < m; ++ i)
        {
            memset(nxtb[i], -1, 4 * 26);
            for (int j = i; j < m; ++ j)
                if (nxtb[i][b[j] - 'a'] == -1)
                    nxtb[i][b[j] - 'a'] = j;
        }
        for (int i = 0; i < n; ++ i)
        {
            int now = i;
            for (int j = 0; j < w && now != -1; ++ j)
            {
                if (now >= n)
                {
                    now = -1;
                    break;
                }
                if (nxta[now][c[j] - 'a'] != -1)
                    now = nxta[now][c[j] - 'a'] + 1;
                else
                    now = -1;
            }
            mina[i] = now;
        }
        for (int i = 0; i < m; ++ i)
        {
            int now = i;
            for (int j = 0; j < w && now != -1; ++ j)
            {
                if (now >= m)
                {
                    now = -1;
                    break;
                }
                if (nxtb[now][c[j] - 'a'] != -1)
                    now = nxtb[now][c[j] - 'a'] + 1;
                else
                    now = -1;
            }
            minb[i] = now;
        }
        //printf("%d %d\n", lcs[n - 1][m - 1], w);
        int ans = -1;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
                if (mina[i] != -1 && minb[j] != -1)
                {
                    int tot = w + rlcs[mina[i]][minb[j]];
                    if (i && j)
                        tot += lcs[i - 1][j - 1];
                    ans = max(ans, tot);
                }
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}
