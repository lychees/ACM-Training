#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
#define it tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
using namespace std;
struct msgnode
{
	int cnt[26];
	friend msgnode operator + (const msgnode &a,const msgnode &b)
	{
		msgnode c;
		for(int i=0;i<26;++i)
			c.cnt[i]=a.cnt[i]+b.cnt[i];
		return c;
	}
};
struct Seg_Tree
{
	char mark;
	int size;
	msgnode msg;
}tree[maxn<<2];
char str[maxn];
int n,m;
void Build(int root,int l,int r)
{
	it.size=r-l+1;
	if(l==r)
	{
		it.msg.cnt[str[l]-'a']=1;
		return ;
	}
	int mid=(l+r)>>1;
	Build(root<<1,l,mid),Build(root<<1|1,mid+1,r);
	it.msg=lson.msg+rson.msg;
}
void set(int root,char c)
{
	it.mark=c;
	memset(it.msg.cnt,0,sizeof(it.msg.cnt));
	it.msg.cnt[c-'a']=it.size;
}
void push_down(int root)
{
	if(it.mark)
	{
		set(root<<1,it.mark),set(root<<1|1,it.mark);
		it.mark=0;
	}
}
void Modify(int root,int l,int r,int x,int y,char c)
{
	if(l==x&&r==y)
	{
		set(root,c);
		return ;
	}
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		Modify(root<<1,l,mid,x,y,c);
	else if(mid<x)
		Modify(root<<1|1,mid+1,r,x,y,c);
	else
		Modify(root<<1,l,mid,x,mid,c),Modify(root<<1|1,mid+1,r,mid+1,y,c);
	it.msg=lson.msg+rson.msg;
}
msgnode Query(int root,int l,int r,int x,int y)
{
	if(l==x&&r==y)
		return it.msg;
	push_down(root);
	int mid=(l+r)>>1;
	if(y<=mid)
		return Query(root<<1,l,mid,x,y);
	else if(mid<x)
		return Query(root<<1|1,mid+1,r,x,y);
	else
		return Query(root<<1,l,mid,x,mid)+Query(root<<1|1,mid+1,r,mid+1,y);
}
void Print(int root)
{
	if(it.size==1)
	{
		for(int i=0;i<26;++i)
			if(it.msg.cnt[i])
				printf("%c",i+'a');
		return ;
	}
	push_down(root);
	Print(root<<1),Print(root<<1|1);
}
void Query()
{
	for(int i=1,l,r;i<=m;++i)
	{
		scanf("%d %d",&l,&r);
		msgnode ans=Query(1,1,n,l,r);
		int x=0;
		for(int j=0;j<26;++j)
			x+=ans.cnt[j]&1;
		if(x>1)
			continue;
		for(int j=0;j<26;++j)
			if(ans.cnt[j])
			{
				int len=ans.cnt[j]>>1;
				if(len)
				{
					Modify(1,1,n,l,l+len-1,'a'+j),Modify(1,1,n,r-len+1,r,'a'+j);
					l+=len,r-=len;
				}
				if(ans.cnt[j]&1)
					Modify(1,1,n,(l+r)>>1,(l+r)>>1,'a'+j);
			}
	}
	Print(1);
	printf("\n");
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d %s",&n,&m,str+1);
	Build(1,1,n);
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
