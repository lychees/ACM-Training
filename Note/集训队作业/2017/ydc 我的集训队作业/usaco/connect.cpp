#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define MAXN 400010
#define now tree[root]
#define lson tree[root*2]
#define rson tree[root*2+1]
using namespace std;
struct node
{
	bool p1,p2,p3,p4,p5,p6;
	/*
		p1:(1,0)->(1,1)
		p2:(1,0)->(0,0)
		p3:(1,0)->(0,1)
		p4:(0,0)->(1,1)
		p5:(0,0)->(0,1)
		p6:(1,1)->(0,1)
	*/
};
struct Seg
{
	int left,right;
	node p;
}tree[MAXN];
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();!isdigit(c);c=getchar());
	for(;isdigit(c);digit=digit*10+c-'0',c=getchar());
}
int n,m;
bool edge[MAXN][2];
void Build(int root,int l,int r)
{
	now.left=l,now.right=r;
	int mid=(l+r)>>1;
	if(l==r)
	{
		now.p.p1=now.p.p5=true;
		return ;
	}
	Build(root*2,l,mid),Build(root*2+1,mid+1,r);
}
node update(const node &l,const node &r,int k)
{
	node ans;
	ans.p1=(l.p1&edge[k][1]&r.p1)|(l.p3&edge[k][0]&r.p4);
	ans.p2=l.p2|(l.p1&edge[k][1]&r.p2&edge[k][0]&l.p5);
	ans.p3=(l.p1&edge[k][1]&r.p3)|(l.p3&edge[k][0]&r.p5);
	ans.p4=(l.p4&edge[k][1]&r.p1)|(l.p5&edge[k][0]&r.p4);
	ans.p5=(l.p4&edge[k][1]&r.p3)|(l.p5&edge[k][0]&r.p5);
	ans.p6=r.p6|(r.p1&edge[k][1]&l.p6&edge[k][0]&r.p5);
	return ans;
}
void work(int root,int a,int b,int c,int d,bool k)
{
	/*
		p1:(1,0)->(1,1)
		p2:(1,0)->(0,0)
		p3:(1,0)->(0,1)
		p4:(0,0)->(1,1)
		p5:(0,0)->(0,1)
		p6:(1,1)->(0,1)
	*/
	if(now.left==a&&now.right==c)
	{
		if(a==c&&abs(b-d)==1)  now.p.p2=now.p.p3=now.p.p4=now.p.p6=k;
		if(a==c-1)  now.p=update(lson.p,rson.p,lson.right);
		return ;
	}
	int mid=(now.left+now.right)>>1;
	if(c<=mid)  work(root*2,a,b,c,d,k);
	else if(mid<a)  work(root*2+1,a,b,c,d,k);
	now.p=update(lson.p,rson.p,lson.right);
}
node Find(int root,int l,int r)
{
	if(now.left==l&&now.right==r)  return now.p;
	int mid=(now.left+now.right)>>1;
	if(r<=mid)  return Find(root*2,l,r);
	else if(mid<l)  return Find(root*2+1,l,r);
	else return update(Find(root*2,l,mid),Find(root*2+1,mid+1,r),mid);
}
bool Query(int a,int b,int c,int d)
{
	/*
		p1:(1,0)->(1,1)
		p2:(1,0)->(0,0)
		p3:(1,0)->(0,1)
		p4:(0,0)->(1,1)
		p5:(0,0)->(0,1)
		p6:(1,1)->(0,1)
	*/
	if(a==c&&b==d)  return true;
	if(a>c)  swap(a,c),swap(b,d);
	node ans1,ans2=Find(1,a,c),ans3;
	if(a>1)  ans1=Find(1,1,a-1);
	if(c<n)  ans3=Find(1,c+1,n);
	//Part1
	if(a==c&&ans2.p2)  return true;
	if(a!=c&&b==1&&d==1&&ans2.p1)  return true;
	if(a!=c&&b==1&&d==0&&ans2.p3)  return true;
	if(a!=c&&b==0&&d==1&&ans2.p4)  return true;
	if(a!=c&&b==0&&d==0&&ans2.p5)  return true;
	return false;
}
void read()
{
	int K;
	Read(K),Read(n),Read(m);
	Build(1,1,m);
	for(int i=1,a,b,c,d;i<=K;++i)
	{
		Read(b),Read(a),Read(d),Read(c);
		if(a>c)
			swap(a,c),swap(b,d);
		if(a==c-1)
			edge[a][b-1]=true;
		work(1,a,b-1,c,d-1,true);
	}
}
void Ask()
{
	int a,b,c,d,A[2],preans=0,Xr=0;
	char C;
	while(1)
	{
		for(C=getchar();!isalpha(C);C=getchar());
		if(C=='E')
			break;
		Read(b),Read(a),Read(d),Read(c),Read(A[0]),Read(A[1]);
		Xr=(Xr+A[preans])&1048575,b^=Xr,a^=Xr,d^=Xr,c^=Xr;
		if(C=='O')
		{
			if(a>c)  swap(a,c),swap(b,d);
			if(a==c-1)  edge[a][b-1]=true;
			work(1,a,b-1,c,d-1,true);
		}
		if(C=='C')
		{
			if(a>c)  swap(a,c),swap(b,d);
			if(a==c-1)  edge[a][b-1]=false;
			work(1,a,b-1,c,d-1,false);
		}
		if(C=='T')
		{
			preans=Query(a,b-1,c,d-1);
			printf("%c\n",preans?'Y':'N');
		}
	}
}
int main()
{
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
	read();
	Ask();
	return 0;
}
