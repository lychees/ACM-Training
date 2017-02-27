#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 105;

int n, ca;
double a[N];

void work() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        scanf("%lf:%lf", &x, &y);
        a[i] = x / (x + y);
    }
    sort(a, a + n);
    double res = 0;
    for (int i = 0; i < n; ++i) {
        res += a[i];
        if (res >= 1) {
            printf("Case #%d: %d\n", ++ca, i);
            return;
        }
    }
    printf("Case #%d: %d\n", ++ca, n);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
    return 0;
}