#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=100003;
int n,Q;
struct node
{
    int l,r,v;
    node(){}
    node(int _l,int _r,int _v){l=_l,r=_r,v=_v;}
}s[22];
inline node operator +(const node &a,const node &b){return node(a.l,b.r,a.v+b.v);}
inline bool operator <(const node &a,const node &b){return a.v<b.v;}
struct Ttree
{
    node maxr,maxl,maxs,minr,minl,mins,sum;
    bool rev;
    inline void init(int l,int v)
    {
        maxl=maxr=maxs=minr=minl=mins=sum=node(l,l,v);
        rev=0;
    }
}tree[maxn*4];
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
#define min(a,b) ((a)<(b))?(a):(b)
#define max(a,b) ((b)<(a))?(a):(b)
inline void pushup(int p)
{
    int l=p*2,r=p*2+1;
    tree[p].minl=min(tree[l].minl,tree[l].sum+tree[r].minl);
    tree[p].minr=min(tree[r].minr,tree[l].minr+tree[r].sum);
    tree[p].mins=min(min(tree[l].mins,tree[r].mins),tree[l].minr+tree[r].minl);
    tree[p].maxl=max(tree[l].maxl,tree[l].sum+tree[r].maxl);
    tree[p].maxr=max(tree[r].maxr,tree[l].maxr+tree[r].sum);
    tree[p].maxs=max(max(tree[l].maxs,tree[r].maxs),tree[l].maxr+tree[r].maxl);
    tree[p].sum=tree[l].sum+tree[r].sum;
    tree[p].rev=0;
}
inline void _swap(node &a,node &b)
{
    a.v*=-1,b.v*=-1;
    swap(a,b);
}
inline void reverse(int p)
{
    _swap(tree[p].minr,tree[p].maxr);
    _swap(tree[p].minl,tree[p].maxl);
    _swap(tree[p].mins,tree[p].maxs);
    tree[p].sum.v*=-1; tree[p].rev^=1;
}
inline void pushdown(int p)
{
    if(tree[p].rev)tree[p].rev=0,reverse(p*2),reverse(p*2+1);
}
inline Ttree merge(const Ttree &a,const Ttree &b)
{
    Ttree c;
    c.maxs=max(max(a.maxs,b.maxs),a.maxr+b.maxl);
    c.maxl=max(a.maxl,a.sum+b.maxl);
    c.maxr=max(b.maxr,a.maxr+b.sum);
    return c;
}
inline void Build(int p,int l,int r)
{
    if(l==r){tree[p].init(l,get());return;}
    int mid=(l+r)/2;
    Build(p*2,l,mid),Build(p*2+1,mid+1,r);
    pushup(p);
}
inline Ttree Ask(int p,int l,int r,int a,int b)
{
    if(a<=l&&r<=b)return tree[p];
    pushdown(p);
    int mid=(l+r)/2;
    if(b<=mid)return Ask(p*2,l,mid,a,b);
    else if(a>mid)return Ask(p*2+1,mid+1,r,a,b);
    else return merge(Ask(p*2,l,mid,a,b),Ask(p*2+1,mid+1,r,a,b));
}
inline void Reverse(int p,int l,int r,int a,int b)
{
    if(a<=l&&r<=b){reverse(p);return;}
    pushdown(p);
    int mid=(l+r)/2;
    if(a<=mid)Reverse(p*2,l,mid,a,b);
    if(b>mid)Reverse(p*2+1,mid+1,r,a,b);
    pushup(p);
}
inline void Change(int p,int l,int r,int pos,int v)
{
    if(l==r){tree[p].init(l,v);return;}
    pushdown(p);
    int mid=(l+r)/2;
    if(pos<=mid)Change(p*2,l,mid,pos,v);else Change(p*2+1,mid+1,r,pos,v);
    pushup(p);
}
int main()
{
    n=get();
    Build(1,1,n);
    Q=get();
    while(Q--)
    {
        int type=get();
        if(type)
        {
            int l=get(),r=get(),k=get(),tot=0,ans=0;
            while(tot<k)
            {
                Ttree res=Ask(1,1,n,l,r);
                if(res.maxs.v<=0)break;
                s[++tot]=res.maxs,ans+=s[tot].v;
                Reverse(1,1,n,s[tot].l,s[tot].r);
            }
            printf("%d\n",ans);
            for(int i=1;i<=tot;i++)Reverse(1,1,n,s[i].l,s[i].r);
        }else
        {
            int pos=get(),a=get();
            Change(1,1,n,pos,a);
        }
    }
    return 0;
}
