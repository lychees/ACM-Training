using namespace std;
#include <bits/stdc++.h>
#define N 100005
#define fi first
#define se second
#define mp(x,y) make_pair(x,y)
#define ll long long
int n,Q;
char str[N];
int m,fa[N*2],id[N];
vector<pair<int,int> > q[N];
namespace SAM{
	struct Node{
		Node *c[26],*fail;
		int len;
	} d[N*2],*S,*T;
	void insert(int ch){
		Node *nw=&d[++m],*p;
		nw->len=T->len+1;
		for (p=T;p && !p->c[ch];p=p->fail)
			p->c[ch]=nw;
		if (!p)
			nw->fail=S;
		else{
			Node *q=p->c[ch];
			if (p->len+1==q->len)
				nw->fail=q;
			else{
				Node *clone=&d[++m];
				memcpy(clone,q,sizeof(Node));
				clone->len=p->len+1;
				for (;p && p->c[ch]==q;p=p->fail)
					p->c[ch]=clone;
				nw->fail=q->fail=clone;
			}
		}
		T=nw;
	}
	void build(){
		S=T=&d[++m];
		for (int i=1;i<=n;++i)
			insert(str[i]-'a'),id[i]=T-d;
		for (int i=2;i<=m;++i)
			fa[i]=d[i].fail-d;
	}
}
struct Node{
	Node *fa,*c[2];
	int isr;
	bool getson(){return fa->c[0]!=this;}
	void rotate(){
		Node *y=fa,*z=y->fa;
		if (y->isr!=-1)
			isr=y->isr,y->isr=-1;
		else
			z->c[y->getson()]=this;
		int k=getson();
		fa=z;
		y->c[k]=c[k^1],c[k^1]->fa=y;
		c[k^1]=y,y->fa=this;
	}
	void splay(){
		for (;isr==-1;rotate())
			if (!fa->isr)
				getson()!=fa->getson()?rotate():fa->rotate();
	}
} d[N*2],*null,*rt;
namespace SGT{
	int tag[N*4],mx[N*4];
	void modify(int st,int en,int c,int k=1,int l=1,int r=n){
		if (c<=tag[k])
			return;
		if (st<=l && r<=en){
			tag[k]=c;
			mx[k]=max(max(mx[k<<1],mx[k<<1|1]),tag[k]-l);
			return;
		}
		int mid=l+r>>1;
		if (st<=mid) modify(st,en,c,k<<1,l,mid);
		if (mid<en) modify(st,en,c,k<<1|1,mid+1,r);
		mx[k]=max(max(mx[k<<1],mx[k<<1|1]),tag[k]-l);
	}
	int query(int st,int en,int k=1,int l=1,int r=n){
		if (st<=l && r<=en)
			return mx[k];
		int mid=l+r>>1,res=tag[k]-max(l,st);
		if (st<=mid) res=max(res,query(st,en,k<<1,l,mid));
		if (mid<en) res=max(res,query(st,en,k<<1|1,mid+1,r));
		return res;
	}
}
void modify(int i){
	Node *x=&d[id[i]],*y=null;

	cout <<id[i] << endl;

	for (;x!=rt;y=x,x=x->fa){
		x->splay();
		if (x->isr){
			int l=SAM::d[x->fa-d].len+1,r=SAM::d[x-d].len;

			cout << i << " "<< l <<" " << r <<endl;
//			printf("%d %d %d\n",x->isr-r+1,x->isr-l+1,x->isr);
			SGT::modify(x->isr-r+1,x->isr-l+1,x->isr+1);
		}
		x->c[1]->isr=x->isr;
		x->c[1]=y;
		y->isr=-1;
		x->isr=i;
	}
}
int ans[N];
int main(){

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
	scanf("%d%d",&n,&Q);
	scanf("%s",str+1);
	for (int i=1;i<=Q;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		q[r].push_back(mp(l,i));
	}
	SAM::build();
	null=d;
	*null={null,null,null,-1};
	for (int i=1;i<=m;++i) {
		d[i]={&d[fa[i]],null,null,0};
	}
	rt=&d[1];
	for (int i=1;i<=n;++i){
		modify(i);
		for (int j=0;j<q[i].size();++j){
			int l=q[i][j].fi;
			ans[q[i][j].se]=i-l+1-max(SGT::query(l,i),0);
		}
	}
	for (int i=1;i<=Q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
