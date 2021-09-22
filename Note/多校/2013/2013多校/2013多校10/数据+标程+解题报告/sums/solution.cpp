#include <cctype>
#include <cstdio>
#include <cstring>
#include <cassert>

const int N = 100000;
const int MOD = (int)1e9 + 7;

int pow(int a, int n) {
    int ret = 1;
    while (n) {
        if (n & 1) {
            ret = (long long)ret * a % MOD;
        }
        a = (long long)a * a % MOD;
        n >>= 1;
    }
    return ret;
}

int main() {
    while (true) {
        int n = 0;
        int p = 0;
        while (true) {
            char token = getchar();
            if (!isdigit(token)) {
                break;
            }
            n ++;
            p = ((long long)p * 10 + token - '0') % (MOD - 1);
        }
        if (n == 0) {
            break;
        }
        assert(1 <= n && n <= N);
        (p += MOD - 2) %= (MOD - 1);
        printf("%d\n", pow(2, p));
    }
    return 0;     
}
