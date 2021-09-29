#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
LL get()
{
	LL f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100005;
const LL inf=LL(1e18);
int s[maxn],a[maxn],n,m,p;
LL pos[maxn],dist[maxn];
bool vis[maxn],avl[maxn];
struct data
{
	int v,id;
	data(){}
	data(int _v,int i){v=_v,id=i;}
	inline bool operator <(const data &b)const{return v<b.v||(v==b.v&&id>b.id);}
};
priority_queue<data> Q;
void modify(LL k)
{
	int front=0,rear=0;
	for(int i=0;i<p;i++)
		if(dist[i]<inf)vis[i]=1,s[rear++]=i;
	while(front!=rear)
	{
		int x=s[front++],y=(k+x)%p;
		if(front==maxn)front=0;
		vis[x]=0;
		if(dist[x]+k<dist[y])
		{
			dist[y]=dist[x]+k;
			if(!vis[y])
			{
				vis[y]=1;s[rear++]=y;
				if(rear==maxn)rear=0;
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(!avl[i]&&dist[pos[i]%p]<=pos[i])avl[i]=1,Q.push(data(a[i],i));
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	get(),n=get(),m=get(),p=get();
	for(int i=1;i<=n;i++)pos[i]=get(),a[i]=get();
	for(int i=0;i<p;i++)dist[i]=inf;
	dist[1%p]=1;
	modify(p);
	while(m--)
	{
		int op=get();
		if(op==1)modify(get());
		else if(op==2)
		{
			int x=get();
			a[x]-=get();
			if(avl[x])Q.push(data(a[x],x));
		}else
		{
			while(!Q.empty()&&Q.top().v!=a[Q.top().id])Q.pop();
			if(!Q.empty())
			{
				data t=Q.top();Q.pop();
				a[t.id]=-1;
				printf("%d\n",t.v);
			}else puts("0");
		}
	}
	return 0;
}
