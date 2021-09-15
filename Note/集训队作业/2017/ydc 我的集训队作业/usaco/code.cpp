#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define maxn 50010
#define mod 1234567
using namespace std;
typedef long long LL;
int tot;
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
struct Node
{
	Node* son[11];
	int num,dp;
	bool mark;
}*part[maxn];
Node* NewNode()
{
	Node *p=new Node;
	p->num=0,p->dp=0,p->mark=false;
	memset(p->son,0,sizeof(p->son));
	return p;
}
void Insert(char *str,Node *p)
{
	int i;
	for(i=1;str[i];++i)
	{
		int x=str[i]-'0';
		if(!p->son[x])
			p->son[x]=NewNode(),p->son[x]->num=p->num<<4|x;
		p=p->son[x];
	}
	if(i>5)
		p->mark=true;
}
Node* Query(Node *p,int v)
{
	static int a[20];
	int n=0;
	for(int i=v;i;i>>=4)
		a[++n]=i&15;
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		if(!p->son[a[i]])
			return p;
		p=p->son[a[i]];
	}
	return p;
}
int n,m,fa[maxn];
int nEdge=1,to[maxn],next[maxn],start[maxn];
void make(int a,int b)
{
	++nEdge,to[nEdge]=b,next[nEdge]=start[a],start[a]=nEdge;
}
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;++i)
		part[i]=NewNode();
	for(int i=2;i<=n;++i)
	{
		scanf("%d",fa+i);
		make(++fa[i],i);
	}
	static char str[10];
	for(int i=1,x;i<=m;++i)
	{
		scanf("%d %s",&x,str+1);
		for(int j=1;j<=5;++j)
			++str[j];
		for(int j=1,v=++x;j<=5;++j,v=fa[v])
			Insert(str+j-1,part[v]);
	}
}
void DFS(int x,Node *p)
{
	if(p->mark)
		return ;
	p->dp=1;
	int base=1;
	while(base<=p->num)
		base<<=4;
	for(int i=start[x];i;i=next[i])
	{
		int sum=0;
		for(int j=1;j<=10;++j)
			add(sum,Query(part[to[i]],p->num+j*base)->dp);
		p->dp=(LL)p->dp*sum%mod;
	}
	for(int i=1;i<=10;++i)
		if(p->son[i])
			DFS(x,p->son[i]);
}
void Dp()
{
	for(int i=n;i>=1;--i)
		DFS(i,part[i]);
	int ans=1;
	for(int i=1;i<=n;++i)
		ans=(LL)ans*10%mod;
	for(int i=1;i<=10;++i)
		add(ans,mod-Query(part[1],i)->dp);
	printf("%d\n",ans);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Dp();
	printf("%d\n",tot);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
