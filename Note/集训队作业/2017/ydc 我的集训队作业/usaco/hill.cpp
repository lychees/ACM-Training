#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 200010
#define it tree[root]
using namespace std;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct Seg
{
	int lx,rx,ly,ry,id;
	Seg() {}
	Seg(int lx,int rx,int ly,int ry,int id): lx(lx),rx(rx),ly(ly),ry(ry),id(id) {}
	double calc(double x)
	{
		return ly+1.0*(ry-ly)/(rx-lx)*(x-lx);
	}
	friend bool operator < (Seg a,Seg b)
	{
		return a.calc(max(a.lx,b.lx))<b.calc(max(a.lx,b.lx));
	}
}seg[maxn];
struct Seg_Tree
{
	vector<Seg> p;
	bool mark;
	int i;
}tree[maxn<<2];
int n,x[maxn][2],y[maxn][2],rank[maxn];
int px[maxn],tot;
int ID(int x)
{
	int l=1,r=tot;
	while(l<r)
	{
		int mid=(l+r)>>1;
		px[mid]<x?l=mid+1:r=mid;
	}
	return l;
}
int cmp(int a,int b,int x)
{
	if(a==0)
		return b;
	if(b==0)
		return a;
	return seg[a].calc(x)>seg[b].calc(x)?a:b;
}
int Find(vector<Seg> &a,int &i,int x,int y)
{
	while(i>=0&&a[i].calc(x)>y)
		--i;
	return ~i?a[i].id:0;
}
void Insert(int root,int l,int r,int x,int y,Seg &s)
{
	if(l==x&&r==y)
	{
		it.p.push_back(s);
		return ;
	}
	int mid=(l+r)>>1;
	if(y<=mid)
		Insert(root<<1,l,mid,x,y,s);
	else if(mid<x)
		Insert(root<<1|1,mid+1,r,x,y,s);
	else
		Insert(root<<1,l,mid,x,mid,s),Insert(root<<1|1,mid+1,r,mid+1,y,s);
}
int Query(int root,int l,int r,int x,int y)
{
	if(!it.mark)
	{
		it.mark=true;
		sort(it.p.begin(),it.p.end());
		it.i=(int)it.p.size()-1;
	}
	if(l==r)
		return Find(it.p,it.i,px[x],y);
	int mid=(l+r)>>1;
	if(x<=mid)
		return cmp(Find(it.p,it.i,px[x],y),Query(root<<1,l,mid,x,y),px[x]);
	else
		return cmp(Find(it.p,it.i,px[x],y),Query(root<<1|1,mid+1,r,x,y),px[x]);
}
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
	{
		Read(x[i][0]),Read(y[i][0]),Read(x[i][1]),Read(y[i][1]);
		px[++tot]=x[i][0],px[++tot]=x[i][1];
		seg[i]=Seg(x[i][0],x[i][1],y[i][0],y[i][1],i);
	}
	sort(px+1,px+tot+1),tot=unique(px+1,px+tot+1)-px-1;
	for(int i=1;i<=n;++i)
	{
		rank[i]=ID(x[i][1]);
		Insert(1,1,tot,ID(x[i][0]),rank[i]-1,seg[i]);
	}
}
int work()
{
	int ans=0,now=1;
	while(now)
	{
		++ans;
		now=Query(1,1,tot,rank[now],y[now][1]);
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",work());
	fclose(stdin);
	fclose(stdout);
	return 0;
}
