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

#define MAXN 500005
#define MAXNODE (MAXN*22)
#define MAXHSIZE (MAXN+500005)

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

struct segnode begin
	segnode *s[2];
	int cnt;
end;

segnode _seg[MAXNODE],*_segtot=_seg;

inline segnode * newsegnode()
begin
	*++_segtot=(segnode){{_seg,_seg},0};
	return _segtot;
end;

inline segnode * insert(segnode *b,int val)
begin
	segnode *ret=newsegnode(),*a=ret;
	int i,t;
	for i=19;i>=0;i-- do begin
		t=(val>>i)&1;
		a->s[t^1]=b->s[t^1];
		a=a->s[t]=newsegnode();
		b=b->s[t];
		a->cnt=b->cnt+1;
	end;
	return ret;
end;

segnode *root[MAXN];
int wid[MAXN],rank[MAXN];

inline bool cmpw(int i,int j)
begin
	return w[i]<w[j];
end;

inline void init_seg()
begin
	*_seg=(segnode){{_seg,_seg},0};
	int i;
	root[0]=_seg;
	for i=1;i<=n;i++ do begin
		wid[i]=i;
	end;
	std::sort(wid+1,wid+n+1,cmpw);
	for i=1;i<=n;i++ do begin
		rank[wid[i]]=i;
	end;
	for i=1;i<=n;i++ do begin
		root[i]=insert(root[fa[i]],rank[i]);
	end;
end;

struct segtree begin
	segnode *A,*B,*C,*a,*b,*c;
	
	inline segtree go(int t)
	begin
		return (segtree){A->s[t],B->s[t],C->s[t],a->s[t],b->s[t],c->s[t]};
	end;
	
	inline int cnt()
	begin
		return A->cnt+B->cnt+C->cnt-a->cnt-b->cnt-c->cnt;
	end;
end;

segtree seg[MAXN];
int cnt[MAXN];

inline void get(int id)
begin
	int x,y,z;
	read(x);read(y);read(z);
	if d1[x]>d1[y] then swap(x,y);
	if d1[x]>d1[z] then swap(x,z);
	if d1[y]>d1[z] then swap(y,z);
	int l1=getlca(x,y),l2=getlca(y,z);
	if h[l1]<=h[l2] then begin
		seg[id]=(segtree){root[x],root[y],root[z],root[l1],root[l2],root[fa[l1]]};
	end else begin
		seg[id]=(segtree){root[x],root[y],root[z],root[l1],root[l2],root[fa[l2]]};
	end;
	cnt[id]=seg[id].go(0).cnt()+seg[id].go(1).cnt();
end;

inline int getkth(segtree a,int k)
begin
	int i,ret=0;
	for i=19;i>=0;i-- do begin
		segtree t=a.go(0);
		int tmp=t.cnt();
		if tmp<k then begin
			k-=tmp;
			ret|=1<<i;
			a=a.go(1);
		end else begin
			a=t;
		end;
	end;
	return ret;
end;

struct data begin
	int w;
	int id;
	int from;
	int pos;
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
		_H[i]=(data){w[i],i,i,cnt[i]};
	end;
	hsize=n;
	std::make_heap(_H+1,_H+n+1);
	while k-- do begin
		data t=_H[1];
		pop();
		int W=t.w;
		printf("%d\n",W);
		int id=t.id;
		int from=t.from;
		int pos=t.pos;
		int id1=wid[getkth(seg[id],1)];
		push((data){W+w[id1],id1,id,1});
		if pos<cnt[from] then begin
			id1=wid[getkth(seg[from],pos+1)];
			push((data){W+w[id1]-w[id],id1,from,pos+1});
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
	init_seg();
	for i=1;i<=n;i++ do begin
		get(i);
	end;
	solve();
end