#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long LL;
const int N = 505;
const int Q = 1e9 + 7;

int f[2][N] , p[N] , C[N][N] , res[N];
int power(int A , int B) {
    int res = 1;
    while (B) {
        if (B & 1) {
            res = (LL)res * A % Q;
        }
        A = (LL)A * A % Q;
        B >>= 1;
    }
    return res;
}
int TestCount;
void work(int n , int m , int K) {
    ++ TestCount;
    printf("%d %d %d\n" , n , m , K);
    if (n < m) swap(n , m);
    int cur = 0 , nxt = 1;
    memset(f[cur] , 0 , sizeof(f[cur]));
    f[cur][0] = 1;
    for (int i = 0 ; i < K ; ++ i) {
        memset(f[nxt] , 0 , sizeof(f[nxt]));
        for (int j = 0 ; j <= m ; ++ j) {
            if (!f[cur][j]) continue;
            for (int k = 0 ; j + k <= m ; ++ k) {
                int x = (LL)power(i , k * (n + m - k - j - j - 1)) * f[cur][j] % Q;
                x = (LL)x * C[m - j][k] % Q * C[n - j][k] % Q * p[k] % Q;
                f[nxt][j + k] += x;
                f[nxt][j + k] %= Q;
            }
        }
        swap(cur , nxt);
    }
    for (int i = 0 ; i <= m ; ++ i) {
        res[i] = (LL)power(K , (n - i) * (m - i)) * f[cur][i] % Q;
    }
    for (int i = m ; i >= 0 ; -- i) {
        for (int j = i - 1 ; j >= 0 ; -- j) {
            res[j] += Q -(LL)C[i][j] * res[i] % Q;
            res[j] %= Q;
        }
    }
    int ans = 0;
    for (int i = 0 ; i <= m ; ++ i) {
        ans = (ans + (LL)(i + 1) * res[i] % Q) % Q;
    }
    static int ca = 0;
    fprintf(stderr , "Case #%d: %d\n" , ++ ca , ans);
}
int main(int argc, char **argv) {
    assert(argc == 3);
    int diff = atoi(argv[1]);
    srand(atoi(argv[2]));
    assert(RAND_MAX == 2147483647);
    
    for (int i = 0 ; i < N ; ++ i) {
        C[i][0] = 1;
        p[i] = i ? (LL)p[i - 1] * i % Q : 1;
        for (int j = 1 ; j <= i ; ++ j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Q;
        }
    }
    int T = 20;
    printf("%d\n" , T);
    for (int i = 0 ; i < 10 ; ++ i) {
        work(rand() % 100 + 1 , rand() % 100 + 1 , rand() % 100 + 1);
    }
    work(1 , 200 , 100);
    work(200 , 2 , 3);
    work(100 , 100 , 1);
    for (int i = 0 ; i < 6 ; ++ i) {
        work(rand() % 20 + 181 , rand() % 20 + 181 , rand() % 20 + 181);
    }
    work(200 , 200 , 200);
    return 0;
}