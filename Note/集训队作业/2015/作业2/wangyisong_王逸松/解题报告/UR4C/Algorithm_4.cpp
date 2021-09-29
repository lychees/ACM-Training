#include <stdio.h>
#include <algorithm>

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

#define MAXN 30005
#define MAXNODE (3000005)
#define MAXHSIZE (MAXN+100005*2)

int n,k;
int w[MAXN];
int fa[MAXN],h[MAXN];
int pt[MAXN][20];

struct edge begin
	edge *next;
	int y;
end *se[MAXN],e[MAXN],*etot=e;

inline void addedge(int x,int y)
begin
	*++etot=(edge){se[x],y};
	se[x]=etot;
end;

int d1[MAXN],dfstot;

inline void dfs(int x)
begin
	d1[x]=++dfstot;
	edge *te=se[x];
	while te do begin
		dfs(te->y);
		te=te->next;
	end;
end;

inline void pre()
begin
	int i,j;
	for i=1;i<=19;i++ do begin
		for j=1;j<=n;j++ do pt[j][i]=pt[pt[j][i-1]][i-1];
	end;
	for i=2;i<=n;i++ do begin
		addedge(fa[i],i);
	end;
	dfs(1);
end;

inline int jump(int x,int d)
begin
	int i=0,j=1;
	while j<=d do ++i,j<<=1;
	while d do begin
		--i;j>>=1;
		if j<=d then d-=j,x=pt[x][i];
	end;
	return x;
end;

inline int getlca(int x,int y)
begin
	if h[x]>h[y] then x=jump(x,h[x]-h[y]); else y=jump(y,h[y]-h[x]);
	if x==y then return x;
	int i;
	for i=19;i>=0;i-- do begin
		if pt[x][i]^pt[y][i] then begin
			x=pt[x][i];y=pt[y][i];
		end;
	end;
	return fa[x];
end;

struct node begin
	node *l,*r;
	int npl;
	int id;
end;

node _nodes[MAXNODE],*_nodetot=_nodes;

#define null _nodes

inline void init_nodes()
begin
	*_nodes=(node){_nodes,_nodes,0,0};
end;

inline node * newnode(int id)
begin
	*++_nodetot=(node){null,null,1,id};
	return _nodetot;
end;

inline node * merge(node *a,node *b)
begin
	if a==null then return b;
	if b==null then return a;
	if w[a->id]>w[b->id] then swap(a,b);
	node *ret=++_nodetot;
	*ret=(node){a->l,merge(a->r,b),0,a->id};
	if ret->r->npl>ret->l->npl then swap(ret->l,ret->r);
	ret->npl=ret->r->npl+1;
	return ret;
end;

node *H[MAXN][20];
node *H1[MAXN];

inline void init_heap()
begin
	int i,j;
	for i=0;i<=19;i++ do H[0][i]=null;
	for i=1;i<=n;i++ do begin
		H[i][0]=newnode(i);
		H1[i]=null;
	end;
	for i=1;i<=19;i++ do begin
		for j=1;j<=n;j++ do begin
			H[j][i]=merge(H[j][i-1],H[pt[j][i-1]][i-1]);
		end;
	end;
end;

inline void add(int id,int x,int d)
begin
	node *tmp=null;
	int i=0,j=1;
	while j<=d do ++i,j<<=1;
	while d do begin
		--i;j>>=1;
		if j<=d then d-=j,tmp=merge(tmp,H[x][i]),x=pt[x][i];
	end;
	H1[id]=merge(H1[id],tmp);
end;

inline void get(int id)
begin
	int x,y,z;
	read(x);read(y);read(z);
	if d1[x]>d1[y] then swap(x,y);
	if d1[x]>d1[z] then swap(x,z);
	if d1[y]>d1[z] then swap(y,z);
	int l1=getlca(x,y),l2=getlca(y,z);
	if h[l1]<=h[l2] then begin
		add(id,x,h[x]-h[l1]);
		add(id,y,h[y]-h[l2]);
		add(id,z,h[z]-h[l1]+1);
	end else begin
		add(id,x,h[x]-h[l2]+1);
		add(id,y,h[y]-h[l1]);
		add(id,z,h[z]-h[l2]);
	end;
end;

struct data begin
	int w;
	node *x;
end;

inline bool operator < (const data &a,const data &b)
begin
	return !(a.w<b.w);
end;

data _H[MAXHSIZE];

int hsize;

inline void push(data x)
begin
	_H[++hsize]=x;
	std::push_heap(_H+1,_H+hsize+1);
end;

inline void pop()
begin
	std::pop_heap(_H+1,_H+(hsize--)+1);
end;

inline void solve()
begin
	int i;
	for i=1;i<=n;i++ do begin
		_H[i]=(data){w[i],H[i][0]};
	end;
	hsize=n;
	std::make_heap(_H+1,_H+n+1);
	while k-- do begin
		data t=_H[1];
		pop();
		int W=t.w;
		printf("%d\n",W);
		node *x=t.x;
		int id=x->id;
		push((data){W+w[H1[id]->id],H1[id]});
		if x->l!=null then begin
			int id1=x->l->id;
			push((data){W+w[id1]-w[id],x->l});
		end;
		if x->r!=null then begin
			int id1=x->r->id;
			push((data){W+w[id1]-w[id],x->r});
		end;
	end;
end;

int main()
begin
	read(n);read(k);
	int i;
	for i=1;i<=n;i++ do read(w[i]);
	for i=2;i<=n;i++ do begin
		read(fa[i]);h[i]=h[fa[i]]+1;
		pt[i][0]=fa[i];
	end;
	pre();
	init_nodes();
	init_heap();
	for i=1;i<=n;i++ do begin
		get(i);
	end;
	solve();
end