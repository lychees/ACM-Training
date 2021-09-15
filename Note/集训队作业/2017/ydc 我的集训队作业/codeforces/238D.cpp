#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 100010
#define maxm maxn*10
using namespace std;
struct msgnode
{
	int sum[10];
	msgnode()
	{
		memset(sum,0,sizeof(sum));
	}
}val[maxn*2];
char pro[maxn];
bool use[maxn];
int n,m,T1[maxn],T2[maxn],pos[maxm],tot;
void work(int S)
{
	static int next[maxn],prev[maxn],T,stack[maxn];
	msgnode now;
	if(S==1)
	{
		for(int i=1;i<=n;++i)
			prev[i]=i-1,next[i]=i+1;
	}
	int i=S,dir=1,top=0,last=-1;
	while(i>=S&&i<=n)
	{
		use[i]=true;
		++T;
		char c=pro[i];
		int x=T1[i];
		if(!T1[i])
			T1[i]=T,stack[++top]=i,pos[T]=++tot,val[tot]=now;
		if(x&&top&&stack[top]>i)
		{
			pos[T]=++tot,val[tot]=now;
			while(x&&top&&stack[top]>i)
				T2[stack[top--]]=T;
		}
		if(isdigit(c))
		{
			++now.sum[c-'0'];
			if(c=='0')
				prev[next[i]]=prev[i],next[prev[i]]=next[i];
			else
				--pro[i];
		}
		else
		{
		 	dir=pro[i]=='>'?1:-1;
		 	if(last!=-1&&!isdigit(pro[last]))
			 	prev[next[last]]=prev[last],next[prev[last]]=next[last];
		}
		last=i,i=dir==1?next[i]:prev[i];
	}
	++T;
	if(i<S&&top)
	{
		pos[T]=++tot,val[tot]=now;
		while(i<S&&top)
			T2[stack[top--]]=T;
	}
	if(i>n)
		T1[n+1]=T,pos[T]=++tot,val[tot]=now;
}
void Prepare()
{
	T1[n+1]=1<<30;
	fill(T2+1,T2+n+1,1<<30);
	for(int i=1;i<=n;++i)
		if(use[i]==false)
			work(i);
}
void Query()
{
	for(int i=1,l,r;i<=m;++i)
	{
		scanf("%d %d",&l,&r);
		int t1=pos[T1[l]],t2=pos[min(T1[r+1],T2[l])];
		for(int j=0;j<10;++j)
			printf("%d%c",val[t2].sum[j]-val[t1].sum[j],j<9?' ':'\n');
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d %s",&n,&m,pro+1);
	Prepare();
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
