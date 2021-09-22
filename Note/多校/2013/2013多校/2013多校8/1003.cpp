/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/15 13:25:56
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£8\1003.cpp
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
const int MAXN = 1010;
bool g[MAXN][MAXN];
int move[][2] = {{0,1},{0,-1},{-1,0},{1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
bool used[MAXN][MAXN];
int n,m;
bool check(int x,int y)
{
	if(x > 0 && g[x-1][y])return true;
	if(x < n-1 && g[x+1][y])return true;
	if(y > 0 && g[x][y-1])return true;
	if(y < m-1 && g[x][y+1])return true;
	if(x > 0 && y > 0 && g[x-1][y-1])return true;
	if(x > 0 && y < m-1 && g[x-1][y+1])return true;
	if(x < n-1 && y > 0 && g[x+1][y-1])return true;
	if(x < n-1 && y < m-1 && g[x+1][y+1])return true;
	return false;
}
int dfs(int x,int y)
{
	queue<pair<int,int> >q;
	q.push(make_pair(x,y));
	int cnt = 0;
	used[x][y] = true;
	while(!q.empty())
	{
		pair<int,int> tmp = q.front();
		q.pop();
		int nx = tmp.first;
		int ny = tmp.second;
		if(check(nx,ny))
		{
			cnt++;
			continue;
		}
		for(int i = 0;i < 8;i++)
		{
			int tx = nx + move[i][0];
			int ty = ny + move[i][1];
			if(tx < 0 || tx >= n || ty < 0|| ty >= m)continue;
			if(used[tx][ty])continue;
			if(g[tx][ty])continue;
			q.push(make_pair(tx,ty));
			used[tx][ty] = true;
		}
	}
	return cnt;
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	int T;
	scanf("%d",&T);
	int iCase = 0;
	while(T--)
	{
		iCase ++;
		int k;
		scanf("%d%d%d",&n,&m,&k);
		memset(g,false,sizeof(g));
		int x,y;
		while(k--)
		{
			scanf("%d%d",&x,&y);
			g[x][y] = true;
		}
		memset(used,false,sizeof(used));
		int ans = 0;
		for(int i = 0;i < n;i++)
			for(int j = 0 ;j < m;j++)
				if(!g[i][j] && !used[i][j] && !check(i,j))
				{
					int tmp = dfs(i,j);
					ans ^=  (tmp%2+1);
				}
		for(int i = 0;i < n;i++)
			for(int j = 0;j < m;j++)
				if(!g[i][j] && !used[i][j] && check(i,j))
					ans ^= 1;
		if(ans == 0)printf("Case #%d: Fanglaoshi\n",iCase);
		else printf("Case #%d: Xiemao\n",iCase);
	}
    
    return 0;
}
