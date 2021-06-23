/*
    This code has been written by MinakoKojima, feel free to ask me question. Blog: http://www.shuizilong.com/house
    Template Date: 2015.10.12
    Note: ...
*/

#pragma comment(linker, "/STACK:36777216")
//#pragma GCC optimize ("O2")
#define LOCAL
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


#define fp(i,a,b) for(int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)

template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=4e5+5;
typedef int arr[N];
typedef long long ll;
struct eg{int nx,to;}e[N*2];
int n,m,ce,fi[N];ll ans;
struct LCT{
    int fa[N],ch[N][2];ll s[N],val[N],vs[N];
    #define lc(u) (ch[u][0])
    #define rc(u) (ch[u][1])
    inline bool gf(int u){return rc(fa[u])==u;}
    inline bool ir(int u){return lc(fa[u])^u&&rc(fa[u])^u;}
    inline void up(int u){s[u]=s[lc(u)]+s[rc(u)]+val[u]+vs[u];}
    inline void rot(int u){
        int p=fa[u],k=gf(u);
        if(!ir(p))ch[fa[p]][gf(p)]=u;
        if(ch[u][!k])fa[ch[u][!k]]=p;
        ch[p][k]=ch[u][!k],ch[u][!k]=p;
        fa[u]=fa[p],fa[p]=u,up(p);
    }
    void splay(int u){
        for(int f=fa[u];!ir(u);rot(u),f=fa[u])
            if(!ir(f))rot(gf(f)==gf(u)?f:u);
        up(u);
    }
    inline ll calc(int u,ll t,ll h){

        h = max(h, val[u]);

        return (h*2>t?(t-h)*2:t-1);

        }
    inline void mdy(int u,int w){
        splay(u);int v;
        ll t=s[u]-s[lc(u)],h=s[rc(u)];

        //cout << " " <<  t << " " << h << " "<<  calc(u,t,h) <<" ";

        ans-=calc(u,t,h);s[u]+=w,val[u]+=w,t+=w;
        if(h*2<t+1)vs[u]+=h,rc(u)=0;
        //up(u);
         ans+=calc(u,t,h);

        //out << " " <<  t << " " << h << " "<<  calc(u,t,h) <<" " << endl;

        //access

        for(u=fa[v=u];u;u=fa[v=u]){
            splay(u);t=s[u]-s[lc(u)],h=s[rc(u)];
            ans-=calc(u,t,h);s[u]+=w,vs[u]+=w,t+=w;
            if(h*2<t+1) {
                vs[u]+=h,rc(u)=0,h=0;

                vs[u]-=s[v],rc(u)=v,h=s[v];

                if(h*2<t+1) {
                    vs[u]+=h,rc(u)=0,h=0;
                }
            }
            //up(u);
            ans+=calc(u,t,h);
        }
    }
    void dfs(int u){
        s[u]=val[u];int p=0;ll mx=val[u];
        go(u)if(v^fa[u]){
            fa[v]=u,dfs(v),s[u]+=s[v];
            if(s[v]>mx)mx=s[p=v];
        }
        ans+=min(s[u]-1,(s[u]-mx)*2);
        if(mx*2>=s[u]+1)rc(u)=p;
        vs[u]=s[u]-val[u]-s[rc(u)];
    }
}t;
inline void add(int u,int v){e[++ce]={fi[u],v},fi[u]=ce;}
int main(){

    sd(n),sd(m);int u,v;
    fp(i,1,n)sd(t.val[i]);
    fp(i,2,n)sd(u),sd(v),add(u,v),add(v,u);
    t.dfs(1);we(ans);
    while(m--){
        sd(u),sd(v);
        t.mdy(u,v);
        we(ans);
    }
return Ot(),0;
}
