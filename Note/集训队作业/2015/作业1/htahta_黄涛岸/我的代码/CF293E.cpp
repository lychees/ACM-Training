#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100100;
int n,L,W,Link[maxn],pre[maxn*2],t[maxn*2],v[maxn*2],s[maxn],vis[maxn],l[maxn],d[maxn],N,lim,size[maxn],c[maxn];
long long ans=0;
struct data
{
	int l,w;
	data(){}
	data(int _l,int _w){l=_l,w=_w;}
	bool operator <(const data &b)const{return w<b.w;}
}a[maxn];
inline int findroot(int x)
{
	int front=0,rear=1;
	s[front]=x,vis[x]=1;
	while(front!=rear)
	{
		int p=s[front];
		for(int i=Link[p];i;i=pre[i])
			if(!vis[t[i]])vis[t[i]]=1,s[rear++]=t[i];
		front++;
	}
	int root,tp,m=n;
	for(int i=rear-1;i>=0;i--)
	{
		tp=vis[s[i]]=0;size[s[i]]=1;
		for(int j=Link[s[i]];j;j=pre[j])
			if(!vis[t[j]])size[s[i]]+=size[t[j]],tp=max(tp,size[t[j]]);
		tp=max(tp,rear-size[s[i]]);
		if(tp<m)m=tp,root=s[i];
	}
	return root;
}
inline void add(int x)
{
	for(x++;x<=lim;x+=x&-x)c[x]++;
}
inline int ask(int x)
{
	int res=0;
	for(x++;x;x-=x&-x)res+=c[x];
	return res;
}
inline void make(int x,int f)
{
	int front=0,rear=1;
	s[front]=x;vis[x]=1;
	while(front!=rear)
	{
		int p=s[front];
		for(int i=Link[p];i;i=pre[i])
			if(!vis[t[i]])vis[t[i]]=1,s[rear++]=t[i],l[t[i]]=l[p]+1,d[t[i]]=d[p]+v[i];
		front++;
	}
	N=0;lim=l[s[rear-1]]+1;
	for(int i=0;i<rear;i++)a[++N]=data(l[s[i]],d[s[i]]),vis[s[i]]=0;
	sort(a+1,a+1+N);
	memset(c+1,0,lim*4);
	for(int i=N,j=1;i;i--)
	{
		for(;j<=N&&a[i].w+a[j].w<=W;j++)add(a[j].l);
		if(a[i].l<=L)ans+=ask(min(L-a[i].l,lim-1))*f;
	}
}

void solve(int x)
{
	x=findroot(x);
	l[x]=d[x]=0;
	make(x,1);
	vis[x]=1;
	for(int i=Link[x];i;i=pre[i])
		if(!vis[t[i]])make(t[i],-1);
	for(int i=Link[x];i;i=pre[i])
		if(!vis[t[i]])solve(t[i]);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),L=get(),W=get();
	for(int i=1,tot=0;i<n;i++)
	{
		int x=i+1,y=get(),z=get();
		pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y; v[tot]=z;
		pre[++tot]=Link[y]; Link[y]=tot; t[tot]=x; v[tot]=z;
	}
	solve(1);
	cout<<(ans-n)/2<<endl;
	return 0;
}

