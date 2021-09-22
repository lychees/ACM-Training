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
long long gcd(long long a,long long b)
{
    if(b==0)return a;
    else return gcd(b,a%b);
}
long long lcm(long long a,long long b)
{
    return a/gcd(a,b)*b;
}
long long calc(int n,int a,int b)
{
    long long ans = 0;
    int i = 0;
    int ta=0,tb=0;
    int p = 0;
    while(i < n)
    {
        if(ta+a >= n && tb+b >= n)
        {
            ans += (long long)(n-i)*p;
            i = n;
            continue;
        }
        if(ta+a < tb+b)
        {
            ans += (long long)p*(ta+a-i);
            i = ta+a;
            p = i - tb;
            ta+=a;
        }
        else if(ta+a==tb+b)
        {
            ans+= (long long)p*(ta+a-i);
            i = ta+a;
            ta+=a;
            tb+=b;
            p = 0;
        }
        else
        {
            ans += (long long)p*(tb+b-i);
            i = tb+b;
            tb+= b;
            p = i-ta;
        }
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int n,a,b;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&a,&b);
        if(a==b)
        {
            printf("0\n");
            continue;
        }
        if(a < b)swap(a,b);
        long long LCM = lcm(a,b);
        if(LCM >= n)
        {
            printf("%I64d\n",calc(n,a,b));
            continue;
        }
        long long tmp = calc(LCM,a,b);
        long long ans = tmp * (n/LCM)+calc(n%LCM,a,b);
        printf("%I64d\n",ans);
    }
    return 0;
}

