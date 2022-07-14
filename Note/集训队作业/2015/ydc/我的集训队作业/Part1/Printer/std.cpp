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
struct Task
{
	int t,s,id;
	double p;
	Task() {}
	friend bool operator < (const Task &a,const Task &b)
	{
		return a.p<b.p;
	}
}task[maxn];
bool cmp(const Task &a,const Task &b)
{
	return a.t<b.t;
}
LL T,ans[maxn];
int n,x;
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d %lf",&task[i].t,&task[i].s,&task[i].p);
		if(task[i].p<0)
			x=i;
		task[i].id=i;
	}
	cin>>T;
}
LL calc(int rank)
{
	int num;
	for(int i=1;i<=n;++i)
		if(task[i].id==x)
			num=i;
	swap(task[num],task[n]);
	sort(task+1,task+n);
	task[n].p=task[rank-1].p+0.5;
	sort(task+1,task+n+1,cmp);
	priority_queue<Task> Q;
	LL now=0;
	for(int i=1,j=1;i<=n;i=j)
	{
		LL last=now;
		now=task[i].t;
		while(!Q.empty()&&Q.top().s+last<=now)
			last+=Q.top().s,ans[Q.top().id]=last,Q.pop();
		if(!Q.empty())
		{
			Task a=Q.top();
			a.s-=now-last;
			Q.pop(),Q.push(a);
		}
		for(;task[j].t==task[i].t;++j)
			Q.push(task[j]);
	}
	while(!Q.empty())
	{
		Task a=Q.top();
		now+=Q.top().s,ans[Q.top().id]=now,Q.pop();
	}
	return ans[x];
}
void binary(int l,int r)
{
	while(l<r)
	{
		int mid=(l+r)>>1;
		calc(mid)>T?l=mid+1:r=mid;
	}
	calc(l);
	sort(task+1,task+n+1);
	while(l<n&&abs(task[l+1].p-task[l-1].p-1)<1e-10)
		swap(task[l],task[l+1]),++l;
	calc(l);
	sort(task+1,task+n+1);
	printf("%.0f\n",task[l-1].p+1);
	for(int i=1;i<=n;++i)
		printf("%I64d%c",ans[i],i<n?' ':'\n');
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	binary(1,n);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
