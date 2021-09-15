#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#define maxn 700010
#define eps 1e-6
using namespace std;
typedef long long LL;
inline void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
int n,Q,A,B,x[maxn];
struct Node
{
	Node *son[2],*fa;
	double len,sumlen;
	LL k,b,vA,vB,vC,A,B,C;
}*Root,*stack[maxn];
int top;
double low[maxn],ans[maxn],sum;
void read()
{
	Read(n),Read(Q),Read(A),Read(B);
	for(int i=1;i<=n;++i)
		Read(x[i]);
	for(int i=1;i<=2*n;++i)
		stack[++top]=new Node;
}
inline void move(Node *p,LL x)
{
	p->A+=x,p->C+=p->B*x;
	p->vA+=x,p->vC+=p->vB*x;
}
inline void addK(Node *p,LL x)
{
	p->B+=x;
	p->vB+=x;
}
inline void add(Node *p,LL x)
{
	p->C+=x;
	p->vC+=x;
}
inline void push_down(Node *p)
{
	if(p->A)
	{
		if(p->son[0])
			move(p->son[0],p->A);
		if(p->son[1])
			move(p->son[1],p->A);
		p->A=0;
	}
	if(p->B)
	{
		if(p->son[0])
			addK(p->son[0],p->B);
		if(p->son[1])
			addK(p->son[1],p->B);
		p->B=0;
	}
	if(p->C)
	{
		if(p->son[0])
			add(p->son[0],p->C);
		if(p->son[1])
			add(p->son[1],p->C);
		p->C=0;
	}
}
inline Node* NewNode(LL k,LL b,double len)
{
	Node *p=stack[top--];
	p->k=k,p->b=b,p->len=p->sumlen=len,p->vA=p->vB=p->vC=p->A=p->B=p->C=0;
	p->fa=p->son[0]=p->son[1]=0;
	return p;
}
void Erase(Node *p)
{
	if(p==0)
		return ;
	stack[++top]=p;
	Erase(p->son[0]),Erase(p->son[1]);
}
inline void update(Node *p)
{
	p->sumlen=p->len;
	if(p->son[0])
		p->sumlen+=p->son[0]->sumlen;
	if(p->son[1])
		p->sumlen+=p->son[1]->sumlen;
}
inline void Rotate(Node *p,Node *x)
{
	bool mark=p==x->son[1];
	Node *y=p->son[mark^1],*z=x->fa;
	if(y!=0)
		y->fa=x;
	if(z!=0)
		z->son[x==z->son[1]]=p;
	p->son[mark^1]=x,p->fa=z,x->son[mark]=y,x->fa=p,update(x);
}
inline void Splay(Node *p,Node *go,bool mark=true)
{
	if(mark)
	{
		static Node *ancestor[maxn];
		int top=0;
		ancestor[++top]=p;
		for(Node *i=p;i->fa!=go;i=i->fa)
			ancestor[++top]=i->fa;
		while(top)
			push_down(ancestor[top--]);
	}
	while(p->fa!=go)
	{
		Node *x=p->fa,*y=x->fa;
		if(y==go)
			Rotate(p,x);
		else if((p==x->son[1])^(x==y->son[1]))
			Rotate(p,x),Rotate(p,y);
		else
			Rotate(x,y),Rotate(p,x);
	}
	update(p);
	if(go==0)
		Root=p;
}
inline Node* Find(Node *p,int d)
{
	if(!p->son[d])
		return 0;
	for(p=p->son[d];p->son[d^1];p=p->son[d^1]);
	return p;
}
inline Node* Query(Node *p,double &l,double &r,double &x,double fr)
{
	double sum=fr;
	while(1)
	{
		push_down(p);
		double newl,newr;
		newl=sum+(p->son[0]?p->son[0]->sumlen:0);
		newr=newl+p->len;
		l=newl,r=newr;
		double X=-1.0*(p->b+p->vA*p->k+p->vC)/(p->k+p->vB);
		if(X<newl)
		{
			if(p->son[0])
				p=p->son[0];
			else
			{
				x=newl;
				break;
			}
		}
		else if(newr<X)
		{
			if(p->son[1])
				sum=newr,p=p->son[1];
			else
			{
				x=newr;
				break;
			}
		}
		else
		{
			l=newl,r=newr,x=X;
			break;
		}
	}
	Splay(p,0,0);
	return p;
}
inline Node* Query(Node *p,double x,double &l,double fr)
{
	double sum=fr;
	while(1)
	{
		push_down(p);
		double newl,newr;
		newl=sum+(p->son[0]?p->son[0]->sumlen:0);
		newr=newl+p->len;
		if(x-newl<-eps)
			p=p->son[0];
		else if(newr-x<-eps)
			p=p->son[1],sum=newr;
		else
		{
			l=newl;
			break;
		}
	}
	Splay(p,0,0);
	return p;
}
inline void Delete(Node *p)
{
	Splay(p,0);
	if(p->son[0]==0&&p->son[1]!=0)
		p->son[1]->fa=0,Root=p->son[1];
	else if(p->son[1]==0&&p->son[0]!=0)
		p->son[0]->fa=0,Root=p->son[0];
	else
	{
		Node *i;
		for(i=p->son[0];i->son[1];i=i->son[1])
			push_down(i);
		push_down(i);
		i->son[1]=p->son[1],p->son[1]->fa=i,p->son[0]->fa=0,Splay(i,0);
	}
	stack[++top]=p;
}
void work()
{
	Root=NewNode(2,-2*x[1],Q-1);
	for(int i=2;i<=n;++i)
	{
		double l,r;
		Node *p=Query(Root,l,r,low[i-1],A*(i-2)+1);
		Node *a=Find(p,0),*b=Find(p,1);
		Node *q=NewNode(p->k+p->vB,p->b+p->vA*p->k+p->vC,r-low[i-1]);
		Node *nq;
		p->len=low[i-1]-l,update(p);
		if(a==0)
		{
			if(p->son[1])
				p->son[1]->fa=q;
			q->son[1]=p->son[1],p->son[1]=q,q->fa=p,Splay(q,0);
		}
		else if(b==0)
			p->son[1]=q,q->fa=p,Splay(q,0);
		else
		{
			Splay(a,0),Splay(b,a);
			p->son[1]=q,q->fa=p,Splay(q,0);
		}
		nq=NewNode(0,0,B-A);
		Splay(p,0),Splay(q,Root),q->son[0]=nq,nq->fa=q,Splay(nq,0);
		if(low[i-1]-l<=-eps)
			Delete(p);
		if(r-low[i-1]<=-eps)
			Delete(q);
		Splay(nq,0);
		if(nq->son[0])
			move(nq->son[0],-A);
		if(nq->son[1])
			move(nq->son[1],-B);
		if(A==B)
			Delete(nq);
		p=Query(Root,Q,l,A*(i-1)+1);
		p->len=Q-l,Erase(p->son[1]),update(p);
		p->son[1]=0,add(p,-2*x[i]),addK(p,2);
	}
	double l,r;
	Query(Root,l,r,ans[n],A*(n-1)+1);
}
void print()
{
	for(int i=n;i>=1;--i)
	{
		sum+=(ans[i]-x[i])*(ans[i]-x[i]);
		if(i>1)
		{
			double l=ans[i]-B,r=ans[i]-A;
			if(low[i-1]-l<-eps)
				ans[i-1]=l;
			else if(low[i-1]-r>eps)
				ans[i-1]=r;
			else
				ans[i-1]=low[i-1];
		}
	}
	for(int i=1;i<=n;++i)
		printf("%.10f%c",ans[i],i<n?' ':'\n');
	printf("%.10f\n",sum);
}
int main()
{
	read();
	work();
	print();
	return 0;
}
