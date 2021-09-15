#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 10010
#define maxm maxn*2
#define P 99991
using namespace std;
typedef unsigned long long ULL;
int n,father[maxn];
char col[maxn];
int nEdge,to[maxm],next[maxm],start[maxn];
int size[maxn];
ULL Power[maxn],down[maxn],up[maxn];
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void read()
{
	nEdge=1;
	memset(start,0,sizeof(start));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		char &c=col[i];
		for(c=getchar();!isalpha(c);c=getchar());
	}
	for(int i=2,a,b;i<=n;++i)
	{
		scanf("%d %d",&a,&b);
		make(a,b),make(b,a);
	}
}
bool check()
{
	static bool can[maxn];
	static pair<ULL,int> val[maxn];
	static ULL pre[maxn],suf[maxn];
	static int queue[maxn],sufsum[maxn];
	memset(can,false,sizeof(can));
	memset(father,0,sizeof(father));
	int front=0,rear=1;
	queue[rear]=1;
	while(front<rear)
	{
		int p=queue[++front];
		size[p]=1,down[p]=col[p];
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
			{
				father[to[i]]=p;
				queue[++rear]=to[i];
			}
	}
	for(int j=rear;j>=1;--j)
	{
		int p=queue[j],tot=0;
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
			{
				val[++tot]=make_pair(down[to[i]],size[to[i]]);
				size[p]+=size[to[i]];
			}
		sort(val+1,val+tot+1);
		for(int i=1;i<=tot;++i)
			down[p]=down[p]*Power[val[i].second]+val[i].first;
		if(!tot)
			down[p]+=100;
	}
	for(int j=1;j<=rear;++j)
	{
		int p=queue[j],tot=0;
		val[++tot]=make_pair(up[p],n-size[p]);
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
				val[++tot]=make_pair(down[to[i]],size[to[i]]);
		sort(val+1,val+tot+1);
		suf[tot+1]=sufsum[tot+1]=0;
		for(int i=1;i<=tot;++i)
			pre[i]=pre[i-1]*Power[val[i].second]+val[i].first;
		for(int i=tot;i>=1;--i)
		{
			suf[i]=val[i].first*Power[sufsum[i+1]]+suf[i+1];
			sufsum[i]=sufsum[i+1]+val[i].second;
		}
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
			{
				int q=to[i],id=lower_bound(val+1,val+tot+1,make_pair(down[to[i]],size[to[i]]))-val;
				up[q]=col[p]*Power[n-size[q]-1]+pre[id-1]*Power[sufsum[id+1]]+suf[id+1];
				if(p==1&&tot==2)
					up[q]+=100;
				if(up[q]==down[q])
					return true;
			}
	}
	for(int j=rear;j>=1;--j)
	{
		int p=queue[j],tot=0;
		ULL all=0;
		val[++tot]=make_pair(up[p],0);
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
				val[++tot]=make_pair(down[to[i]],to[i]);
		sort(val+1,val+tot+1);
		for(int i=1;i<=tot;++i)
			all^=val[i].first;
		if(all==up[p])
			can[p]=true;
		if(!all)
			return true;
		for(int i=start[p];i;i=next[i])
			if(to[i]!=father[p])
			{
				int q=to[i];
				if(down[q]==(all^up[p])&&can[q])
					can[p]=true;
				if(down[q]==all&&can[q])
					return true;
				if(can[q])
				{
					int id=lower_bound(val+1,val+tot+1,make_pair(all^down[q],0))-val;
					if(val[id].first==(all^down[q])&&can[val[id].second])
						return true;
				}
			}
	}
	return can[1];
}
void Prepare(int n)
{
	Power[0]=1;
	for(int i=1;i<=n;++i)
		Power[i]=Power[i-1]*P;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	Prepare(10000);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		printf("Case #%d: %s\n",++C,check()?"SYMMETRIC":"NOT SYMMETRIC");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
