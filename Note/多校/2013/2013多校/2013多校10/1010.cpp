/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/22 12:27:59
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£10\1010.cpp
************************************************ */
#pragma comment(linker, "/STACK:1024000000,1024000000")
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
struct Edge
{
	int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void init()
{
	memset(head,-1,sizeof(head));
	tot = 0;
}
void addedge(int u,int v)
{
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}


int num[MAXN];
int n;
long long ans;
void dfs(int u,int pre)
{
	num[u] = 1;
	int tmp = 0;
	for(int i = head[u];i!= -1;i = edge[i].next)
	{
		int v = edge[i].to;
		if(v == pre)continue;
		dfs(v,u);
		ans += (long long)tmp*num[v];
		num[u] += num[v];
		tmp += num[v];
	}
	ans += (long long)tmp*(n-num[u]);
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int u,v;
	while(scanf("%d",&n) == 1)
	{
		init();
		for(int i = 1;i < n;i++)
		{
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		ans = 0;
		dfs(1,-1);
		long long tot = (long long)n*(n-1)*(n-2)/6;
		printf("%I64d\n",tot-ans);
	}
    return 0;
}
