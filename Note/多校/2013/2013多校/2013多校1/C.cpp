#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <math.h>
using namespace std;
const int MOD = 1e9+7;
long long pow_m(long long a,long long n)
{
    long long ret = 1;
    long long tmp = a%MOD;
    while(n)
    {
        if(n&1)
        {
            ret *= tmp;
            ret %= MOD;
        }
        tmp *= tmp;
        tmp%=MOD;
        n>>=1;
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        if(n==k)
        {
            printf("1\n");
            continue;
        }
        if(k < 1||k > n)
        {
            printf("0\n");
            continue;
        }
        long long ans = pow_m(2,n-k);
        if(n-k>1)
        {
            ans += (n-k-1)*pow_m(2,n-k-2);
            ans %=MOD;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}





