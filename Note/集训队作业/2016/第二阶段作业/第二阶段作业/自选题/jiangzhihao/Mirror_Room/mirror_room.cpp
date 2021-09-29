#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int N = 105000;
const int M = 250000;
const int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
struct node
{
	int x,y;
}row[N],column[N],now,start,next;
int fx,startfx;
int rowmin[M],rowmax[M],columnmin[M],columnmax[M];
bool twice;
long long ans;
int n,m,p;
char data[5];
int hang(struct node a,struct node b)
{
	if(a.x<b.x)
		return 1;
	if(a.x>b.x)
		return 0;
	return a.y<b.y;
}
int lie(struct node a,struct node b)
{
	if(a.y<b.y)
		return 1;
	if(a.y>b.y)
		return 0;
	return a.x<b.x;
}
int equal(struct node a,struct node b)
{
	if(a.x!=b.x)
		return 0;
	if(a.y!=b.y)
		return 0;
	return 1;
}
void Init()
{
	int i,j;
	int a,b;
	scanf("%d%d%d",&n,&m,&p);
	for(i=1;i<=p;i++)
	{
		scanf("%d%d",&a,&b);
		row[i].x=a+b;
		row[i].y=b-a;
		column[i]=row[i];
	}
	sort(row+1,row+p+1,hang);
	sort(column+1,column+p+1,lie);
	scanf("%d%d",&a,&b);
	now.x=a+b;
	now.y=b-a;
	scanf("%s",data);
	if(data[0]=='N')
	{
		if(data[1]=='E')
			fx=0;
		else
			fx=3;
	}
	else
	{
		if(data[1]=='E')
			fx=1;
		else
			fx=2;
	}
	memset(rowmin,0x3f,sizeof rowmin);
	memset(rowmax,0xc0,sizeof rowmax);
	memset(columnmin,0x3f,sizeof columnmin);
	memset(columnmax,0xc0,sizeof columnmax);
	for(i=0;i<=m+1;i++)
	{
		rowmin[i]=min(rowmin[i],i);
		rowmax[i]=max(rowmax[i],i);
		rowmin[n+i+1]=min(rowmin[n+i+1],i-n-1);
		rowmax[n+i+1]=max(rowmax[n+i+1],i-n-1);
		columnmin[i+N]=min(columnmin[i+N],i);
		columnmax[i+N]=max(columnmax[i+N],i);
		columnmin[i-n-1+N]=min(columnmin[i-n-1+N],n+i+1);
		columnmax[i-n-1+N]=max(columnmax[i-n-1+N],n+i+1);
	}
	for(i=0;i<=n+1;i++)
	{
		rowmin[i]=min(rowmin[i],-i);
		rowmax[i]=max(rowmax[i],-i);
		rowmin[m+i+1]=min(rowmin[m+i+1],m+1-i);
		rowmax[m+i+1]=max(rowmax[m+i+1],m+1-i);
		columnmin[N-i]=min(columnmin[N-i],i);
		columnmax[N-i]=max(columnmax[N-i],i);
		columnmin[m+1-i+N]=min(columnmin[m+1-i+N],m+i+1);
		columnmax[m+1-i+N]=max(columnmax[m+1-i+N],m+i+1);
	}
}
void rowmore(int l,int r)
{
	if(l>=r)
	{
		if(l==r && hang(now,row[l]) && now.x==row[l].x)
			next=row[l];
		else
		{
			next.x=now.x;
			next.y=rowmax[next.x];
		}
		return;
	}
	int mid=(l+r)>>1;
	if(hang(now,row[mid]))
		rowmore(l,mid);
	else
		rowmore(mid+1,r);
}
void rowless(int l,int r)
{
	if(l>=r)
	{
		if(l==r && hang(row[l],now) && now.x==row[l].x)
			next=row[l];
		else
		{
			next.x=now.x;
			next.y=rowmin[next.x];
		}
		return;
	}
	int mid=(l+r+1)>>1;
	if(hang(row[mid],now))
		rowless(mid,r);
	else
		rowless(l,mid-1);
}
void columnmore(int l,int r)
{
	if(l>=r)
	{
		if(l==r && lie(now,column[l]) && now.y==column[l].y)
			next=column[l];
		else
		{
			next.y=now.y;
			next.x=columnmax[next.y+N];
		}
		return;
	}
	int mid=(l+r)>>1;
	if(lie(now,column[mid]))
		columnmore(l,mid);
	else
		columnmore(mid+1,r);
}
void columnless(int l,int r)
{
	if(l>=r)
	{
		if(l==r && lie(column[l],now) && now.y==column[l].y)
			next=column[l];
		else
		{
			next.y=now.y;
			next.x=columnmin[next.y+N];
		}
		return;
	}
	int mid=(l+r+1)>>1;
	if(lie(column[mid],now))
		columnless(mid,r);
	else
		columnless(l,mid-1);
}
int exist(int l,int r,struct node key)
{
	if(l>r)
	{
		if(rowmin[key.x]==key.y || rowmax[key.x]==key.y || columnmin[key.y+N]==key.x || columnmax[key.y+N]==key.x)
			return 1;
		return 0;
	}
	int mid=(l+r)>>1;
	if(equal(key,row[mid]))
		return 1;
	if(hang(key,row[mid]))
		return exist(l,mid-1,key);
	return exist(mid+1,r,key);
}
void Go()
{
	if(fx==0)
		rowmore(1,p);
	else if(fx==1)
		columnmore(1,p);
	else if(fx==2)
		rowless(1,p);
	else
		columnless(1,p);
	next.x-=dir[fx][0];
	next.y-=dir[fx][1];
	ans+=max(next.x-now.x,now.x-next.x)+max(next.y-now.y,now.y-next.y);
	now=next;
	next.x=now.x+dir[(fx+3)%4][0];
	next.y=now.y+dir[(fx+3)%4][1];
	if(exist(1,p,next))
	{
		next.x=now.x+dir[(fx+1)%4][0];
		next.y=now.y+dir[(fx+1)%4][1];
		if(exist(1,p,next))
		{
			fx^=2;
			twice=1;
		}
		else
			fx=(fx+1)%4;
	}
	else
	{
		next.x=now.x+dir[(fx+1)%4][0];
		next.y=now.y+dir[(fx+1)%4][1];
		if(exist(1,p,next))
			fx=(fx+3)%4;
		else
		{
			fx^=2;
			twice=1;
		}
	}
}
void Do()
{
	Go();
	start=now;
	startfx=fx;
	ans=0;
	Go();
	while(!equal(now,start) || fx!=startfx)
		Go();
	ans>>=1;
	if(twice)
		ans>>=1;
}
int main()
{
	Init();
	Do();
	cout<<ans<<endl;
	return 0;
}
