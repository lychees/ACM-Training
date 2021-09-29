#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

int n,m,q,i,j,k,u,v,val,ll,rr,aim;
int son[100005],next[200005],ed[200005],tot;
int pre[100005],a[300005],lson[100005],lnext[300005],l[300005],r[300005],cnt;
int size[100005],heavy[100005],root_heavy,root_sum;
int ans[100005];
bool vis[100005],flag;

long long Sum;

struct node
{
	int l,r,sum;
}t[10000005];
int root[100005];

void dfs1(int x)
{
	vis[x]=true;
	size[x]=1;
	for(int i=son[x];i;i=next[i])
	if(!vis[ed[i]])dfs1(ed[i]),size[x]+=size[ed[i]];
	vis[x]=false;
}

void dfs2(int x)
{
	vis[x]=true;
	size[x]=root_sum-size[x];
	for(int i=son[x];i;i=next[i])
	if(!vis[ed[i]]&&size[ed[i]]>size[x])size[x]=size[ed[i]];
	if(size[x]<size[root_heavy])root_heavy=x;
	for(int i=son[x];i;i=next[i])
	if(!vis[ed[i]])dfs2(ed[i]);
	vis[x]=false;
}

void merge(int &A,int B,int l,int r)
{
	if(!B)return;if(!A){A=B;return;}
	t[++tot]=t[A];A=tot;++Sum;
	t[A].sum+=t[B].sum;
	if(l==r)return;
	int mid=l+r>>1;
	merge(t[A].l,t[B].l,l,mid);
	merge(t[A].r,t[B].r,mid+1,r);
}

void Q(int &x,int l,int r)
{
	if(!x)return;
	if(l>=ll&&r<=rr)
	{
		val+=t[x].sum;x=0;
		return;
	}
	t[++tot]=t[x];x=tot;++Sum;
	int mid=l+r>>1;
	if(rr<=mid)Q(t[x].l,l,mid);
	else if(ll>mid)Q(t[x].r,mid+1,r);
		else Q(t[x].l,l,mid),Q(t[x].r,mid+1,r);
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum;
	if(!t[x].sum)x=0;
}

void A(int &x,int l,int r)
{
	t[++tot]=t[x];x=tot;++Sum;
	t[x].sum+=val;
	if(l==r)return;
	int mid=l+r>>1;
	if(aim<=mid)A(t[x].l,l,mid);
	else A(t[x].r,mid+1,r);
}

void work(int &root,int l,int r)
{
	if(l>r)return;
	ll=l;rr=r;val=0;Q(root,1,m);
	if(r==m)return;
	aim=r+1;if(val)A(root,1,m);
}

void Work(int &root,int e)
{
	int i,k;
	for(i=lson[e],k=0;i;i=lnext[i])
	work(root,k+1,l[i]-1),k=r[i];
	work(root,k+1,m);
}

void dfs3(int x)
{
	vis[x]=true;
	int i,j;
	root[x]=0;
	for(i=son[x];i;i=next[i])
	if(!vis[ed[i]])
	{
		dfs3(ed[i]);
		Work(root[ed[i]],i>>1);
		merge(root[x],root[ed[i]],1,m);
	}
	aim=val=1;A(root[x],1,m);
	vis[x]=false;
}

void dfs4(int x,int root,int tot_)
{
	if(!t[root].sum)return;
	vis[x]=true;
	if(flag)ans[x]+=t[root].sum;
	else ans[x]-=t[root].sum;
	int i,k;
	for(i=son[x];i;i=next[i])
	if(!vis[ed[i]])
	{
		k=root;Work(k,i>>1);
		dfs4(ed[i],k,tot);
		tot=tot_;
	}
	vis[x]=false;
}

void dfs(int x)
{
	dfs1(x);
	root_heavy=x;root_sum=size[x];
	dfs2(x);
	x=root_heavy;tot=0;
	int i;
	vis[x]=true;flag=false;root[x]=0;
	for(i=son[x];i;i=next[i])
	if(!vis[ed[i]])
	{
		dfs3(ed[i]);
		Work(root[ed[i]],i>>1);
		dfs4(ed[i],root[ed[i]],tot);
		merge(root[x],root[ed[i]],1,m);
	}
	aim=val=1;A(root[x],1,m);
	flag=true;dfs4(x,root[x],tot);
	vis[x]=true;
	for(i=son[x];i;i=next[i])
	if(!vis[ed[i]])dfs(ed[i]);
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(i=tot=1;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		++tot;next[tot]=son[u];son[u]=tot;ed[tot]=v;
		++tot;next[tot]=son[v];son[v]=tot;ed[tot]=u;
	}
	for(i=1;i<=m;++i)
	{
		scanf("%d",&u);
		if(pre[u])
		{
			l[++cnt]=pre[u];r[cnt]=i;
			lnext[cnt]=lson[u];lson[u]=cnt;
			pre[u]=0;
		}
		else pre[u]=i;
	}
	for(i=1;i<n;++i)
	if(pre[i])
	{
		l[++cnt]=pre[i];r[cnt]=m;
		lnext[cnt]=lson[i];lson[i]=cnt;
	}
	for(i=1;i<n;++i)
	{
		for(j=lson[i],tot=0;j;j=lnext[j])a[++tot]=j;
		for(lson[i]=0,j=1;j<=tot;++j)lnext[a[j]]=lson[i],lson[i]=a[j];
	}
	dfs(1);
	for(;q;--q)scanf("%d",&u),printf("%d\n",ans[u]);
	cerr << Sum << endl;
}
