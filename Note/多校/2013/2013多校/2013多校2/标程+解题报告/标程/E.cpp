#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

typedef __int64 LL;

const int N = 1100;

int n;
int mtx[2][N][N];
int d[N];

int ans[N * N][4], an;

void work()
{
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (mtx[0][i][j]) d[i]++, d[j]++;
            if (mtx[1][i][j]) d[i]--, d[j]--;
        }
        for (int i = 0; i < n; i++) if (d[i]) {
            puts("-1");
            return ;
        }

        an = 0;
//      int stk[N], stn;
        int C = 2;
        for (int cc = 0; cc < C; cc++) {
            for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!mtx[0][i][j] && mtx[1][i][j]) {
                    int x = i;
                    int w = j;
                    int ok = 0;
                    for (int y = i + 1; y < n; y++) {
                        if (mtx[0][i][y] && !mtx[1][i][y]) {
                            int z = -1;
                            for (int k = i + 1; k < n; k++) {
                                if (mtx[0][j][k] && !mtx[0][k][y] && k != y) {
                                    z = k;
                                    break;
                                }
                            }
                            if (z != -1) {
                                ans[an][0] = x;
                                ans[an][1] = y;
                                ans[an][2] = z;
                                ans[an][3] = w;
                                an++;
                                mtx[0][x][y] = mtx[0][y][x] = 0;
                                mtx[0][z][w] = mtx[0][w][z] = 0;
                                mtx[0][x][w] = mtx[0][w][x] = 1;
                                mtx[0][y][z] = mtx[0][z][y] = 1;
                                ok = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (!mtx[0][i][j] && mtx[1][i][j]) {
                    int x = i;
                    int w = j;
                    int ok = 0;
                    for (int y = n - 1; y >= 0; y--) {
                        if (mtx[0][i][y] && !mtx[1][i][y]) {
                            int z = -1;
                            for (int k = n - 1; k >= 0; k--) {
                                if (mtx[0][j][k] && !mtx[0][k][y] && k != y) {
                                    z = k;
                                    break;
                                }
                            }
                            if (z != -1) {
                                ans[an][0] = x;
                                ans[an][1] = y;
                                ans[an][2] = z;
                                ans[an][3] = w;
                                an++;
                                mtx[0][x][y] = mtx[0][y][x] = 0;
                                mtx[0][z][w] = mtx[0][w][z] = 0;
                                mtx[0][x][w] = mtx[0][w][x] = 1;
                                mtx[0][y][z] = mtx[0][z][y] = 1;
                                ok = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
	}
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (mtx[0][i][j] != mtx[1][i][j]) {
                printf("-1\n");
                return ;
            }
    printf("%d\n", an);
    for (int i = 0; i < an; i++) {
        for (int j = 0; j < 4; j++) {
            if (j) printf(" ");
            printf("%d", ans[i][j]);
        }
       	printf("\n");
    }
}

bool myin()
{
    if (scanf("%d", &n) == EOF) 
	return false;
    for (int tp = 0; tp < 2; tp++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &mtx[tp][i][j]);
    }
    return true;
}

int main()
{
    while (myin()) {
        work();
    }
    return 0;
}
