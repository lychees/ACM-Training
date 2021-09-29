#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <ctime>
#include <map>
#include <queue>
#include <set>
#define LL long long
using namespace std;
 
const int modd=1000000007;
const int maxk=50+15;
struct Node
{
    LL A,B,C,N,K1,K2;
    Node(LL A=0,LL B=0,LL C=0,LL N=0,LL K1=0,LL K2=0):A(A),B(B),C(C),N(N),K1(K1),K2(K2) {}
};
LL K,L,R,A,B,C;
LL Rat[maxk][maxk];
LL Com[maxk][maxk];
const bool operator < (const Node &a,const Node &b)
{
    if (a.A==b.A)
    {
        if (a.B==b.B)
        {
            if (a.C==b.C)
            {
                if (a.N==b.N)
                {
                    if (a.K1==b.K1) return a.K2<b.K2;
                    return a.K1<b.K1;
                }
                return a.N<b.N;
            }
            return a.C<b.C;
        }
        return a.B<b.B;
    }
    return a.A<b.A;
}
map <Node , LL > Map;
LL powe(LL x,LL y)
{
    LL ans=1ll;
    for (;y;y>>=1,x=x*x%modd)
        if (y&1)
            ans=ans*x%modd;
    return ans;
}
LL S(LL N,LL K)
{
    LL ans=0;
    for (int i=K+1;i>=0;i--) ans=(ans*N+Rat[K][i])%modd;
    return ans+(K==0);
}
LL done(LL A,LL B,LL C,LL N,LL K1,LL K2)
{
    if (Map.find(Node(A,B,C,N,K1,K2))!=Map.end()) return Map[Node(A,B,C,N,K1,K2)];
    if (K2==0) return Map[Node(A,B,C,N,K1,K2)]=S(N,K1);
    if (A>=C)
    {
        long long ans=0;
        long long gog=1ll;
        for (int i=0;i<=K2;i++)
        {
            ans+=done(A%C,B,C,N,K1+i,K2-i)*gog%modd*Com[K2][i];
            ans%=modd;
            gog*=A/C;
            gog%=modd;
        }
        return Map[Node(A,B,C,N,K1,K2)]=ans;
    }
    if (B>=C)
    {
        long long ans=0;
        long long gog=1ll;
        for (int i=0;i<=K2;i++)
        {
            ans+=done(A,B%C,C,N,K1,K2-i)*gog%modd*Com[K2][i];
            ans%=modd;
            gog*=B/C;
            gog%=modd;
        }
        return Map[Node(A,B,C,N,K1,K2)]=ans;
    }
    if (A==0 || (A*N+B)/C==0) return 0;
    LL maxx=(A*N+B)/C-1;    
    LL nA=C,nB=C-B-1,nC=A;
    if (K1==0)
    {
        LL ans=powe(maxx+1,K2)*N%modd;
        for (int i=0;i<K2;i++)
        {
            ans-=Com[K2][i]*done(nA,nB,nC,maxx,i,1);
            ans%=modd;
        }
        if (ans<0) ans+=modd;
        return Map[Node(A,B,C,N,K1,K2)]=ans;
    }
    LL ans=powe(maxx+1,K2)*S(N,K1)%modd;
    for (int i=0;i<K2;i++)
        for (int j=1;j<=K1+1;j++)
        {
            ans-=Com[K2][i]*Rat[K1][j]%modd*done(nA,nB,nC,maxx,i,j);
            ans%=modd;
        }
    if (ans<0) ans+=modd;
    return Map[Node(A,B,C,N,K1,K2)]=ans;
}
int main()
{
    cin >> K >> L >> R >> A >> B >> C;
    Rat[0][1]=1;
    for (LL i=0,j;i<=K+1;i++)
        for (Com[i][0]=j=1;j<=i;j++)
         Com[i][j]=(Com[i-1][j-1]+Com[i-1][j])%modd;
    for (LL i=1;i<=K;i++)
        for (LL j=1;j<=i+1;j++)
        {
            Rat[i][j]=Com[i+1][j];
            for (int k=0;k<=i-1;k++)
                Rat[i][j]-=Com[i+1][k]*Rat[k][j]%modd;
            Rat[i][j]%=modd;
            if (Rat[i][j]<0) Rat[i][j]+=modd;
            Rat[i][j]=Rat[i][j]*powe(i+1,modd-2)%modd;
        }
    printf("%d\n",(int)((done(A,B,C,R,0,K)-done(A,B,C,L-1,0,K)+modd)%modd));
    return 0;
}
