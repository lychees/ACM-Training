//基础包。。
// <<= '2. Number Theory .,//{
namespace NT{
#define gcd __gcd
inline LL lcm(LL a, LL b){return a*b/gcd(a,b);}

inline void INC(int &a, int b){a += b; if (a >= MOD) a -= MOD;}
inline int sum(int a, int b){a += b; if (a >= MOD) a -= MOD; return a;}

/* 模数两倍刚好超 int 时。
inline int sum(uint a, int b){a += b; a %= MOD;if (a < 0) a += MOD; return a;}
inline void INC(int &a, int b){a = sum(a, b);}
*/

inline void DEC(int &a, int b){a -= b; if (a < 0) a += MOD;}
inline int dff(int a, int b){a -= b; if (a < 0) a  += MOD; return a;}
inline void MUL(int &a, int b){a = (LL)a * b % MOD;}
inline int pdt(int a, int b){return (LL)a * b % MOD;}

/*
inline int pdt(int x,int y) {
    int ret; __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
    return ret;
}*/

inline int gcd(int m, int n, int &x, int &y){

    x = 1, y = 0; int xx = 0, yy = 1, q;

    while (1){
        q = m / n, m %= n;
        if (!m){x = xx, y = yy; return n;}
        DEC(x, pdt(q, xx)), DEC(y, pdt(q, yy));
        q = n / m, n %= m;
        if (!n) return m;
        DEC(xx, pdt(q, x)), DEC(yy, pdt(q, y));
    }
}

inline int sum(int a, int b, int c){return sum(a, sum(b, c));}
inline int sum(int a, int b, int c, int d){return sum(sum(a, b), sum(c, d));}
inline int pdt(int a, int b, int c){return pdt(a, pdt(b, c));}
inline int pdt(int a, int b, int c, int d){return pdt(pdt(a, b), pdt(c, d));}

inline int pow(int a, LL b){
    int c(1); while (b){
        if (b&1) MUL(c, a);
        MUL(a, a), b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, LL b){
    T c(1); while (b){
        if (b&1) c *= a;
        a *= a, b >>= 1;
    }
    return c;
}

template<class T> inline T pow(T a, int b){
    return pow(a, (LL)b);
}

inline int _I(int b){
    int a = MOD, x1 = 0, x2 = 1, q; while (1){
        q = a / b, a %= b;
        if (!a) return x2;
        DEC(x1, pdt(q, x2));

        q = b / a, b %= a;
        if (!b) return x1;
        DEC(x2, pdt(q, x1));
    }
}

inline void DIV(int &a, int b){MUL(a, _I(b));}
inline int qtt(int a, int b){return pdt(a, _I(b));}

} using namespace NT;//}

//。。自带取模的环类。。
// by hirosegolf

struct Int{
    LL val;
    Int():val(0){}
    Int(LL _val){_val %= MOD; if (_val < 0) _val += MOD;val = _val;}
    Int&operator+=(LL r){*this=a.val+b.val;}
    //Int&operator-=
    //Int&operator*=
};



// by me
struct Int{
    int val;

    operator int() const{return val;}

    Int(int val = 0):val(val){
        val %= MOD; if (val < 0) val += MOD;
    }
    Int(LL _val){
        _val %= MOD; if (_val < 0) _val += MOD;
        val = _val;
    }
    Int& operator +=(const int& rhs){INC(val, rhs);rTs;}
    Int operator +(const int& rhs) const{return sum(val, rhs);}
    Int& operator -=(const int& rhs){DEC(val, rhs);rTs;}
    Int operator -(const int& rhs) const{return dff(val, rhs);}
    Int& operator *=(const int& rhs){MUL(val, rhs);rTs;}
    Int operator *(const int& rhs) const{return pdt(val, rhs);}
    Int& operator /=(const int& rhs){DIV(val, rhs);rTs;}
    Int operator /(const int& rhs) const{return qtt(val, rhs);}
    Int operator-()const{return MOD-*this;}
};


//线性素筛。。
const int PMAX = 46341;
VI P; bitset<PMAX> isC;
#define ii (i*P[j])
void sieve(){
    FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i);
        for (int j=0;j<SZ(P)&&ii<PMAX;++j){
            isC[ii]=1; if (!(i%P[j])) break;
        }
    }
}
#undef ii

//因数分解。。
VII fac; void fact(int x){
    int z = x; fac.clear(); ECH(it, P) if (!(x%*it)){
        int c=1; x/=*it; while (!(x%*it)) x/=*it, ++c;
        fac.PB(MP(*it, c));
    }
    if (x!=1) fac.PB(MP(x, 1));
}

//最小素因子。。
const int PMAX = 46341;
VI P; bitset<PMAX> isC; int p[PMAX];
#define ii (i*P[j])
void sieve(){
    FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i),p[i]=i;
        for (int j=0;j<SZ(P)&&ii<PMAX;++j){
            isC[ii]=1; p[ii]=P[j]; if (!(i%P[j])) break;
        }
    }
}
#undef ii

//欧拉 phi 函数

int phi(int n){
    int z = n; for (int i=2;i*i<=n;++i) if (n%i==0){
        z -= z/i; while (n%i==0) n/=i;
    }
    if (n>1) z -= z/n;
    return z % MOD;
}


const int PMAX = 46341;
VI P; bitset<PMAX> isC; int phi[PMAX];
#define ii (i*P[j])
void sieve(){
    phi[1] = 1; FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i),phi[i]=i-1;
        for (int j=0;j<SZ(P)&&ii<PMAX;++j){
            isC[ii]=1;if (!(i%P[j])){
                phi[ii] = phi[i]*P[j];
                break;
            }
            else{
                phi[ii] = phi[i]*(P[j]-1);
            }
        }
    }
}
#undef ii


//莫比乌斯 mu 函数
const int PMAX = 46341;
VI P; bitset<PMAX> isC; int mu[PMAX];
#define ii (i*P[j])
void sieve(){
    mu[1] = 1; FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i),mu[i]=-1;
        for (int j=0;j<SZ(P)&&ii<PMAX;++j){
            isC[ii]=1;if (!(i%P[j])){
                mu[ii] = 0;
                break;
            }
            else{
                mu[ii] = -mu[i];
            }
        }
    }
}
#undef ii

//原根
int getPrimitive(int p){
    --p; VI d; for (int i=2;i*i<=p;++i) if (!(p%i)) d.PB(i), d.PB(p/i);
    UNQ(d); MOD = ++p; FOR(i, 2, p){
        int j = 0; REP_N(j, SZ(d)) if (pow(i, d[j]) == 1) break;
        if (j == SZ(d)) return i;
    }
    assert(0);
    return -1; //!
}

// 离散对数


struct HashTable{

	int index[PMAX], head[PMAX], next[PMAX], sz;
	int key[PMAX];

	inline void clear() {
		sz = 0;
		memset(head, -1, sizeof(head));
	}
	inline void insert(int id, int val) {
		int x = val % PMAX;
		index[sz] = id, key[sz] = val;
		next[sz] = head[x];
		head[x] = sz++;
	}
	inline int search(int val){
		int x = val % PMAX;
		for ( int it = head[x] ; it != -1 ; it = next[it] )
			if ( key[it] == val ) return index[it];
		return -1;
	}
} H;

#define p MOD

int Dlog(int a, int b){

    a %= p, b %= p;

    // Baby-Step ...
    int m = ceil(sqrt(p));

	static Int A[PMAX]; A[0] = 1%p; REP_1(i, m){
		A[i] = A[i-1] * a;
		if (A[i] == b) return i;
	}

	H.clear(); REP(i, m){
		H.insert(i, A[i]);
	}

    // Giant-Step
	Int bb = b, am = _I(A[m]); FOR(i, 1, m){
	    bb *= am; int j = H.search(bb);
		if (~j) return i*m+j;
	}
	return -1;
}

const int LN = 32;
int o;

int exDlog(int a, int b){

    a %= p, b %= p;

    Int aa = 1%p; int x0 = -1; REP(i, LN){
        if (aa == b){x0 = i; break;}
        aa *= a;
    }

    aa = 1; o = 0; for (int d = gcd(a, p); d != 1; d = gcd(a, p)){
        ++o; if (b % d) return ~x0 ? x0 : -1;
        b /= d, p /= d, aa *= a/d;
    }

    if (~x0) return x0;

    int z = Dlog(a, qtt(b, aa)); if (~z) z += o;
    return z;
}

#undef p


// 128位乘

#define m _mod
LL _mod;
inline void Incc(LL&x,LL y){
    x += y; if (x >= m) x -= m;
}

inline LL pdtt(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    LL p=sqrt(m)+0.5,q=p*p-m,a=x/p,b=x%p,c=y/p,d=y%p,e=a*c/p*q,f=a*c%p*q;
    LL t=((a*d+b*c)%m+e)%m;x=t/p*q,y=t%p*p;
    x = (((b*d+f)%m+x)%m+y)%m; if (x<0) x += m;
    return x;
}

inline LL pdtt1(LL x,LL y){
    //x%=m,y%=m; if(a<0)a+=m;if(b<0)b+=m;
    x =(x*y-(LL)(((long double)x*y+0.5)/(long double)m)*m)%m; if (x<0) x += m;
    return x;
}

inline LL pdtt2(LL a,LL b){
    a%=m,b%=m; if (a<0) a+=m; if (b<0) b += m;
    LL c=0; for (;b;b>>=1,Incc(a,a))
        if (b&1) Incc(c,a);
    return c;
}
#undef m


//Rho && Miller_Rabin
map<LL, int> fac;

inline LL pdtt(LL x,LL y,LL z){
    return (x*y-(LL)(((long double)x*y+0.5)/z)*z+z)%z;
}

inline LL poww(LL a, LL b, LL z){
    LL c = 1; for (;b;a=pdtt(a, a, z),b>>=1)
        if (b&1) c = pdtt(c, a, z);
    return c;
}

inline bool Miller_Rabin(int p,LL n){
	int t=0; LL u=n-1; while(!(u&1)) ++t,u>>=1;
	LL x=poww(p,u,n); if(x==1) return 1; DO(t){
		if(x==n-1) return 1;
		x=pdtt(x,x,n);
	}
	return 0;
}

inline bool isPrime(LL n){
	static const int P[]={2,3,5,7,11,13,17,19,23}, Pn = 9;
	if(find(P,P+Pn,n)!=P+Pn) return 1; if(n==1||!(n&1)) return 0;
	REP(i, Pn) if(!Miller_Rabin(P[i],n)) return 0;
	return 1;
}

void rho(LL n){

	if(isPrime(n)){
        fac[n]++;
        return;
	}

	int c=1; while(1){

		LL x1=1,x2=1; int i=1,k=2; while(1){

			x1=pdtt(x1,x1,n)+c;
			LL d=gcd(abs(x1-x2),n);
			if(d!=1&&d!=n){
				rho(d),rho(n/d);
				return;
			}
			if(x1==x2) break;
			if(++i==k) k<<=1,x2=x1;
		}
		++c;
	}
}

//
