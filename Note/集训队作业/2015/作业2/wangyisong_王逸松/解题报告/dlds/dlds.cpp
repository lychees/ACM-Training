#include <stdio.h>

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
	while ch>32 do begin
		x=x*10+ch-48;ch=getchar();
	end;
end;

#define u32 unsigned int

inline u32 getrand()
begin
	static u32 ret=417647121;
	return ret=ret*16807ull%2147483647ull;
end;

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}

#define MAXN 250005

#define LOGN 19

#define MAXSEGNODE (MAXN*(LOGN+5))

int tags[MAXN];

struct treapnode begin
	treapnode *l,*r;
	u32 key;
	int size;
end;

treapnode _treap[MAXN];
treapnode *tr[MAXN];

inline treapnode * join(treapnode *a,treapnode *b)
begin
	if !a then return b;
	if !b then return a;
	if a->key<b->key then begin
		a->size+=b->size;
		a->r=join(a->r,b);
		return a;
	end else begin
		b->size+=a->size;
		b->l=join(a,b->l);
		return b;
	end;
end;

int __nowtag;

inline void dfsL(treapnode *a)
begin
	if a->l then dfsL(a->l);
	tags[a-_treap]=++__nowtag;
	if a->r then dfsL(a->r);
end;

inline void dfsR(treapnode *a)
begin
	if a->r then dfsR(a->r);
	tags[a-_treap]=--__nowtag;
	if a->l then dfsR(a->l);
end;

inline treapnode * get_kth(treapnode *a,int k)
begin
	int cnt=a->l?a->l->size:0;
	return k<=cnt ? get_kth(a->l,k) : k>cnt+1 ? get_kth(a->r,k-cnt-1) : a;
end;

struct tnode begin
	tnode *l,*r;
	u32 key;
	int *tag;
	int size;
	int B,maxB;
	
	inline void update()
	begin
		maxB=B;
		if l && l->maxB>maxB then maxB=l->maxB;
		if r && r->maxB>maxB then maxB=r->maxB;
	end;
end;

tnode _nodes[MAXN][LOGN+1];

inline tnode * join(tnode *a,tnode *b)
begin
	if !a then return b;
	if !b then return a;
	if a->key<b->key then begin
		a->size+=b->size;
		a->r=join(a->r,b);
		a->update();
		return a;
	end else begin
		b->size+=a->size;
		b->l=join(a,b->l);
		b->update();
		return b;
	end;
end;

inline void split(tnode *a,int *tag,tnode *&l,tnode *&r)
begin
	if !a then begin
		l=r=NULL;
		return;
	end;
	if *a->tag<*tag then begin
		split(a->r,tag,l,r);
		a->size-=r?r->size:0;
		a->r=l;l=a;
	end else begin
		split(a->l,tag,l,r);
		a->size-=l?l->size:0;
		a->l=r;r=a;
	end;
	a->update();
end;

inline void insert(tnode *&a,tnode *x)
begin
	if !a then begin
		a=x;
		return;
	end;
	if x->key<a->key then begin
		tnode *t1,*t2;
		x->size+=a->size;
		split(a,x->tag,t1,t2);
		x->l=t1;x->r=t2;
		a=x;
		x->update();
		return;
	end;
	++a->size;
	if *x->tag<*a->tag then begin
		insert(a->l,x);
	end else begin
		insert(a->r,x);
	end;
	a->update();
end;

inline void del(tnode *&a,tnode *x)
begin
	if a==x then begin
		x->size=1;
		x->maxB=x->B;
		a=join(x->l,x->r);
		x->l=x->r=NULL;
		return;
	end;
	--a->size;
	if *x->tag<*a->tag then begin
		del(a->l,x);
	end else begin
		del(a->r,x);
	end;
	a->update();
end;

inline void update(tnode *a,tnode *x)
begin
	if a->tag==x->tag then begin
		a->update();
		return;
	end;
	if *x->tag<*a->tag then begin
		update(a->l,x);
	end else begin
		update(a->r,x);
	end;
	a->update();
end;

inline int getmaxBR(tnode *a,int *x)  // [x,+inf)
begin
	int ret=0;
	while a do begin
		if *x<=*a->tag then begin
			if a->B>ret then ret=a->B;
			if a->r && a->r->maxB>ret then ret=a->r->maxB;
			a=a->l;
		end else begin
			a=a->r;
		end;
	end;
	return ret;
end;

inline int getmaxBL(tnode *a,int *x)  // (-inf,x]
begin
	int ret=0;
	while a do begin
		if *x>=*a->tag then begin
			if a->B>ret then ret=a->B;
			if a->l && a->l->maxB>ret then ret=a->l->maxB;
			a=a->r;
		end else begin
			a=a->l;
		end;
	end;
	return ret;
end;

inline int getmaxB(tnode *a,int *L,int *R)
begin
	while 1 do begin
		if !a then return 0;
		if *L==*a->tag then begin
			return max(a->B,getmaxBL(a->r,R));
		end;
		if *R==*a->tag then begin
			return max(a->B,getmaxBR(a->l,L));
		end;
		if *R<*a->tag then begin
			a=a->l;
		end else if *L>*a->tag then begin
			a=a->r;
		end else begin
			break;
		end;
	end;
	return max(a->B,max(getmaxBR(a->l,L),getmaxBL(a->r,R)));
end;

inline int countL(tnode *a,int *L)
begin
	int ret=0;
	while a do begin
		if *a->tag<*L then begin
			ret+=a->size-(a->r?a->r->size:0);
			a=a->r;
		end else begin
			a=a->l;
		end;
	end;
	return ret;
end;

inline int countLE(tnode *a,int *L)
begin
	int ret=0;
	while a do begin
		if *L<*a->tag then begin
			a=a->l;
		end else begin
			ret+=a->size-(a->r?a->r->size:0);
			a=a->r;
		end;
	end;
	return ret;
end;

inline int count(tnode *a,int *L,int *R)
begin
	return countLE(a,R)-countL(a,L);
end;

struct segnode begin
	segnode *s[2];
	tnode *t;
end;

segnode _seg[MAXSEGNODE];
segnode *_segtot=_seg;

inline void init_seg()
begin
	*_seg=(segnode){{_seg,_seg},NULL};
end;

inline segnode * newsegnode()
begin
	*++_segtot=(segnode){{_seg,_seg},NULL};
	return _segtot;
end;

inline segnode * join(segnode *a,segnode *b)
begin
	if !a->t then return b;
	if !b->t then return a;
	a->t=join(a->t,b->t);
	a->s[0]=join(a->s[0],b->s[0]);
	a->s[1]=join(a->s[1],b->s[1]);
	return a;
end;

inline void insert(segnode *a,tnode *x,int val)
begin
	int i;
	for i=LOGN;i>=0;i-- do begin
		int t=(val>>i)&1;
		if a->s[t]==_seg then begin
			a->s[t]=newsegnode();
		end;
		a=a->s[t];
		insert(a->t,x+i);
	end;
end;

inline void del(segnode *a,tnode *x,int val)
begin
	int i;
	for i=LOGN;i>=0;i-- do begin
		int t=(val>>i)&1;
		a=a->s[t];
		del(a->t,x+i);
	end;
end;

inline void modifyA(segnode *a,tnode *x,int oldval,int newval)
begin
	del(a,x,oldval);
	insert(a,x,newval);
end;

inline void dfs(tnode *x)
begin
	if x->l then dfs(x->l);
	printf("%d ",x->tag-tags);
	if x->r then dfs(x->r);
end;

inline void modifyB(segnode *a,tnode *x,int A,int B)
begin
	int i;
	for i=LOGN;i>=0;i-- do begin
		int t=(A>>i)&1;
		a=a->s[t];
		x[i].B=B;
		update(a->t,x+i);
	end;
end;

inline int querycnt(segnode *a,int *L,int *R,int val)  // count (A > val)
begin
	int ret=0;
	int i;
	for i=LOGN;i>=0;i-- do begin
		int t=(val>>i)&1;
		if !t then begin
			ret+=count(a->s[1]->t,L,R);
		end;
		a=a->s[t];
	end;
	return ret;
end;

inline int querykth(segnode *a,int *L,int *R,int k)
begin
	int ret=0;
	int i;
	for i=LOGN;i>=0;i-- do begin
		int tmp=count(a->s[1]->t,L,R);
		if tmp<k then begin
			k-=tmp;
			a=a->s[0];
		end else begin
			ret|=1<<i;
			a=a->s[1];
		end;
	end;
	return ret;
end;

inline int querymaxBR(segnode *a,int *L,int *R,int x,int i)
begin
	int ret=0;
	for ;i>=0;i-- do begin
		int t=(x>>i)&1;
		if !t then begin
			ret=max(ret,getmaxB(a->s[1]->t,L,R));
		end;
		a=a->s[t];
	end;
	return ret;
end;

inline int querymaxBL(segnode *a,int *L,int *R,int x,int i)
begin
	int ret=0;
	for ;i>=0;i-- do begin
		int t=(x>>i)&1;
		if t then begin
			ret=max(ret,getmaxB(a->s[0]->t,L,R));
		end;
		a=a->s[t];
	end;
	return ret;
end;

inline int querymaxB(segnode *a,int *L,int *R,int Al,int Ar)
begin
	int i;
	--Al;++Ar;
	for i=LOGN;i>=0;i-- do begin
		int t1,t2;
		t1=(Al>>i)&1;
		t2=(Ar>>i)&1;
		if t1!=t2 then begin
			break;
		end;
		a=a->s[t1];
	end;
	return max(querymaxBR(a->s[0],L,R,Al,i-1),querymaxBL(a->s[1],L,R,Ar,i-1));
end;

int n,m;
int A[MAXN],B[MAXN];
segnode *seg[MAXN];

inline void init()
begin
	init_seg();
	int i,j;
	for i=1;i<=n;i++ do begin
		_treap[i].key=getrand();
		_treap[i].size=1;
		tr[i]=_treap+i;
		seg[i]=newsegnode();
		for j=0;j<=LOGN;j++ do begin
			_nodes[i][j]=(tnode){NULL,NULL,getrand(),tags+i,1,B[i],B[i]};
		end;
		insert(seg[i],_nodes[i],A[i]);
	end;
end;

inline int get_id(int x,int y)
begin
	return get_kth(tr[x],y)-_treap;
end;

inline void modifyA(int x,int y,int val)
begin
	int id=get_id(x,y);
	modifyA(seg[x],_nodes[id],A[id],val);
	A[id]=val;
end;

inline void modifyB(int x,int y,int val)
begin
	int id=get_id(x,y);
	modifyB(seg[x],_nodes[id],A[id],val);
	B[id]=val;
end;

inline void join(int x,int y)
begin
	seg[x]->s[0]=join(seg[x]->s[0],seg[y]->s[0]);
	seg[x]->s[1]=join(seg[x]->s[1],seg[y]->s[1]);
	if tr[x]->size<tr[y]->size then begin
		__nowtag=tags[get_id(y,1)];
		dfsR(tr[x]);
	end else begin
		__nowtag=tags[get_id(x,tr[x]->size)];
		dfsL(tr[y]);
	end;
	tr[x]=join(tr[x],tr[y]);
end;

inline int querycnt(int x,int l,int r,int val)
begin
	int idl=get_id(x,l);
	int idr=get_id(x,r);
	return querycnt(seg[x],tags+idl,tags+idr,val);
end;

inline int querykth(int x,int l,int r,int k)
begin
	int idl=get_id(x,l);
	int idr=get_id(x,r);
	return querykth(seg[x],tags+idl,tags+idr,k);
end;

inline int querymaxB(int x,int l,int r,int Al,int Ar)
begin
	int idl=get_id(x,l);
	int idr=get_id(x,r);
	return querymaxB(seg[x],tags+idl,tags+idr,Al,Ar);
end;

int main()
begin
	freopen("dlds.in","r",stdin);
	freopen("dlds.out","w",stdout);
	read(n);read(m);
	int i;
	for i=1;i<=n;i++ do begin
		read(A[i]);read(B[i]);
	end;
	init();
	int lastans=0;
	for i=1;i<=m;i++ do begin
		int op,x,y,val,l,r,Al,Ar,k;
		read(op);
		if op==1 then begin
			read(x);read(y);read(val);
			x^=lastans;y^=lastans;val^=lastans;
			modifyA(x,y,val);
		end else if op==2 then begin
			read(x);read(y);read(val);
			x^=lastans;y^=lastans;val^=lastans;
			modifyB(x,y,val);
		end else if op==3 then begin
			read(x);read(y);
			x^=lastans;y^=lastans;
			join(x,y);
		end else if op==4 then begin
			read(x);read(l);read(r);read(val);
			x^=lastans;l^=lastans;r^=lastans;val^=lastans;
			printf("%d\n",lastans=querycnt(x,l,r,val));
		end else if op==5 then begin
			read(x);read(l);read(r);read(k);
			x^=lastans;l^=lastans;r^=lastans;k^=lastans;
			printf("%d\n",lastans=querykth(x,l,r,k));
		end else begin
			read(x);read(l);read(r);read(Al);read(Ar);
			x^=lastans;l^=lastans;r^=lastans;Al^=lastans;Ar^=lastans;
			printf("%d\n",lastans=querymaxB(x,l,r,Al,Ar));
		end;
	end;
end