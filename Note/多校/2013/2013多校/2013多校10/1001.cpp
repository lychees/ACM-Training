/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/22 13:25:04
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£10\1001.cpp
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
const int MAXN = 100010;
int T[MAXN],C[MAXN];
int M;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int N,Q;
	while(scanf("%d%d",&N,&Q) == 2)
	{
		for(int i = 1;i <= N;i++)
			scanf("%d",&T[i]);
		bool flag = false;
		for(int i = 1;i <= N;i++)
		{
			scanf("%d",&C[i]);
			if(C[i] == 1)
				flag = true;
		}
		while(Q--)
		{
			scanf("%d",&M);
			if(M <= 0)
				printf("NO\n");
			else
			{
				if(flag)printf("YES\n");
				else if(M%2)printf("NO\n");
				else printf("YES\n");
			}
		}
	}
    return 0;
}
