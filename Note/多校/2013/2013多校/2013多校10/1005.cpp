/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/22 13:51:49
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£10\1005.cpp
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
const int MAXN = 110;
int F[MAXN][MAXN];
int G[MAXN][MAXN];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
	while(scanf("%d",&n) == 1)
	{
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
			{
				scanf("%d",&F[i][j]);
				G[i][j] = F[i][j];
				if(i!=j)G[i][j] = 0;
			}
		bool flag = true;
		for(int k = 0;k < n;k++)
			for(int i = 0;i < n;i++)
				for(int j = 0;j < n;j++)
					if(i != j && i != k && j != k)
					{
						if(!flag)break;
						int t = min(F[i][k],F[k][j]);
						if(t > F[i][j])
						{
							flag = false;
							break;
						}
						G[i][j] = max(G[i][j],F[i][j] - t);
					}
		if(!flag)
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
		for(int i = 0;i < n;i++)
		{
			for(int j = 0;j < n-1;j++)
				printf("%d ",G[i][j]);
			printf("%d\n",G[i][n-1]);
		}
	}
    return 0;
}





