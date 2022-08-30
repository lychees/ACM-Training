
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

using namespace std;

#define PB push_back
// <<= 'Bignum ., //{
namespace BIGNUM{

const int __base = 10;
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
        inline bignum(int s = 0){
            data.clear();
            while (s) data.PB(s%__base), s/=__base;
            if (data.empty()) data.PB(0);
        }

        inline bignum(long long s){
            data.clear();
            while (s) data.PB(int(s%__base)), s/=__base;
            if (data.empty()) data.PB(0);
        }

        inline bignum(string s){
            int t, i; data.clear();
            for (i=int(s.size())-8;i>0;i-=8){
                istringstream(s.substr(i, 8)) >> t;
                data.PB(t);
            }
            istringstream(s.substr(0, i+8)) >> t;
            data.PB(t);
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
            res += 1;
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
    if (*i != 0) output << *i;
    for (i++;i!=a.data.rend();i++){
        /*if (*i >= 10000) {
            if (*i >= 1000000) {if (*i>=10000000) cout << *i; else cout << 0 << *i;}
            else {if (*i>=100000) cout << "00" << *i; else cout << "000" << *i;}
        }
        else {
            if (*i >= 100) {if (*i>=1000)  cout << "0000" << *i; else cout << "00000" << *i;}
            else { if (*i>=10) cout << "000000" << *i; else cout << "0000000" << *i;}
        }*/
        cout << *i;
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
    list<int>::const_iterator i, j; bignum c; c.data.clear(); int t = 0;
    for (i=a.data.begin(),j=b.data.begin(); i!=a.data.end()&&j!=b.data.end(); i++,j++){
        c.data.PB(t+*i+*j);
        t=c.data.back()/__base; c.data.back()%=__base;
    }
    while (i!=a.data.end()) {c.data.PB(t+*i); t=c.data.back()/__base; c.data.back()%=__base; i++;}
    while (j!=b.data.end()) {c.data.PB(t+*j); t=c.data.back()/__base; c.data.back()%=__base; j++;}
    if (t!=0) c.data.PB(t);
    return c;
}

} //using namespace BIGNUM;
//}


const int N = 105;
struct bign
{
    int len,s[N];
    bign()  {  memset(s,0,sizeof(s));  len=1;  }
    bign(int num)  {  *this=num; }
    bign(char *num) { *this=num; }
    bign operator =(int num)
    {
        char c[N];
        sprintf(c,"%d",num);
        *this=c;
        return *this;
    }
    bign operator =(const char *num)
    {
        len=strlen(num);
        for (int i=0;i<len;i++) s[i]=num[len-1-i]-'0';
        return *this;
    }
    string str()
    {
        string res="";
        for (int i=0;i<len;i++) res=(char)(s[i]+'0')+res;
        return res;
    }
    void clean()
    {
        while (len>1&&!s[len-1]) len--;
    }
    bign operator +(const bign &b)
    {
        bign c;
        c.len=0;
        for (int i=0,g=0;g||i<len||i<b.len;i++)
        {
            int x=g;
            if (i<len) x+=s[i];
            if (i<b.len) x+=b.s[i];
            c.s[c.len++]=x%10;
            g=x/10;
        }
        return c;
    }
    bign operator -(const bign &b)
    {
        bign c;
        c.len=0;
        int x;
        for (int i=0,g=0;i<len;i++)
        {
            x=s[i]-g;
            if (i<b.len) x-=b.s[i];
            if (x>=0) g=0;
            else{
                x+=10;
                g=1;
            };
            c.s[c.len++]=x;
        }
        c.clean();
        return c;
    }
    bign operator *(const bign &b)
    {
        bign c;
        c.len=len+b.len;
        for (int i=0;i<len;i++) for (int j=0;j<b.len;j++) c.s[i+j]+=s[i]*b.s[j];
        for (int i=0;i<c.len-1;i++) { c.s[i+1]+=c.s[i]/10; c.s[i]%=10; }
        c.clean();
        return c;
    }
    bool operator <(const bign &b)
    {
        if (len!=b.len) return len<b.len;
        for (int i=len-1;i>=0;i--)
             if (s[i]!=b.s[i]) return s[i]<b.s[i];
        return false;
    }
    bign operator +=(const bign &b)
    {
        *this=*this+b;
        return *this;
    }
    bign operator -=(const bign &b)
    {
        *this=*this-b;
        return *this;
    }
};
istream& operator >>(istream &in,bign &x)
{
  string s;
  in>>s;
  x=s.c_str();
  return in;
}
ostream& operator <<(ostream &out,bign &x)
{
    out<<x.str();
    return out;
}


using namespace std;
const int maxnode=100+20;
int sigma_size;//后面读入
struct AC_Automata
{
    int ch[maxnode][50+20];
    int match[maxnode];
    int f[maxnode];
    map<char ,int> mp;
    int sz;
    void init()
    {
        sz=1;
        memset(ch[0],0,sizeof(ch[0]));
        match[0]=f[0]=0;
        mp.clear();
    }
    void insert(char *s)
    {
        int n=strlen(s),u=0;
        for(int i=0;i<n;i++)
        {
            int id=mp[s[i]];
            if(ch[u][id]==0)
            {
                ch[u][id]=sz;
                memset(ch[sz],0,sizeof(ch[sz]));
                match[sz++]=0;
            }
            u=ch[u][id];
        }
        match[u]=1;
    }
    void getFail()
    {
        f[0]=0;
        queue<int> q;
        for(int i=0;i<sigma_size;i++)
        {
            int u=ch[0][i];
            if(u)
            {
                f[u]=0;
                q.push(u);
            }
        }
        while(!q.empty())
        {
            int r=q.front();q.pop();
            for(int i=0;i<sigma_size;i++)
            {
                int u=ch[r][i];
                if(!u){ ch[r][i]=ch[f[r]][i]; continue; }
                q.push(u);
                int v=f[r];
                while(v && ch[v][i]==0) v=f[v];
                f[u]=ch[v][i];
                match[u] |= match[f[u]];
            }
        }
    }
};
AC_Automata ac;
using namespace BIGNUM;
bign dp[100+20][50+10];

int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif


    int n,m,p;
    char str[50+20];
    scanf("%d%d%d",&n,&m,&p);

        sigma_size=n;
        ac.init();
        scanf("%s",str);
        for(int i=0;i<n;i++)
            ac.mp[str[i]]=i;
        while(p--)
        {
            scanf("%s",str);
            ac.insert(str);
        }
        ac.getFail();



        dp[0][0]=bign(1);//起点
        for(int k=0;k<m;k++)
        {
            for(int i=0;i<ac.sz;i++)
                if(ac.match[i]==0) {
                for(int j=0;j<sigma_size;j++)  if(ac.match[ac.ch[i][j]]==0)
                        dp[ac.ch[i][j]][k+1] = dp[ac.ch[i][j]][k+1] + dp[i][k];
                }
        }
        bign z = 0;
        for(int i=0;i<ac.sz;i++) if(ac.match[i]==0)
			z = z + dp[i][m];
        cout << z;
}
