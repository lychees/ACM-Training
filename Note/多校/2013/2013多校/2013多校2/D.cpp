#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <math.h>
using namespace std;
const int MAXN = 50010;
struct Node
{
    int l,r;
    int sum;
    int lazy;
    int first;
    int last;
}segTree[MAXN*3];
void push_up(int i)
{
    if(segTree[i].l==segTree[i].r)return;
    segTree[i].sum = segTree[i<<1].sum+segTree[(i<<1)|1].sum;
    if(segTree[i<<1].first != -1)segTree[i].first = segTree[i<<1].first;
    else segTree[i].first = segTree[(i<<1)|1].first;
    if(segTree[(i<<1)|1].last != -1)segTree[i].last = segTree[(i<<1)|1].last;
    else segTree[i].last = segTree[(i<<1)].last;
}
void push_down(int i)
{
    if(segTree[i].r == segTree[i].l)return;
    if(segTree[i].lazy==1)
    {
        segTree[i<<1].first = segTree[i<<1].l;
        segTree[i<<1].last = segTree[i<<1].r;
        segTree[i<<1].sum = segTree[i<<1].r-segTree[i<<1].l+1;
        segTree[i<<1].lazy=1;
        segTree[(i<<1)|1].first = segTree[(i<<1)|1].l;
        segTree[(i<<1)|1].last = segTree[(i<<1)|1].r;
        segTree[(i<<1)|1].sum = segTree[(i<<1)|1].r-segTree[(i<<1)|1].l+1;
        segTree[(i<<1)|1].lazy=1;
    }
    if(segTree[i].lazy == -1)
    {
        segTree[i<<1].first = -1;
        segTree[i<<1].last = -1;
        segTree[i<<1].sum = 0;
        segTree[i<<1].lazy=-1;
        segTree[(i<<1)|1].first = -1;
        segTree[(i<<1)|1].last = -1;
        segTree[(i<<1)|1].sum = 0;
        segTree[(i<<1)|1].lazy=-1;
    }
    segTree[i].lazy = 0;
}
void build(int i,int l,int r)
{
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].sum = r-l+1;
    segTree[i].lazy = 0;
    segTree[i].first = l;
    segTree[i].last = r;
    if(l==r)return ;
    int mid = (l+r)/2;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}
void update(int i,int l,int r,int type)
{
    if(segTree[i].l == l && segTree[i].r==r)
    {
        if(type == 0)
        {
            if(segTree[i].sum == 0)return;
            segTree[i].sum = 0;
            segTree[i].lazy = -1;
            segTree[i].first = -1;
            segTree[i].last = -1;
            return;
        }
        else if(type == 1)
        {
            if(segTree[i].sum == segTree[i].r-segTree[i].l+1)return;
            segTree[i].sum = segTree[i].r-segTree[i].l+1;
            segTree[i].lazy = 1;
            segTree[i].first = segTree[i].l;
            segTree[i].last = segTree[i].r;
            return;
        }

    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r)/2;
    if(r <= mid)update(i<<1,l,r,type);
    else if(l > mid)update((i<<1)|1,l,r,type);
    else
    {
        update(i<<1,l,mid,type);
        update((i<<1)|1,mid+1,r,type);
    }
    push_up(i);
}
int sum(int i,int l,int r)
{
    if(segTree[i].l == l && segTree[i].r == r)
    {
        return segTree[i].sum;
    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r)/2;
    if(r <= mid)return sum(i<<1,l,r);
    else if(l > mid)return sum((i<<1)|1,l,r);
    else return sum((i<<1)|1,mid+1,r)+sum(i<<1,l,mid);
}
int n,m;
int query1(int i,int l,int r)
{
    if(segTree[i].l == l && segTree[i].r == r)
    {
        return segTree[i].first;
    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r)/2;
    int ans1,ans2;
    if(r <= mid)return query1(i<<1,l,r);
    else if(l > mid)return query1((i<<1)|1,l,r);
    else
    {
        ans1 = query1(i<<1,l,mid);
        if(ans1 != -1)return ans1;
        return query1((i<<1)|1,mid+1,r);
    }
}
int query2(int i,int l,int r)
{
    if(segTree[i].l == l && segTree[i].r == r)
    {
        return segTree[i].last;
    }
    push_down(i);
    int mid = (segTree[i].l + segTree[i].r)/2;
    int ans1,ans2;
    if(r <= mid)return query2(i<<1,l,r);
    else if(l > mid)return query2((i<<1)|1,l,r);
    else
    {
        ans1 = query2((i<<1)|1,mid+1,r);
        if(ans1 != -1)return ans1;
        return query2(i<<1,l,mid);
    }
}
int bisearch(int A,int F)
{
    if(sum(1,A,n)==0)return -1;
    if(sum(1,A,n)<F)return n;
    int l= A,r = n;
    int ans=A;
    while(l<=r)
    {
        int mid = (l+r)/2;
        if(sum(1,A,mid)>=F)
        {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        build(1,1,n);
        int op,u,v;
        while(m--)
        {
            scanf("%d%d%d",&op,&u,&v);
            if(op == 1)
            {
                u++;
                int t = bisearch(u,v);
                //printf("t:%d\n",t);
                if(t==-1)
                {
                    printf("Can not put any one.\n");
                    continue;
                }
                printf("%d %d\n",query1(1,u,t)-1,query2(1,u,t)-1);
                update(1,u,t,0);
            }
            else
            {
                u++;v++;
                //printf("sum:%d\n",sum(1,u,v));
                printf("%d\n",v-u+1-sum(1,u,v));
                update(1,u,v,1);
            }
        }
        printf("\n");
    }
    return 0;
}







