#include <lastweapon/io>

int main() {
    VI A, B;
    REP_1(i, 20) A.PB(i),A.PB(i+i),A.PB(i+i+i),B.PB(i+i);
    A.PB(0); A.PB(25); A.PB(50); B.PB(50);

    int z = 0; REP(i, SZ(A)) REP(j, i+1) for (auto b: B) {
        if (A[i] + A[j] + b < 100) ++z;
    }
    cout << z << endl;
}


