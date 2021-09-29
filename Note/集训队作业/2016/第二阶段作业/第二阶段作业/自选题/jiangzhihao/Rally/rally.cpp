#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;
const int N = 500500;
const int M = 1050000;
const int T = 524288;
const int MAXM = 2100000;
int n,m;
int point[N],to[MAXM],next[MAXM],kind[MAXM],cc;
int zhan[N],ru[N];
int order[N];
int maxa[N],maxb[N];
int tree[M];
void AddEdge(int x,int y,int z)
{
	cc++;
	next[cc]=point[x];
	point[x]=cc;
	to[cc]=y;
	kind[cc]=z;
}
void GetData()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		AddEdge(a,b,0);
		AddEdge(b,a,1);
		ru[b]++;
	}
}
void Init()
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(!ru[i])
			zhan[++zhan[0]]=i;
	}
	while(zhan[0])
	{
		int now=zhan[zhan[0]];
		zhan[0]--;
		order[++order[0]]=now;
		int then=point[now];
		while(then)
		{
			if(!kind[then])
			{
				int tox=to[then];
				ru[tox]--;
				if(!ru[tox])
					zhan[++zhan[0]]=tox;
			}
			then=next[then];
		}
	}
}
void Add(int x)
{
	x+=T;
	while(x)
	{
		tree[x]++;
		x>>=1;
	}
}
void Del(int x)
{
	x+=T;
	while(x)
	{
		tree[x]--;
		x>>=1;
	}
}
int FindMax()
{
	int now=1;
	while(now<T)
	{
		now<<=1;
		if(tree[now^1])
			now++;
	}
	return(now-T);
}
void Do()
{
	int i;
	for(i=1;i<=n;i++)
	{
		int now=order[i];
		int then=point[now];
		while(then)
		{
			if(kind[then])
			{
				int tox=to[then];
				maxa[now]=max(maxa[now],maxa[tox]);
			}
			then=next[then];
		}
		maxa[now]++;
	}
	for(i=1;i<=n;i++)
		maxa[i]--;
	for(i=n;i>=1;i--)
	{
		int now=order[i];
		int then=point[now];
		while(then)
		{
			if(!kind[then])
			{
				int tox=to[then];
				maxb[now]=max(maxb[now],maxb[tox]);
			}
			then=next[then];
		}
		maxb[now]++;
	}
	for(i=1;i<=n;i++)
		maxb[i]--;
	int ans=n,ansx;
	for(i=1;i<=n;i++)
		Add(maxb[order[i]]);
	for(i=1;i<=n;i++)
	{
		int now=order[i];
		Del(maxb[now]);
		int then=point[now];
		while(then)
		{
			if(kind[then])
			{
				int tox=to[then];
				Del(maxa[tox]+maxb[now]+1);
			}
			then=next[then];
		}
		int val=FindMax();
		if(ans>val)
		{
			ans=val;
			ansx=now;
		}
		then=point[now];
		while(then)
		{
			if(!kind[then])
			{
				int tox=to[then];
				Add(maxa[now]+maxb[tox]+1);
			}
			then=next[then];
		}
		Add(maxa[now]);
	}
	printf("%d %d\n",ansx,ans);
}
int main()
{
	GetData();
	Init();
	Do();
	return 0;
}
