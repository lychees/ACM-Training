#include <stdio.h>
#include <vector>

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

#define MAXN 300005
#define INFLL 0x3f3f3f3f3f3f3f3fLL

#define u32 unsigned int
#define u64 unsigned long long

template <class T1=u64,class T2=long long,int SIZE=MAXN,u32 MOD=1000003u>
struct HashMap begin
	int first[MOD];
	int next[SIZE];
	T1 key[SIZE];
	T2 data[SIZE];
	int data_pool[SIZE];
	int *data_pool_p;
	
	inline HashMap()
	begin
		data_pool_p=data_pool+1;
		int i;
		for i=1;i<MAXN;i++ do begin
			data_pool[i]=i;
		end;
	end;
	
	inline int allocate()
	begin
		return *(data_pool_p++);
	end;
	
	inline void deallocate(int x)
	begin
		*(--data_pool_p)=x;
	end;
	
	inline int count(T1 x)
	begin
		int t=first[x%MOD];
		while t do begin
			if x==key[t] then return 1;
			t=next[t];
		end;
		return 0;
	end;
	
	inline T2& at(T1 x)
	begin
		int t=first[x%MOD];
		while 1 do begin
			if x==key[t] then break;
			t=next[t];
		end;
		return data[t];
	end;
	
	inline T2& operator [](T1 x)
	begin
		int pos=x%MOD;
		int t=first[pos];
		while t do begin
			if x==key[t] then return data[t];
			t=next[t];
		end;
		t=allocate();
		next[t]=first[pos];
		first[pos]=t;
		key[t]=x;
		return data[t];
	end;
	
	inline void erase(T1 x)
	begin
		int pos=x%MOD;
		int t=first[pos];
		int last=0;
		while 1 do begin
			if x==key[t] then break;
			last=t;
			t=next[t];
		end;
		if t==first[pos] then begin
			first[pos]=next[t];
		end else begin
			next[last]=next[t];
		end;
		deallocate(t);
	end;
	
	inline T2 at_and_erase(T1 x)
	begin
		int pos=x%MOD;
		int t=first[pos];
		int last=0;
		while 1 do begin
			if x==key[t] then break;
			last=t;
			t=next[t];
		end;
		if t==first[pos] then begin
			first[pos]=next[t];
		end else begin
			next[last]=next[t];
		end;
		deallocate(t);
		return data[t];
	end;
	
	inline bool access(T1 x,T2 *&p)
	begin
		int pos=x%MOD;
		int t=first[pos];
		while t do begin
			if x==key[t] then begin
				p=data+t;
				return 0;
			end;
			t=next[t];
		end;
		t=allocate();
		next[t]=first[pos];
		first[pos]=t;
		key[t]=x;
		p=data+t;
		return 1;
	end;
end;

int n,m,q;

struct edge begin
	edge *next,*rev;
	int y,len;
end;

edge *first[MAXN],e[MAXN*4],*etot=e;

inline void addedge(int x,int y,int len)
begin
	if x==y then return;
	++etot;
	*etot=(edge){first[x],etot+1,y,len};
	first[x]=etot;
	++etot;
	*etot=(edge){first[y],etot-1,x,len};
	first[y]=etot;
end;

edge *fa_e[MAXN],*mo_e[MAXN];

int dfn[MAXN];
int dfstot;

long long dep[MAXN];

struct cycle begin
	long long len;
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

long long ans[MAXN];

#define GET_ID(i,j) ((((u64)(i))<<32)+(u32)(j))

HashMap<u64,long long> M;  // (vector_id, query_id) -> max_depth  [vector_id might not equal to node_id]

std::vector<int> A[MAXN];  // data: query_id
long long A_tag[MAXN];
int size[MAXN];

inline void update_ans(int a,int b,long long add)
begin
	if size[a]<size[b] || !a then begin
		std::swap(a,b);
	end;
	long long tag=A_tag[a]+A_tag[b]+add;
	int cnt=A[b].size();
	int *B=&A[b].front();
	int i;
	for i=0;i<cnt;i++ do begin
		int qid=B[i];
		u64 id=GET_ID(a,qid);
		if M.count(id)==0 then continue;
		ans[qid]=std::max(ans[qid],M.at(GET_ID(b,qid))+M.at(id)+tag);
	end;
end;

struct mergeinfo begin
	int a,b;
	long long tag_a,tag_b;
	int cnt;
	int *qid;
	long long *val;
	long long *org_val;
end;

inline mergeinfo merge_0(int a,int b,long long tag_a,long long tag_b)
begin
	mergeinfo I;
	if size[a]<size[b] || !a then begin
		std::swap(a,b);
		std::swap(tag_a,tag_b);
	end;
	
	A_tag[a]+=tag_a;A_tag[b]+=tag_b;
	I.tag_a=tag_a;I.tag_b=tag_b;
	I.a=a;I.b=b;
	size[a]+=size[b];
	int cnt=A[b].size();
	I.cnt=cnt;
	
	if !cnt then return I;
	
	long long tag_delta=A_tag[b]-A_tag[a];  // from b to a
	int *B=&A[b].front();
	
	I.qid=new int[cnt];
	I.val=new long long[cnt];
	I.org_val=new long long[cnt];
	
	int i;
	for i=0;i<cnt;i++ do begin
		int qid=B[i];
		u64 id_b=GET_ID(b,qid);
		long long val=M.at_and_erase(id_b)+tag_delta;
		
		I.qid[i]=qid;
		I.val[i]=val-tag_delta;
		I.org_val[i]=-INFLL;
		
		u64 id_a=GET_ID(a,qid);
		long long *M_id_a;
		if M.access(id_a,M_id_a) then begin  // inserted
			*M_id_a=val;
			A[a].push_back(qid);
		end else begin
			I.org_val[i]=*M_id_a;
			*M_id_a=std::max(*M_id_a,val);
		end;
	end;
	A[b].clear();
	size[a]+=size[b];
	
	return I;
end;

inline void rollback(const mergeinfo &I)
begin
	int a=I.a,b=I.b;
	
	size[a]-=size[b];
	int cnt=I.cnt;
	A_tag[a]-=I.tag_a;
	A_tag[b]-=I.tag_b;
	if !cnt then return;
	std::vector<int> &B=A[b];
	int i;
	for i=0;i<cnt;i++ do begin
		int qid=I.qid[i];
		long long val=I.val[i];
		long long org_val=I.org_val[i];
		B.push_back(qid);
		M[GET_ID(b,qid)]=val;
		if org_val==-INFLL then begin
			M.erase(GET_ID(a,qid));
			A[a].pop_back();
		end else begin
			M.at(GET_ID(a,qid))=org_val;
		end;
	end;
	
	delete I.qid;
	delete I.val;
	delete I.org_val;
end;

inline int merge_1(int a,int b)
begin
	if size[a]<size[b] || !a then begin
		std::swap(a,b);
	end;
	long long tag_delta=A_tag[b]-A_tag[a];  // from b to a
	int cnt=A[b].size();
	int *B=&A[b].front();
	
	int i;
	for i=0;i<cnt;i++ do begin
		int qid=B[i];
		u64 id_b=GET_ID(b,qid);
		long long val=M.at_and_erase(id_b)+tag_delta;
		
		u64 id_a=GET_ID(a,qid);
		long long *M_id_a;
		if M.access(id_a,M_id_a) then begin  // inserted
			*M_id_a=val;
			A[a].push_back(qid);
		end else begin
			*M_id_a=std::max(*M_id_a,val);
		end;
	end;
	A[b].clear();
	size[a]+=size[b];
	
	return a;
end;

inline bool check_mindist(int x,int fa,long long cyclen)
begin
	return dep[x]-dep[fa]<cyclen-(dep[x]-dep[fa]);
end;

int vector_id[MAXN];

inline int solve(int x)  // vector_id
begin
	int ret=x;
	for edge *te=first[x];te;te=te->next do begin
		if te==fa_e[x] || te==mo_e[x] then continue;
		int ty=te->y;
		if te->rev==mo_e[ty] then continue;
		if !mo_e[ty] then begin
			int id=solve(ty);
			A_tag[id]+=te->len;
			update_ans(ret,id,0);
			ret=merge_1(ret,id);
		end else begin
			long long cyclen=cyc[ty]->len;
			int y=ty;
			while y!=x do begin
				vector_id[y]=solve(y);
				y=mo_e[y]->y;
			end;
			
			static std::vector<mergeinfo> I;
			static mergeinfo I_tmp;
			static int tmp;
			
			int last=cyc[ty]->last;
			if check_mindist(last,x,cyclen) then begin
				y=ty;
				tmp=0;
				while y!=x do begin
					update_ans(tmp,vector_id[y],dep[y]-dep[x]);
					I_tmp=merge_0(tmp,vector_id[y],0,-(dep[y]-dep[x]));
					I.push_back(I_tmp);
					tmp=I_tmp.a;
					y=mo_e[y]->y;
				end;
			end else if !check_mindist(ty,x,cyclen) then begin
				y=last;
				tmp=0;
				while y!=x do begin
					update_ans(tmp,vector_id[y],cyclen-(dep[y]-dep[x]));
					I_tmp=merge_0(tmp,vector_id[y],0,-(cyclen-(dep[y]-dep[x])));
					I.push_back(I_tmp);
					tmp=I_tmp.a;
					y=fa_e[y]->y;
				end;
			end else begin
				tmp=0;
				y=ty;
				while check_mindist(y,x,cyclen) do begin
					update_ans(tmp,vector_id[y],dep[y]-dep[x]);
					I_tmp=merge_0(tmp,vector_id[y],0,-(dep[y]-dep[x]));
					I.push_back(I_tmp);
					tmp=I_tmp.a;
					y=mo_e[y]->y;
				end;
				while !I.empty() do begin
					rollback(I.back());
					I.pop_back();
				end;
				
				int A=fa_e[y]->y;
				int B=y;
				y=last;
				
				tmp=0;
				while y!=A do begin
					update_ans(tmp,vector_id[y],cyclen-(dep[y]-dep[x]));
					I_tmp=merge_0(tmp,vector_id[y],0,-(cyclen-(dep[y]-dep[x])));
					I.push_back(I_tmp);
					tmp=I_tmp.a;
					y=fa_e[y]->y;
				end;
				while !I.empty() do begin
					rollback(I.back());
					I.pop_back();
				end;
				
				tmp=0;
				y=last;
				int i=A;
				while i!=x do begin
					while (dep[i]+cyclen-dep[y])*2<cyclen do begin
						I_tmp=merge_0(tmp,vector_id[y],0,cyclen-(dep[y]-dep[x]));
						I.push_back(I_tmp);
						tmp=I_tmp.a;
						y=fa_e[y]->y;
					end;
					update_ans(tmp,vector_id[i],dep[i]-dep[x]);
					i=fa_e[i]->y;
				end;
				while !I.empty() do begin
					rollback(I.back());
					I.pop_back();
				end;
				
				tmp=0;
				y=B;
				i=ty;
				while i!=B do begin
					while y!=x && (dep[i]+cyclen-dep[y])*2>=cyclen do begin
						I_tmp=merge_0(tmp,vector_id[y],0,dep[y]-dep[A]);
						I.push_back(I_tmp);
						tmp=I_tmp.a;
						y=mo_e[y]->y;
					end;
					update_ans(tmp,vector_id[i],dep[A]-dep[i]);
					i=mo_e[i]->y;
				end;
			end;
			while !I.empty() do begin
				rollback(I.back());
				I.pop_back();
			end;
			
			y=ty;
			tmp=0;
			while y!=x do begin
				long long d=std::min(dep[y]-dep[x],cyclen-(dep[y]-dep[x]));
				A_tag[vector_id[y]]+=d;
				tmp=merge_1(tmp,vector_id[y]);
				y=mo_e[y]->y;
			end;
			update_ans(ret,tmp,0);
			ret=merge_1(ret,tmp);
		end;
	end;
	return ret;
end;

int main()
begin
	read(n);read(m);
	int i;
	for i=1;i<=m;i++ do begin
		int u,v,len;
		read(u);read(v);read(len);
		addedge(u,v,len);
	end;
	read(q);
	for i=1;i<=q;i++ do begin
		int cnt;
		read(cnt);
		while cnt-- do begin
			int x;
			read(x);
			if A[x].empty() || A[x].back()!=i then begin
				A[x].push_back(i);
				++size[x];
				M[GET_ID(x,i)]=0;
			end;
		end;
	end;
	dfs(1);
	solve(1);
	for i=1;i<=q;i++ do begin
		printf("%lld\n",ans[i]);
	end;
end