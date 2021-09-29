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

#define MAXN 500005
#define MAXHSIZE (MAXN+500005*4)

int n,k;
int w[MAXN];
int fa[MAXN],h[MAXN];

int _ch[MAXN],size[MAXN];
int d1[MAXN],_tot;

int up[MAXN];
int _mi[MAXN];

inline void _pre()
begin
	int i;
	for i=1;i<=n;i++ do begin
		if !d1[i] then begin
			int j=i;
			while j do begin
				d1[j]=++_tot;
				up[j]=i;
				j=_ch[j];
			end;
		end;
	end;
end;

#define M (1<<19)

int T[M<<1];

inline void pre()
begin
	int i;
	for i=n;i>=2;i-- do begin
		++size[i];
		int f=fa[i];
		size[f]+=size[i];
		_ch[f]=size[_ch[f]]>size[i] ? _ch[f] : i;
	end;
	up[1]=1;_mi[1]=1;T[1+M]=1;
	_pre();
	for i=2;i<=n;i++ do begin
		T[d1[i]+M]=i;
		if up[i]==i then begin
			_mi[i]=i;
		end else begin
			int t=_mi[fa[i]];
			_mi[i]=w[t]<w[i] ? t : i;
		end;
	end;
	int l=1+M,r=n+M;
	while l^1 do begin
		l>>=1;r>>=1;
		for i=r;i>=l;i-- do T[i]=w[T[i+i]]<w[T[i+i+1]] ? T[i+i] : T[i+i+1];
	end;
end;

inline int getlca(int x,int y)
begin
	int ux=up[x],uy=up[y];
	while ux^uy do begin
		if h[ux]>h[uy] then begin
			x=fa[ux];
			ux=up[x];
		end else begin
			y=fa[uy];
			uy=up[y];
		end;
	end;
	return h[x]<h[y] ? x : y;
end;

inline int que(int l,int r)
begin
	int ret=T[l+M];
	l+=M-1;r+=M+1;
	while l^r^1 do begin
		if ~l&1 then ret=w[T[l^1]]<w[ret] ? T[l^1] : ret;
		if r&1 then ret=w[T[r^1]]<w[ret] ? T[r^1] : ret;
		l>>=1;r>>=1;
	end;
	return ret;
end;

inline int getmin_d(int x,int d)
begin
	int ret=x;
	while 1 do begin
		int u=up[x];
		int len=h[x]-h[u]+1;
		if d>len then begin
			int t=_mi[x];
			ret=w[ret]<w[t] ? ret : t;
			d-=len;
			x=fa[u];
		end else begin
			int t=que(d1[x]-d+1,d1[x]);
			return w[ret]<w[t] ? ret : t;
		end;
	end;
end;

struct data0 begin
	int x1,d1,x2,d2,x3,d3;
end;

data0 A[MAXN];

inline void get(int id)
begin
	int _x,_y,_z;
	read(_x);read(_y);read(_z);
	int _l1=getlca(_x,_y),_l2=getlca(_y,_z),_l3=getlca(_x,_z);
	int l1,l2,x,y,z;
	if _l1==_l2 then begin
		l1=_l1,l2=_l3;
		x=_y,y=_z,z=_x;
	end else if _l1==_l3 then begin
		l1=_l1,l2=_l2;
		x=_x,y=_y,z=_z;
	end else begin
		l1=_l2,l2=_l1;
		x=_z,y=_x,z=_y;
	end;
	A[id]=(data0){x,h[x]-h[l1],y,h[y]-h[l2],z,h[z]-h[l1]+1};
end;

struct data begin
	int w;
	int id;
	int x,d;
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

inline void push(int W,int x,int d)
begin
	int mi=getmin_d(x,d);
	push((data){W+w[mi],mi,x,d});
end;

inline void push(int W,int id)
begin
	if A[id].d1 then push(W,A[id].x1,A[id].d1);
	if A[id].d2 then push(W,A[id].x2,A[id].d2);
	if A[id].d3 then push(W,A[id].x3,A[id].d3);
end;

inline void solve()
begin
	int i;
	for i=1;i<=n;i++ do begin
		_H[i]=(data){w[i],i,i,1};
	end;
	hsize=n;
	std::make_heap(_H+1,_H+n+1);
	while k-- do begin
		data t=_H[1];
		pop();
		int W=t.w;
		printf("%d\n",W);
		int id=t.id;
		int x=t.x;
		int d=t.d;
		push(W,id);
		if id!=x then begin
			int len=h[x]-h[id];
			int mi=getmin_d(x,len);
			push((data){W+w[mi]-w[id],mi,x,len});
		end;
		if h[x]-d+1!=h[id] then begin
			int len=d-(h[x]-h[id]+1);
			int mi=getmin_d(fa[id],len);
			push((data){W+w[mi]-w[id],mi,fa[id],len});
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