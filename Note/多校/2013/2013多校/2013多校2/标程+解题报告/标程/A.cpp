#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>
#include<stdlib.h>
using namespace std;
typedef __int64 int64;
int x[100000],y[100000];
int64 a[100005],a2[100005];
int b[100005],b2[100005],c[100005];
int t1[100005],t2[100005];
int m,z;
bool d[100000];
int cur;
inline int lowbit(int x)
{
    return x&(-x);
}
void initAB(int m)
{
    int i,j;
    for (i=t1[m];i<t2[m];i++)
    {
        j=i;
        if (j-t1[m]==0)
        {
            a[j]+=c[j];
            b[j]++;
        }
        else
        {
            while (j<t2[m])
            {
                a[j]+=c[i];
                b[j]++;
                j+=lowbit(j-t1[m]);
            }
        }
    }
    return;
}
int64 cal3(int x,int y)
{
    int64 s,temp;
    int k,yy;
    yy=y;
    s=0;
    temp=a[t1[x]];
    k=b[t1[x]];
    while (y>t1[x])
    {
        temp+=a[y];
        k+=b[y];
        y-=lowbit(y-t1[x]);
    }
    s+=temp-(int64)cur*k;
    temp=a2[t1[x]];
    k=b2[t1[x]];
    y=yy;
    while (y>t1[x])
    {
        temp+=a2[y];
        k+=b2[y];
        y-=lowbit(y-t1[x]);
    }
    s+=(int64)cur*k-temp;
    return s;
}
int64 cal2(int x,int l,int r)
{
    if (l==t1[x])
        return cal3(x,r);
    else
        return cal3(x,r)-cal3(x,l-1);
}
int64 cal(int x,int y,int n)
{
    int64 s;
    int k;
    if (y+n<=t2[x])
        return cal2(x,y,y+n-1);
    else
    {
        s=cal2(x,y,t2[x]-1);
        n-=t2[x]-y;
        y=t1[x];
        k=n/(t2[x]-t1[x]);
        if (k>0)
        {
            s+=cal2(x,t1[x],t2[x]-1)*k;
            n%=(t2[x]-t1[x]);
        }
        if (n>0)
            s+=cal2(x,t1[x],t1[x]+n-1);
        return s;
    }
}
int main()
{
    int t,N,A,B,i,j,k,u;
    int64 s;
    cin>>t;
    assert(1<=t&&t<=50);
    while (t>0)
    {
        t--;
        cin>>N>>A>>B;
        assert(1<=N&&N<=1000000000);
        assert(1<=A&&A<=100000);
        assert(1<=B&&B<=100000);
        if (A>N)
            A=N;
        if (B>N)
            B=N;
        m=0;
        memset(d,0,sizeof(d));
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(a2,0,sizeof(a2));
        memset(b2,0,sizeof(b2));
        z=0;
        for (i=0;i<B;i++)
        {
            if (d[i]==0)
            {
                j=i;
                t1[m]=z;
                while (d[j]==0)
                {
                    d[j]=1;
                    x[j]=m;
                    y[j]=z;
                    c[z]=j;
                    j=(j+A)%B;
                    z++;
                }
                t2[m]=z;
                m++;
            }
        }
        for (i=0;i<m;i++)
            initAB(i);
        s=0;
        for (i=0;i<A;i++)
        {
            cur=i;
            j=i%B;
            k=N/A;
            if (N%A>i)
                k++;
            s+=cal(x[j],y[j],k);
            u=x[j];
            j=y[j];
            if (i>=B)
                continue;
            if (j-t1[u]==0)
            {
                a[j]-=c[j];
                b[j]--;
                a2[j]+=c[j];
                b2[j]++;
            }
            else
            {
                k=j;
                while (k<t2[u])
                {
                    a[k]-=c[j];
                    b[k]--;
                    a2[k]+=c[j];
                    b2[k]++;
                    k+=lowbit(k-t1[u]);
                }
            }
        }
        cout<<s<<endl;
    }
    return 0;
}
