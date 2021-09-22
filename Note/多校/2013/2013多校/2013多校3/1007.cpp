/*
 *  Author:kuangbin
 *  1007.cpp
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

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        long long ans ;
        if(n&1)ans = (long long)(n/2)*(n-n/2);
        else
        {
            n>>=1;
            if(n == 1)ans = 1;
            else if(n&1)ans = (long long)(n-2)*(n+2);
            else ans = (long long)(n-1)*(n+1);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
