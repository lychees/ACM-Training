线性素筛。。

const int PMAX = 1;
VI P; bitset<PMAX> isP;
void sieve(){
    FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i);
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isP[i*P[j]]=1; if (!(i%P[j])) break;
        }
    }
}


最小素因子。。

const int PMAX = int(1e5) + 9;
VI P; bitset<PMAX> isP; int p[PMAX];
void sieve(){
    p[1]=1;FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i),p[i]=i;
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isP[i*P[j]]=1,p[i*P[j]]=P[j]; if (!(i%P[j])) break;
        }
    }
}

欧拉 phi 函数

const int PMAX = 1000;
VI P; bitset<PMAX> isP; int phi[PMAX];
void sieve(){
    phi[1] = 1; FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i), phi[i] = i-1;
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isP[i*P[j]]=1; if (!(i%P[j])){
                phi[i*P[j]] = phi[i] * P[j];
                break;
            } else{
                phi[i*P[j]] = phi[i] * (P[j] - 1);
            }
        }
    }
}

莫比乌斯 mu 函数  。。。

const int PMAX = int(1e5) + 9;
VI P; bitset<PMAX> isP; int mu[PMAX];
void sieve(){
    mu[1] = 1; FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i), mu[i] = -1;
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isP[i*P[j]]=1; if (!(i%P[j])){
                mu[i*P[j]] = 0;
                break;
            } else{
                mu[i*P[j]] = -mu[i];
            }
        }
    }
}

---------






const int PMAX = int(1e5) + 9;
VI P; bitset<PMAX> isP; int mu[PMAX];
void sieve(){
    mu[1] = 1; FOR(i, 2, PMAX){
        if (!isP[i]) P.PB(i), mu[i] = -1;
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isP[i*P[j]]=1; if (!(i%P[j])){
                mu[i*P[j]] = 0;
                break;
            } else{
                mu[i*P[j]] = -mu[i];
            }
        }
    }
}

const int N = 109;
int A[N], B[N];
int n;

void r(){
    
    REP_1(i, n){
        B[i] = 0;
        REP_1(d, i) if (i%d == 0) B[i] += A[d];
    }
    
    REP(i, n) A[i] = B[i];
}

void l(){
    
    REP_1(i, n){
        B[i] = 0;
        REP_1(d, i) if (i%d == 0) B[i] += mu[d]*A[i/d];
    }
    
    REP(i, n) A[i] = B[i];
}


int main(){
    
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    
    sieve();
    
    n = 10; REP_1(i, n) A[i] = i*i;
    
    r(); r(); r();
    
    
    REP(i, n) printf("%d ", A[i]); puts("");
}


https://en.wikipedia.org/wiki/M%C3%B6bius_inversion_formula#Repeated_transformations

莫比乌斯变换 ↑
莫比乌斯逆变换 ↓




Sigma_0
-2：
Mobius Function：
http://oeis.org/A008683
-1：
单位函数
1,0,0,0,0,0,0...
0：
常函数
1,1,1,1,1,1,1
1：
http://oeis.org/A000005
d0：0阶约数函数。。。约数的个数。。
tau2：拆成两个因子的顺序方案数。（顺序相关）。。。（不涉及相关其他数列的时候不强调下标.。。）
2:
???
http://oeis.org/A007425
tau3：拆成三个因子的方案。（顺序相关）。以下为 tau 4 tau 5.。。
3:
http://oeis.org/A007426 ;
4:
http://oeis.org/A061200



Sigma_1
-2：
http://oeis.org/A007431
-1：
http://oeis.org/A000010 ;
Euler totient function phi(n)
0：
1,2,3,4,5,6。。。
算数序列
1：
sigma_1
http://oeis.org/A000203
2：
http://oeis.org/A007429




Sigma_2:
查不到。1,2,7,9,23,14,47,36,64
Jordan_totient_Function .... // https://en.wikipedia.org/wiki/Jordan's_totient_function
平方序列
sigma_2
http://oeis.org/A007433





(前 n 项 phi 的和。。。
 http://oeis.org/A002088  ??)
 http://acm.hdu.edu.cn/showproblem.php?pid=1695
 
 
 暴力容斥原理 （2000ms）
 
 const int PMAX = int(1e5) + 9;
 VI P; bitset<PMAX> isP; int p[PMAX];
 void sieve(){
     p[1]=1;FOR(i, 2, PMAX){
         if (!isP[i]) P.PB(i),p[i]=i;
         for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
             isP[i*P[j]]=1,p[i*P[j]]=P[j]; if (!(i%P[j])) break;
         }
     }
 }
 
 int a, b, k;
 
 int main(){
     
#ifndef ONLINE_JUDGE
     freopen("in.txt", "r", stdin);
     //freopen("out.txt", "w", stdout);
#endif
     
     sieve(); Rush{
         int _; RD(_, a, _, b, k); if (!k) {OT(0); continue;}; a /= k, b /= k;
         LL z = 0; if (a > b) swap(a, b); REP_1(bb, b){
             int aa = min(bb, a); VI D; int x = bb; while (x != 1) D.PB(p[x]), x /= p[x]; UNQQ(D);
             REP(s, _1(SZ(D))){
                 int c = 0, d = 1; REP(i, SZ(D)) if (_1(s, i)) ++c, d*=D[i];
                 if (c&1) z -= aa/d; else z += aa/d;
             }
         }
         OT(z);
     }
 }
 
 
 莫比乌斯反演
 
 const int PMAX = int(1e5) + 9;
 VI P; bitset<PMAX> isP; int mu[PMAX];
 void sieve(){
     mu[1] = 1; FOR(i, 2, PMAX){
         if (!isP[i]) P.PB(i), mu[i] = -1;
         for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
             isP[i*P[j]]=1; if (!(i%P[j])){
                 mu[i*P[j]] = 0;
                 break;
             } else{
                 mu[i*P[j]] = -mu[i];
             }
         }
     }
 }
 
 int a, b, k;
 
 int main(){
     
#ifndef ONLINE_JUDGE
     freopen("in.txt", "r", stdin);
     //freopen("out.txt", "w", stdout);
#endif
     
     sieve(); Rush{
         int _; RD(_, a, _, b, k); if (!k) {OT(0); continue;}; a /= k, b /= k;
         LL z = 0; if (a > b) swap(a, b);
         REP_1(i, a) z -= (LL)mu[i]*(a/i)*(a/i); z /= 2;
         REP_1(i, a) z += (LL)mu[i]*(a/i)*(b/i); OT(z);
     }
 }
 
 
 
 
 
 
 分拆
 https://oeis.org/A000041
 
 k部-分拆
 https://oeis.org/A026820
 
 
 
 A[i][j] 表示：
 i 分拆成最大数不超过 j 的方案数。。）
 A[0][0] = 1
 A[i][j] = A[i][j-1] + A[i-j][min(i-j, j)];
 不拆出 j 的方案书 + 至少拆除一个 j 的方案数。。
 
 根据共轭性也可以将 A[i][j] 理解成。。
 。。。 i 分拆成不多于 j 项的方案数。
 那么此时转移可以理解成。。小于 j 项的方案数 + 恰好含有 j 项的方案数。。。
 
 const int N = 109;
 int A[N][N], n;
 
 int main(){
     n = 5; A[0][0] = 1; REP_1(i, n) REP_1(j, i)
     A[i][j] = A[i][j-1] + A[i-j][min(i-j, j)];
     
     REP_1(i, n){
         REP_1(j, i) printf("%d ", A[i][j]);
         puts("");
     }
 }
 
/*
 1
 1 2
 1 2 3
 1 3 4 5
 1 3 5 6 7
 */
 
 
 不相同 k-部分拆
 https://oeis.org/A000009
 
 
 
 。。。显然不相同 k 部分拆不满足共轭性质。。。。
 也就是
 
 
 最大项为 k  != 项数为 k
 
 1.
 设 A[i][j]：i 的最大项不大于 j 的不重复 k-部分拆。。。
/*。。
 至多含有一个 j 的 = 至多含有 j-1 的 + 恰好含有一个 j 的。
 */
 
 const int N = 109;
 int A[N][N], n;
 
 int main(){
     
#ifndef ONLINE_JUDGE
     freopen("in.txt", "r", stdin);
     //freopen("out.txt", "w", stdout);
#endif
     
     n = 8; A[0][0] = 1; REP_1(i, n) REP_1(j, i)
     A[i][j] = A[i][j-1] + A[i-j][min(i-j, j-1)];
     REP_1(i, n){
         REP_1(j, i) printf("%d ", A[i][j]);
         puts("");
     }
 }
 
 
 2.
 设 A[i][j]: 项数恰好为 j 项的不重复 k 部分拆数。 
 
 最小数 >1： A[i-j][j] （相当于每个数+1、
 最小数 =1：A[i-j][[j-1]（新增加一个 1，原先的 j-1 项再每个数+1，
               
               n = 10; A[0][0] = 1; REP_1(i, n) REP_1(j, i)
               A[i][j] = A[i-j][j-1] + A[i-j][j]; 
               
               


#define m MOD
inline void INCll(LL&x,LL y){x += y; if (x >= m) x -= m;}
inline LL sumll(LL a, LL b){a += b; if (a >= m) a -= m; return a;}
inline void DECll(LL &a, LL b){a -= b; if (a < 0) a += m;}
inline LL dffll(LL a, LL b){a -= b; if (a < 0) a += m; return a;}
inline int pdtll(LL a, LL b){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    x =(x*y-(LL)(((long double)x*y+0.5)/(long double)m)*m)%m; if (x<0) x += m;
    return x;
}
inline void MULll(LL &a, LL b){a = pdtll(a, b);}
#undef m

/*
inline LL pdt64(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    x =(x*y-(LL)(((long double)x*y+0.5)/(long double)m)*m)%m; if (x<0) x += m;
    return x;
}

inline LL pdt64(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    LL p=sqrt(m)+0.5,q=p*p-m,a=x/p,b=x%p,c=y/p,d=y%p,e=a*c/p*q,f=a*c%p*q;
    LL t=((a*d+b*c)%m+e)%m;x=t/p*q,y=t%p*p;
    x = (((b*d+f)%m+x)%m+y)%m; if (x<0) x += m;
    return x;
}

inline LL pdt64(LL a,LL b){
    a%=m,b%=m; if (a<0) a+=m; if (b<0) b += m;
    LL c=0; for (;b;b>>=1,Incc(a,a))
        if (b&1) Incc(c,a);
    return c;
}*/

