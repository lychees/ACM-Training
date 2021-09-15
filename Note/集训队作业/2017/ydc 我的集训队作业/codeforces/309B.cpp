#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
#define maxm 7000010
using namespace std;
char str[maxm],out[maxm];
int n,r,c,L[maxn],stack[maxn],top,ans,ansl=1,ansr,pos[maxn];
int nEdge=1,to[maxn],next[maxn],start[maxn];
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void DFS(int p)
{
	stack[++top]=p;
	for(int i=start[p];i;i=next[i])
		DFS(to[i]);
	int q=stack[max(1,top-r)];
	if(ans<p-q)
		ans=p-q,ansl=q+1,ansr=p;
	--top;
}
void read()
{
	scanf("%d %d %d",&n,&r,&c);
	int tot=0;
	for(int i=1,j=1,sum=0;i<=n;++i)
	{
		scanf("%s",str+1);
		pos[i]=tot+1;
		for(int k=1;str[k];++k)
			out[++tot]=str[k];
		out[++tot]=' ';
		L[i]=strlen(str+1);
		sum+=L[i]+(i!=j);
		if(L[i]>c)
			sum=0,j=i+1;
		else
		{
			while(sum>c)
				sum-=L[j++]+1;
			make(j-1,i);
		}
	}
	pos[n+1]=tot+1;
}
void print()
{
	DFS(0);
	for(int i=1;i<=n;++i)
		if(L[i]<=c&&L[i-1]>c)
			DFS(i-1);
	for(int i=ansl+1,sum=L[ansl],last=ansl;i<=ansr+1;++i)
	{
		sum+=L[i]+1;
		if(sum>c||i==ansr+1)
		{
			for(int j=pos[last];j<pos[i]-1;++j)
				printf("%c",out[j]);
			printf("\n");
			sum=L[i],last=i;
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
