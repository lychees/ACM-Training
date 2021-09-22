#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
#include <utility>
using namespace std;

const int maxn = 300 + 10;
int mat[maxn][maxn];
int n,m;
int seq[maxn];
int row[maxn][maxn],col[maxn][maxn];
void getPalEven(const int* P,int pal[]) {
    int L,R,PR,i;
    pal[0] = 0;
    R = 0,PR = 0;
    for(i = 1;P[i];i++) {
        L = (PR << 1) - i;
        if(L<0)L = 0;
        else L = pal[L];
        if(PR + R <= i + L) {
            for(L = max(PR + R - i,0);i > L;L++)
                 if(P[i + L]!=P[i - L - 1])break;
            PR = i;
            R = L;
        }
        pal[i] = L;
    }
    pal[i] =0;
}

void getPalOdd(const int* P,int pal[]) {
    int L,R,PR,i;
    pal[0] = 0;
    R =0,PR = 0;
    for(int i = 1;P[i];i++) {
        L = (PR<<1) - i;
        if(L < 0)L = 0;
        else L = pal[L];
        if(PR + R <= i + L) {
            for(L = max(PR + R - i,0);i > L;L++)
                    if(P[i - L - 1]!=P[i + L + 1])break;
            PR = i;
            R = L;
        }
        pal[i] = L;
    }
}


void work() {
    int best = 1;

    //calc Even
    for(int i = 0;i<n;i++) {
        for(int j =0 ;j <m;j++)seq[j] = mat[i][j];
        seq[m] = 0;
        getPalEven(seq,row[i]);
        /*for(int j = 0;j<=m;j++)
            printf("%d ",seq[j]);
        puts("");*/
        /*for(int j = 0;j<m;j++)
            printf("%d ",row[i][j]);
        puts("");*/
    }
    for(int i = 0;i<m;i++) {
        for(int j = 0;j < n;j++)seq[j] = mat[j][i];
        seq[n] = 0;
        getPalEven(seq,col[i]);
        /*for(int j = 0;j<n;j++)
            printf("%d ",col[i][j]);
        puts("");*/
    }
    int tlen;

    for(int r = 1;r<n;r++) {
        for(int c = 1;c<m;c++) {
            int up,down,lt,rt,minlen = 10000;
            for(up = r - 1;up>=0;up--) {
                tlen = min(minlen,row[up][c]);
                if(r - up > minlen)break;
                minlen = tlen;
            }
            up++;

            for(down = r;down<n;down++) {
                tlen = min(minlen,row[down][c]);
                if(down - r + 1 > minlen)break;
                minlen = tlen;
            }
            down--;

            for(lt = c - 1;lt>=0;lt--) {
                tlen = min(minlen,col[lt][r]);
                if(c - lt > minlen)break;
                minlen = tlen;
            }
            lt++;

            for(rt = c;rt < m;rt++) {
                tlen = min(minlen,col[rt][r]);
                if(rt - c + 1 > minlen)break;
                minlen = tlen;
            }
            rt--;
        
            if(minlen * 2 > best)
                best = minlen * 2;
        }
    }

    //calc Odd;
    for(int i = 0;i<n;i++) {
        for(int j =0 ;j <m;j++)seq[j] = mat[i][j];
        seq[m] = 0;
        getPalOdd(seq,row[i]);
    }
    for(int i = 0;i<m;i++) {
        for(int j = 0;j < n;j++)seq[j] = mat[j][i];
        seq[n] = 0;
        getPalOdd(seq,col[i]);
    }
    for(int r = 0;r<n;r++) {
        for(int c = 0;c<m;c++) {
            int up,down,lt,rt,minlen = 10000;
            for(up = r;up>=0;up--) {
                tlen = min(minlen,row[up][c]);
                if(r - up > minlen)break;
                minlen = tlen;
            }
            up++;

            for(down = r;down < n;down++) {
                tlen = min(minlen,row[down][c]);
                if(down - r > minlen)break;
                minlen = tlen;
            }
            down--;

            for(lt = c;c>=0;lt--) {
                tlen = min(minlen,col[lt][r]);
                if(c - lt > minlen)break;
                minlen = tlen;
            }
            lt++;

            for(rt = c;rt < m;rt++) {
                tlen = min(minlen,col[rt][r]);
                if(rt - c > minlen)break;
                minlen = tlen;
            }
            rt--;
            if(minlen * 2 + 1 > best)
                best = minlen * 2 + 1;
        }
    }
    printf("%d\n",best);
}


int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--) {
        scanf("%d%d",&n,&m);
        for(int i = 0;i<n;i++) {
            for(int j =0 ;j<m;j++)
                scanf("%d",&mat[i][j]);
        }
        work();
    }
    return 0;
}
