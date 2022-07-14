#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define maxm 200010
#define lowbit(x) (x&-x)
using namespace std;
typedef long long LL;
int n,n1,n2,sum[maxn];
int nEdge=1,to[maxm],next[maxm],len[maxm],start[maxn];
bool ban[maxn];
LL ans;
void add(int p,int v)
{
	for(int i=p;i<=n;i+=lowbit(i))
		sum[i]+=v;
}
int getsum(int p)
{
	int ans=0;
	for(int i=p;i;i-=lowbit(i))
		ans+=sum[i];
	return ans;
}
void addedge(int a,int b,int c)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge,len[nEdge]=c;
}
void read()
{
	scanf("%d %d %d",&n,&n1,&n2);
	n1=min(n1,n);
	for(int i=2,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		addedge(a,i,b),addedge(i,a,b);
	}
}
int FindRoot(int p)
{
	static int id,use[maxn],queue[maxn],size[maxn],father[maxn];
	int front=0,rear=1;
	father[p]=0,queue[rear]=p,use[p]=++id;
	while(front<rear)
	{
		int p=queue[++front];
		size[p]=1;
		for(int i=start[p];i;i=next[i])
			if(!ban[to[i]]&&use[to[i]]!=id)
			{
				queue[++rear]=to[i];
				father[to[i]]=p;
				use[to[i]]=id;
			}
	}
	for(int i=rear;i>1;--i)
		size[father[queue[i]]]+=size[queue[i]];
	for(int i=rear;i>1;--i)
	{
		int p=queue[i],maxv=rear-size[p];
		for(int j=start[p];j;j=next[j])
			if(to[j]!=father[p]&&use[to[j]]==id)
				maxv=max(maxv,size[to[j]]);
		if(maxv*2<=rear)
			return p;
	}
	return p;
}
void work(int p,int sign,int n1,int n2)
{
	static int id,use[maxn],queue[maxn];
	static pair<int,int> val[maxn];
	int front=0,rear=1;
	queue[rear]=p,use[p]=++id,val[1]=make_pair(0,0);
	while(front<rear)
	{
		int p=queue[++front];
		for(int i=start[p];i;i=next[i])
			if(!ban[to[i]]&&use[to[i]]!=id)
			{
				queue[++rear]=to[i];
				val[rear]=make_pair(val[front].first+len[i],val[front].second+1);
				use[to[i]]=id;
			}
	}
	sort(val+1,val+rear+1);
	int j=rear;
	while(j>1&&val[j].first+val[2].first>n1)
		--j;
	for(int i=2;i<=j;++i)
		add(val[i].second,1);
	for(int i=2;i<=rear;++i)
	{
		if(val[i].first>n1)
			break;
		if(val[i].second>n2)
			continue;
		while(val[j].first+val[i].first>n1)
			add(val[j--].second,-1);
		ans+=(getsum(n2-val[i].second)+2)*sign;
		if(val[i].first*2<=n1&&val[i].second*2<=n2)
			ans-=sign;
	}
	while(j>1)
		add(val[j--].second,-1);
}
void DFS(int p)
{
	p=FindRoot(p);
	ban[p]=true,work(p,1,n2,n1);
	for(int i=start[p];i;i=next[i])
		if(!ban[to[i]])
		{
			work(to[i],-1,n2-len[i]*2,n1-2);
			DFS(to[i]);
		}
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	DFS(1);
	printf("%I64d\n",ans/2);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
