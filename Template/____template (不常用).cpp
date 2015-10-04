/** Add On .. **/ //{
// <<= '2. Number Theory .,//{
namespace NT{
/*
Int Fact[N], Factt[N]; Int Binom(int n, int m){
    return Fact[n] * Factt[m] * Factt[n-m];
}
*/

/*
    Fact[0] = 1; REP_1(i, N-1) Fact[i] = Fact[i-1] * i;
    Factt[N-1] = _I(Fact[N-1]); DWN(i, N, 1) Factt[i-1] = Factt[i] * i;
*/

/*
    int Binom[N][N];
    REP(i, N){Binom[i][0] = 1; REP_1(j, i) Binom[i][j] = Binom[i-1][j-1] + Binom[i-1][j];}
*/


/*
const int PMAX = 1;
VI P; bitset<PMAX> isC;
void sieve(){
    FOR(i, 2, PMAX){
        if (!isC[i]) P.PB(i);
        for (int j=0;j<SZ(P)&&i*P[j]<PMAX;++j){
            isC[i*P[j]]=1; if (!(i%P[j])) break;
        }
    }
}
*/

/*
inline int phi(int n){
    int res = n; for (int i=2;sqr(i)<=n;++i) if (!(n%i)){
        DEC(res, qtt(res, i));
        do{n /= i;} while(!(n%i));
    }
    if (n != 1)
        DEC(res, qtt(res, n));
    return res;
}
*/

/*LL d, x, y; void exGcd(LL a, LL b){
    if(!b) x = 1, y = 0, d = a;
    else{
        exGcd(b, a%b); LL t = y;
        y = x - (a/b)*y, x = t;
    }
}*/

} using namespace NT;//}




// <<= '7. Matrix Theory .,//{
namespace MT{

    const int N = 100;
    int n = 0;

    typedef int rec;

    struct matrix{
        rec d[N][N];

        void init(rec e = 0){RST(d); if(e) REP(i, n) d[i][i] = e;}
        matrix(rec e = 0){init(e);}

        matrix operator *(const matrix &rhs) const{
            matrix res; //REP_3(i, j, k, n, n, n) res.d[i][j] += d[i][k] * rhs.d[k][j];
            REP_2(i, j, n, n){
                LL tmp = 0; REP(k, n) tmp += (LL) d[i][k] * rhs.d[k][j];
                res.d[i][j] = tmp % MOD;
            }
            return res;
        }

        matrix& operator *=(const matrix& rhs){return (*this) = (*this) * rhs;}

        inline int res(){
            int res = 0;
            REP(i, n) INC(res, d[0][i]);
            //REP_2(i, j, n, n) INC(res, d[i][j]);
            return res;
        }
    };

    /*inline matrix pow_sum(const matrix& a, LL nn){
        if (nn == 1) return matrix(1);
        matrix t; REP_2(i, j, n, n) t.d[i][j] = t.d[i][j+n] = a.d[i][j];
        FOR_C(i, n, n*2) t.d[i][i] = 1; n <<= 1; t = pow(t, nn), n >>= 1;
        REP_2(i, j, n, n) t.d[i][j] = t.d[i][j+n];
        return t;
    }*/

    inline matrix pow_sum(const matrix& a, LL nn){
        if (nn == 1) return matrix(1);
        matrix t; REP_2(i, j, n, n) t.d[i][j] = a.d[i][j];
        REP(i, n) t.d[i][i+n] = t.d[i+n][i+n] = 1; n <<= 1; t = pow(t, nn), n >>= 1;
        REP_2(i, j, n, n) t.d[i][j] = t.d[i][j+n];
        return t;
    }

    template<class T> T pow_sum(T a, LL nn){
        int _n = n; n = 1; matrix t; t.d[0][0] = a;
        t = pow_sum(t, nn), n = _n;
        return t.d[0][0];
    }

} //using namespace MT;//}
// <<= '8. Stringology .,//{
namespace SL{

    //http://user.qzone.qq.com/251815992/blog/1381695084

namespace KMP{

    void get_pi(const char P[], int n, int pi[]){
        for (int i = 1, j = pi[0] = -1; i < n; ++i){
            while (j >= 0 && P[i] != P[j+1]) j = pi[j];
            if (P[i] == P[j+1]) ++j;
            pi[i] = j;
        }
        //REP(i, n) cout << pi[i] << " "; cout << endl;
    }

    int run(const char T[], int n, const char P[], int m, const int pi[]){
        int cnt = 0; for (int i = 0, j = -1; i < n; ++i){
            while (j >= 0 && T[i] != P[j+1]) j = pi[j];
            if (T[i] == P[j+1]) ++j;
            if (j == m - 1) ++cnt, j = pi[j];
        }
        return cnt;
    }
} //using namespace KMP;

    namespace Z{
        void calc_z(const char *P, int n, int *z){

            z[0] = n;

            for (int i = 1, l = 0, r = 0; i < n; ++i){
                if (i > r){
                    for(l = r = i; r < n && P[r] == P[r - l];) ++r;
                    z[i] = r - l, --r;
                }
                else {
                    if (z[i - l] < r - i + 1) z[i] = z[i - l];
                    else {
                        for (l = i;r < n && P[r] == P[r - l];) ++r;
                        z[i] = r - l, --r;
                    }
                }
            }

            //REP(i, n) cout << z[i] << " "; cout << endl;
        }

        int run(const char *T, int n, const char *P, int m, const int *z){

            int ex; REP_C_N(ex, min(n, m)) if (T[ex] != P[ex]) break;

            int res = ex == m;

            for (int i = 1, l = 0, r = 0; i < n; ++i){
                if (i > r){
                    for (l = r = i; r < n && T[r] == P[r - l];) ++r;
                    ex = r - l, --r;
                }
                else {
                    if (z[i - l] < r - i + 1) ex = z[i - l];
                    else {
                        for (l = i; r < n && T[r] == P[r - l];) ++r;
                        ex = r - l, --r;
                    }
                }
                if (ex == m) ++res;
            }

            return res;
        }
    } //using namespace Z;

void Manacher(const char ss[], int nn, char s[], int& n, int r[]) {
    n = 2*nn+2; s[0] = '$'; REP(i, nn)s[i*2+1]='.',s[i*2+2]=ss[i];s[n-1]='.';s[n] = 0;
    //puts(s);

    int mx=0,mi=0;FOR(i,1,n){
        for (r[i]=mx>i?min(r[2*mi-i],mx-i):1;s[i+r[i]]==s[i-r[i]];++r[i]);
        if (i+r[i]>mx)mx=i+r[i],mi=i;
    }

    //mx=0;FOR(i,1,n)if(r[i]>mx)mx=r[i],mi=i;--mx;
    //for(int i=mi-mx+1;i<mi+mx;i+=2)putchar(s[i]);
    //mi-=mx;mi/=2;FOR(i,mi,mi+mx) putchar(ss[i]);
	//puts("");
}


const int N = 200009, Z = 257;
uint P[N], S[N];

namespace SHash{
    int h(int l, int r){
        return S[r+1] - S[l] * P[r-l+1];
    }
    void init(){
        P[0] = S[0] = 1; FOR(i, 1, N) P[i] = P[i-1] * Z;
    }
    void init(uint S[], int n, char s[]){
        REP(i, n) S[i+1] = S[i]*Z + s[i];
    }
}


namespace ACM{
}

namespace SAM{
    const int N = int(2e5) + 9, Z = 26;
    int trans[N][Z], par[N], len[N], tail, tot; char buf[N/2];

    inline int new_node(){
        RST(trans[tot]);
        tail = tot;
        return tot++;
    }

    inline int new_node(int u){
        CPY(trans[tot], trans[u]), par[tot] = par[u];
        return tot++;
    }

#define v trans[u][c]
#define p par[u]
#define pp par[uu]

    void Ext(int c){
        int u = tail, uu = new_node(); len[uu] = len[u] + 1;
        while (u && !v) v = uu, u = p;
        if (!u && !v) v = uu, pp = 0;
        else{
            if (len[v] == len[u] + 1) pp = v;
            else{
                int _v = v, vv = new_node(_v); len[vv] = len[u] + 1;
                par[_v] = pp = vv;
                while (v == _v) v = vv, u = p;
            }
        }
    }
} using namespace SAM;



} //using namespace SL;//}


/** Miscellaneous .. **/ //{
// <<= 'Random Event .. . //{
namespace RNG{
//srand((unsigned)time(NULL));
#ifdef _TESTLIB_H_
inline ULL random(LL l, LL r){return rnd.next(l, r);}
int dice(){return random(0, 5);}
bool coin(){return random(0, 1);}
#else
inline unsigned int rand16(){return ((rand()) << 15) ^ rand();}
inline unsigned int rand32(){return (rand16() << 16) | rand16();}
inline ULL rand64(){return ((LL)rand32() << 32) | rand32();}
inline ULL random(LL l, LL r){return l == r ? l : rand64() % (r - l) + l;}
int dice(){return rand() % 6;}
bool coin(){return bool(rand() % 2);}
#endif
} using namespace RNG;
//}
// <<= 'Compile Other Language .. .//{
string __file__(){
    string res = __FILE__;
    int r = SZ(res) - 1; while (res[r] !=  '.') --r;
    int l = r - 1; while (res[l] != '\\') --l; ++l;
    return res.substr(l, r-l);
}

void Exec(string a, string b, string c){
    if (b.empty()) b = __file__();
    string cmd = a + ' ' + b + '.' + c;
    system(cmd.c_str());
}

void Pascal(string file = ""){Exec("pascal", file, "pas");}
void Java(string file = ""){Exec("javac", file, "java");}
void Ruby(string file = ""){Exec("ruby", file, "rb");}
void Python(string file = ""){Exec("python", file, "py");}
void Haskell(string file = ""){Exec("runghc", file, "hs");}
void Ocaml(string file = ""){Exec("ocaml", file, "ml");}
//}

// <<= 'Clock .. . //{
namespace CLOCK{
DB s0, s1, rd, k, T;
inline DB getTime(){
#ifdef LOCAL
    return 1.0 * clock() / CLOCKS_PER_SEC;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec * 1e-6;
#endif
}

inline void st0(DB _T = 0.98){T = _T, s0 = getTime();}
inline void st1(DB _k = 1.618){k = _k, s1 = getTime();}
inline void ed1(){rd = getTime() - s1;}
inline DB elapsed(){return getTime() - s0;}
inline bool TLE(){return elapsed() + rd * k < T;}
} //using namespace CLOCK;
//}
// <<= 'Bignum ., //{
namespace BIGNUM{

const int __base = 1e8;
const int P10[] = {1, 10, int(1e2), int(1e3), int(1e4), int(1e5), int(1e6), int(1e7), int(1e8), int(1e9)};
const int MAX_BUF_SIZE = 109;
char __buf[MAX_BUF_SIZE];

class bignum{
          friend istream& operator>>(istream&, bignum&);
          friend ostream& operator<<(ostream&, const bignum&);
          friend bignum operator +(const bignum&, const bignum&);
          friend bignum operator -(const bignum&, const bignum&);
          friend bignum operator *(const bignum&, const bignum&);
          friend bignum operator /(const bignum&, const bignum&);
          friend bignum operator %(const bignum&, const bignum&);
          friend bignum operator +(const bignum&, const int&);
          friend bignum operator -(const bignum&, const int&);
          friend bignum operator *(const bignum&, const int&);
          friend bignum operator /(const bignum&, const int&);
          friend bignum operator %(const bignum&, const int&);
          friend bool operator ==(const bignum&, const bignum&);
          friend bool operator !=(const bignum&, const bignum&);
          friend bool operator <(const bignum&, const bignum&);
          friend bool operator >(const bignum&, const bignum&);
          friend bool operator <=(const bignum&, const bignum&);
          friend bool operator >=(const bignum&, const bignum&);
          friend bool operator ==(const bignum&, const int&);
          friend bool operator !=(const bignum&, const int&);
          friend bool operator <(const bignum&, const int&);
          friend bool operator >(const bignum&, const int&);
          friend bool operator <=(const bignum&, const int&);
          friend bool operator >=(const bignum&, const int&);
          friend int do_comp(const bignum&, const int&);
          friend int do_comp(const bignum&, const bignum&);
          friend void divide(const bignum&, const bignum&, bignum&, bignum&);
          friend bignum pow(bignum, int);
          friend bignum pow(int, int);
    public:
        inline bignum(){};
        inline bignum(int s){
            while (s) data.PB(s%__base), s/=__base;
            if (data.empty()) data.PB(0);
        }

        inline bignum(long long s){
            while (s) data.PB(int(s%__base)), s/=__base;
            if (data.empty()) data.PB(0);
        }

        inline bignum(string s){
            int t, i; CLR(data);
            for (i=int(s.size())-8;i>0;i-=8){
                istringstream(s.substr(i, 8)) >> t;
                data.PB(t);
            }
            istringstream(s.substr(0, i+8)) >> t;
            data.PB(t);
        }

        void input(){
            CLR(data); RS(__buf); int t = 0, c = 0;
            DWN(i, strlen(__buf), 0){
                t += P10[c] * (int(__buf[i]) - '0'), ++c;
                if (c == 8) data.PB(t), c = t = 0;
            }
            if (c) data.PB(t);
        }

        bignum&operator=(int);
        bignum&operator=(const string&);
        bignum&operator=(const bignum&);
        bignum&operator +=(const bignum&);
        bignum&operator -=(const bignum&);
        bignum&operator *=(const bignum&);
        bignum&operator /=(const bignum&);
        bignum&operator %=(const bignum&);
        bignum&operator +=(const int&);
        bignum&operator -=(const int&);
        bignum&operator *=(const int&);
        bignum&operator /=(const int&);
        bignum&operator %=(const int&);
        bool undefined();
        int do_try(const int&);
        int do_try(const bignum&);
        void do_trim();
        list<int> data;

    int size(){
        list<int>::iterator it; int res = 0;
        for (it=data.begin(); it!=data.end();it++)
            res += 8;
        it--;
        if (*it >= 10000) {
            if ( (*it) >= 1000000) {if (*it >=10000000) ; else res--;}
            else {if ((*it) >= 100000) res-=2; else res-=3;}
        }
        else
            if ( (*it) >= 100) {if (*it >=1000) res-=4; else res-=5;}
            else {if ((*it) >= 10) res-=6; else res-=7;}

        return res;
    }

    void do_reserve(int a){
        if (a <= 0) return;
        list<int>::iterator it;
        for (it=data.begin(); it!=data.end() && a>0; it++) a-=8;
        if (it == data.end() && a>=0) return;
        a+=8, it--; int f = 1;
        for (int i=0;i<a;i++) f *= 10; (*it) %= f;
        data.erase(++it, data.end());
        do_trim();
    }
};

inline bignum&bignum::operator =(const bignum&a){
    data.clear();
    for (list<int>::const_iterator i=a.data.begin();i!=a.data.end();i++){
        data.PB(*i);
    }
    return*this;
}
inline bignum&bignum::operator =(const string&a){
    return*this=bignum(a);
}
inline bignum&bignum::operator =(int a){
    return*this=bignum(a);
}

inline istream& operator>>(istream& input, bignum& a){
    string s; int t, i; input >> s; a.data.clear();
    for (i=int(s.size())-8;i>0;i-=8){
        istringstream(s.substr(i, 8)) >> t;
        a.data.PB(t);
    }
    istringstream(s.substr(0, i+8)) >> t;
    a.data.PB(t);
    return input;
}

inline ostream& operator<<(ostream& output, const bignum& a){
    list<int>::const_reverse_iterator i=a.data.rbegin();
    output << *i;
    for (i++;i!=a.data.rend();i++){
        if (*i >= 10000) {
            if (*i >= 1000000) {if (*i>=10000000) cout << *i; else cout << 0 << *i;}
            else {if (*i>=100000) cout << "00" << *i; else cout << "000" << *i;}
        }
        else {
            if (*i >= 100) {if (*i>=1000)  cout << "0000" << *i; else cout << "00000" << *i;}
            else { if (*i>=10) cout << "000000" << *i; else cout << "0000000" << *i;}
        }
    }
    return output;
}

inline bool bignum::undefined(){
    return data.empty();
}

inline int do_comp(const bignum& a, const bignum& b){
    if (a.data.size()<b.data.size()) return -1; if (a.data.size()>b.data.size()) return 1;
    list<int>::const_reverse_iterator i; list<int>::const_reverse_iterator j;
    for (i=a.data.rbegin(),j=b.data.rbegin(); j!=b.data.rend(); i++,j++){
        if (*i<*j) return -1;              //!!!!
        if (*i>*j) return 1;
    }
    return 0;
}
inline int do_comp(const bignum& a, const int& b){
    return do_comp(a, bignum(b));
}

inline bool operator ==(const bignum& a, const bignum& b){
    return do_comp(a, b) == 0;
}
inline bool operator !=(const bignum& a, const bignum& b){
    return do_comp(a, b) != 0;
}
inline bool operator <(const bignum& a, const bignum& b){
    return do_comp(a, b) == -1;
}
inline bool operator >(const bignum& a, const bignum& b){
    return do_comp(a, b) == 1;
}
inline bool operator <=(const bignum& a, const bignum& b){
    return do_comp(a, b) != 1;
}
inline bool operator >=(const bignum& a, const bignum& b){
    return do_comp(a, b) != -1;
}

inline bool operator ==(const bignum& a, const int& b){
    return do_comp(a, b) == 0;
}
inline bool operator !=(const bignum& a, const int& b){
    return do_comp(a, b) != 0;
}
inline bool operator <(const bignum& a, const int& b){
    return do_comp(a, b) == -1;
}
inline bool operator >(const bignum& a, const int& b){
    return do_comp(a, b) == 1;
}
inline bool operator <=(const bignum& a, const int& b){
    return do_comp(a, b) != 1;
}
inline bool operator >=(const bignum& a, const int& b){
    return do_comp(a, b) != -1;
}

inline void bignum::do_trim(){
    while (data.size()>1&&data.back()==0) data.pop_back();
}

inline bignum& bignum::operator +=(const bignum& a){
    list<int>::iterator i; list<int>::const_iterator j; int t = 0;
    for (i=data.begin(),j=a.data.begin(); i!=data.end()&&j!=a.data.end(); i++,j++){
        *i+=*j+t; t=*i/__base; *i%=__base;
    }
    while (i!=data.end()) {*i+=t; t=*i/__base; *i%=__base; i++;}
    while (j!=a.data.end()) {data.PB(t+*j); t=data.back()/__base; data.back()%=__base; j++;}
    if (t!=0) data.PB(t);
    return *this;
}

inline bignum& bignum::operator -=(const bignum& a){
    list<int>::iterator i; list<int>::const_iterator j; int t = 0;
    for (i=data.begin(),j=a.data.begin(); j!=a.data.end(); i++,j++){
        *i -= t+*j; if (*i>=0) t=0; else *i+=__base, t=1;
    }
    while (i!=data.end()) {*i-=t; if (*i>=0) t=0;else *i+=__base, t=1; i++;}
    (*this).do_trim();
    return *this;
}

inline bignum& bignum::operator +=(const int& a){
    return (*this)+=bignum(a);
}

inline bignum& bignum::operator -=(const int& a){
    return (*this)-=bignum(a);
}

inline bignum operator +(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; bignum c; int t = 0;
    for (i=a.data.begin(),j=b.data.begin(); i!=a.data.end()&&j!=b.data.end(); i++,j++){
        c.data.PB(t+*i+*j);
        t=c.data.back()/__base; c.data.back()%=__base;
    }
    while (i!=a.data.end()) {c.data.PB(t+*i); t=c.data.back()/__base; c.data.back()%=__base; i++;}
    while (j!=b.data.end()) {c.data.PB(t+*j); t=c.data.back()/__base; c.data.back()%=__base; j++;}
    if (t!=0) c.data.PB(t);
    return c;
}

inline bignum operator -(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; bignum c; int t = 0;
    for (i=a.data.begin(),j=b.data.begin(); j!=b.data.end(); i++,j++){
        t = *i - t;
        if (t>=*j) c.data.PB(t-*j), t=0;
        else c.data.PB(t+__base-*j), t=1;
    }
    while (i!=a.data.end()) {t=*i-t; if (t>=0) c.data.PB(t), t=0;else c.data.PB(t+__base), t=1; i++;}
    c.do_trim();
    return c;
}

inline bignum operator *(const bignum& a, const bignum& b){
    list<int>::const_iterator i, j; list<int>::iterator k, kk; bignum c; long long t = 0;

    for (int i=0;i<a.data.size()+b.data.size();i++) c.data.PB(0);
    for (i=a.data.begin(),k=c.data.begin(); i!=a.data.end(); i++,k++){
        for (j=b.data.begin(),kk=k; j!=b.data.end(); j++,kk++){
            t+=(long long)(*i)*(*j)+(*kk);
            *kk=int(t%__base); t/=__base;
        }
        *kk+=t; t=0;
    }
    c.do_trim();
    return c;
}

inline int bignum::do_try(const bignum& a){
    int l = 1, r = 99999999, m, t;
    while (l+2<r){
        m = (l + r) / 2;
        t = do_comp(*this, a*bignum(m));
        if (t==0) return m;
        if (t<0) r = m - 1;
        else l = m;
    }
    while (do_comp(*this, a*bignum(r))<0) r--;
    return r;
}

inline void divide(const bignum& a, const bignum& b, bignum& d, bignum& r){
    list<int>::const_reverse_iterator i = a.data.rbegin(); int t;
    d = bignum(0); r = bignum(0);
    do {
        while (r<b&&i!=a.data.rend()){d.data.push_front(0);r.data.push_front(*i);r.do_trim();i++;}
        if (r>=b){
            t = r.do_try(b); d.data.front() = t;
            r-=(b*bignum(t));
        }
    } while (i!=a.data.rend());
    d.do_trim();
}

inline bignum operator /(const bignum& a, const bignum& b){
    bignum d, r;
    divide(a, b, d, r);
    return d;
}

inline bignum operator %(const bignum& a, const bignum& b){
    bignum d, r;
    divide(a, b, d, r);
    return r;
}

inline bignum operator +(const bignum& a, const int& b){
    return a+bignum(b);
}

inline bignum operator -(const bignum& a, const int& b){
    return a-bignum(b);
}

inline bignum operator *(const bignum& a, const int& b){
    return a*bignum(b);
}

inline bignum operator /(const bignum& a, const int& b){
    return a/bignum(b);
}

inline bignum operator %(const bignum& a, const int& b){
    return a%bignum(b);
}

inline bignum& bignum::operator *=(const bignum& a){
    (*this) = (*this) * a;
    return *this;
}

inline bignum& bignum::operator /=(const bignum& a){
    (*this) = (*this) / a;
    return *this;
}

inline bignum& bignum::operator %=(const bignum& a){
    (*this) = (*this) % a;
    return *this;
}

inline bignum& bignum::operator *=(const int& a){
    return (*this)*=bignum(a);
}

inline bignum& bignum::operator /=(const int& a){
    return (*this)/=bignum(a);
}

inline bignum& bignum::operator %=(const int& a){
    return (*this)%=bignum(a);
}

inline bignum pow(bignum a,int b){
    bignum c(1);
    while (b!=0) {
        if (b&1) c *= a;
        a = a * a; b >>= 1;
    }
    return c;
}
inline bignum pow(int a, int b){
    return pow(bignum(a), b);
}

} //using namespace BIGNUM;
//}
// <<= 'Temp .. . //{
namespace TMP{
template<class T> PTT operator+(const PTT &p1, const PTT &p2) {
	return PTT(p1.fi + p2.fi, p1.se + p2.se);
}

template<class T> PTT operator-(const PTT &p1, const PTT &p2) {
	return PTT(p1.fi - p2.fi, p1.se - p2.se);
}

template<class T> PTT operator*(const PTT &lhs, T k){
    return PTT(lhs.fi * k, lhs.se * k);
}

namespace BIT{
    const int N = int(1e5) + 9;
    int C[N], n;
    int Sum(int x){
        int z=0; for (;x;x^=low_bit(x)) z += C[x];
        return z;
    }
    void Add(int x, int d){
        for(;x<=n;x+=low_bit(x)) C[x] += d;
    }
    int Sum(int l, int r){
        return Sum(r) - Sum(l-1);
    }
} //using namespace BIT;

/*
    void Make(int x){P[x] = x;}
    int Find(int x){return x == P[x] ? x : P[x] = Find(P[x]);}
    void Union(int x, int y){P[y] = x;}
*/

namespace DSU{ // Disjoint Set Union
    const int N = 0;
    int P[N], R[N], n;
    inline void Make(int x){
        P[x] = x, R[x] = 0;
    }
    inline int Find(int x){
        return P[x] == x ? x : P[x] = Find(P[x]);
    }
    inline void Unionn(int x, int y){
        if (R[x] == R[y]) ++R[x];
        else if (R[x] < R[y]) swap(x, y);
        P[y] = x;
    }
    inline void Union(int x, int y){
        x = Find(x), y = Find(y), Unionn(x, y);
    }
    inline void Init(){
        REP_1(i, n) Make(i);
    }
} //using namespace DSU;

namespace ALG{

    template<class T> int LIS(int n, T* a){
        VI b; b.PB(a[0]); FOR(i, 1, n){
            if (b.back() < a[i]) b.PB(a[i]);
            else {
                b[lower_bound(ALL(b), a[i]) - b.begin()] = a[i];
            }
        }
        return SZ(b);
    }

    //template<class T, class C = __typeof less<T>()> int LIS(int n, T* a, C cmp = less<T>()){
    template<class T, class C> int LIS(int n, T* a, C cmp){
        vector<T> b; b.PB(a[0]); FOR(i, 1, n){
            if (cmp(b.back(), a[i])) b.PB(a[i]);
            else {
                b[lower_bound(ALL(b), a[i], cmp) - b.begin()] = a[i];
            }
        }
        return SZ(b);
    }

    template<class T> int LISS(int n, T* a, int* pre, int& lst){
        VI b; b.PB(0); pre[0] = -1; FOR(i, 1, n){
            if (a[b.back()] < a[i]) pre[i] = b.back(), b.PB(i);
            else {
                int l = 0, r = SZ(b); while (l < r){
                    int m = l + r >> 1;
                    if (a[b[m]] < a[i]) l = m + 1;
                    else r = m;
                }
                pre[i] = !r ? -1 : b[r-1];
                b[r] = i;
            }
        }
        lst = b.back();
        return SZ(b);
    }

    //template<class T, class C = __typeof less<T>()> int LISS(int n, T* a, int* pre, int& lst, C cmp = less<T>()){
    template<class T, class C> int LISS(int n, T* a, int* pre, int& lst, C cmp){
        VI b; b.PB(0); pre[0] = -1; FOR(i, 1, n){
            if (cmp(a[b.back()], a[i])) pre[i] = b.back(), b.PB(i);
            else {
                int l = 0, r = SZ(b); while (l < r){
                    int m = l + r >> 1;
                    if (cmp(a[b[m]], a[i])) l = m + 1;
                    else r = m;
                }
                pre[i] = !r ? -1 : b[r-1];
                b[r] = i;
            }
        }

        lst = b.back();
        return SZ(b);
    }
}  using namespace ALG;
} using namespace TMP;
//}
//}

//}/* .................................................................................................................................. */

int n;

int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif

//汇编调栈
int __size__ = 256 << 20; // 256MB
char *__p__ = (char*)malloc(__size__) + __size__;
__asm__("movl %0, %%esp\n" :: "r"(__p__));

//IO 同步
ios_base::sync_with_stdio(false);

//随机种子
srand((unsigned)time(NULL));



}

