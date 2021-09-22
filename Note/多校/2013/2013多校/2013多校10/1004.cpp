/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/22 13:38:35
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£10\1004.cpp
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
const int MAXN = 1000010;

int a[MAXN];
int next[MAXN],pre[MAXN],tot;
int NewNode()
{
	next[tot] = -1;
	pre[tot] = -1;
	tot++;
	return tot-1;
}
int root;
int sum[MAXN];
vector<int>vec;
int now;
int n;
void init()
{
	tot = 0;
	root = NewNode();
	vec.clear();
	n = now = 0;
}

void I(int x)
{
	n++;
	int t = NewNode();
	a[t] = x;
	pre[t] = now;
	next[t] = next[now];
	if(next[now] != -1)pre[next[now]] = t;
	next[now] = t;
	now = t;
	if(n == 1)
	{
		sum[n] = x;
		vec.push_back(n);
	}
	else
	{
		sum[n] = sum[n-1] + x;
		int sz = vec.size();
		if(sum[n] > sum[vec[sz-1]])
			vec.push_back(n);
	}
}
void D()
{
	if(n == 0)return;
	int sz = vec.size();
	if(vec[sz-1] == n)
		vec.pop_back();
	n--;
	int t = pre[now];
	next[t] = next[now];
	if(next[now] != -1)pre[next[now]] = t;
	now = t;
}
void L()
{
	if(n == 0)return;
	int sz = vec.size();
	if(vec[sz-1] == n)
		vec.pop_back();
	now = pre[now];
	n--;
}
void R()
{
	if(next[now] == -1)return;
	n++;
	now = next[now];
	if(n == 1)
	{
		sum[n] = a[now];
		vec.push_back(n);
	}
	else
	{
		int sz = vec.size();
		sum[n] = sum[n-1] + a[now];
		if(sum[n] > sum[vec[sz-1]])
			vec.push_back(n);
	}
}


int Q(int k)
{
	int sz = vec.size();
	if(vec[sz-1] <= k)
		return sum[vec[sz-1]];
	int t = upper_bound(vec.begin(),vec.end(),k) - vec.begin();
	return sum[vec[t-1]];
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int M;
	int x;
	char op[10];
	while(scanf("%d",&M) == 1)
	{
		init();
		while(M--)
		{
			scanf("%s",&op);
			if(op[0] == 'I')
			{
				scanf("%d",&x);
				I(x);
			}
			else if(op[0] == 'D')
				D();
			else if(op[0] == 'L')
				L();
			else if(op[0] == 'R')
				R();
			else
			{
				scanf("%d",&x);
				printf("%d\n",Q(x));
			}
		}
	}
    return 0;
}
