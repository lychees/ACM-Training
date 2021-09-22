/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 18:25:38
File Name   : F:\2013ACM¡∑œ∞\2013∂‡–£7\1001.cpp
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
int a[60010][10];
multiset<int>mst[1<<5];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	int q,k;
	while(scanf("%d%d",&q,&k)==2)
	{
		for(int i = 0;i < (1<<k);i++)
			mst[i].clear();
		int od,x;
		for(int i = 1;i <= q;i++)
		{
			scanf("%d",&od);
			if(od == 0)
			{
				for(int j = 0;j < k;j++)
					scanf("%d",&a[i][j]);
				for(int j = 0; j < (1<<k); j++)
				{
					int s = 0;
					for(int t = 0; t < k;t++)
						if(j & (1<<t))
							s += a[i][t];
						else s -= a[i][t];
					mst[j].insert(s);
				}
			}
			else
			{
				scanf("%d",&x);
				for(int j = 0; j < (1<<k); j++)
				{
					int s = 0;
					for(int t = 0; t < k;t++)
						if(j & (1<<t))
							s += a[x][t];
						else s -= a[x][t];
					multiset<int>::iterator it = mst[j].find(s);
					mst[j].erase(it);
				}
			}
			int ans = 0;
			for(int j = 0; j < (1<<k);j++)
			{
				multiset<int>::iterator it = mst[j].end();
				it--;
				int t1 = (*it);
				it = mst[j].begin();
				int t2 = (*it);
				ans = max(ans,t1-t2);
			}
			printf("%d\n",ans);
		}
	}
    return 0;
}
