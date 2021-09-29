/*
ID:huangta3
PROG:hillwalk
LANG:C++
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include <ctime>
#include <set>
#include <bitset>
#include <deque>
#include <fstream>
#include <stack>
#include <map>
#include <utility>
#include <cassert>
#include <string>
#include <iterator>
#include <cctype>
using namespace std;
typedef long long LL;
const int maxn=100003;
inline int get()
{
    int f=0,v=0;char ch;
    while(!isdigit(ch=getchar()))if(ch=='-')break;
    if(ch=='-')f=1;else v=ch-48;
    while(isdigit(ch=getchar()))v=v*10+ch-48;
    if(f==1)return -v;else return v;
}
struct Tpoint
{
    int x,y;
    Tpoint(){}
    inline Tpoint(int _x,int _y){x=_x,y=_y;}
    inline Tpoint operator -(const Tpoint &b)const{return Tpoint(x-b.x,y-b.y);}
    inline LL operator *(const Tpoint &b)const{return LL(x)*b.y-LL(y)*b.x;}
};
struct Tline
{
    Tpoint p1,p2;
    inline bool operator <(const Tline &b)const
    {
        if(p1.x<b.p1.x)return (p2-p1)*(b.p1-p1)<0;
        else return (b.p2-b.p1)*(p1-b.p1)>0;
    }
    inline void getl(){p1.x=get(),p1.y=get(),p2.x=get(),p2.y=get();}
}a[maxn],cur;
struct Tevent
{
    int x,id;
}event[maxn];
set<Tline> S;
int n;
bool used[maxn];
set<Tline>::iterator it;
inline bool cmpa(const Tline &a,const Tline &b){return a.p1.x<b.p1.x;}
inline bool cmpe(const Tevent &a,const Tevent &b){return a.x<b.x;}
int main()
{
    n=get()-1; cur.getl();
    for(int i=1;i<=n;i++)a[i].getl();
    sort(a+1,a+1+n,cmpa);
    for(int i=1;i<=n;i++)event[i].x=a[i].p2.x,event[i].id=i;
    sort(event+1,event+1+n,cmpe);
    int ans=1;
    for(int i=1,j=1;;)
    {
        for(;i<=n&&a[i].p1.x<=cur.p2.x;i++)
            if(a[i].p2.x>cur.p2.x)S.insert(a[i]),used[i]=1;
        it=S.upper_bound(cur);
        if(it==S.end())break;else ans++;
        cur=*it;
        for(;j<=n&&event[j].x<=cur.p2.x;j++)
            if(used[event[j].id])S.erase(a[event[j].id]);
    }
    printf("%d\n",ans);
    return 0;
}
