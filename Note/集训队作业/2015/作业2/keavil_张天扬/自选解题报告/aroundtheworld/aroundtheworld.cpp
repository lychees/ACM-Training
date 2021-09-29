/**************************************************************
    Problem: 3827
    User: keavil
    Language: C++
    Result: Accepted
    Time:52124 ms
    Memory:20804 kb
****************************************************************/
 
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n,q,d,l[1000001],mone,to[2000001],ans,h[2000001],top,fi,r;
int calc(int st)
{
    for(fi=st;fi<st+n;fi=to[fi]);
    for(int i=st,t=to[i];i!=fi;i=t,t=to[t])to[i]=fi;
    return h[st]-h[fi];
}
int getint()
{
    int ret=0;char ch=getchar();for(;ch<'0'||ch>'9';ch=getchar());
    for(;ch>='0'&&ch<='9';ch=getchar())ret=ret*10+ch-'0';
    return ret;
}
int main()
{
    n=getint();q=getint();r=n<<1;
    for(int i=1;i<=n;++i){l[i]=getint();if(mone<l[i])mone=l[i];}
    while(q--)
    {
        d=getint();ans=2147483647;
        if(d<mone){puts("NIE");continue;}
        for(int i=1,now=1,dist=0,t=2;i<=r;)
        {
            while(now<r)
                if(dist+l[t]<=d){++now;dist+=l[t];if(t==n)t=1;else ++t;}
                else break;
            to[i]=now;
            ++i;dist-=l[i>n?i-n:i];
        }
        for(int i=r;i>=1;--i)h[i]=h[to[i]]+1;
        for(int i=1;i<=n;++i){int t=calc(i);if(t<ans)ans=t;}
        printf("%d\n",ans);
    }
    return 0;
}