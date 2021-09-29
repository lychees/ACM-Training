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
#include <vector>
#include <list>
using namespace std;
 
const double eps=0.8;
const long long maxl=(1 << 27)-1;
const long long maxw=(1 << 20)-1;
const int maxn=200000+15;
struct Trie
{
    int root;
    int l,r,hav,dep;
    int clear()
    {
        root=l=r=hav=dep=0;
        return 0;
    }
}trie[maxn*28];
int tot,poot[maxn*28];
int root;
struct Node
{
    int wid[2],l,r,sum;
    int clear()
    {
        wid[0]=wid[1]=l=r=sum=0;
        return 0;
    }
}pp[maxn*28*2];
int top,poop[maxn*28*2];
int n,m;
int a[maxn];
int prebit[maxw];
int rect(int x)
{
    trie[x].clear();
    poot[++tot]=x;
    return 0;
}
int recp(int x)
{
    pp[x].clear();
    poop[++top]=x;
    return 0;
}
int merge(int r1,int r2)
{
    if (r1==0 && r2==0) return 0;
    if (r1==0) swap(r1,r2);
    int root=poop[top--];
    if (r2==0)
    {
        pp[root]=pp[r1];
        pp[root].l=merge(pp[root].l,0);
        pp[root].r=merge(pp[root].r,0);
        return root;
    }
    if (pp[r1].wid[0]==pp[r2].wid[0] && pp[r1].wid[1]==pp[r2].wid[1])
    {
        pp[root]=pp[r1];
        pp[root].sum+=pp[r2].sum;
        pp[root].l=merge(pp[r1].l,pp[r2].l);
        pp[root].r=merge(pp[r1].r,pp[r2].r);
        return root;
    }
    if (pp[r1].wid[1]-pp[r1].wid[0]<pp[r2].wid[1]-pp[r2].wid[0]) swap(r1,r2);
    if (pp[r1].wid[0]<=pp[r2].wid[0] && pp[r1].wid[1]>=pp[r2].wid[1])
    {
        pp[root]=pp[r1];
        pp[root].sum+=pp[r2].sum;
        int mid=(pp[r1].wid[0]+pp[r1].wid[1])>>1;
        if (pp[r2].wid[1]<=mid)
        {
            pp[root].l=merge(pp[root].l,r2);
            pp[root].r=merge(pp[root].r,0);
        }
        else
        {
            pp[root].l=merge(pp[root].l,0);
            pp[root].r=merge(pp[root].r,r2);
        }
        return root;
    }
    int upp=prebit[pp[r1].wid[0]^pp[r2].wid[0]];
    pp[root].wid[0]=pp[root].wid[1]=(pp[r1].wid[0]/upp/2)*upp*2;
    pp[root].wid[1]+=upp*2-1;
    pp[root].sum=pp[r1].sum+pp[r2].sum;
    if (pp[r1].wid[0]&upp) swap(r1,r2);
    pp[root].l=merge(r1,0);
    pp[root].r=merge(r2,0);
    return root;
}
long double pwson[35],pwfa[35];
int inser(int root,int l,int r,int x)
{
    if (l>x || r<x) return root;
    if (root==0)
    {
        root=poop[top--];
        pp[root].wid[0]=pp[root].wid[1]=x;
        pp[root].sum=1;
        return root;
    }
    if (pp[root].wid[0]>x || pp[root].wid[1]<x)
    {
        int lroot=root;
        root=poop[top--];
        pp[root].sum=pp[lroot].sum+1;
        int xj=prebit[pp[lroot].wid[0]^x];
        pp[root].wid[0]=pp[root].wid[1]=(x/xj/2)*xj*2;
        pp[root].wid[1]+=2*xj-1;
        int mid=(pp[root].wid[0]+pp[root].wid[1])>>1;
        if (x>mid)
        {
            pp[root].l=lroot;
            pp[root].r=inser(pp[root].r,x,x,x);
        }
        else
        {
            pp[root].r=lroot;
            pp[root].l=inser(pp[root].l,x,x,x);
        }
        return root;
    }
    pp[root].sum++;
    if (l==r) return root;
    int mid=(l+r)>>1;
    if (pp[root].wid[0]==l && pp[root].wid[1]==r)
    {
        pp[root].l=inser(pp[root].l,l,mid,x);
        pp[root].r=inser(pp[root].r,mid+1,r,x);
        return root;
    }
    pp[root].sum--;
    return inser(root,pp[root].wid[0],pp[root].wid[1],x);
}
int build(int root,int dep,int l,int r,int x,int y)
{
    if (x>y) return 0;
    root=poot[tot--];
    trie[root].hav=y-x+1;
    trie[root].dep=dep;
    if (l==r)
    {
        trie[root].root=inser(trie[root].root,0,maxw,a[x]);
        return root;
    }
    int mid=(l+r)>>1;
    int md=(x+y-1)>>1;
    trie[root].l=build(trie[root].l,dep-1,l,mid,x,md);
    trie[root].r=build(trie[root].r,dep-1,mid+1,r,md+1,y);
    trie[root].root=merge(trie[trie[root].l].root,trie[trie[root].r].root);
    return root;
}
int topp,fg,fx;
int ins(int root,int l,int r,int x,int y)
{
    if (l+1==r)
    {
        int aa=1;
    }
    trie[root].root=inser(trie[root].root,0,maxw,y);
    trie[root].hav++;
    if (l+1==r)
    {
        trie[root].l=poot[tot--];
        trie[trie[root].l].hav++;
        trie[trie[root].l].dep=trie[root].dep-1;
        trie[trie[root].l].root=inser(trie[trie[root].l].root,0,maxw,y);
        return root;
    }
    int mid=(l+r)>>1;
    int ss=trie[trie[root].l].hav;
    if (ss>=x)
    {
        trie[root].l=ins(trie[root].l,l,mid,x,y);
        int ls=trie[root].l;
        if (trie[ls].hav*pwfa[trie[ls].dep]>(mid-l+1)*pwson[trie[ls].dep]) topp=root;
        if (topp==ls) fg=root,fx=0; 
            else if (topp==root) fg=0;
        return root;
    }
    trie[root].r=ins(trie[root].r,mid+1,r,x-ss,y);
    int ls=trie[root].r;
    if (trie[ls].hav*pwfa[trie[ls].dep]>(r-mid)*pwson[trie[ls].dep]) topp=root;
    if (topp==ls) fg=root,fx=1; 
        else if (topp==root) fg=0;
    return root;
}
int sz;
int del(int root,int x)
{
    if (root==0 || pp[root].wid[0]>x || pp[root].wid[1]<x) return root;
    pp[root].sum--;
    pp[root].l=del(pp[root].l,x);
    pp[root].r=del(pp[root].r,x);
    if (pp[root].sum==0)
    {
        recp(root);
        return 0;
    }
    if (pp[root].sum==pp[pp[root].l].sum)
    {
        int ls=pp[root].l;
        recp(root);
        return ls;
    }
    if (pp[root].sum==pp[pp[root].r].sum)
    {
        int ls=pp[root].r;
        recp(root);
        return ls;
    }
    return root;
}
int delet(int root,int l,int r,int x)
{
    trie[root].hav--;
    if (l==r)
    {
        sz=pp[trie[root].root].wid[0];
        recp(trie[root].root);
        rect(root);
        return 0;
    }
    int mid=(l+r)>>1;
    int ss=trie[trie[root].l].hav;
    if (ss>=x) trie[root].l=delet(trie[root].l,l,mid,x);
        else trie[root].r=delet(trie[root].r,mid+1,r,x-ss);
    trie[root].root=del(trie[root].root,sz);
    if (trie[root].hav==0)
    {
        rect(root);
        return 0;
    }
    return root;
}
int change(int root,int l,int r,int x,int y)
{
    if (l==r)
    {
        sz=pp[trie[root].root].wid[0];
        recp(trie[root].root);
        trie[root].root=inser(0,0,maxl,y);
        return root;
    }
    int mid=(l+r)>>1;
    int ss=trie[trie[root].l].hav;
    if (ss>=x) trie[root].l=change(trie[root].l,l,mid,x,y);
        else trie[root].r=change(trie[root].r,mid+1,r,x-ss,y);
    trie[root].root=del(trie[root].root,sz);
    trie[root].root=inser(trie[root].root,0,maxl,y);
    return root;
}
int sum;
int resep(int root)
{
    if (root==0) return 0;
    resep(pp[root].l);
    resep(pp[root].r);
    recp(root);
    return 0;
}
int reset(int root)
{
    if (root==0) return 0;
    if (trie[root].dep==0)
    {
        a[sum++]=pp[trie[root].root].wid[0];
        resep(trie[root].root);
        rect(root);
        return 0;
    }
    resep(trie[root].root);
    reset(trie[root].l);
    reset(trie[root].r);
    rect(root);
    return 0;
}
int sumrot,rot1[60],rot2[60];
int ask(int root,int x,int y)
{
    if (trie[root].hav==0) return 0;
    if (trie[root].hav==y-x+1) 
    {
        rot1[++sumrot]=trie[root].root;
        return 0;
    }
    int ss=trie[trie[root].l].hav;
    if (ss>=x) ask(trie[root].l,x,min(y,ss));
    if (y>ss) ask(trie[root].r,max(1,x-ss),y-ss);
    return 0;
}
int foundsec()
{
    int ans=0;
    int sd=2;
    int ll=0,rr=maxw,mid;
    for (int i=19;i>=0;i--)
    {
        int ss=0;
        mid=(ll+rr)>>1;
        for (int j=1;j<=sumrot;j++)
        {
            if (pp[rot1[j]].wid[0]==ll && pp[rot1[j]].wid[1]==rr)
                ss+=pp[pp[rot1[j]].r].sum;
            else
            if (pp[rot1[j]].wid[0]>mid)
                ss+=pp[rot1[j]].sum;
        }
        if (ss>=sd)
        {
            ans+=1 << i;
            for (int j=1;j<=sumrot;j++)
            {
                if (pp[rot1[j]].wid[0]==ll && pp[rot1[j]].wid[1]==rr)   rot1[j]=pp[rot1[j]].r;
                else
                if (pp[rot1[j]].wid[1]<=mid) rot1[j]=0;
            }
            ll=mid+1;
        }
        else
        {
            sd-=ss;
            for (int j=1;j<=sumrot;j++)
            {
                if (pp[rot1[j]].wid[0]==ll && pp[rot1[j]].wid[1]==rr)   rot1[j]=pp[rot1[j]].l;
                else
                if (pp[rot1[j]].wid[0]>mid) rot1[j]=0;
            }
            rr=mid;
        }
    }
    return ans;
}
int foundans(int sec)
{
    int ans=0;
    int ll=0,rr=maxw,mid,chel,cher;
    for (int i=19;i>=0;i--)
    {
        int ss=0;
        mid=(ll+rr)>>1;
        if (sec&(1 << i)) chel=ll,cher=mid;
            else chel=mid+1,cher=rr;
        for (int j=1;j<=sumrot && ss==0;j++)
        {
            if (pp[rot2[j]].wid[0]==ll && pp[rot2[j]].wid[1]==rr)
                if (sec&(1 << i)) ss+=pp[pp[rot2[j]].l].sum;
                    else ss+=pp[pp[rot2[j]].r].sum;
            else if (chel<=pp[rot2[j]].wid[0] && pp[rot2[j]].wid[1]<=cher) ss+=pp[rot2[j]].sum;
        }
        if (ss>0)
        {
            ans+=1 << i;
            for (int j=1;j<=sumrot;j++)
            {
                if (pp[rot2[j]].wid[0]==ll && pp[rot2[j]].wid[1]==rr)
                    if (sec&(1 << i)) rot2[j]=pp[rot2[j]].l;
                        else rot2[j]=pp[rot2[j]].r;
                else if (!(chel<=pp[rot2[j]].wid[0] && pp[rot2[j]].wid[1]<=cher)) rot2[j]=0;
            }
            ll=chel;rr=cher;
        }
        else
        {
            for (int j=1;j<=sumrot;j++)
            {
                if (pp[rot2[j]].wid[0]==ll && pp[rot2[j]].wid[1]==rr)
                    if (sec&(1 << i)) rot2[j]=pp[rot2[j]].r;
                        else rot2[j]=pp[rot2[j]].l;
                else if (chel<=pp[rot2[j]].wid[0] && pp[rot2[j]].wid[1]<=cher) rot2[j]=0;
            }
            ll=ll+mid+1-chel;
            rr=mid+rr-cher;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    prebit[0]=0;
    prebit[1]=1;
    pwson[0]=1;
    pwfa[0]=1;
    for (int i=1;i<=27;i++) pwson[i]=pwson[i-1]*4,pwfa[i]=pwfa[i-1]*5;
    for (int i=2;i<=maxw;i++) prebit[i]=prebit[i>>1]<<1;
    for (int i=1;i<=(n+m)*28;i++) poot[i]=i;
    tot=(n+m)*28;
    for (int i=1;i<=(n+m)*28*2;i++) poop[i]=i;
    top=(n+m)*28*2;
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    root=build(root,27,0,maxl,1,n);
    int ss=n;
    int lastans=0;
    while (m--)
    {
        char od[2];
        scanf("%s",od);
        if (od[0]=='I')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x=(x+lastans)%ss;
            y=(y+lastans)&maxw;
            fg=0;
            root=ins(root,0,maxl,x+1,y);
            int dd=trie[topp].dep;
            int ll=0,rr=(1 << dd)-1;
            sum=1;
            reset(topp);
            sum--;
            if (fg==0)  root=build(0,27,0,maxl,1,sum);
                else
                {
                    if (fx==0)
                        trie[fg].l=build(0,dd,ll,rr,1,sum);
                    else
                        trie[fg].r=build(0,dd,ll,rr,1,sum);
                }
            ss++;
        }
        else
        if (od[0]=='D')
        {
            int x;
            scanf("%d",&x);
            x=(x+lastans)%ss;
            root=delet(root,0,maxl,x+1);
            ss--;
        }
        else
        if (od[0]=='C')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            x=(x+lastans)%ss;
            y=(y+lastans)&maxw;
            root=change(root,0,maxl,x+1,y);
        }
        else
        if (od[0]=='F')
        {
            int l,r;
            scanf("%d%d",&l,&r);
            l=(l+lastans)%ss;
            r=(r+lastans)%ss;
            if (l>r) swap(l,r);
            sumrot=0;
            ask(root,l+1,r+1);
            memcpy(rot2,rot1,sizeof(rot1));
            int sec=foundsec();
            lastans=foundans(sec);
            printf("%d\n",lastans);
        }
    }
    return 0;
}
