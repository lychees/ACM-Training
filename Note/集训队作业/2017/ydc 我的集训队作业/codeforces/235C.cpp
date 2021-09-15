#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 1000010
using namespace std;
struct State
{
	State *trans[26],*parent;
	int val,Sum,hash;
}pool[maxn<<1],*Root,*tail;
int tot;
char str[maxn];
void Build(int v)
{
	State *p=tail,*np=&pool[++tot];
	np->val=p->val+1,np->Sum=1;
	while(p!=0&&p->trans[v]==0)
		p->trans[v]=np,p=p->parent;
	if(p==0)
		np->parent=Root;
	else
	{
		State *q=p->trans[v];
		if(q->val==p->val+1)
			np->parent=q;
		else
		{
			State *nq=&pool[++tot];
			nq->val=p->val+1,nq->parent=q->parent;
			memcpy(nq->trans,q->trans,sizeof(q->trans));
			q->parent=nq,np->parent=nq;
			while(p!=0&&p->trans[v]==q)
				p->trans[v]=nq,p=p->parent;
		}
	}
	tail=np;
}
int calc(char a[])
{
	static int id=0;
	++id;
	int n=strlen(a+1),nl=0,ans=0;
	State* p=Root;
	for(int i=1;i<=n*2-1;++i)
	{
		int v=i<=n?a[i]-'a':a[i-n]-'a';
		while(p&&p->trans[v]==0)
			p=p->parent,nl=p==0?0:p->val;
		if(p==0)
			p=Root,nl=0;
		else
			p=p->trans[v],++nl;
		while(p->parent&&p->parent->val>=n)
			p=p->parent,nl=p->val;
		if(nl>=n&&p->hash!=id)
		{
			p->hash=id;
			ans+=p->Sum;
		}
	}
	return ans;
}
vector<State*> to[maxn];
void read()
{
	scanf("%s",str+1);
	int n=strlen(str+1);
	Root=tail=&pool[++tot];
	for(int i=1;i<=n;++i)
		Build(str[i]-'a');
	for(int i=1;i<=tot;++i)
		to[pool[i].val].push_back(&pool[i]);
	for(int i=n;i>=1;--i)
		for(int j=0;j<to[i].size();++j)
			if(to[i][j]->parent)
				to[i][j]->parent->Sum+=to[i][j]->Sum;
	int m;
	scanf("%d",&m);
	static char a[maxn];
	for(int i=1;i<=m;++i)
	{
		scanf("%s",a+1);
		printf("%d\n",calc(a));
	}
}
int main()
{
	read();
	return 0;
}
