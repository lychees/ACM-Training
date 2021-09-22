/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 13:34:52
File Name   : F:\2013ACM¡∑œ∞\2013∂‡–£7\1006.cpp
*********************************************** */

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
using namespace std;
int a[110][110];
bool used[110];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
	while(scanf("%d%d",&n,&m) == 2)
	{
		if(n >= m)
		{
			for(int i = 1;i <= m;i++)
			{
				a[i][1] = i;
				a[i][2] = n;
				if(a[i][1]==n)a[i][2] = n-1;
				memset(used,false,sizeof(used));
				used[a[i][1]] = used[a[i][2]] = true;
				int t = 1;
				for(int j = 3;j <= n;j++)
				{
					while(used[t])t++;
					a[i][j] = t++;
				}
			}
		}
		else
		{
			int t = 1;
			for(int i = 1;i <= m;i++)
			{
				a[i][1] = t++;
				if(t > n)t = 1;
			}
			for(int i = 1;i <= n;i++)
			{
				if(i < n)t = n;
				else t = n-1;
				for(int j = 0;j*n+i <= m;j++)
				{
					a[j*n+i][2] = t;
					t--;
				//	printf("%d %d %d\n",i,j,t);
					if(t == 0)t = n;
					if(t == i)t--;
					if(t==0)t=n;
				}

			}
			for(int i = 1;i <= m;i++)
			{
				memset(used,false,sizeof(used));
				used[a[i][1]] = used[a[i][2]] = true;
				int t = 1;
				for(int j = 3;j <= n;j++)
				{
					while(used[t])t++;
					a[i][j] = t++;
				}
			}
		}
		for(int i = 1;i <= m;i++)
		{
			for(int j = 1;j <= n;j++)
			{
				printf("%d",a[i][j]);
				if(j < n)printf(" ");
				else printf("\n");
			}
		}
	}
    return 0;
}
