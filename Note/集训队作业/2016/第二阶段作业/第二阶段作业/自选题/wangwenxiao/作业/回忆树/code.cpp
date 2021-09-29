#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;
const int Maxn=100005,Maxl=300005,Maxp=Maxn+Maxl*2,inf=999999999+208;
int n,m,tot=0;
int fst[Maxn],next[Maxn*2],to[Maxn*2],En=0;
char ch[Maxn*2],par[Maxn];
int depth[Maxn],fa[Maxn][19],hei=0,Trie_id[Maxn];
int in[Maxp],ou[Maxp];
char s[Maxl],*sn=s,str[Maxn];

inline int get() {
	char ch;
	while (!isdigit(ch=getchar()));
	int v=ch-48;
	while (isdigit(ch=getchar())) v=v*10+ch-48;
	return v;
}

int Trie_size=0;
struct Trie{
	int ch[26],fail;
}tr[Maxp];

void Trie_clear() {
	memset(tr,0,sizeof(Trie)*(Trie_size+1));
	Trie_size=0;
}

inline int Step(int x,char ch) {
	int &ret=tr[x].ch[ch-'a'];
	if (!ret) ret=++Trie_size;
	return ret;
}

void build() {
	static int Q[Maxp],ne[Maxp*2];
	int l=1,r=1;
	for (int i=0;i<26;i++)
		if (tr[0].ch[i]) Q[r++]=tr[0].ch[i];
	ne[0]=1;
	while (l<r) {
		int x=Q[l++],fail=tr[x].fail;
		ne[x<<1]=x<<1|1;
		ne[x<<1|1]=ne[fail<<1];
		ne[fail<<1]=x<<1;
		for (int i=0;i<26;i++) {
			int &c=tr[x].ch[i];
			if (c) tr[Q[r++]=c].fail=tr[fail].ch[i];
			else c=tr[fail].ch[i];
		}
	}
	ne[1]=-1;
	for (int p=0;p!=-1;p=ne[p])
		if (p&1) ou[p>>1]=tot;
		else in[p>>1]=++tot;
}

struct node{
	node *lc,*rc;
	int size;
}po[Maxn*23],*null=po,*pn=po;

class Segment_Tree{
	node *root;
	void ins(node *&x,node *y,int l,int r,int p) {
		(x=++pn)->size=y->size+1;
		if (l<r) {
			int mid=(l+r)>>1;
			if (p<=mid) x->rc=y->rc,ins(x->lc,y->lc,l,mid,p);
			else x->lc=y->lc,ins(x->rc,y->rc,mid+1,r,p);
		}
	}
	int count(node *x,int l,int r,int s,int t) {
		if (x->size==0||(s<=l&&t>=r)) return x->size;
		int mid=(l+r)>>1;
		if (t<=mid) return count(x->lc,l,mid,s,t);
		if (s>mid) return count(x->rc,mid+1,r,s,t);
		return count(x->lc,l,mid,s,t)+count(x->rc,mid+1,r,s,t);
	}
	public:
		void set() {
			null->lc=null->rc=null;
			root=null;
		}
		void insert(Segment_Tree &pre,int pos) {
			ins(root,pre.root,1,tot,pos);
		}
		int count(int s,int t) {
			return count(root,1,tot,s,t);
		}
}T[Maxn];

inline int kth_parent(int x,int k) {
	for (int i=0;k;k>>=1,i++)
		if (k&1) x=fa[x][i];
	return x;
}

int Lca(int u,int v) {
	if (depth[u]<depth[v]) swap(u,v);
	u=kth_parent(u,depth[u]-depth[v]);
	if (u==v) return u;
	for (int k=hei;fa[u][0]!=fa[v][0];k--)
		if (fa[u][k]!=fa[v][k])
			u=fa[u][k],v=fa[v][k];
	return fa[u][0];
}

int query(int x,int &pa,int id,int len) {
	if (depth[x]-depth[pa]<len) return pa=x,0;
	pa=kth_parent(x,depth[x]-depth[pa]-len+1);
	return T[x].count(in[id],ou[id])-T[pa].count(in[id],ou[id]);
}

int Kmp(char *a,int la,char *b,int lb) {
	static int fail[Maxn];
	fail[0]=-1;
	for (int i=1,j;i<lb;i++) {
		for (j=fail[i-1];j!=-1&&b[j+1]!=b[i];j=fail[j]);
		fail[i]=j+(b[j+1]==b[i]);
	}
	int ret=0;
	for (int i=0,j=0;i<la;i++) {
		while (j&&a[i]!=b[j]) j=fail[j-1]+1;
		j+=a[i]==b[j];
		if (j==lb) ++ret,j=fail[j-1]+1;
	}
	return ret;
}

struct Task{
	int u,v,len,_Trie_id[2];
	char *s;
	void Run() {
		int &x=_Trie_id[0],&y=_Trie_id[1];
		x=0; y=0;
		for (int i=0;i<len;i++) x=Step(x,s[i]);
		for (int i=len-1;i>=0;i--) y=Step(y,s[i]);
	}
	void init() {
		u=get(); v=get();
		scanf(" %s",sn);
		sn+=len=strlen(s=sn);
		Run();
	}
	void solve() {
		int w=Lca(u,v),t1=w,t2=w,
			ans=query(u,t1,_Trie_id[1],len)+query(v,t2,_Trie_id[0],len);
		if (depth[u]+depth[v]-2*depth[w]>=len) {
			int _len=min(depth[u]-depth[w],len-1)+min(depth[v]-depth[w],len-1);
			for (int i=0;t1!=w;t1=fa[t1][0])
				str[i++]=par[t1];
			for (int i=_len;t2!=w;t2=fa[t2][0])
				str[--i]=par[t2];
			ans+=Kmp(str,_len,s,len);
		}
		printf("%d\n",ans);
	}
}task[Maxn];

void predeal() {
	static int Q[Maxn];
	int l=1,r=2;
	depth[Q[1]=1]=1;
	while (l<r) {
		int x=Q[l++];
		for (int k=0;fa[x][k]!=0;k++)
			fa[x][k+1]=fa[fa[x][k]][k];
		for (int k=fst[x],t=to[k];k;t=to[k=next[k]])
			if (!depth[t])
				depth[Q[r++]=t]=depth[x]+1,
				Trie_id[t]=Step(Trie_id[fa[t][0]=x],par[t]=ch[k]);
	}
	while ((1<<(hei+1))<depth[Q[r-1]]-1) ++hei;
	build();
	Trie_clear();
	for (int i=1;i<=m;i++) task[i].Run();
	for (int i=2,x=Q[i];i<r;x=Q[++i])
		Step(Trie_id[fa[x][0]],par[x]);
	T[0].set();
	for (int i=1,x=Q[i];i<r;x=Q[++i])
		T[x].insert(T[fa[x][0]],in[Trie_id[x]]);
}

int main() {
	n=get(); m=get();
	for (int i=1,u,v;i<n;i++) {
		u=get(); v=get();
		next[++En]=fst[u]; fst[u]=En; to[En]=v;
		while (!islower(ch[En]=getchar()));
		next[++En]=fst[v]; fst[v]=En; to[En]=u;
		ch[En]=ch[En-1];
	}
	for (int i=1;i<=m;i++) task[i].init();
	predeal();
	for (int i=1;i<=m;i++) task[i].solve();
	return 0;
}