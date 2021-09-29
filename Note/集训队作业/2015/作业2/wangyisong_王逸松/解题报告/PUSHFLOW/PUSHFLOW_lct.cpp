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
template <class T>
inline T min(T a,T b){return a<b?a:b;}

#define MAXN 100005
#define MAXM 200005
#define MAXNODE (MAXN+MAXM)

int n,m,q;

int F[MAXN];
inline int G(int x){return F[x]?F[x]=G(F[x]):x;}
inline bool M(int x,int y){return (x=G(x))!=(y=G(y))?F[x]=y,1:0;}

int ex[MAXM],ey[MAXM],ew[MAXM];
int ids[MAXM];

inline bool cmp(int i,int j)
begin
	return ew[i]>ew[j];
end;

struct cycle begin
	int A,B,id;
end;

cycle _cyc[MAXN],*_cyc_tot=_cyc;

struct node begin
	node *s[2],*fa;
	bool rev;
	bool isedge;
	int x,mi,add;
	cycle *cyc;
	
	inline void add_rev_tag()
	begin
		swap(s[0],s[1]);rev^=1;
	end;
	
	inline void add_tag(int d)
	begin
		x+=isedge?d:0;mi+=(mi!=2147483647)?d:0;add+=d;
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
		mi=x;
		if s[0] then mi=min(mi,s[0]->mi);
		if s[1] then mi=min(mi,s[1]->mi);
	end;
end;

node lct[MAXNODE];

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
	while 1 do begin
		tmp[cnt++]=x;
		node *fa=x->fa;
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

inline node * access(node *x)
begin
	node *ret=NULL;
	while x do splay(x)->s[1]=ret,(ret=x)->update(),x=x->fa;
	return ret;
end;

inline void setroot(int x){access(lct+x)->add_rev_tag();}

inline void setcyc(node *x,cycle *c)
begin
	if !x then return;
	x->cyc=c;
	setcyc(x->s[0],c);setcyc(x->s[1],c);
end;

inline void link(int x,int y)
begin
	setroot(x),splay(lct+x)->fa=lct+y;
end;

inline void cut(int x,int y)
begin
	setroot(x),access(lct+y),splay(lct+y)->s[0]=NULL,lct[x].fa=NULL,lct[y].update();
end;

int main()
begin
	read(n);read(m);
	int i;
	for i=1;i<=n;i++ do lct[i].x=lct[i].mi=2147483647;
	for i=1;i<=m;i++ do begin
		read(ex[i]);read(ey[i]);read(ew[i]);
		ids[i]=i;
		lct[n+i].isedge=1;lct[n+i].x=lct[n+i].mi=ew[i];
	end;
	std::sort(ids+1,ids+m+1,cmp);
	for i=1;i<=m;i++ do begin
		int id=ids[i];
		int x=ex[id],y=ey[id],w=ew[id];
		if M(x,y) then begin
			link(x,n+id);
			link(n+id,y);
		end else begin
			cycle *c=++_cyc_tot;
			c->A=x;c->B=y;c->id=id;
			node *t=(setroot(x),access(lct+y));
			setcyc(t,c);lct[n+id].cyc=c;
			t->add_tag(w);
		end;
	end;
	read(q);
	for i=1;i<=q;i++ do begin
		int op,u,v,id,w;
		read(op);
		if op==0 then begin
			read(u);read(v);
			printf("%d\n",(setroot(u),access(lct+v))->mi);
		end else begin
			read(id);read(w);
			cycle *c=lct[n+id].cyc;
			if !c then begin
				splay(lct+n+id)->x+=w-ew[id];
				lct[n+id].update();
				ew[id]=w;
			end else begin
				node *t=(setroot(c->A),access(lct+c->B));
				t->add_tag(-ew[c->id]);
				splay(lct+n+id)->x+=w-ew[id];
				lct[n+id].update();
				ew[id]=w;
				if splay(t)->mi<ew[c->id] then begin
					int tmp=t->mi;
					while t->x!=tmp do begin
						t->down();
						t=t->s[t->s[1] && t->s[1]->mi==tmp];
					end;
					int id1=splay(t)-lct-n;
					cut(n+id1,ex[id1]);cut(n+id1,ey[id1]);
					link(c->A,n+c->id);link(c->B,n+c->id);
					c->A=ex[id1],c->B=ey[id1],c->id=id1;
				end;
				setroot(c->A),access(lct+c->B)->add_tag(ew[c->id]);
			end;
		end;
	end;
end