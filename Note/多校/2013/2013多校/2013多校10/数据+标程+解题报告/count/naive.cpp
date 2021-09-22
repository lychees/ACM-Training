#include <cstdio>
#include <cstring>

const int N = 1000;

int n, m, k, sum[N + 1][N + 1];

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < k; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            sum[-- x][-- y] = 1;
        }
        for (int i = n - 1; i >= 0; -- i) {
            for (int j = m - 1; j >= 0; -- j) {
                sum[i][j] += sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1];
            }
        }
        int answer = 0;
        for (int i = 0; i < n; ++ i) {
            for (int ii = i; ii < n; ++ ii) {
                for (int j = 0; j < m; ++ j) {
                    for (int jj = j; jj < m; ++ jj) {
                        answer += sum[i][j] - sum[ii + 1][j] - sum[i][jj + 1] + sum[ii + 1][jj + 1] > 0;
                    }
                }
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
