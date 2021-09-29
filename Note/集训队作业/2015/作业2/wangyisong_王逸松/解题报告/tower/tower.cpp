#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <algorithm>

#define MAXEVENT 140

#define BITSET_SIZE (MAXEVENT)

#include "bitset.h"

#include "hashmap.h"

#define MAXN 35
#define KEY_CNT 3

#define MAX_STAT_CNT 7000000

#define INF 100000000

#define u32 unsigned int

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define begin {
#define end }

template <class T>
inline void read(T &x)
begin
	x=0;char ch=getchar();
	while ch<=32 do ch=getchar();
	int f=1;
	if ch=='-' then f=-1,ch=getchar();
	while ch>32 do x=x*10+ch-48,ch=getchar();
	x*=f;
end;

template <class T>
inline T max(T a,T b){return a>b?a:b;}
template <class T>
inline T min(T a,T b){return a<b?a:b;}
template <class T>
inline void swap(T &a,T &b){T t=a;a=b;b=t;}

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};

int n,m;
int hcnt,dh[105];
int acnt,da[105];
int dcnt,dd[105];
int icnt,di[105];
int mcnt;
int mh[105],ma[105],md[105],mp1[105],mp2[105];
int map[MAXN][MAXN];
int sx,sy,ex,ey;

struct human begin
	int h,a,d,i;
	short k[KEY_CNT];
	
	inline u32 getHash(u32 MOD) const
	begin
		u32 ret=((1ull<<32)*a+d)%MOD;
		ret=((1ull<<32)*ret+i)%MOD;
		int i;
		for i=0;i<KEY_CNT;i++ do begin
			ret=((1ull<<32)*ret+i)%MOD;
		end;
		return ret;
	end;
end;

inline bool operator == (const human &a,const human &b)
begin
	if a.a!=b.a || a.d!=b.d || a.i!=b.i then return false;
	for int i=0;i<KEY_CNT;i++ do if a.k[i]!=b.k[i] then return false;
	return true;
end;

human s_,e_;

inline void readhuman(human &x)
begin
	read(x.h);read(x.a);read(x.d);read(x.i);
	int i;
	for i=0;i<KEY_CNT;i++ do read(x.k[i]);
end;

inline void printhuman(const human &x)
begin
	printf("%d %d %d %d ",x.h,x.a,x.d,x.i);
	int i;
	for i=0;i<KEY_CNT;i++ do printf(" %d",x.k[i]);
end;

inline void read_data()
begin
	read(n);read(m);
	int i,j;
	read(hcnt);
	for i=1;i<=hcnt;i++ do read(dh[i]);
	read(acnt);
	for i=1;i<=acnt;i++ do read(da[i]);
	read(dcnt);
	for i=1;i<=dcnt;i++ do read(dd[i]);
	read(icnt);
	for i=1;i<=icnt;i++ do read(di[i]);
	read(mcnt);
	for i=1;i<=mcnt;i++ do begin
		read(mh[i]);read(ma[i]);read(md[i]);read(mp1[i]);read(mp2[i]);
	end;
	for i=1;i<=n;i++ do begin
		for j=1;j<=m;j++ do begin
			read(map[i][j]);
		end;
	end;
	read(sx);read(sy);readhuman(s_);
	read(ex);read(ey);readhuman(e_);
end;

inline int calc(int h1,int a1,int d1,int p1,int p2,int a,int d,int i)
begin
	if a<=d1 then return INF;
	if p1>p2 then swap(p1,p2);
	if (p1==4096 || p2==4096) then begin
		printf("NOT IMPLEMENTED (p1 %d p2 %d)\n",p1,p2);
		exit(1);
	end;
	if (p1==9920 || p2==9920) then begin
		printf("NOT IMPLEMENTED (p1 %d p2 %d)\n",p1,p2);
		exit(1);
	end;
	if (p1==9960 || p2==9960) then begin
		printf("NOT IMPLEMENTED (p1 %d p2 %d)\n",p1,p2);
		exit(1);
	end;
	if (p1==64 || p2==64) then begin
		d=0;
	end;
	if (p1==8 || p2==8) then begin
		d1=max(d1,a-1);
	end;
	int A=max(a1-d,0);
	int ret=0;
	if (p1==16 || p2==16) then begin
		ret+=A;
	end;
	if (p1==233 || p2==233) then begin
		printf("NOT IMPLEMENTED (p1 %d p2 %d)\n",p1,p2);
		exit(1);
	end;
	int cnt=1;
	if p1<0 then cnt*=-p1;
	ret+=(h1-1)/(a-d1)*(a1-d)*cnt;
	return max(ret-i,0);
end;

inline int calc(int id,int a,int d,int i)
begin
	return calc(mh[id],ma[id],md[id],mp1[id],mp2[id],a,d,i);
end;

inline int calc(int id,const human &x)
begin
	// no pre-calc
	return calc(mh[id],ma[id],md[id],mp1[id],mp2[id],x.a,x.d,x.i);
end;

struct event begin
	int x,y;
	int data;
end;

event e[MAXEVENT];
int ecnt;

int e_adj[MAXEVENT][MAXEVENT];
int e_adj_cnt[MAXEVENT];
int eid[MAXN][MAXN];
int s_id;
int e_id;

inline void pre_e(int id)
begin
	static int l1[MAXN*MAXN],l2[MAXN*MAXN];
	static bool visit[MAXN][MAXN];
	memset(visit,0,sizeof(visit));
	int s=0,t=1;
	l1[1]=e[id].x,l2[1]=e[id].y;
	visit[e[id].x][e[id].y]=1;
	int cnt=0;
	while s<t do begin
		int x=l1[++s],y=l2[s];
		int i;
		for i=0;i<4;i++ do begin
			int nx=x+dx[i],ny=y+dy[i];
			if nx<1 || ny<1 || nx>n || ny>m then continue;
			if visit[nx][ny] then continue;
			if map[nx][ny]==1 then continue;
			visit[nx][ny]=1;
			int tid=eid[nx][ny];
			if tid>=0 then begin
				e_adj[id][cnt++]=tid;
			end else begin
				l1[++t]=nx,l2[t]=ny;
			end;
		end;
	end;
	e_adj_cnt[id]=cnt;
end;

inline void init_event()
begin
	int i,j;
	int cnt=0;
	for i=1;i<=n;i++ do begin
		for j=1;j<=m;j++ do begin
			bool t=map[i][j]!=0 && map[i][j]!=1;
			if i==sx && j==sy then t=1;
			if i==ex && j==ey then t=1;
			cnt+=t;
		end;
	end;
	if cnt>MAXEVENT then begin
		fprintf(stderr,"too many events (needed = %d, MAXEVENT = %d)\n",cnt,MAXEVENT);
		exit(1);
	end;
	for i=1;i<=n;i++ do begin
		for j=1;j<=m;j++ do begin
			bool t=map[i][j]!=0 && map[i][j]!=1;
			if i==sx && j==sy then t=1;
			if i==ex && j==ey then t=1;
			if t then begin
				e[ecnt++]=(event){i,j,map[i][j]};
				eid[i][j]=ecnt-1;
			end else begin
				eid[i][j]=-1;
			end;
		end;
	end;
	for i=0;i<ecnt;i++ do begin
		if e[i].x==sx && e[i].y==sy then s_id=i;
		if e[i].x==ex && e[i].y==ey then e_id=i;
		pre_e(i);
	end;
end;

inline void init()
begin
	init_event();
end;

struct map_key begin
	bitset now;
	human a;
	
	inline u32 getHash(u32 MOD) const
	begin
		return ((1ull<<32)*now.getHash(MOD)+a.getHash(MOD))%MOD;
	end;
end;

inline bool operator == (const map_key &a,const map_key &b)
begin
	return a.now==b.now && a.a==b.a;
end;

struct Stat begin
	bitset now,next;
	human a;
	const Stat *last;
	short event_cnt;
	short did;
	
	inline void add(int id)
	begin
		if now.is1(id) then return;
		now.set1(id);
		next.set0(id);
		++event_cnt;
		int i;
		for i=0;i<e_adj_cnt[id];i++ do begin
			int id1=e_adj[id][i];
			if !now.is1(id1) then next.set1(id1);
		end;
	end;
	
	inline map_key get_key() const
	begin
		return (map_key){now,a};
	end;
end;

inline bool cmpstat(const Stat *a,const Stat *b)
begin
	return !(a->event_cnt<b->event_cnt);
end;

Stat _statpool[MAX_STAT_CNT],*_stattot=_statpool;

inline bool isEndStat_human(const human &a)
begin
	bool f=a.h>=e_.h && a.a>=e_.a && a.d>=e_.d && a.i>=e_.i;
	int i;
	for i=0;i<KEY_CNT;i++ do f=f && a.k[i]>=e_.k[i];
	return f;
end;

inline bool isEndStat(const Stat *a)
begin
	return a->now.is1(e_id) && isEndStat_human(a->a);
end;

inline void printStat(const Stat *s)
begin
	putchar('[');
	printhuman(s->a);
	putchar(']');
	putchar('\n');
end;

inline void printevent(int id,human a)
begin
	if e[id].data==0 then return;
	printf("go to (%d, %d)  val=%d ",e[id].x,e[id].y,e[id].data);
	int val=e[id].data;
	if val>500 then begin
		int tmp=calc(val-500,a);
		printf("[-%d] ",tmp);
		a.h-=tmp;
	end else if val>400 then begin
		printf("[+%d] ",di[val-400]);
		a.i+=di[val-400];
	end else if val>300 then begin
		printf("[+%d] ",dd[val-300]);
		a.d+=dd[val-300];
	end else if val>200 then begin
		printf("[+%d] ",da[val-200]);
		a.a+=da[val-200];
	end else if val>100 then begin
		printf("[+%d] ",dh[val-100]);
		a.h+=dh[val-100];
	end else if val>=21 && val<=20+KEY_CNT then begin
		printf("[k%d -1] ",val-20);
		--a.k[val-21];
	end else if val>=11 && val<=10+KEY_CNT then begin
		printf("[k%d +1] ",val-10);
		++a.k[val-11];
	end else begin
		if val!=0 then printf("val %d\n",val);
		assert(val==0);
	end;
	putchar('[');
	printhuman(a);
	putchar(']');
	putchar('\n');
end;

inline Stat getInitStat_0()
begin
	Stat a;
	memset(&a,0,sizeof(a));
	a.a=s_;  // human
	a.add(s_id);
	a.did=s_id;
	return a;
end;

inline Stat getInitStat()
begin
	Stat a;
	memset(&a,0,sizeof(a));
	a.a=s_;  // human
	a.add(s_id);
	a.did=s_id;
	return a;
end;

inline bool go(human &a,int val)
begin
	if val>500 then begin
		a.h-=calc(val-500,a);
		return a.h>0;
	end;
	if val>=21 && val<=20+KEY_CNT then begin
		return --a.k[val-21]>=0;
	end;
	if val>400 then begin
		a.i+=di[val-400];
	end else if val>300 then begin
		a.d+=dd[val-300];
	end else if val>200 then begin
		a.a+=da[val-200];
	end else if val>100 then begin
		a.h+=dh[val-100];
	end else if val>=11 && val<=10+KEY_CNT then begin
		++a.k[val-11];
	end else begin
		if val!=0 then printf("val = %d\n",val);
		assert(val==0);
	end;
	return 1;
end;

inline bool can_go(const human &a,int val)
begin
	if val>500 then begin
		return a.h>calc(val-500,a);
	end else if val>=21 && val<=20+KEY_CNT then begin
		return a.k[val-21]>0;
	end else begin
		assert(val!=1);
		return 1;
	end;
end;

inline int can_get(const Stat &a,int id)
begin
	if id==e_id then return 0;
	
	int val=e[id].data;
	
	if val>500 then begin
		int tmp=calc(val-500,a.a);
		if tmp==0 then begin
			return 1;
		end;
	end else if val>400 then begin
		return 1;
	end else if val>300 then begin
		return 1;
	end else if val>200 then begin
		return 1;
	end else if val>100 then begin
		return 1;
	end else if val>=21 && val<=20+KEY_CNT then begin
		// skip
		// return 0;
	end else if val>=11 && val<=10+KEY_CNT then begin
		return 1;
	end else begin
		assert(val==0);
		return 1;
	end;
	
	assert(val>500 || (val>=21 && val<=23));
	
	int i;
	for i=0;i<e_adj_cnt[id];i++ do begin
		int id1=e_adj[id][i];
		// if val<500 then begin
		// 	if !a.now.is1(id1) then break;
		// end else begin
			if !a.now.is1(id1) && !a.next.is1(id1) then break;
		// end;
	end;
	
	if i>=e_adj_cnt[id] then begin
		return 2;
	end else begin
		return 0;
	end;
end;

inline Stat go_opt(Stat a,bool _print = 0)
begin
	static int l[MAXEVENT+5];
	int s=0,t=0;
	int id=a.next.is1(0) ? 0 : a.next.findnext(0);
	while id<ecnt do begin
		if !a.now.is1(id) then begin
			int tmp=can_get(a,id);
			if tmp then begin
				a.add(id);
				if tmp==1 then begin
					if _print then printevent(id,a.a);
					go(a.a,e[id].data);
				end;
				l[++t]=id;
			end;
		end;
		id=a.next.findnext(id);
	end;
	while s<t do begin
		int x=l[++s];
		int i;
		for i=0;i<e_adj_cnt[x];i++ do begin
			int y=e_adj[x][i];
			if a.now.is1(y) then continue;
			int tmp=can_get(a,y);
			if !tmp then continue;
			a.add(y);
			if tmp==1 then begin
				if _print then printevent(y,a.a);
				go(a.a,e[y].data);
			end;
			l[++t]=y;
		end;
	end;
	
	return a;
end;

inline Stat go(const Stat *a0,int id,bool _print = 0)  // id in a0->next
begin
	Stat a=*a0;
	assert(a0->next.is1(id));
	assert(a0->next.is1(id));
	// if !go(a.a,e[id].data) then begin
	// 	a.a.h=-1;
	// 	return a;
	// end;
	// a.add(id);
	a.did=id;
	a.last=a0;
	
	while 1 do begin
		if _print then begin
			printevent(id,a.a);
		end;
		if !go(a.a,e[id].data) then begin
			a.a.h=-1;
			return a;
		end;
		int val=e[id].data;
		// bool f=1;
		if id==e_id || (val<500 && !(val>=21 && val<=20+KEY_CNT)) then begin
			// f=0;
			a.add(id);
			break;
		end;
		// if val<500 then f=0;
		int y=-1;
		// if f then begin
		int i;
		for i=0;i<e_adj_cnt[id];i++ do begin
			y=e_adj[id][i];
			// printf("[id %d    y %d   now %d next %d]\n",id,y,a.now.is1(y),a.next.is1(y));
			if !a.now.is1(y) && !a.next.is1(y) then break;
		end;
		if i>=e_adj_cnt[id] then y=-1;
		// if y!=-1 then printf("found y = %d  id %d\n",y,id);
		// if y!=-1 then printf("found  (id %d) y = %d   now[y] %d   next[y] %d\n",id,y,a.now.is1(y),a.next.is1(y));
		if y!=-1 then begin
			int j;
			for j=i+1;j<e_adj_cnt[id];j++ do begin
				int y1=e_adj[id][j];
				if !a.now.is1(y1) && !a.next.is1(y1) then break;
			end;
			if j<e_adj_cnt[id] then begin
				y=-2;
			end;
			// printf("now  (id %d) y = %d   now[y] %d   next[y] %d\n",id,y,a.now.is1(y),a.next.is1(y));
		end;
		// f=y!=-1;
		// end;
		a.add(id);
		if y==-1 then begin
			a.a.h=-1;return a;
			// break;
		end else if y==-2 then begin
			break;
		end else if y>=0 then begin
			id=y;
			// printf("y = %d   now[y] %d   next[y] %d\n",y,a.now.is1(y),a.next.is1(y));
			assert(a.next.is1(y));
		end;
	end;
	
	while 1 do begin
		Stat b=go_opt(a,_print);
		if a.now==b.now then break;
		a=b;
	end;
	
	return a;
end;

inline void printOp(const Stat *s0,const Stat *s1,int did)
begin
	// printevent(did,s0->a);
	go(s0,did,1);
end;

inline void printPath(const Stat *s)
begin
	static const Stat *A[MAXEVENT+5];
	int cnt=0;
	while s do begin
		A[++cnt]=s;
		s=s->last;
	end;
	Stat tmp0=getInitStat_0();
	A[++cnt]=&tmp0;
	int i;
	printStat(A[cnt]);
	for i=cnt-1;i>=1;i-- do begin
		const Stat *s0=A[i+1],*s1=A[i];
		int did=s1->did;
		if i!=cnt-1 then printOp(s0,s1,did);
	end;
end;

hashmap<map_key,Stat *,MAX_STAT_CNT> M;

Stat *_queue[MAX_STAT_CNT];
int q_size;
int q_tot;

inline void _push(Stat *s)
begin
	++q_tot;
	_queue[++q_size]=s;
	std::push_heap(_queue+1,_queue+q_size+1,cmpstat);
end;

inline Stat * _top()
begin
	return _queue[1];
end;

inline void _pop()
begin
	std::pop_heap(_queue+1,_queue+(q_size--)+1,cmpstat);
end;

inline void push(Stat s)
begin
	Stat *&t=M[s.get_key()];
	if !t then begin
		*++_stattot=s;
		t=_stattot;
		_push(t);
	end else begin
		if s.a.h>t->a.h then begin
			t->a=s.a;
			t->last=s.last;
			t->did=s.did;
		end;
	end;
end;

inline void solve()
begin
	push(getInitStat());
	int cnt=0;
	while q_size>0 do begin
		++cnt;
		Stat *s=_top();
		_pop();
		if cnt%10000==0 then begin
			// fprintf(stderr,"popped %d pushed %d  q_size %d\n",cnt,q_tot,q_size);
			fprintf(stderr,"popped %d pushed %d  q_size %d   event_cnt %d\n",cnt,q_tot,q_size,s->event_cnt);
		end;
		int id=s->next.is1(0) ? 0 : s->next.findnext(0);
		while id<ecnt do begin
			Stat s1=go(s,id);
			if s1.a.h>0 then begin
				push(s1);
			end;
			id=s->next.findnext(id);
		end;
	end;
	printf("stat tot = %ld\n",(long)(_stattot-_statpool));
	int i;
	Stat *ans=NULL;
	int anscnt=0,bestanscnt=0;
	int besth=0;
	for i=1;i<=_stattot-_statpool;i++ do begin
		Stat *s=_statpool+i;
		if isEndStat(s) then begin
			++anscnt;
			if s->a.h>besth then begin
				besth=s->a.h;
				ans=s;
				bestanscnt=1;
			end else if s->a.h==besth then begin
				++bestanscnt;
			end;
		end;
	end;
	if !ans then begin
		printf("No Solution\n");
	end else begin
		printf("anscnt = %d, bestanscnt = %d\n",anscnt,bestanscnt);
		putchar('[');
		printhuman(ans->a);
		putchar(']');
		putchar('\n');
		printPath(ans);
	end;
end;

inline void printProgramInfo()
begin
	printf("event_cnt %d of %d\n",ecnt,MAXEVENT);
	long mem_used=(long)q_tot*(sizeof(Stat));
	printf("mem: %ld KB \n",mem_used>>10);
end;

int main()
begin
	read_data();
	double time_start=clock();
	init();
	solve();
	printProgramInfo();
	printf("time: %.3lf s\n",(clock()-time_start)/CLOCKS_PER_SEC);
end