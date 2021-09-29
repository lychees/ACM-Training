#include <stdio.h>
#include <stdlib.h>

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define begin {
#define end }

char ch;
inline void read(int &x)
begin
	x=0;ch=getchar();
	while ch<=32 do ch=getchar();
	while ch>32 do x=x*10+ch-48,ch=getchar();
end;

template <class T>
inline void swap(T &a,T &b){T t=a;a=b;b=t;}
template <class T>
inline T min(T a,T b){return a<b?a:b;}

#define MAXN 100005
#define MAXM 200005
#define MAXNODE (MAXN+MAXM)

int n,m,q;

struct node;

struct cycle begin
	int A,B;
	node *ex;
end;

cycle _cyc[MAXN],*_cyctot=_cyc;

struct node begin
	node *s[2],*fa;
	bool rev;
	bool isedge;
	cycle *cyc;
	int x,mi,add;
	int size;
	
	inline void add_rev_tag()
	begin
		swap(s[0],s[1]);rev^=1;
	end;
	
	inline void add_tag(int d)
	begin
		x+=isedge?d:0;mi+=(isedge||(size>1))?d:0;add+=d;
	end;
	
	inline void down()
	begin
		if rev then begin
			if s[0] then s[0]->add_rev_tag();
			if s[1] then s[1]->add_rev_tag();
			rev=0;
		end;
		if s[0] then s[0]->add_tag(add);
		if s[1] then s[1]->add_tag(add);
		add=0;
	end;
	
	inline void update()
	begin
		mi=x;size=1;
		if s[0] then size+=s[0]->size,mi=min(mi,s[0]->mi);
		if s[1] then size+=s[1]->size,mi=min(mi,s[1]->mi);
	end;
end;

node lcc[MAXNODE];

inline int get_parent(node *x,node *&fa)
begin
	return (fa=x->fa) ? fa->s[0]==x?0:fa->s[1]==x?1:-1 : -1;
end;

inline void rotate(node *x)
begin
	int t1,t2;
	node *fa,*gfa;
	t1=get_parent(x,fa);
	t2=get_parent(fa,gfa);
	if (fa->s[t1]=x->s[t1^1]) then fa->s[t1]->fa=fa;
	fa->fa=x;x->fa=gfa;x->s[t1^1]=fa;
	if t2!=-1 then gfa->s[t2]=x;
	fa->update();
end;

inline void pushdown(node *x)
begin
	static node *tmp[MAXNODE];
	int cnt=0;
	node *fa;
	while 1 do begin
		tmp[cnt++]=x;
		fa=x->fa;
		if !fa || (fa->s[0]!=x && fa->s[1]!=x) then break;
		x=fa;
	end;
	while cnt-- do tmp[cnt]->down();
end;

inline node * splay(node *x)
begin
	pushdown(x);
	while 1 do begin
		int t1,t2;
		node *fa,*gfa;
		t1=get_parent(x,fa);
		if t1==-1 then break;
		t2=get_parent(fa,gfa);
		if t2==-1 then begin
			rotate(x);break;
		end else if t1==t2 then begin
			rotate(fa);rotate(x);
		end else begin
			rotate(x);rotate(x);
		end;
	end;
	x->update();
	return x;
end;

inline int getrank(node *x)
begin
	node *t=splay(x)->s[0];
	return 1+(t?t->size:0);
end;

inline node * access(node *x)
begin
	node *ret=NULL;
	while x do begin
		node *t=splay(x)->s[0];
		if !t then begin
			x->s[1]=ret;
			(ret=x)->update();
			x=x->fa;
			continue;
		end;
		while t->s[1] do t->down(),t=t->s[1];
		if !splay(t)->cyc then begin
			splay(x)->s[1]=ret;
			(ret=x)->update();x=x->fa;
		end else begin
			cycle *c=t->cyc;
			node *A=lcc+c->A,*B=lcc+c->B,*ex=splay(c->ex);
			if splay(B)->fa==A then begin
				B->s[0]->add_tag(-ex->mi);B->s[1]=ex;ex->fa=B;B->update();
			end else if splay(A)->fa==B then begin
				swap(c->A,c->B);swap(A,B);ex->add_rev_tag();
				B->s[0]->add_tag(-ex->mi);B->s[1]=ex;ex->fa=B;B->update();
			end else begin
				if getrank(A)>getrank(B) then swap(c->A,c->B),swap(A,B),ex->add_rev_tag();
				splay(A)->s[1]->fa=NULL;A->s[1]=NULL;A->update();
				splay(B)->s[1]=ex;ex->fa=B;B->s[0]->add_tag(-ex->mi);B->update();
			end;
			splay(x);c->B=x-lcc;
			if x->s[1]->size<x->s[0]->size then x->add_rev_tag(),x->down();
			x->s[0]->add_tag(x->s[1]->mi);c->ex=x->s[1];x->s[1]->fa=NULL;x->s[1]=ret;x->update();
			if splay(A)->s[1] then begin
				ret=x;x=A;
			end else begin
				A->s[1]=x;x->fa=A;A->update();
				ret=A;x=A->fa;
			end;
		end;
	end;
	return ret;
end;

inline int query(int u,int v)
begin
	return access(lcc+u)->add_rev_tag(),access(lcc+v)->mi;
end;

int _u[MAXM],_v[MAXM],_val[MAXM];

struct edge begin
	edge *next;
	int y,id;
end;

edge *se[MAXN],e[MAXM*2],*etot=e;

inline void addedge(int x,int y,int id)
begin
	*++etot=(edge){se[x],y,id};
	se[x]=etot;
end;

int fa[MAXN],fa_e[MAXN];
bool visit[MAXN];
bool instack[MAXN];

inline void splay_link_fa(node *x)
begin
	x->fa->s[1]=x,x->fa->update();
end;

inline void cover(int id,int y,int x,int val)
begin
	splay_link_fa(lcc+n+fa_e[y]);
	cycle *c=++_cyctot;
	*c=(cycle){x,y,lcc+n+fa_e[y]};
	lcc[n+fa_e[y]].cyc=c;
	int t=fa[y];
	while t!=x do begin
		splay_link_fa(lcc+t);
		if fa[t]!=x then splay_link_fa(lcc[t].fa);
		lcc[t].fa->cyc=c;
		t=fa[t];
	end;
	lcc[y].fa=lcc+n+id;
	lcc[n+id].fa=lcc+x;
	lcc[n+id].size=1;
	lcc[n+id].isedge=1;
	lcc[n+id].x=lcc[n+id].mi=val+splay(lcc+n+fa_e[y])->mi;
	splay(lcc+n+fa_e[y])->add_rev_tag();
	lcc[n+id].cyc=c;
	splay_link_fa(lcc+y);
	splay_link_fa(lcc+n+id);
end;

inline void dfs(int x,int last)
begin
	visit[x]=instack[x]=1;
	lcc[x].size=1;lcc[x].x=lcc[x].mi=2147483647;
	edge *te=se[x];
	while te do begin
		int ty=te->y,id=te->id;
		if !visit[ty] then begin
			fa[ty]=x;fa_e[ty]=id;
			lcc[n+id].fa=lcc+x;
			lcc[n+id].size=1;
			lcc[n+id].x=lcc[n+id].mi=_val[id];
			lcc[n+id].isedge=1;
			lcc[ty].fa=lcc+n+id;
			dfs(ty,x);
		end else if instack[ty] && ty!=last then begin
			cover(id,x,ty,_val[id]);
		end;
		te=te->next;
	end;
	instack[x]=0;
end;

inline void init()
begin
	dfs(1,0);
end;

inline void modify(int id,int val)
begin
	int u=_u[id],v=_v[id];
	access(lcc+u)->add_rev_tag(),access(lcc+v);
	node *t=lcc+n+id;
	splay(t)->add_tag(val-_val[id]);
	_val[id]=val;
end;

int main()
begin
	int size=20<<20;
	char *p =(char*)malloc(size)+size;
	__asm__("movl %0, %%esp\n" :: "r"(p));
	read(n);read(m);
	int i;
	for i=1;i<=m;i++ do begin
		int u,v,val;
		read(u);read(v);read(val);
		_u[i]=u;_v[i]=v;_val[i]=val;
		addedge(u,v,i);addedge(v,u,i);
	end;
	init();
	read(q);
	for i=1;i<=q;i++ do begin
		int op,u,v,id,val;
		read(op);
		if op==0 then begin
			read(u);read(v);
			printf("%d\n",query(u,v));
		end else begin
			read(id);read(val);
			modify(id,val);
		end;
	end;
end