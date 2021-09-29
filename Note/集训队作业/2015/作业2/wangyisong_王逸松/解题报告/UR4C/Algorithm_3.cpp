#include <stdio.h>
#include <string.h>
#include <queue>
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

#define MAXN 1005

int n,k;
int w[MAXN];
int fa[MAXN],h[MAXN];
bool visit[MAXN];
int list[MAXN][MAXN];
int lcnt[MAXN];
int wid[MAXN];

inline bool cmpw(int i,int j)
begin
	return w[i]<w[j];
end;

inline void pre()
begin
	int i;
	for i=1;i<=n;i++ do begin
		wid[i]=i;
	end;
	std::sort(wid+1,wid+n+1,cmpw);
end;

inline void add(int x,int y)
begin
	int hx=h[x],hy=h[y];
	while hx>hy do visit[x]=1,x=fa[x],--hx;
	while hy>hx do visit[y]=1,y=fa[y],--hy;
	while x^y do visit[x]=visit[y]=1,x=fa[x],y=fa[y];
	visit[x]=1;
end;

inline void get(int id)
begin
	memset(visit,0,sizeof(visit));
	int x,y,z;
	read(x);read(y);read(z);
	add(x,y);add(y,z);add(x,z);
	int i;
	for i=1;i<=n;i++ do begin
		int x=wid[i];
		if visit[x] then begin
			list[id][++lcnt[id]]=x;
		end;
	end;
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

std::priority_queue<data> PQ;

inline void solve()
begin
	int i;
	for i=1;i<=n;i++ do begin
		PQ.push((data){w[i],i,i,lcnt[i]});
	end;
	while k-- do begin
		data t=PQ.top();
		PQ.pop();
		int W=t.w;
		printf("%d\n",W);
		int id=t.id;
		int from=t.from;
		int pos=t.pos;
		int x=list[id][1];
		PQ.push((data){W+w[x],x,id,1});
		if pos<lcnt[from] then begin
			x=list[from][pos+1];
			PQ.push((data){W+w[x]-w[id],x,from,pos+1});
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
	end;
	pre();
	for i=1;i<=n;i++ do begin
		get(i);
	end;
	solve();
end