/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/15 12:08:11
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£8\1001.cpp
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

const int MAXN = 20010;
int lowbit(int x)
{
	return x&(-x);
}
int c[MAXN];
int n;
int sum(int i)
{
	int s = 0;
	while(i > 0)
	{
		s += c[i];
		i -= lowbit(i);
	}
	return s;
}
void add(int i,int val)
{
	while(i <= n)
	{
		c[i] += val;
		i += lowbit(i);
	}
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    return 0;
}
