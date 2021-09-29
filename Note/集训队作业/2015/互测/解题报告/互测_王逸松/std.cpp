#include <stdio.h>
#include <algorithm>
#include <vector>

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define switch switch (
#define begin {
#define ___ namespace
#define end }

inline void read(int &x)
begin
	x=0;char ch=getchar();
	while ch<=32 do ch=getchar();
	while ch>32 do x=x*10+ch-48,ch=getchar();
end;

inline int getint()
begin
	int ret;
	read(ret);
	return ret;
end;

#define MAXV 1000005
#define MAXE 3000005

int n,m,q;

___ Graph begin
	struct edge begin
		int x,y;
	end;
	
	edge e[MAXE];
	
	int ecnt=0;
	
	inline void addedge(int x,int y)
	begin
		e[++ecnt]=(edge){x,y};
	end;
	
	inline void out()
	begin
		int V=n+q;
		int i;
		for i=1;i<=ecnt;i++ do begin
			V=std::max(V,std::max(e[i].x,e[i].y));
		end;
		printf("%d %d\n",V,ecnt);
		for i=1;i<=ecnt;i++ do begin
			printf("%d %d\n",e[i].x,e[i].y);
		end;
	end;
end;

___ treap_merge begin
	
	#define MAXN 100005
	#define MAXNODE (1024*1024)
	
	int idtot;
	int _x[MAXN],_d[MAXN];
	std::vector<int> _qid[MAXN];
	
	inline bool cmp_d(int i,int j)
	begin
		return _d[i]<_d[j];
	end;
	
	#define u32 unsigned int
	
	inline u32 getrand()
	begin
		static u32 ret=531789253;
		return ret=ret*16807ull%2147483647ull;
	end;
	
	struct tnode begin
		tnode *l,*r;
		u32 key;
		int val;
		int tag;
		int id;
		int id_sum;
		bool type;
		
		inline void add_tag(int x)
		begin
			val+=x;tag+=x;
		end;
		
		inline void down()
		begin
			if l then l->add_tag(tag);
			if r then r->add_tag(tag);
			tag=0;
		end;
		
		inline void update()
		begin
			id_sum=++idtot;
			if !type then begin
				Graph::addedge(id_sum,id);
				if l then begin
					Graph::addedge(id_sum,l->id_sum);
				end;
				if r then begin
					Graph::addedge(id_sum,r->id_sum);
				end;
			end else begin
				Graph::addedge(id,id_sum);
				if l then begin
					Graph::addedge(l->id_sum,id_sum);
				end;
				if r then begin
					Graph::addedge(r->id_sum,id_sum);
				end;
			end;
		end;
	end;
	
	tnode _tr[MAXN*2+MAXNODE],*_tr_tot;
	
	inline tnode * new_tnode(tnode x)
	begin
		*++_tr_tot=x;
		return _tr_tot;
	end;
	
	inline tnode * new_tnode_and_update(tnode x)
	begin
		*++_tr_tot=x;
		_tr_tot->update();
		return _tr_tot;
	end;
	
	inline tnode * join(tnode *a,tnode *b)
	begin
		if !a then return b;
		if !b then return a;
		a->down();b->down();
		if a->key<b->key then begin
			a->r=join(a->r,b);
			a->update();
			return a;
		end else begin
			b->l=join(a,b->l);
			b->update();
			return b;
		end;
	end;
	
	inline void split(tnode *a,tnode *x,tnode *&l,tnode *&r)
	begin
		if !a then begin
			l=r=NULL;
			return;
		end;
		a->down();
		if a->val<x->val || (a->val==x->val && a<x) then begin
			split(a->r,x,l,r);
			a->r=l;l=a;
		end else begin
			split(a->l,x,l,r);
			a->l=r;r=a;
		end;
		a->update();
	end;
	
	inline tnode * merge(tnode *a,tnode *b)
	begin
		if !a then return b;
		if !b then return a;
		if a->key>b->key then std::swap(a,b);
		a->down();
		tnode *t1,*t2;
		split(b,a,t1,t2);
		a->l=merge(a->l,t1);
		a->r=merge(a->r,t2);
		a->update();
		return a;
	end;
	
	inline tnode * add_tag(tnode *a,int x)
	begin
		if !a then return NULL;
		return new_tnode((tnode){a->l,a->r,a->key,a->val+x,a->tag+x,a->id,a->id_sum,a->type});
	end;
	
	inline tnode * down(tnode *a)
	begin
		return new_tnode((tnode){a->l?add_tag(a->l,a->tag):NULL,a->r?add_tag(a->r,a->tag):NULL,
							a->key,a->val,0,a->id,a->id_sum,a->type});
	end;
	
	inline tnode * join2(tnode *a,tnode *b)
	begin
		if !a then return b;
		if !b then return a;
		a=down(a);b=down(b);
		if a->key<b->key then begin
			return new_tnode_and_update((tnode){a->l,join2(a->r,b),a->key,a->val,0,a->id,a->id_sum,a->type});
		end else begin
			return new_tnode_and_update((tnode){join2(a,b->l),b->r,b->key,b->val,0,b->id,b->id_sum,b->type});
		end;
	end;
	
	inline void split2(tnode *a,tnode *x,tnode *&l,tnode *&r)
	begin
		if !a then begin
			l=r=NULL;
			return;
		end;
		a=down(a);
		if a->val<x->val then begin
			split2(a->r,x,l,r);
			a=new_tnode_and_update((tnode){a->l,l,a->key,a->val,0,a->id,a->id_sum,a->type});
			l=a;
		end else begin
			split2(a->l,x,l,r);
			a=new_tnode_and_update((tnode){r,a->r,a->key,a->val,0,a->id,a->id_sum,a->type});
			r=a;
		end;
	end;
	
	inline tnode * merge2(tnode *a,tnode *b)
	begin
		if !a then return b;
		if !b then return a;
		if a->key>b->key then std::swap(a,b);
		a=down(a);
		tnode *t1,*t2;
		split2(b,a,t1,t2);
		return new_tnode_and_update((tnode){merge2(a->l,t1),merge2(a->r,t2),a->key,a->val,0,a->id,a->id_sum,a->type});
	end;
	
	inline tnode * build(tnode **a,int l,int r)
	begin
		if l>r then return NULL;
		if l==r then return a[l];
		int mi=l;
		int i;
		for i=l+1;i<=r;i++ do begin
			if a[i]->key<a[mi]->key then mi=i;
		end;
		tnode *ret=a[mi];
		ret->l=build(a,l,mi-1);
		ret->r=build(a,mi+1,r);
		ret->update();
		return ret;
	end;
	
	inline tnode * get_T2(int x)
	begin
		int size=_qid[x].size();
		int i;
		static tnode *a[MAXN];
		for i=0;i<size;i++ do begin
			int id=_qid[x][i];
			tnode *tmp=_tr+id+n;
			tmp->key=getrand();
			tmp->val=_d[id]*2+1;
			tmp->id=tmp->id_sum=n+id;
			tmp->type=1;
			a[i]=tmp;
		end;
		return build(a,0,size-1);
	end;
	
	inline void add(tnode *&a,tnode *&b)
	begin
		if !a || !b then return;
		tnode *t1,*t2;
		if a->key<b->key then begin
			a->down();
			split(b,a,t1,t2);
			if t2 then begin
				Graph::addedge(t2->id_sum,a->id);
				if a->l then begin
					Graph::addedge(t2->id_sum,a->l->id_sum);
				end;
			end;
			add(a->l,t1);
			add(a->r,t2);
			b=join(t1,t2);
		end else begin
			b->down();
			split(a,b,t1,t2);
			if t1 then begin
				Graph::addedge(b->id,t1->id_sum);
				if b->r then begin
					Graph::addedge(b->r->id_sum,t1->id_sum);
				end;
			end;
			add(t1,b->l);
			add(t2,b->r);
			a=join(t1,t2);
		end;
	end;
	
	inline void add2(tnode *a,tnode *b)
	begin
		if !a || !b then return;
		tnode *t1,*t2;
		if a->key<b->key then begin
			a=down(a);
			split2(b,a,t1,t2);
			if t2 then begin
				Graph::addedge(t2->id_sum,a->id);
				if a->l then begin
					Graph::addedge(t2->id_sum,a->l->id_sum);
				end;
			end;
			add2(a->l,t1);
			add2(a->r,t2);
		end else begin
			b=down(b);
			split2(a,b,t1,t2);
			if t1 then begin
				Graph::addedge(b->id,t1->id_sum);
				if b->r then begin
					Graph::addedge(b->r->id_sum,t1->id_sum);
				end;
			end;
			add2(t1,b->l);
			add2(t2,b->r);
		end;
	end;
	
	struct edge begin
		edge *next,*rev;
		int y,len;
	end;
	
	edge *first[MAXN],e[MAXN*4],*etot=e;
	
	inline void addedge(int x,int y,int len)
	begin
		++etot;
		*etot=(edge){first[x],etot+1,y,len};
		first[x]=etot;
		++etot;
		*etot=(edge){first[y],etot-1,x,len};
		first[y]=etot;
	end;
	
	edge *fa_e[MAXN],*mo_e[MAXN];
	
	int dfn[MAXN],dfstot;
	int dep[MAXN];
	
	struct cycle begin
		int len;
		int last;
	end;
	
	cycle _cyc[MAXN],*_cyc_tot=_cyc;
	cycle *cyc[MAXN];
	
	inline void dfs(int x)
	begin
		dfn[x]=++dfstot;
		for edge *te=first[x];te;te=te->next do begin
			if te==fa_e[x] then continue;
			int ty=te->y;
			if !dfn[ty] then begin
				fa_e[ty]=te->rev;
				dep[ty]=dep[x]+te->len;
				dfs(ty);
			end else if dfn[ty]<dfn[x] then begin
				mo_e[x]=te;
				cycle *c=++_cyc_tot;
				c->len=dep[x]-dep[ty]+te->len;
				c->last=x;
				cyc[x]=c;
				int x1=x;
				while fa_e[x1]->y!=ty do begin
					int x2=fa_e[x1]->y;
					mo_e[x2]=fa_e[x1]->rev;
					cyc[x2]=c;
					x1=x2;
				end;
			end;
		end;
	end;
	
	inline bool check_mindist(int x,int fa,int cyclen)
	begin
		return dep[x]-dep[fa]<cyclen-(dep[x]-dep[fa]);
	end;
	
	
	inline void update_ans(tnode *T1,tnode *T2,tnode *t1,tnode *t2,int d)
	begin
		tnode *tmp=_tr_tot;
		add2(add_tag(T1,2*d),t2);
		_tr_tot=tmp;
		add2(add_tag(t1,2*d),T2);
		_tr_tot=tmp;
	end;
	
	inline void merge(tnode *&T1,tnode *&T2,tnode *t1,tnode *t2,int d)
	begin
		T1=merge2(T1,add_tag(t1,d*2));
		T2=merge2(T2,add_tag(t2,-d*2));
	end;
	
	inline void solve(int x,tnode *&T1,tnode *&T2)
	begin
		T1=_tr+x;
		T1->key=getrand();
		T1->val=0;
		T1->id=T1->id_sum=x;
		T2=get_T2(x);
		add(T1,T2);
		for edge *te=first[x];te;te=te->next do begin
			if te==fa_e[x] || te==mo_e[x] then continue;
			int ty=te->y;
			if te->rev==mo_e[ty] then continue;
			if !mo_e[ty] then begin
				tnode *t1,*t2;
				solve(ty,t1,t2);
				if t1 then t1->add_tag(2*te->len);
				if t2 then t2->add_tag(-2*te->len);
				add(t1,T2);add(T1,t2);
				T1=merge(T1,t1);T2=merge(T2,t2);
			end else begin
				int cyclen=cyc[ty]->len;
				int y=ty;
				static tnode *_t1[MAXN],*_t2[MAXN];
				while y!=x do begin
					solve(y,_t1[y],_t2[y]);
					y=mo_e[y]->y;
				end;
				
				tnode *tmp1,*tmp2,*tmp;
				
				int last=cyc[ty]->last;
				if check_mindist(last,x,cyclen) then begin
					y=ty;
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					while y!=x do begin
						update_ans(tmp1,tmp2,_t1[y],_t2[y],dep[y]-dep[x]);
						merge(tmp1,tmp2,_t1[y],_t2[y],-(dep[y]-dep[x]));
						y=mo_e[y]->y;
					end;
					_tr_tot=tmp;
				end else if !check_mindist(ty,x,cyclen) then begin
					y=last;
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					while y!=x do begin
						update_ans(tmp1,tmp2,_t1[y],_t2[y],cyclen-(dep[y]-dep[x]));
						merge(tmp1,tmp2,_t1[y],_t2[y],-(cyclen-(dep[y]-dep[x])));
						y=fa_e[y]->y;
					end;
					_tr_tot=tmp;
				end else begin
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					y=ty;
					while check_mindist(y,x,cyclen) do begin
						update_ans(tmp1,tmp2,_t1[y],_t2[y],dep[y]-dep[x]);
						merge(tmp1,tmp2,_t1[y],_t2[y],-(dep[y]-dep[x]));
						y=mo_e[y]->y;
					end;
					_tr_tot=tmp;
					
					int A=fa_e[y]->y;
					int B=y;
					y=last;
					
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					while y!=A do begin
						update_ans(tmp1,tmp2,_t1[y],_t2[y],cyclen-(dep[y]-dep[x]));
						merge(tmp1,tmp2,_t1[y],_t2[y],-(cyclen-(dep[y]-dep[x])));
						y=fa_e[y]->y;
					end;
					_tr_tot=tmp;
					
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					y=last;
					int i=A;
					while i!=x do begin
						while (dep[i]+cyclen-dep[y])*2<cyclen do begin
							merge(tmp1,tmp2,_t1[y],_t2[y],cyclen-(dep[y]-dep[x]));
							y=fa_e[y]->y;
						end;
						update_ans(tmp1,tmp2,_t1[i],_t2[i],dep[i]-dep[x]);
						i=fa_e[i]->y;
					end;
					_tr_tot=tmp;
					
					tmp1=tmp2=NULL;
					tmp=_tr_tot;
					y=B;
					i=ty;
					while i!=B do begin
						while y!=x && (dep[i]+cyclen-dep[y])*2>=cyclen do begin
							merge(tmp1,tmp2,_t1[y],_t2[y],dep[y]-dep[A]);
							y=mo_e[y]->y;
						end;
						update_ans(tmp1,tmp2,_t1[i],_t2[i],dep[A]-dep[i]);
						i=mo_e[i]->y;
					end;
					_tr_tot=tmp;
				end;
				
				
				y=ty;
				tmp1=tmp2=NULL;
				while y!=x do begin
					int d=std::min(dep[y]-dep[x],cyclen-(dep[y]-dep[x]));
					if _t1[y] then _t1[y]->add_tag(d*2);
					if _t2[y] then _t2[y]->add_tag(-d*2);
					tmp1=merge(tmp1,_t1[y]);
					tmp2=merge(tmp2,_t2[y]);
					y=mo_e[y]->y;
				end;
				
				add(T1,tmp2);
				add(tmp1,T2);
				T1=merge(T1,tmp1);
				T2=merge(T2,tmp2);
				
				
			end;
		end;
	end;
	
	inline void solve()
	begin
		idtot=n+q;
		_tr_tot=_tr+n+q;
		int i;
		for i=1;i<=m;i++ do begin
			int u,v,len;
			read(u);read(v);read(len);
			addedge(u,v,len);
		end;
		for i=1;i<=q;i++ do begin
			read(_x[i]);read(_d[i]);
			_qid[_x[i]].push_back(i);
		end;
		for i=1;i<=n;i++ do begin
			if _qid[i].size()==0 then continue;
			std::sort(&_qid[i].front(),&_qid[i].back()+1,cmp_d);
		end;
		dfs(1);
		tnode *t1,*t2;
		solve(1,t1,t2);
	end;
	
end;

int main()
begin
	read(n);read(m);read(q);
	treap_merge::solve();
	Graph::out();
end