#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MaxS = 2000010, Log = 20, MaxN = 100010;
int Fail[MaxS], N, Q, CTotal, Pos[MaxN], Ch[MaxS][26], F[MaxS], Time[MaxN], SumTime, Total;
struct Node {
    int Son[2], F, Sum, Lazy;
}   T[MaxN];
bool Use[MaxS];
 
void MakeTrie(char S[], int Ind) {
    int Now = 0;
    for (int i = 1; S[i]; i++) {
        if (Ch[Now][S[i] - 'a']) Now = Ch[Now][S[i] - 'a'];
        else {
            Ch[Now][S[i] - 'a'] = ++CTotal;
            Now = CTotal;
        }
    }
    Pos[Ind] = Now;
    Use[Now] = 1;
}
 
void Build_AC() {
    int* Que = new int[MaxS];
    Que[1] = 0;
    int L = 0, R = 1;
    while (L++ != R) {
        int U = Que[L];
        for (int i = 0; i < 26; i++)
            if (Ch[U][i]) {
                if (U) Fail[Ch[U][i]] = Ch[Fail[U]][i];
                Que[++R] = Ch[U][i];
            } else
                if (U) Ch[U][i] = Ch[Fail[U]][i];
    }
    int Ind = 0;
    for (int i = 1; i <= R; i++)
        if (Use[Que[i]]) {
            F[Que[i]] = ++Ind;
            T[Ind].F = F[Fail[Que[i]]];
        }   else F[Que[i]] = F[Fail[Que[i]]];
    Total = Ind;
    delete(Que);
}
 
void MakeLazy(int U) {
    if (T[U].Son[0]) T[T[U].Son[0]].Lazy += T[U].Lazy;
    if (T[U].Son[1]) T[T[U].Son[1]].Lazy += T[U].Lazy;
    T[U].Sum += T[U].Lazy;
    T[U].Lazy = 0;
}
inline bool NotRoot(int U) {
    return (T[T[U].F].Son[0] == U) || (T[T[U].F].Son[1] == U);
}
void Clear(int U) {
    if (NotRoot(U)) Clear(T[U].F);
    MakeLazy(U);
}
int FindRoot(int U) {
    while (NotRoot(U)) U = T[U].F;
    return U;
}
 
void Rotate(int U, int P) {
    int F = T[U].F, Q = (T[T[F].F].Son[1] == F);
    T[F].Son[P] = T[U].Son[!P]; if (T[U].Son[!P]) T[T[U].Son[!P]].F = F;
    if (NotRoot(F)) T[T[F].F].Son[Q] = U;   T[U].F = T[F].F;
    T[U].Son[!P] = F;   T[F].F = U;
}
 
void Splay(int U) {
    Clear(U);
    int F, Gf, P, Q;
    while (NotRoot(U)) {
        F = T[U].F; Gf = T[F].F;
        P = (T[F].Son[1] == U); Q = (T[Gf].Son[1] == F);
        if (!NotRoot(F)) {
            Rotate(U, P);
            return;
        }
        Rotate(P == Q ? F : U, P);
        Rotate(U, Q);
    }
}
 
void Access(int U) {
    if (Time[FindRoot(U)] == SumTime) return;
    int V = 0, Ind = U;
    while (U && (Time[FindRoot(U)] != SumTime)) {
        Splay(U);
        T[U].Son[1] = V;
        if (V) T[V].F = U;
        V = U;
        U = T[U].F;
    }
    Splay(Ind);
    Time[Ind] = SumTime;
    T[Ind].Lazy++;
}
 
void Modify(char S[]) {
    static int NTime[MaxN] = {}, SumTime = 0;
    int Now = 0;
    SumTime++;
    NTime[0] = SumTime;
    for (int i = 0; S[i]; i++) {
        Now = Ch[Now][S[i] - 'a'];
        if (NTime[F[Now]] != SumTime) {
            NTime[F[Now]] = SumTime;
            Access(F[Now]);
        }
    }
}
 
void FastIn(char S[]) {
    char C = getchar();
    while ((C < 'a') || (C > 'z')) C = getchar();
    int Len = 0;
    S[0] = C;   C = getchar();
    while ((C >= 'a') && (C <= 'z')) {
        S[++Len] = C;
        C = getchar();
    }
    S[++Len] = 0;
}
 
void Query(int X) {
    Splay(X);
    printf("%d\n", T[X].Sum + T[X].Lazy);
}
 
int main()
{
    char *S = new char[MaxS];
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        FastIn(S + 1);
        MakeTrie(S, i);
    }
    Build_AC();
     
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int Type;
        scanf("%d", &Type);
        if (Type == 1) {
            FastIn(S + 1);
            SumTime++;
            Modify(S + 1);
        } else {
            int X;
            scanf("%d", &X);
            Query(F[Pos[X]]);
        }
    }
    delete(S);
    return 0;
}
