#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=200003;
int n,m,f[maxn],L[maxn],R[maxn],a[maxn],b[maxn],s[maxn],front,rear;
struct data
{
    int l,r;
    inline bool operator <(const data &b)const{return l<b.l;}
}g[maxn];
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
int main()
{
    n=get(),m=get();
    for(int i=1;i<=n+1;i++)R[i]=n+1;
    for(int i=1;i<=m;i++)
    {
        int a=get(),b=get();
        L[b]=max(L[b],a);R[b]=min(R[b],a);
    }
    for(int i=n;i>=1;i--)R[i]=min(R[i],R[i+1]);
    for(int i=2;i<=n;i++)L[i]=max(L[i],L[i-1]);
    front=1,rear=1;s[front]=0;
    for(int i=1,pre=0;i<=n+1;i++)
    {
        int m1=L[i-1],m2=min(R[i],i)-1;
        if(m1>m2){f[i]=-1;continue;}
        for(int j=pre+1;j<=m2;j++)
        {
            if(f[j]==-1)continue;
            while(front<=rear&&f[s[rear]]<f[j])rear--;
            s[++rear]=j;
        }
        pre=max(pre,m2);
        while(front<=rear&&s[front]<m1)front++;
        if(front>rear)f[i]=-1;else f[i]=f[s[front]]+1;
    }
    if(f[n+1]==-1)puts("-1");else printf("%d\n",f[n+1]-1);
    return 0;
}
