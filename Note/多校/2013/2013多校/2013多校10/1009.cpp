/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/22 12:00:50
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£10\1009.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MOD = 1e9+7;
long long n;
long long solve()
{
	long long ret = 1;
	long long tmp = 2;
	while( n > 0)
	{
		if(n%2)
		{
			ret *= tmp;
			ret %= MOD;
		}
		tmp *= tmp;
		tmp %= MOD;
		n = n/2;
	}
	return ret;
}
char str[5000000];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	while(scanf("%s",str) == 1)
	{
		n = 0;
		int len = strlen(str);
		for(int i = 0;i < len;i++)
		{
			n = (n*10 + str[i] -'0')%(MOD-1);
		}
		n = (n-1+MOD-1)%(MOD-1);
		printf("%d\n",(int)solve());
	}
    return 0;
}
