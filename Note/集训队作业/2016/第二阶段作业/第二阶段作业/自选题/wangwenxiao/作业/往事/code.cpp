#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
typedef unsigned long long u64;
const int Maxn=200005,inf=999999999+208;
const int K=99999+208,L=999999999+208;
int n,ans=0;
int ch[Maxn],d[Maxn];
int ord[Maxn];
int fa[19][Maxn],h[Maxn][19],pw[20],hei[Maxn];
int len[Maxn],minl[Maxn*4];

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

namespace SuffixArray{
	int seq[Maxn],seq2[Maxn],cnt[Maxn],ord2[Maxn];
	
	void build() {
		pw[0]=K;
		for (int i=1;(1<<i)<=n;i++)
			pw[i]=u64(pw[i-1])*pw[i-1]%L;
		int H=0;
		hei[1]=-1;
		for (int u=2;u<=n;u++) {
			h[u][0]=ch[u];
			int &k=hei[u];
			while (fa[k][fa[k][u]]) {
				fa[k+1][u]=fa[k][fa[k][u]];
				h[u][k+1]=(u64(h[u][k])*pw[k]+h[fa[k][u]][k])%L;
				k++;
			}
			H=max(H,hei[u]);
		}
		for (int i=2;i<=n;i++) ++cnt[ch[i]];
		for (int i=1;i<=300;i++) cnt[i]+=cnt[i-1];
		for (int i=2;i<=n;i++) seq[cnt[ch[i]]--]=i;
		ord[seq[1]]=1;
		for (int i=2;i<n;i++)
			ord[seq[i]]=ord[seq[i-1]]+(ch[seq[i]]!=ch[seq[i-1]]);
		memset(cnt,0,301<<2);
		for (int k=0,N;k<=H;k++) {
			N=ord[seq[n-1]];
			memcpy(ord2+1,ord+1,n<<2);
			for (int i=2;i<=n;i++) ++cnt[ord2[fa[k][i]]];
			for (int i=1;i<=N;i++) cnt[i]+=cnt[i-1];
			for (int i=2;i<=n;i++)
				seq2[cnt[ord2[fa[k][i]]]--]=i;
			memset(cnt,0,(N+1)<<2);
			for (int i=2;i<=n;i++) ++cnt[ord2[i]];
			for (int i=1;i<=N;i++) cnt[i]+=cnt[i-1];
			for (int i=n-1;i>=1;i--)
				seq[cnt[ord2[seq2[i]]]--]=seq2[i];
			memset(cnt,0,(N+1)<<2);
			ord[seq[1]]=1;
			for (int i=2,u,v;i<n;i++) {
				u=seq[i]; v=seq[i-1];
				ord[u]=ord[v]+(ord2[u]!=ord2[v]||ord2[fa[k][u]]!=ord2[fa[k][v]]);
			}
		}
		for (int i=1,u,v;i+1<n;i++) {
			u=seq[i]; v=seq[i+1];
			int k=min(hei[u],hei[v]);
			while (k>=0) {
				if (h[u][k]==h[v][k]) {
					len[i]+=1<<k;
					u=fa[k][u];
					v=fa[k][v];
					k=min(k-1,min(hei[u],hei[v]));
				}
				else k--;
			}
		}
	}
}

struct node{
	node *lc,*rc;
	int maxl,maxr;
}po[Maxn*20],*null=po,*pn=po;

void build(int o,int l,int r) {
	if (l==r) {
		minl[o]=len[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	minl[o]=min(minl[o<<1],minl[o<<1|1]);
}

class SegmentTree{
	node *root;
	int d;
	void insert(node *&x,int l,int r,int p,int o) {
		x=++pn;
		if (l==r) {
			x->maxl=inf;
			x->maxr=minl[o];
			x->lc=x->rc=null;
			return;
		}
		int mid=(l+r)>>1;
		if (p<=mid) {
			x->rc=null;
			insert(x->lc,l,mid,p,o<<1);
			x->maxl=x->lc->maxl;
			x->maxr=min(minl[o<<1|1],x->lc->maxr);
		}
		else {
			x->lc=null;
			insert(x->rc,mid+1,r,p,o<<1|1);
			x->maxl=min(minl[o<<1],x->rc->maxl);
			x->maxr=x->rc->maxr;
		}
	}
	node *merge(node *x,node *y,int l,int r) {
		if (x==null) return y;
		if (y==null) return x;
		int mid=(l+r)>>1;
		x->maxl=max(x->maxl,y->maxl);
		x->maxr=max(x->maxr,y->maxr);
		x->lc=merge(x->lc,y->lc,l,mid);
		x->rc=merge(x->rc,y->rc,mid+1,r);
		ans=max(ans,d+min(x->lc->maxr,x->rc->maxl));
		return x;
	}
	public:
		void set(int _d) {
			d=_d;
			null->lc=null->rc=null;
			null->maxl=null->maxr=-inf;
			root=null;
		}
		void set(int _d,int pos) {
			d=_d;
			root=null;
			insert(root,1,n-1,pos,1);
		}
		void merge(const SegmentTree &rhs) {
			root=merge(root,rhs.root,1,n-1);
		}
}T[Maxn];

int main() {
	n=get();
	for (int u=2;u<=n;u++) {
		d[u]=d[fa[0][u]=get()]+1;
		ch[u]=get()+1;
	}
	SuffixArray::build();
	build(1,1,n-1);
	T[1].set(0);
	for (int u=2;u<=n;u++)
		T[u].set(d[u],ord[u]);
	for (int u=n;u>1;u--)
		T[fa[0][u]].merge(T[u]);
	printf("%d\n",ans);
	return 0;
}
