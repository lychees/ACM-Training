#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define if if (
#define then )
#define do )
#define for for (
#define while while (
#define begin {
#define end }

template <class T>
inline void read(T &x,FILE *_f=stdin)
begin
	x=0;char ch=fgetc(_f);
	while ch<=32 do ch=fgetc(_f);
	while ch>32 do x=x*10+ch-48,ch=fgetc(_f);
end;

// ---------- SPJ Template ----------

#define SPJ_LEMON 1
#define SPJ_TSINSEN 2

FILE *fin, *fout, *fans, *fsco, *fmsg;
int SPJ_type;

inline void score(int s, const char *message)
begin
	if SPJ_type==SPJ_TSINSEN then begin
		if s>0 then s=1;
	end;
	fprintf(fsco, "%d\n", s);
	if fmsg != NULL then fprintf(fmsg, "%s\n", message);
	fclose(fin);
	fclose(fans);
	fclose(fsco);
	if fout != NULL then fclose(fout);
	if fmsg != NULL then fclose(fmsg);
	exit(0);
end;

inline void fileNotFound()
begin
	score(0, "Cannot find contestant's output file");
end;

// void WA(const char *s) {score(0,s);}

#define WA(...) { if fmsg then fprintf(fmsg,__VA_ARGS__); score(0,""); }
#define AC(...) { if fmsg then fprintf(fmsg,__VA_ARGS__); score(10,""); }


inline void init_SPJ(int type,int argc,char **argv)
begin
	SPJ_type=type;
	if type==SPJ_LEMON then begin
		fin = fopen(argv[1], "r");   // input file (th11.*.in)
		fans = fopen(argv[3], "r");  // answer file (th11.*.ans)
		fsco = fopen(argv[5], "w");  // score output file (cannot be NULL)
		fmsg = fopen(argv[6], "w");  // message output file (can be NULL)
		fout = fopen(argv[2], "r");  // contestant output file (th11.*.out)
		
		if !fin then return exit(0);
		if fout == NULL then fileNotFound();
	end else if type==SPJ_TSINSEN then begin
		fin=fopen(argv[1],"r");
		fout=fopen(argv[2],"r");
		fans=fopen(argv[3],"r");
		fsco=fopen(argv[4],"w");
		fmsg=NULL;
	end;
end;

inline int getint(int l,int r)
begin
	if l>r then begin
		WA("SPJERR (l=%d, r=%d)",l,r);
	end;
	int ret=-1;
	fscanf(fout,"%d",&ret);
	if ret<l || ret>r then begin
		WA("got %d, expected an integer in [%d, %d]",ret,l,r);
	end;
	return ret;
end;


// ----------------------------

#define u32 unsigned int
#define u64 unsigned long long

#define MAXV 1300005
#define MAXE 3000005

// #define LIM_V 1000000
// #define LIM_E 3000000

int n,m,q;

const u32 mo1=1000000009u;
const u32 mo2=1050000011u;

struct data begin
	u32 p1,p2;
	u32 ma,mi;
	u32 size,size_m1,size_m2;
	u64 sum;
	u32 sum_m1,sum_m2;
end;

inline data new_data(u32 x)
begin
	return (data){x%mo1,x%mo2,x,x,1,1,1,x,x%mo1,x%mo2};
end;

inline data operator + (const data &a,const data &b)
begin
	return (data){
		1ull*a.p1*b.p1%mo1,1ull*a.p2*b.p2%mo2,
		std::max(a.ma,b.ma),std::min(a.mi,b.mi),
		a.size+b.size,(a.size_m1+b.size_m1)%mo1,(a.size_m2+b.size_m2)%mo2,
		a.sum+b.sum,(a.sum_m1+b.sum_m1)%mo1,(a.sum_m2+b.sum_m2)%mo2
	};
end;

inline bool operator == (const data &a,const data &b)
begin
	return a.p1==b.p1 && a.p2==b.p2 &&
		a.ma==b.ma && a.mi==b.mi &&
		a.size==b.size && a.size_m1==b.size_m1 && a.size_m2==b.size_m2 &&
		a.sum==b.sum && a.sum_m1==b.sum_m1 && a.sum_m2==b.sum_m2;
end;

inline void out(const data &a,FILE *f=stdout)
begin
	fprintf(f,"_________ %u %u %u %u %u %u %u %llu %u %u      \n",a.p1,a.p2,a.ma,a.mi,a.size,a.size_m1,a.size_m2,a.sum,a.sum_m1,a.sum_m2);
end;

data f[MAXV];
bool visit[MAXV];

int ind[MAXV];

int V,E;

struct edge begin
	edge *next;
	int y;
end;

edge *se[MAXV],e[MAXE],*etot=e;

inline void addedge(int x,int y)
begin
	*++etot=(edge){se[x],y};
	se[x]=etot;
end;

bool _instack[MAXV];
bool _visit[MAXV];

inline void dfs(int x)
begin
	_instack[x]=1;
	_visit[x]=1;
	edge *te=se[x];
	while te do begin
		int ty=te->y;
		if _instack[ty] then begin
			WA("not a DAG");
		end else if !_visit[ty] then begin
			dfs(ty);
		end;
		te=te->next;
	end;
	_instack[x]=0;
end;

inline data F(int x)
begin
	if visit[x] then return f[x];
	edge *te=se[x];
	data ret=(data){1,1,0,4294967295u,0,0,0,0ull,0,0};
	while te do begin
		ret=ret+F(te->y);
		te=te->next;
	end;
	f[x]=ret;
	visit[x]=1;
	return ret;
end;

inline void check()
begin
	// int type;
	// fscanf(fin,"%d",&type);
	// fscanf(fin,"%d%d%d",&n,&m,&q);
	// int testcase,type;
	// fscanf(fin,"%d%d",&testcase,&type);
	int LIM_V,LIM_E;
	// LIM_V=_LIM_V[testcase];
	// LIM_E=_LIM_E[testcase];
	LIM_V=1200000;
	LIM_E=2400000;
	fscanf(fin,"%d%d%d",&n,&m,&q);
	V=getint(n+q,LIM_V);
	E=getint(0,LIM_E);
	int i;
	for i=1;i<=E;i++ do begin
		int u,v;
		u=getint(n+1,V);
		v=getint(1,V);
		addedge(u,v);
		++ind[v];
	end;
	for i=1;i<=n;i++ do begin
		u32 x;
		// fscanf(fans,"%u",&x);
		read(x,fans);
		// fprintf(fmsg,"a %d = %u   \n",i,x);
		visit[i]=1;
		f[i]=new_data(x);
	end;
	for i=1;i<=q;i++ do begin
		if !_visit[n+i] then dfs(n+i);
	end;
	for i=1;i<=q;i++ do begin
		data x=F(n+i);
		data x1;
		memset(&x1,0,sizeof(x1));
		read(x1.p1,fans);read(x1.p2,fans);
		read(x1.ma,fans);read(x1.mi,fans);
		read(x1.size,fans);read(x1.size_m1,fans);read(x1.size_m2,fans);
		read(x1.sum,fans);read(x1.sum_m1,fans);read(x1.sum_m2,fans);
		if !(x==x1) then begin
			// out(x,fmsg);
			// out(x1,fmsg);
			WA("Wrong Answer on query %d",i);
		end;
	end;
	AC("ok, n = %d, q = %d, V = %d, E = %d",n,q,V,E);
end;




int main(int argc,char **argv)
begin
	init_SPJ(SPJ_TSINSEN,argc,argv);
	check();
end