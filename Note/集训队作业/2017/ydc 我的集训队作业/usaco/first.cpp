#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXM 300010
#define MAXN 30010
#define now tree[root]
#define N 30
using namespace std;
struct trie
{
	int son[30],mark,father;
	char p;
}tree[MAXM];
char a[MAXM],stack[MAXM];
int n,total,pos[MAXN],ans[MAXN],s,top,dis[MAXN],update[MAXN],queue[40];
bool use[MAXN];
int tot,num[710],next[710],start[30];
void make(int a,int b){  tot++,num[tot]=b,next[tot]=start[a],start[a]=tot;  }
void Insert(char a[],int k)
{
	int root=0;
	for(int i=0;a[i];i++)
	{
		if(now.son[a[i]-'a']==0)  now.son[a[i]-'a']=++total,tree[total].father=root,tree[total].p=a[i];
		root=now.son[a[i]-'a'];
	}
	now.mark=k,pos[k]=root;
}
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a);
		Insert(a,i);
	}
}
void makegraph()
{
	memset(start,0,sizeof(start));
	tot=0;
	int root=0;
	for(int i=top;i>=1;i--)
	{
		int k=stack[i]-'a';
		for(int j=0;j<26;j++)
			if(j!=k&&now.son[j])
				make(k,j);
		root=now.son[k];
	}
}
bool check(int k)
{
	for(int root=pos[k];root;root=now.father)
		if(root!=pos[k]&&now.mark)
			return false;
	memset(use,false,sizeof(use));
	memset(update,0,sizeof(update));
	int front=0,rear=1;
	queue[rear]=26;
	for(int i=0;i<26;i++)
		make(26,i),dis[i]=-1<<30;
	int p;
	while(front!=rear)
	{
		front=front%N+1,p=queue[front],use[p]=false;
		for(int i=start[p];i;i=next[i])
			if(dis[num[i]]<dis[p]+1)
			{
				dis[num[i]]=dis[p]+1,update[num[i]]++;
				if(update[num[i]]>26)  return false;
				if(!use[num[i]])  rear=rear%N+1,queue[rear]=num[i],use[num[i]]=true;
			}
	}
	return true;
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		top=0;
		for(int root=pos[i];root;root=now.father)
			stack[++top]=now.p;
		makegraph();
		if(check(i))  ans[++s]=i;
	}
}
void print()
{
	printf("%d\n",s);
	for(int i=1;i<=s;i++)
	{
		top=0;
		for(int root=pos[ans[i]];root;root=now.father)
			stack[++top]=now.p;
		for(int i=top;i>=1;i--)
			printf("%c",stack[i]);
		printf("\n");
	}
}
int main()
{
	read();
	solve();
	print();
	return 0;
}
