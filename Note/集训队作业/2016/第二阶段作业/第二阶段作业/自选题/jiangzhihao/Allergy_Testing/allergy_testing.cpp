#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const long long inf = 1e16;
long long n,a,b;
long long s[100],t[100];
int pre[100];
long long zuhe(long long x,long long y,long long z)
{
    int i,j,now,p;
    for(i=1;i<=z;i++)
    {
        s[i]=x-i+1;
        t[i]=y-i+1;
    }
    for(i=1;i<=z;i++)
    {
        now=i;
        while(now>1)
        {
            p=pre[now];
            for(j=1;s[j]%p;j++);
            s[j]/=p;
            for(j=1;t[j]%p;j++);
            t[j]/=p;
            now/=p;
        }
    }
    long double za=1,zb=1;
    for(i=1;i<=z;i++)
    {
        za*=s[i];
        zb*=t[i];
    }
    za-=zb;
    if(za>inf)
        return inf;
    long long ra=1,rb=1;
    for(i=1;i<=z;i++)
    {
        ra*=s[i];
        rb*=t[i];
    }
    ra-=rb;
    return ra;
}
long long getval(long long x)
{
    int i;
    long long res=0;
    for(i=0;b*i<=x;i++)
    {
        long long minz,maxz;
        if(x-b-b*i<0)
            minz=0;
        else
            minz=(x-b-b*i)/a+1;
        maxz=(x-b*i)/a;
        res+=zuhe(maxz+i+1,minz+i,i+1);
        if(res>inf)
            return inf;
    }
    return res;
}
long long erfen(long long l,long long r)
{
    if(l==r)
        return l;
    long long mid=(l+r)>>1;
    if(getval(mid)>=n)
        return erfen(l,mid);
    return erfen(mid+1,r);
}
void f()
{
    cin>>n>>a>>b;
    long long mz=0;
    long long now=1;
    while(now<n)
    {
        mz++;
        now<<=1;
    }
    mz*=b;
    long long r=erfen(0,mz);
    cout<<r<<endl;
}
int main()
{
    int T,i,j;
    cin>>T;
    for(i=2;i<=80;i++)
    {
        for(j=2;i%j;j++);
        pre[i]=j;
    }
    for(i=1;i<=T;i++)
    {
        cout<<"Case #"<<i<<": ";
        f();
    }
    return 0;
}
