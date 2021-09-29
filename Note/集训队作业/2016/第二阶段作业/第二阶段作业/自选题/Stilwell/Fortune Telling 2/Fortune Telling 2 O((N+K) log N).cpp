#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct node
{
	int l,r,key;
}t[3000005];
int root,tot;
bool stage;

struct Query
{
	int t,id;
}q[200005];
inline bool cmp(const Query &a,const Query &b){return a.t<b.t;}

int n,m,i,j,k,A[200005],B[200005],T[200005],rev[200005];
int aim,key,ll,rr;
long long ans;

void C(int &p,int l,int r)
{
	if(!p)
	{
		p=++tot;
		t[p].l=t[p].r=t[p].key=0;
	}
	if(stage)
	{
		if(key>t[p].key)t[p].key=key;
	}else ++t[p].key;
	if(l==r)return;
	int mid=l+r>>1;
	if(aim<=mid)C(t[p].l,l,mid);
	else C(t[p].r,mid+1,r);
}

void Q(int p,int l,int r)
{
	if(!p)return;
	if(l>=ll&&r<=rr)
	{
		if(stage)
		{
			if(t[p].key>key)key=t[p].key;
		}else key+=t[p].key;
		return;
	}
	int mid=l+r>>1;
	if(rr<=mid)Q(t[p].l,l,mid);
	else if(ll>mid)Q(t[p].r,mid+1,r);
		else Q(t[p].l,l,mid),Q(t[p].r,mid+1,r);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d%d",&A[i],&B[i]);
	stage=true;
	for(i=1;i<=m;++i)
	{
		scanf("%d",&T[i]);
		aim=T[i];key=i;
		C(root,1,1000000000);
	}
	for(i=1;i<=n;++i)
	{
		key=0;
		ll=A[i];rr=B[i];
		if(ll>rr)swap(ll,rr);
		--rr;
		if(ll<=rr)Q(root,1,1000000000);
		if(key&&A[i]<B[i])swap(A[i],B[i]);
		q[i].t=key+1;
		q[i].id=i;
	}
	stage=false;
	root=tot=0;
	sort(q+1,q+n+1,cmp);
	for(j=n;j>=1&&q[j].t>m;--j);
	for(i=m;i>=1;--i)
	{
		aim=T[i];C(root,1,1000000000);
		while(j>=1&&q[j].t==i)
		{
			key=0;
			ll=A[q[j].id];rr=1000000000;
			Q(root,1,1000000000);
			rev[q[j].id]=key;
			--j;
		}
	}
	for(i=1;i<=n;++i)if(rev[i]&1)ans+=B[i];else ans+=A[i];
	printf("%I64d\n",ans);
}
