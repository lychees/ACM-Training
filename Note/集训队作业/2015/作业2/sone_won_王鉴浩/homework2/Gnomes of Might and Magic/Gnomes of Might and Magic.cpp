#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#define N 200010
#define mk(x,y) make_pair(x,y)
#define Up update(tr[q],tr[tr[q].l],tr[tr[q].r])
#define Gen(x) gen(1,1,m,x)
#define wocao tmp=s,sb=a1,tt=a3,ttt=a2,tttt=ss,an1=i,an2=j,an3=k
#define For(i,x,y) for (i=x;i<=y;i++)
using namespace std;
struct w {
	int sum,x,y,len;
	inline bool operator < (const w &A) const {
		if (sum<A.sum) return 1;
		if (sum>A.sum) return 0;
		if (len<A.len) return 1;
		if (len>A.len) return 0;
		return x<A.x||x==A.x&&y<A.y;
	}
	inline bool operator == (const w &A) const {
		return sum==A.sum&&x==A.x&&y==A.y&&len==A.len;
	}
};
struct ww {
	int l,r,c;
	w a[2];
} tr[N*4],kong;
int i,j,k,n,m,t,q,ro,an1,an2,an3;
int se[N],id[N],root[N],ge[N],len[N];
vector<int> a[N];
inline void Gao(int x,int y) {
	ww O={},A=tr[root[y]];
	O.a[0]=(w){ge[y],a[0][y-1],a[0][y],1};
	O.a[1]=(w){ge[y],a[0][y],a[0][y-1],1};
	if (A.a[0]<O.a[0]) swap(A,O);
	tr[x].a[0]=O.a[0],tr[x].a[1]=O.a[1];
}
inline w merge(w a,w b) {
	int d[10]={},t=0;
	if (a.x&&a.x!=d[t]) d[++t]=a.x;
	if (a.y&&a.y!=d[t]) d[++t]=a.y;
	if (b.x&&b.x!=d[t]) d[++t]=b.x;
	if (b.y&&b.y!=d[t]) d[++t]=b.y;
	return (w){a.sum+b.sum,d[1],d[2],a.len+b.len};
}
inline void update(ww &a,ww b,ww c) {
	a.a[0]=merge(b.a[0],c.a[0]);
	a.a[1]=merge(c.a[1],b.a[1]);
}
inline ww Merge(ww a,ww b) {
	ww O=a;
	update(a,O,b);
	return a;
}
inline void Cl(int x) {
	tr[x].c=1;
	tr[x].a[0].sum=tr[x].a[1].sum=0;
}
inline void renew(int x) {
	if (tr[x].c) Cl(tr[x].l),Cl(tr[x].r);
	tr[x].c=0;
}
void Build(int _,int &q,int x,int y) {
	if (!q) q=++t;
	if (x==y) {
		tr[q].a[0]=(w){0,a[_][x-1],a[_][x],1};
		tr[q].a[1]=(w){0,a[_][x],a[_][x-1],1};
		return;
	}
	int mid=(x+y)/2;
	Build(_,tr[q].l,x,mid);
	Build(_,tr[q].r,mid+1,y);
	Up;
}
void build(int &q,int x,int y) {
	if (!q) q=++t;
	if (x==y) {
		Build(x,root[x],1,len[x]);
		Gao(q,x);
		return;
	}
	int mid=(x+y)/2;
	build(tr[q].l,x,mid);
	build(tr[q].r,mid+1,y);
	Up;
}
inline void Cl(int q,int x,int y,int l,int r) {
	if (l>r) return;
	if (l<=x&&y<=r) {
		Cl(q);
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (l<=mid) Cl(tr[q].l,x,mid,l,r);
	if (mid<r) Cl(tr[q].r,mid+1,y,l,r);
	Up;
}
inline void Renew(int x,int y) {
	if (!tr[x].c) return;
	tr[x].c=0;
	ww O={};
	O.a[0]=(w){ge[y],a[0][y+1],1};
	O.a[1]=(w){ge[y],a[0][y],1};
	if (O.a[0]<tr[root[y]].a[0]) ge[y]=0;
	else Cl(root[y],1,len[y],1,len[y]);
}
void Inc(int q,int x,int y,int k) {
	if (x==y) {
		tr[q].a[0].sum++;
		tr[q].a[1].sum++;
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (k<=mid) Inc(tr[q].l,x,mid,k);
	else Inc(tr[q].r,mid+1,y,k);
	Up;
}
void inc(int q,int x,int y,int k) {
	if (x==y) {
		Renew(q,x);
		ge[x]++;
		Gao(q,x);
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (k<=mid) inc(tr[q].l,x,mid,k);
	else inc(tr[q].r,mid+1,y,k);
	Up;
}
ww Cal(int q,int x,int y,int l,int r) {
	if (l>r) return kong;
	if (l<=x&&y<=r) return tr[q];
	renew(q);
	int mid=(x+y)/2,F=0;
	ww A;
	if (l<=mid) A=Cal(tr[q].l,x,mid,l,r),F=1;
	if (mid<r) {
		ww B=Cal(tr[q].r,mid+1,y,l,r);
		if (!F) A=B;
		else A=Merge(A,B);
	}
	return A;
}
void gen(int q,int x,int y,int k) {
	if (x==y) {
		Renew(q,x);
		Gao(q,x);
		return;
	}
	renew(q);
	int mid=(x+y)/2;
	if (k<=mid) gen(tr[q].l,x,mid,k);
	else gen(tr[q].r,mid+1,y,k);
	Up;
}







inline void jia(int x,int y) {
	int A=id[x],B=id[y];
	if (A==B&&se[x]>se[y]||!(A==m&&B==1)&&A>B||A==1&&B==m) swap(A,B),swap(x,y);
	if (A!=B&&x==a[0][A-1]&&y==a[0][A]) inc(1,1,m,A);
	else Gen(A),Inc(root[A],1,len[A],se[x]),Gen(A);
}
inline ww merge(int x1,int y1,int x2,int y2) {
	ww A=Cal(1,1,m,x1,y1),B=Cal(1,1,m,x2,y2);
	return Merge(A,B);
}
inline void wen(int x,int y) {
	int A=id[x],B=id[y],an1,an2,an3;
	ww tmp,tt,ttt,tttt,sb;
	an1=an2=an3=0;
	tmp.a[0].sum=N;
	Gen(A),Gen(B);
	if (A==B) {
		int _=0,l=se[x],r=se[y];
		if (l>r) swap(l,r),_=1;
		ww O=Cal(root[A],1,len[A],l,r-1);
		tmp.a[0]=O.a[_];
		an1=-1; an2=l,an3=r;
	}
	int i,j,k,X,Y;
	For(i,0,1) {
		ww a1=Cal(root[A],1,len[A],1,se[x]-1);
		if (i) a1=Cal(root[A],1,len[A],se[x],len[A]),X=A+1;
		else swap(a1.a[0],a1.a[1]),X=A;
		
		For(j,0,1) {
			ww a2=Cal(root[B],1,len[B],1,se[y]-1);
			if (j) {
				a2=Cal(root[B],1,len[B],se[y],len[B]),Y=B+1;
				swap(a2.a[0],a2.a[1]);
			} else Y=B;
			
			For(k,0,1) {
				ww a3;
				if (!k) {
					if (X<=Y) a3=Cal(1,1,m,X,Y-1);
					else a3=merge(X,m,1,Y-1);
				} else {
					if (X>=Y) a3=Cal(1,1,m,Y,X-1);
					else a3=merge(Y,m,1,X-1);
					swap(a3.a[0],a3.a[1]);
				}
				
				ww ss=Merge(a3,a2),s=Merge(a1,ss);
				if (s.a[0]<tmp.a[0]) wocao;
				else if (s.a[0]==tmp.a[0]&&a1.a[0].len==sb.a[0].len) {
					if (ss.a[0]<tttt.a[0]) wocao;
					else if (ss.a[0]==tttt.a[0]) {
						if (a3.a[0].len>tt.a[0].len&&a3.a[1].x<ttt.a[0].y||
							a3.a[0].len<tt.a[0].len&&a2.a[0].y<tt.a[1].x)
							wocao;
					}
				}
			}
		}
	}
	printf("%d\n",tmp.a[0].sum);
	
	if (an1<0) Cl(root[A],1,len[A],an2,an3-1);
	else
	For(i,an1,an1) {
		if (i) Cl(root[A],1,len[A],se[x],len[A]),X=A+1;
		else Cl(root[A],1,len[A],1,se[x]-1),X=A;
		
		For(j,an2,an2) {
			if (j) Cl(root[B],1,len[B],se[y],len[B]),Y=B+1;
			else Cl(root[B],1,len[B],1,se[y]-1),Y=B;
			
			For(k,an3,an3) {
				if (!k) {
					if (X<=Y) Cl(1,1,m,X,Y-1);
					else {
						Cl(1,1,m,X,m);
						Cl(1,1,m,1,Y-1);
					}
				} else {
					if (X>=Y) Cl(1,1,m,Y,X-1);
					else {
						Cl(1,1,m,Y,m);
						Cl(1,1,m,1,X-1);
					}
				}
			}
		}
	}
	Gen(A),Gen(B);
}
int main() {
	//freopen("175f.in","r",stdin);
	scanf("%d%d",&n,&m);
	For(i,1,m) {
		scanf("%d",&k);
		a[0].push_back(k);
	}
	a[0].push_back(a[0][0]);
	For(i,1,m) {
		int x;
		scanf("%d",&x);
		For(j,1,x) {
			scanf("%d",&k);
			a[i].push_back(k);
			if (j<x) se[k]=j,id[k]=i;
		}
		len[i]=x-1;
	}
	build(ro,1,m);
	scanf("%d",&q);
	For(i,1,q) {
		char p[10];
		int x,y;
		scanf("%s%d%d",p,&x,&y);
		if (p[0]=='+') jia(x,y);
		else wen(x,y);
	}
	return 0;
}
