/*
 * Author:  kuangbin
 * Created Time:  2013/8/8 11:54:00
 * File Name: 1007.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <time.h>
using namespace std;
const int MOD = 1e9+7;

//求ax = 1( mod m) 的x值，就是逆元(0<a<m)
long long inv(long long a,long long m)
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

long long INV[1000010];


int main()
{
    int n;
    int T;
    int u,v;
    for(int i = 1;i <= 1000000;i++)
        INV[i] = inv(i,MOD);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);

        for(int i = 1;i < n;i++)
            scanf("%d%d",&u,&v);
        long long ans = 1;
        for(int i = 1;i <= 2*(n-1);i++)
        {
            ans = (ans*i)%MOD;
        }
        ans = ans*INV[n+1]%MOD;
        //for(int i = 1;i < n;i++)
        //    ans = ans*INV[i]%MOD;
        printf("%I64d\n",ans);
    }
    return 0;
}

