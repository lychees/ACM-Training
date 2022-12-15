#include <lastweapon/number>
using namespace lastweapon;

const int N = int(1e5) + 9;
bool isSquare[N];

int main() {

#ifndef ONLINE_JUDGE
     //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

    int m = 100, z = 0;

    FOR_1(i, 1, 100*2) isSquare[i*i] = 1;

    REP_1(a, m) REP_1(b, m) REP_1(c, m) REP_1(d, m) {
        int A = (a+c) * (b+d);
        int B = gcd(a, b) + gcd(b, c) + gcd(c, d) + gcd(d, a);
        int i = (A-B)/2 + 1;
        if (isSquare[i]) {
            ++z;
        }
    }

    cout << z << endl;
}
