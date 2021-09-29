/**************************************************************
    Problem: 2416
    User: keavil
    Language: C++
    Result: Accepted
    Time:896 ms
    Memory:3936 kb
****************************************************************/
 
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
int ran()
{
    static unsigned int PXPX=451263164;
    return (PXPX+=(PXPX<<2)+125515)&(~0u>>1);
}
long long gcd(long long x,long long y)
{return y?gcd(y,x%y):x;}
long long calc(long long n,long long a,long long b)
{
    if(!a||!n)return 0;
    if(a>=b)return calc(n,a%b,b)+(a/b*(n*(n+1)>>1));
    return n*(n*a/b)+n/(b/gcd(a,b))-calc(a*n/b,b,a);
}
long long getv(long long a,long long b,long long n)
{
    return ((n+1)*n>>1)*a-calc(n,a,b)*b;
}
long long make(long long a,long long b,long long l,long long r)
{
    /*long long ret=0;
    for(int p=l;p<=r;p++)ret+=a*p%b;
    return ret;*/
    if(l>r)return 0;
    long long ret=getv(a,b,r)-getv(a,b,l-1);
    return ret;
}
struct treap
{
    struct node
    {
        node*ls,*rs;int sz;long long a,b,l,r,v,sum,st,left,right;
        node(long long a1=0,long long b1=0,long long l1=0,long long r1=0,long long st1=0)
        :a(a1),b(b1),l(l1),r(r1),st(st1),sz(1),left(l1),right(r1)
        {
            sum=v=make(a,b,l-st+1,r-st+1);
            ls=rs=NULL;
        }
        void maintain()
        {
            sum=(ls?ls->sum:0)+(rs?rs->sum:0)+v;
            sz=(ls?ls->sz:0)+(rs?rs->sz:0)+1;
            left=ls?ls->left:l;
            right=rs?rs->right:r;
        }
    };
    node*root;
    node*merge(node*lrt,node*rrt)
    {
        if(!lrt)return rrt;if(!rrt)return lrt;
        if(ran()%(lrt->sz+rrt->sz)<lrt->sz){lrt->rs=merge(lrt->rs,rrt);lrt->maintain();return lrt;}
        else{rrt->ls=merge(lrt,rrt->ls);rrt->maintain();return rrt;}
    }
    pair<node*,node*>split_l(node*rt,int L)
    {
        if(!rt)return pair<node*,node*>(NULL,NULL);
        pair<node*,node*>q;
        if(rt->l<=L){q=split_l(rt->rs,L);rt->rs=q.first;q.first=rt;}
        else {q=split_l(rt->ls,L);rt->ls=q.second;q.second=rt;}
        rt->maintain();return q;
    }
    pair<node*,node*>split_r(node*rt,int R)
    {
        if(!rt)return pair<node*,node*>(NULL,NULL);
        pair<node*,node*>q;
        if(rt->r<=R){q=split_r(rt->rs,R);rt->rs=q.first;q.first=rt;}
        else {q=split_r(rt->ls,R);rt->ls=q.second;q.second=rt;}
        rt->maintain();return q;
    }
    void dfs_l(node*rt,int R)
    {
        if(rt->rs)
        {
            dfs_l(rt->rs,R);
            rt->maintain();
        }
        else
        {
            if(rt->r>R){rt->r=R;rt->v=make(rt->a,rt->b,rt->l-rt->st+1,rt->r-rt->st+1);}
            rt->maintain();
        }
    }
    void dfs_r(node*rt,int L)
    {
        if(rt->ls)
        {
            dfs_r(rt->ls,L);
            rt->maintain();
        }
        else
        {
            if(rt->l<L){rt->l=L;rt->v=make(rt->a,rt->b,rt->l-rt->st+1,rt->r-rt->st+1);}
            rt->maintain();
        }   
    }
    node*dfs_special(node*rt,int l,int r)
    {
        if(rt->ls)
        {
            node*ret=dfs_special(rt->ls,l,r);
            rt->maintain();
            return ret;
        }
        else
        {
            if(l<=rt->l)return NULL;
            node*ret=new node(rt->a,rt->b,rt->l,l-1,rt->st);
            rt->l=r+1;rt->v=make(rt->a,rt->b,rt->l-rt->st+1,rt->r-rt->st+1);
            rt->maintain();
            return ret;
        }
    }
    long long dfs(node*rt,long long l,long long r)
    {
        if(!rt)return 0;
        if(rt->left>=l&&rt->right<=r)return rt->sum;
        if(rt->left>r||rt->right<l)return 0;
        long long ret=dfs(rt->ls,l,r)+dfs(rt->rs,l,r);
        if(l<=rt->l&&r>=rt->r)ret+=rt->v;
        else ret+=make(rt->a,rt->b,max(rt->l,l)-rt->st+1,min(rt->r,r)-rt->st+1);
        return ret;
    }
    void insert(long long l,long long r,long long a,long long b)
    {
        node*nert=new node(a,b,l,r,l);
        pair<node*,node*>p,q;
        p=split_r(root,r);q=split_l(p.first,l-1);
        if(p.second){node*t=dfs_special(p.second,l,r);if(t)nert=merge(t,nert);}
        if(q.first)dfs_l(q.first,l-1);if(p.second)dfs_r(p.second,r+1);
        root=merge(merge(q.first,nert),p.second);
    }
    long long ask(long long l,long long r)
    {
        return dfs(root,l,r);
    }
}M;
int main()
{
    int q;scanf("%d%d",&q,&q);
    while(q--)
    {
        int type,l,r,a,b;
        scanf("%d%d%d",&type,&l,&r);
        if(type==1)
        {
            scanf("%d%d",&a,&b);a%=b;
            M.insert(l,r,a,b);
        }
        else printf("%lld\n",M.ask(l,r));
    }
    return 0;
}