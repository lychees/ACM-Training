#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 200010
using namespace std;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct node
{
	node *son[2],*fa;
	int va,val,maxv,add;
}pool[maxn],*root,*st=pool;
node* newnode()
{
	return ++st;
}
void update_add(node *p,int x)
{
	p->add+=x,p->va-=x,p->val+=x,p->maxv+=x;
}
void push_down(node *p)
{
	if(p->add)
	{
		if(p->son[0])
			update_add(p->son[0],p->add);
		if(p->son[1])
			update_add(p->son[1],p->add);
		p->add=0;
	}
}
void update(node *p)
{
	p->maxv=p->val;
	if(p->son[0])
		p->maxv=max(p->maxv,p->son[0]->maxv);
	if(p->son[1])
		p->maxv=max(p->maxv,p->son[1]->maxv);
}
void Rotate(node *p,node *x)
{
	bool mark=p==x->son[1];
	node *y=p->son[mark^1],*z=x->fa;
	if(y!=0)
		y->fa=x;
	if(z!=0)
		z->son[x==z->son[1]]=p;
	p->fa=z,p->son[mark^1]=x,x->fa=p,x->son[mark]=y,update(x);
}
void Splay(node *p)
{
	static node *ancestor[maxn];
	int top=0;
	for(node *i=p;i;i=i->fa)
		ancestor[++top]=i;
	for(;top;--top)
		push_down(ancestor[top]);
	while(p->fa)
	{
		node *x=p->fa,*y=x->fa;
		if(y==0)
			Rotate(p,x);
		else if((p==x->son[1])^(x==y->son[1]))
			Rotate(p,x),Rotate(p,y);
		else
			Rotate(x,y),Rotate(p,x);
	}
	update(p),root=p;
}
void Insert(int x,int y)
{
	node *i=root;
	while(i->son[i->va<x])
		push_down(i),i=i->son[i->va<x];
	node *p=newnode();
	push_down(i),p->fa=i,p->va=x,p->val=y,i->son[i->va<x]=p,Splay(p);
}
void Delete(node *p)
{
	if(p->son[0]==0&&p->son[1])
		root=p->son[1],p->son[1]->fa=0;
	else if(p->son[1]==0&&p->son[0])
		root=p->son[0],p->son[0]->fa=0;
	else
	{
		node *i=p->son[0];
		i->fa=0;
		while(i->son[1])
			i=i->son[1];
		Splay(i),i->son[1]=p->son[1],p->son[1]->fa=i,update(i);
	}
}
void modify(double x)
{
	node *i=root;
	while(i->son[i->va<x])
		push_down(i),i=i->son[i->va<x];
	node *p=newnode();
	push_down(i),p->fa=i,i->son[i->va<x]=p,Splay(p);
	update_add(p->son[0],1);
	Delete(p);
	p->son[0]=p->son[1]=p->fa=0,--st;
}
int Query(double x)
{
	node *i=root;
	while(i->son[i->va<x])
		push_down(i),i=i->son[i->va<x];
	node *p=newnode();
	push_down(i),p->fa=i,i->son[i->va<x]=p,Splay(p);
	int ans=p->son[0]->maxv;
	Delete(p);
	p->son[0]=p->son[1]=p->fa=0,--st;
	return ans;
}
int S[maxn],T[maxn],n;
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
		Read(S[i]),Read(T[i]);
	root=newnode();
}
int work()
{
	int ans=0;
	for(int i=n;i>=1;--i)
	{
		int x=Query(S[i]-0.5)+S[i]+T[i];
		ans=max(ans,x);
		modify(S[i]-0.5),Insert(S[i]-1,x-S[i]+1);
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
