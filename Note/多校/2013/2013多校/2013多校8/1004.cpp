/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/15 14:48:54
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£8\1004.cpp
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
	int id;
	int w;
}edge[MAXN*2];
int mm[MAXN];
int maxn[MAXN];
int smaxn[MAXN];
int head[MAXN],tot;
void init()
{
	memset(head,-1,sizeof(head));
	tot = 0;
}
void addedge(int u,int v,int w,int id)
{
	edge[tot].to = v;
	edge[tot].w = w;
	edge[tot].id = id;
	edge[tot].next = head[u];
	head[u] = tot++;
	edge[tot].to = u;
	edge[tot].w = w;
	edge[tot].id = id;
	edge[tot].next = head[v];
	head[v] = tot++;
}
void dfs(int u,int pre)
{
	mm[u] = 0;
	maxn[u] = 0;
	smaxn[u] = 0;
	for(int i = head[u];i != -1;i = edge[i].next)
	{
		int v = edge[i].to;
		if(v == pre)continue;
		dfs(v,u);
		if(maxn[v]+1 > smaxn[u])
		{
			smaxn[u] = maxn[v] + 1;
			if(smaxn[u] > maxn[u])
			{
				swap(smaxn[u],maxn[u]);
			}
		}
		if(mm[v] > mm[u])
			mm[u] = mm[v];
	}
	mm[u] = max(mm[u],maxn[u]+smaxn[u]);
}
int ans;
int dep[MAXN];
int p[MAXN];
bool used[MAXN];
int cnt;
int index;
int a[MAXN];
void solve(int u,int pre)
{
	for(int i = head[u];i != -1;i = edge[i].next)
	{
		int v = edge[i].to;
		int w = edge[i].w;
		if(v == pre)continue;
		solve(v,u);
		if(used[v])
		{
			a[edge[i].id] = max(a[edge[i].id],w*mm[v]);
		}
		else
		{
			a[edge[i].id] = max(a[edge[i].id],w*cnt);
		}
	}
}
;
void dfs1(int u,int pre)
{
	p[u] = pre;
	dep[u] = dep[pre] + 1;
	for(int i = head[u]; i != -1;i = edge[i].next)
	{
		int v = edge[i].to;
		if(v==pre)continue;
		dfs1(v,u);
	}
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	int T;
	int n;
	scanf("%d",&T);
	int u,v,w;
	int iCase = 0;
	while(T--)
	{
		iCase ++;
		init();
		scanf("%d",&n);
		for(int i = 1;i < n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			addedge(u,v,w,i);
		}
		dep[0] = 0;
		dfs1(1,0);
		u = 1;
		for(int i = 1;i <= n;i++)
			if(dep[u] < dep[i])
				u = i;
		dfs1(u,0);
		v = 1;
		for(int i =1;i <= n;i++)
			if(dep[v] < dep[i])
				v = i;
		cnt = dep[v]-1;
		memset(used,false,sizeof(used));
		int tmp = v;
		while(tmp)
		{
			used[tmp] = true;
			tmp = p[tmp];
		}
		for(int i = 1;i <= n;i++)
			a[i] = 0;
		ans = 1000000000;
		dfs(u,0);
		solve(u,-1);
		dfs(v,0);
		solve(v,-1);
		for(int i = 1;i < n;i++)
			if(a[i]<ans)
			{
				ans = a[i];
				index = i;
			}
		printf("Case #%d: %d\n",iCase,index);
	}
    
    return 0;
}
