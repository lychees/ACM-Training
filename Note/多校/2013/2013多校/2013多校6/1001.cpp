/*
 * Author:  kuangbin
 * Created Time:  2013/8/8 11:52:58
 * File Name: 1001.cpp
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
const int MAXN = 1000010;
int a[MAXN];

int main()
{
    int T;
    int n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        long long S = 1;
        for(int i = 0;i < n;i++)
        {
            scanf("%d",&a[i]);
            S *= a[i];
            S %=MOD;
        }
        long long ans = S*n%MOD;
        sort(a,a+n);
        reverse(a,a+n);
        int cnt = n-1;
        for(int i = 0;i < n;i++)
        {
            if(cnt == 0)break;
            long long tmp = S*inv(a[i],MOD)%MOD;
            ans -= tmp;
            ans = (ans%MOD+MOD)%MOD;
            cnt--;
            if(cnt == 0)break;
            ans -= tmp;
            ans = (ans%MOD+MOD)%MOD;
            cnt--;
            if(cnt == 0)break;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

