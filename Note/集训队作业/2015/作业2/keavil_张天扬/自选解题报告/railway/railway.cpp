/**************************************************************
    Problem: 2080
    User: keavil
    Language: C++
    Result: Accepted
    Time:440 ms
    Memory:7620 kb
****************************************************************/
 
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[100001],color[100001],stk[100001],top,pos[100001],suc[100001];
int fir[100001],to[300001],next[300001],sz;bool viewed[100001];
int stack1[100001],stack2[100001],top1,top2;
int fa[100001];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void merge(int x,int y){fa[get(x)]=get(y);}
void add(int x,int y)
{
    next[++sz]=fir[x];fir[x]=sz;to[sz]=y;
    next[++sz]=fir[y];fir[y]=sz;to[sz]=x;
}
void bfs(int x)
{
    static int q[100001];int l=0,r=0;q[++r]=x;viewed[x]=true;color[x]=0;
    while(l<r)
    {
        x=q[++l];
        for(int i=fir[x];i;i=next[i])
        if(!viewed[to[i]])
        {
            color[to[i]]=!color[x];
            viewed[to[i]]=true;
            q[++r]=to[i];
        }
        ++color[x];
    }
}
int main()
{
    scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]),pos[a[i]]=i;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=n;i++)
    {
        int p=pos[i];
        if(p!=n)merge(p,p+1);else fa[p]=0;
        if(get(p)!=p)suc[p]=get(p);
    }
    for(int i=n,last=n;i>=1;i--)
    {
        int p=pos[i];
        viewed[p]=true;
        if(p==last)
        {
            for(;last&&viewed[last];--last);
            continue;
        }
        for(;top&&stk[top]>p;--top)
        if(stk[top]<last)
            add(stk[top],p);
        stk[++top]=p;
        if(suc[p]&&suc[p]<last)add(suc[p],p);
    }
    memset(viewed,false,sizeof(viewed));
    for(int i=1;i<=n;i++)if(!viewed[i])bfs(i);
    int now=1;
    for(int i=1;i<=n;i++)
    {
        if(color[i]==1)stack1[++top1]=a[i];
        else stack2[++top2]=a[i];
        while(stack1[top1]==now||stack2[top2]==now)
        {
            if(stack1[top1]==now)--top1;
            else --top2;
            ++now;
        }
    }
    if(now<=n)printf("NIE\n");
    else
    {
        printf("TAK\n");
        for(int i=1;i<n;i++)
        printf("%d ",color[i]);printf("%d\n",color[n]);
    }
    return 0;
}