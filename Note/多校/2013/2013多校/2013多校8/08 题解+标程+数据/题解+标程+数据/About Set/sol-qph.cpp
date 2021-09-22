#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;
const int N=110010;
const int INF=2000000000;
struct Treap
{
    int val,fix;
    int size,G,ID;
    Treap *L,*R;
    Treap()
    {
        L=NULL;R=NULL;
    }
    int L_size()
    {
        return (L==NULL)?0:L->size;
    }
    int R_size()
    {
        return (R==NULL)?0:R->size;
    }
}*rot[N];
int Val[N],set[N];
int now=0;
int gcd(int a,int b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
void Treap_Up(Treap* &rot)
{
    if(rot==NULL)return;
    rot->size=rot->L_size()+rot->R_size()+1;
    int ret=rot->val;
    if(rot->L!=NULL)
        ret=gcd(ret, rot->L->G);
    if(rot->R!=NULL)
        ret=gcd(ret, rot->R->G);
    rot->G=ret;
}
void Treap_L_Rotate(Treap* &rot)
{
    Treap* tmp=rot->R;
    rot->R=tmp->L;
    tmp->L=rot;
    Treap_Up(rot);
    rot=tmp;
    Treap_Up(rot);
}
void Treap_R_Rotate(Treap* &rot)
{
    Treap* tmp=rot->L;
    rot->L=tmp->R;
    tmp->R=rot;
    Treap_Up(rot);
    rot=tmp;
    Treap_Up(rot);
}
void Treap_Insert(Treap* &rot, int val,  int ID)
{
    if(rot==NULL)
    {
        rot=new Treap();
        rot->val=val;rot->fix=rand();rot->G=val;rot->ID=ID;
        rot->size=1;
        return;
    }
    if(val<rot->val || (val==rot->val && ID<rot->ID))
    {
        Treap_Insert(rot->L, val, ID);
        Treap_Up(rot);
        if(rot->L->fix < rot->fix)
            Treap_R_Rotate(rot);
    }
    else
    {
        Treap_Insert(rot->R, val, ID);
        Treap_Up(rot);
        if(rot->R->fix<rot->fix)
            Treap_L_Rotate(rot);
    }
}
void Treap_Delete(Treap* &rt, int val,int ID)
{
    if(rt==NULL)
        return;
    if(val==rt->val && rt->ID==ID)
    {
        if(rt->L==NULL||rt->R==NULL)
        {
            Treap* tmp=rt;
            if(rt->L==NULL)
                rt=rt->R;
            else
                rt=rt->L;
            delete tmp;
        }
        else
        {
            if(rt->L->fix<rt->R->fix)
            {
                Treap_R_Rotate(rt);
                Treap_Delete(rt->R, val, ID);
            }
            else
            {
                Treap_L_Rotate(rt);
                Treap_Delete(rt->L, val, ID);
            }
        }
    }
    else if(val<rt->val || (val==rt->val && ID<rt->ID))
        Treap_Delete(rt->L, val, ID);
    else
        Treap_Delete(rt->R, val, ID);
    Treap_Up(rt);
}
int Treap_Succ(Treap* rot, int val, int opt)
{
    if(rot==NULL)
        return opt;
    if(rot->val >= val)
        return Treap_Succ(rot->L, val, rot->val);
    else
        return Treap_Succ(rot->R, val, opt);
}
void Treap_clear(Treap* &rot)
{
    if(rot==NULL)
        return;
    Treap_clear(rot->L);
    Treap_clear(rot->R);
    delete rot;
}
void Treap_Union(Treap* &rot1, Treap* &rot2, int ID)
{
    if(rot1==NULL)
        return;
    Treap_Union(rot1->L, rot2, ID);
    Treap_Union(rot1->R, rot2, ID);
    Treap_Insert(rot2, rot1->val, rot1->ID);
    set[rot1->ID]=ID;
//    delete rot1;
    rot1=NULL;
}
void Treap_GCD(Treap* rot, int l, int r, int &ans)
{
    if(rot==NULL)
        return;
    if( l<=rot->val && rot->val<=r )
    {
        if(ans!=-1)
            ans=gcd(ans, rot->val);
        else
            ans=rot->val;
        if(l==-1)
        {
            if(rot->L!=NULL)
                ans=gcd(ans, rot->L->G);
            if(rot->R!=NULL)
                Treap_GCD(rot->R, l, r, ans);
        }
        else if(r>=INF)
        {
            if(rot->R!=NULL)
                ans=gcd(ans, rot->R->G);
            if(rot->L!=NULL)
                Treap_GCD(rot->L, l, r, ans);
        }
        else
        {
            Treap_GCD(rot->L, l, INF, ans);
            Treap_GCD(rot->R, -1, r, ans);
        }
        return;
    }
    if(r<rot->val)
        Treap_GCD(rot->L, l, r, ans);
    if(rot->val<l)
        Treap_GCD(rot->R, l, r, ans);
}
int Treap_Kth(Treap *rot, int k)
{
    if(rot==NULL)
        return INF;
    int tmp=rot->L_size();
    if(k==tmp+1)
        return rot->val;
    if(k<=tmp)
        return Treap_Kth(rot->L, k);
    else
        return Treap_Kth(rot->R, k-tmp-1);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("out_hutu.txt","w",stdout);
    int t,T=0;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case #%d:\n",++T);
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&Val[i]);
            rot[i]=NULL;set[i]=i;
            Treap_Insert(rot[i], Val[i], i);
        }
        while(m--)
        {
            int kind;
            scanf("%d",&kind);
            if(kind==1)
            {
                int u,v;// 合并集合
                scanf("%d%d",&u,&v);
                int x=set[u],y=set[v];
                if(x!=y)
                {
                    if(rot[x]->size <= rot[y]->size)
                        Treap_Union(rot[x], rot[y], y);
                    else
                        Treap_Union(rot[y], rot[x], x);
                }
            }
            if(kind==2)
            {
                int u,v;// 移动集合
                scanf("%d%d",&u,&v);
                int x=set[u],y=set[v];
                if(x!=y)
                {
                    Treap_Delete(rot[x], Val[u], u);
                    Treap_Insert(rot[y], Val[u], u);
                    set[u]=y;
                }
            }
            if(kind==3)
            {
                int u,v,x;// Val[u]=x;
                scanf("%d%d",&u,&v);
                x=set[u];
                Treap_Delete(rot[x], Val[u] ,u);
                Val[u]=v;
                Treap_Insert(rot[x], Val[u], u);
            }
            if(kind==4)
            {
                int u,x;// 查询三角形
                scanf("%d",&u);
                x=set[u];
                int now1=Treap_Kth(rot[x], 1);
                int now2=Treap_Kth(rot[x], 2),ans=1;
                while(now2<INF)
                {
                    int tmp=Treap_Succ(rot[x], now1+now2, INF);
                    ans++;
                    now1=now2;now2=tmp;
                }
                printf("%d\n",ans);
            }
            if(kind==5)
            {
                int u,l,r;// 查询区间最大公约数
                scanf("%d%d%d",&u,&l,&r);
                int x=set[u],ans=-1;
                Treap_GCD(rot[x], l, r, ans);
                printf("%d\n",ans);
            }
        }
        for(int i=1;i<=n;i++)
            Treap_clear(rot[i]);
    }
    return 0;
}
