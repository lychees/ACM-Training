#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define maxn 100010
using namespace std;
typedef long long LL;
struct Node
{
	int p;
	LL T;
	Node() {}
	Node(int p,LL T): p(p),T(T) {}
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.T>b.T;
	}
};
priority_queue<Node> Q;
pair<int,int> que[maxn];
int n,nQ,father[maxn],M[maxn],fa[maxn],last[maxn];
LL sum[maxn],T[maxn],C[maxn];
int Find(int p)
{
	if(fa[p]!=p)
		fa[p]=Find(fa[p]);
	return fa[p];
}
void read()
{
	scanf("%d %d",&n,&nQ);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=2;i<=n;++i)
	{
		scanf("%d %I64d %d",father+i,C+i,M+i);
		sum[i]+=M[i],sum[father[i]]-=M[i];
	}
	for(int i=2;i<=n;++i)
		if(sum[i]>0)
			T[i]=C[i]/sum[i],Q.push(Node(i,T[i]));
	for(int i=1;i<=nQ;++i)
	{
		scanf("%d",&que[i].first);
		que[i].second=i;
	}
	sort(que+1,que+nQ+1);
}
void work()
{
	static LL ans[maxn];
	int i=1;
	while(!Q.empty()&&i<=nQ)
	{
		while(i<=nQ&&que[i].first<=Q.top().T)
			ans[que[i].second]=C[1]-sum[1]*que[i].first,++i;
		if(T[Q.top().p]!=Q.top().T||fa[Q.top().p]!=Q.top().p)
		{
			Q.pop();
			continue;
		}
		else
		{
			int a=Q.top().p,b=Find(father[a]);
			Q.pop();
			C[b]+=C[a],sum[b]+=sum[a],fa[a]=b;
			if(sum[b]>0)
				T[b]=C[b]/sum[b],Q.push(Node(b,T[b]));
		}
	}
	for(int j=i;j<=nQ;++j)
		ans[que[j].second]=C[1];
	for(int j=1;j<=nQ;++j)
		printf("%I64d\n",ans[j]);
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
