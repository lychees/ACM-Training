/*
 *  Author:kuangbin
 *  1011.cpp
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <math.h>
using namespace std;
const int MAXN = 500010;
struct Point
{
    int x,y;
    int id;
    int index;
    Point(int _x = 0,int _y = 0,int _index = 0)
    {
        x = _x;
        y = _y;
        index = _index;
    }
};

Point P[MAXN];


long long dist(Point a,Point b)
{
    return ((long long)(a.x-b.x)*(a.x-b.x) + (long long)(a.y-b.y)*(a.y-b.y));
}
Point p[MAXN];
Point tmpt[MAXN];
bool cmpxy(Point a,Point b)
{
    if(a.x != b.x)return a.x < b.x;
    else return a.y < b.y;
}
bool cmpy(Point a,Point b)
{
    return a.y < b.y;
}
pair<int,int> Closest_Pair(int left,int right)
{
    long long d = (1LL<<50);
    if(left == right)return make_pair(left,right);
    if(left + 1 == right)
        return make_pair(left,right);
    int mid = (left+right)/2;
    pair<int,int>pr1 = Closest_Pair(left,mid);
    pair<int,int>pr2 = Closest_Pair(mid+1,right);
    long long d1,d2;
    if(pr1.first == pr1.second)
        d1 = (1LL<<50);
    else d1 = dist(p[pr1.first],p[pr1.second]);

    if(pr2.first == pr2.second)
        d2 = (1LL<<50);
    else d2 = dist(p[pr2.first],p[pr2.second]);

    pair<int,int>ans;
    if(d1 < d2)ans = pr1;
    else ans = pr2;

    d = min(d1,d2);


    int k = 0;
    for(int i = left;i <= right;i++)
    {
        if((long long)(p[mid].x - p[i].x)*(p[mid].x - p[i].x) <= d)
            tmpt[k++] = p[i];
    }
    sort(tmpt,tmpt+k,cmpy);
    for(int i = 0;i <k;i++)
    {
        for(int j = i+1;j < k && (long long)(tmpt[j].y - tmpt[i].y)*(tmpt[j].y - tmpt[i].y) < d;j++)
        {
            if(d > dist(tmpt[i],tmpt[j]))
            {
                d = dist(tmpt[i],tmpt[j]);
                ans = make_pair(tmpt[i].id,tmpt[j].id);
            }
        }
    }
    return ans;
}

int main()
{
    //freopen("in.txt","r",stdin);
   // freopen("out.txt","w",stdout);
    int T;
    int n,Ax,Ay,Bx,By,Cx,Cy;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d%d",&n,&Ax,&Bx,&Cx,&Ay,&By,&Cy);
        P[0] = Point(0,0,0);
        for(int i = 1;i <= n;i++)
        {
            long long x= ((long long)P[i-1].x*Ax + Bx)%Cx;
            long long y = ((long long)P[i-1].y*Ay + By)%Cy;
            P[i] = Point(x,y,i);
        }
        int end = n;
        long long ans = 0;
        while(end > 1)
        {
            for(int i = 0;i < end;i++)
                p[i] = P[i+1];
            sort(p,p+end,cmpxy);
            for(int i = 0;i < end;i++)
                p[i].id = i;
            pair<int,int>pr = Closest_Pair(0,end-1);
            int Max = max(p[pr.first].index,p[pr.second].index);
            ans += (long long)(end-Max+1)*dist(p[pr.first],p[pr.second]);
            end = Max-1;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
