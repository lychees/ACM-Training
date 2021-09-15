#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 310
#define maxm 100010
using namespace std;
int n,V,m,cntans,father[maxn];
int a[maxn],b[maxn];
int nEdge=1,to[maxm],next[maxm],start[maxn];
struct Ans
{
	int u,v,flow;
	Ans() {}
	Ans(int u,int v,int flow): u(u),v(v),flow(flow) {}
}ans[maxn*maxn*2];
void make(int a,int b)
{
	nEdge++,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void read()
{
	scanf("%d %d %d",&n,&V,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d %d",&u,&v);
		make(u,v),make(v,u);
	}
}
bool check()
{
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i])
			return false;
	return true;
}
int BFS(int p)
{
	static int queue[maxn];
	static bool use[maxn];
	for(int i=1;i<=n;i++)
		use[i]=false;
	int front=0,rear=1;
	queue[rear]=p,use[p]=true;
	while(front<rear)
	{
		int p=queue[++front];
		for(int i=start[p],q;i;i=next[i])
			if(use[q=to[i]]==false)
			{
				use[q]=true,father[q]=p;
				if(a[q]>b[q])
					return q;
				queue[++rear]=q;
			}
	}
	return -1;
}
bool Find()
{
	static int seq[maxn];
	static bool use[maxn];
	for(int i=1;i<=n;i++)
		use[i]=false;
	int top=0;
	for(int i=1;i<=n;i++)
		if(a[i]<b[i])
		{
			int p=i,q=BFS(i);
			if(q==-1)
				return false;
			for(int j=q;j!=p;j=father[j])
				seq[++top]=j;
			seq[++top]=p;
			int c=min(min(b[p]-a[p],a[q]-b[q]),(V+1)/2);
			for(int j=1;j<=top-1;j++)
				for(int k=1;k<=top-1;k++)
					if(use[k]==false&&a[seq[k]]>=c&&a[seq[k+1]]+c<=V)
					{
						use[k]=true;
						a[seq[k]]-=c,a[seq[k+1]]+=c;
						ans[++cntans]=Ans(seq[k],seq[k+1],c);
						if(cntans>m*m*2)
						{
							printf("NO\n");
							exit(0);
						}
					}
			return true;
		}
	return false;
}
void print()
{
	printf("%d\n",cntans);
	for(int i=1;i<=cntans;i++)
		printf("%d %d %d\n",ans[i].u,ans[i].v,ans[i].flow);
}
void work()
{
	while(1)
		if(Find()==false)
			break;
	if(check()==false)
	{
		printf("NO\n");
		return ;
	}
	print();
}
int main()
{
	read();
	work();
	return 0;
}
