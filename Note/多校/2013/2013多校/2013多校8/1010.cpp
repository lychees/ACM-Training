/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/15 23:20:43
File Name     :F:\2013ACM练习\2013多校8\1010.cpp
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
int uN,vN;
int g[MAXN][MAXN];
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)
{
	for(int v = 1; v <= vN;v++)
		if(g[u][v] && !used[v])
		{
			used[v] = true;
			if(linker[v] == -1 || dfs(linker[v]))
			{
				linker[v] = u;
				return true;
			}
		}
	return false;
}
int hungary()
{
	int res = 0;
	memset(linker,-1,sizeof(linker));
	for(int u = 1; u <= uN;u++)
	{
		memset(used,false,sizeof(used));
		if(dfs(u))res++;
	}
	return res;
}
int lx[MAXN];
const int MAXM = 500100;//边数
struct Edge
{
	int to,next;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~scc
int Index,top;
int scc;//强连通分量的个数
bool Instack[MAXN];
int num[MAXN];//各个强连通分量包含点的个数，数组编号1~scc
//num数组不一定需要，结合实际情况

void addedge(int u,int v)
{
	edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void Tarjan(int u)
{
	int v;
	Low[u] = DFN[u] = ++Index;
	Stack[top++] = u;
	Instack[u] = true;
	for(int i = head[u];i != -1;i = edge[i].next)
	{
		v = edge[i].to;
		if( !DFN[v] )
		{
			Tarjan(v);
			if( Low[u] > Low[v] )Low[u] = Low[v];
		}
		else if(Instack[v] && Low[u] > DFN[v])
			Low[u] = DFN[v];
	}
	if(Low[u] == DFN[u])
	{
		scc++;
		do
		{
			v = Stack[--top];
			Instack[v] = false;
			Belong[v] = scc;
			num[scc]++;
		}
		while( v != u);
	}
}
void solve(int N)
{
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	memset(num,0,sizeof(num));
	Index = scc = top = 0;
	for(int i = 1;i <= N;i++)
		if(!DFN[i])
			Tarjan(i);
}
void init()
{
	tot = 0;
	memset(head,-1,sizeof(head));
}

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
	int k;
	int T;
	scanf("%d",&T);
	int iCase = 0;
	while(T--)
	{
		iCase++;
		scanf("%d%d",&n,&m);
		memset(g,0,sizeof(g));
		int v;
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&k);
			while(k--)
			{
				scanf("%d",&v);
				g[i][v] = 1;
			}
		}
		uN = n;
		vN = m;
		int res = hungary();
		uN = vN = n + m - res;
		for(int i = n+1;i <= uN;i++)
			for(int j = 1;j <= vN;j++)
				g[i][j] = 1;
		for(int i = 1;i <= uN;i++)
			for(int j = m+1;j <= vN;j++)
				g[i][j] = 1;
		hungary();
		memset(lx,-1,sizeof(lx));
		for(int i = 1;i <= vN;i++)
			if(linker[i] != -1)
				lx[linker[i]] = i;
		init();
		for(int i = 1;i <= uN;i++)
			for(int j = 1;j <= vN;j++)
				if(g[i][j] && j != lx[i])
					addedge(lx[i],j);
		solve(vN);
		printf("Case #%d:\n",iCase);
		vector<int>ans;
		for(int i = 1;i <= n;i++)
		{
			ans.clear();
			for(int j = 1; j <= m;j++)
				if(g[i][j] && Belong[j] == Belong[lx[i]])
					ans.push_back(j);
			int sz = ans.size();
			printf("%d",sz);
			for(int i = 0;i < sz;i++)
				printf(" %d",ans[i]);
			printf("\n");
		}
	}
    return 0;
}
