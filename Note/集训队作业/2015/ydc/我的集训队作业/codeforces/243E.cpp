#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxc 510
#define maxn maxc*10
using namespace std;
int son[maxn*3],l=10001,r=10000;
int isP[maxn];
int n,rt,top;
int to[maxn],next[maxn],start[maxn],father[maxn];
int pool_p[maxn],pool_e[maxn],n_p,n_e;
int have[maxn][2];
int newnode()
{
	int p=pool_p[n_p--];
	isP[p]=true;
	start[p]=0;
	return p;
}
void make(int a,int b)
{
	int x=pool_e[n_e--];
	to[x]=b,next[x]=start[a],start[a]=x,father[b]=a;
}
void clean(int p)
{
	for(int &i=start[p];i;i=next[i])
		pool_e[++n_e]=i;
}
void Reverse(int p)
{
	static int stack[maxn];
	int top=0;
	for(int &i=start[p];i;i=next[i])
		stack[++top]=i;
	start[p]=stack[top];
	for(;top;--top)
		next[stack[top]]=stack[top-1];
}
void Fail()
{
	printf("NO\n");
	exit(0);
}
void print(int p,int *ans,int &n)
{
	if(!start[p])
		ans[++n]=p;
	for(int i=start[p];i;i=next[i])
		print(to[i],ans,n);
}
void print(int p)
{
	if(p<=n)
		printf("I'm %d ",p);
	printf("(%d %c): ",p,isP[p]?'P':'Q');
	for(int i=start[p];i;i=next[i])
		printf("%d ",to[i]);
	printf("\n");
	for(int i=start[p];i;i=next[i])
		print(to[i]);
}
void update(int p)
{
	if(!start[p])
		return ;
	have[p][0]=have[p][1]=0;
	for(int i=start[p];i;i=next[i])
		have[p][0]|=have[to[i]][0],have[p][1]|=have[to[i]][1];
}
int find(int p,int c1,int c2)
{
	int cnt=0;
	for(int i=start[p];i;i=next[i])
		if(have[to[i]][0]==c1&&have[to[i]][1]==c2)
			++cnt;
	return cnt;
}
bool check(int p,int x)
{
	/*
		x=0 : none->half->all
		x=1 : all->half->none
	*/
	int a;
	if(x==0)
	{
		for(a=start[p];a&&!have[to[a]][1];a=next[a]);
		for(;a&&have[to[a]][0]&&have[to[a]][1];a=next[a]);
		for(;a;a=next[a])
			if(have[to[a]][0])
				return false;
		return true;
	}
	else
	{
		for(a=start[p];a&&!have[to[a]][0];a=next[a]);
		for(;a&&have[to[a]][0]&&have[to[a]][1];a=next[a]);
		for(;a;a=next[a])
			if(have[to[a]][1])
				return false;
		return true;
	}
}
void work(int p,int x,int dep)
{
	/*
		x=0 : t_L
		x=1 : t_R
	*/
	static int p_none[maxn],p_half[maxn],p_all[maxn];
	bool mark=true;
	int n1,n2,n3;
	if(isP[p])
	{
		mark=false;
		n1=0,n2=0,n3=0;
		for(int i=start[p];i;i=next[i])
		{
			int x=to[i];
			if(have[x][0]&&!have[x][1])
				p_none[++n1]=x;
			if(have[x][0]&&have[x][1])
				p_half[++n2]=x;
			if(!have[x][0]&&have[x][1])
				p_all[++n3]=x;
		}
		if(n2>1)
			Fail();
		clean(p);
		if(x==0)
		{
			for(int i=n3;i>=1;--i)
				make(p,p_all[i]);
			for(int i=n2;i>=1;--i)
				make(p,p_half[i]);
			for(int i=n1;i>=1;--i)
				make(p,p_none[i]);
			if(n2)
				work(p_half[1],0,dep+1);
		}
		else
		{
			for(int i=n1;i>=1;--i)
				make(p,p_none[i]);
			for(int i=n2;i>=1;--i)
				make(p,p_half[i]);
			for(int i=n3;i>=1;--i)
				make(p,p_all[i]);
			if(n2)
				work(p_half[1],1,dep+1);
		}
		n1=0,n2=0,n3=0;
		for(int i=start[p];i;i=next[i])
		{
			int x=to[i];
			if(have[x][0]&&!have[x][1])
				p_none[++n1]=x;
			if(have[x][0]&&have[x][1])
				p_half[++n2]=x;
			if(!have[x][0]&&have[x][1])
				p_all[++n3]=x;
		}
		clean(p);
		int u=n1>1?newnode():p,v=n3>1?newnode():p;
		if(x==0)
		{
			if(v!=p)
				make(p,v);
			for(int i=n3;i>=1;--i)
				make(v,p_all[i]);
			for(int i=n2;i>=1;--i)
				make(p,p_half[i]);
			for(int i=n1;i>=1;--i)
				make(u,p_none[i]);
			if(u!=p)
				make(p,u);
		}
		else
		{
			if(u!=p)
				make(p,u);
			for(int i=n1;i>=1;--i)
				make(u,p_none[i]);
			for(int i=n2;i>=1;--i)
				make(p,p_half[i]);
			for(int i=n3;i>=1;--i)
				make(v,p_all[i]);
			if(v!=p)
				make(p,v);
		}
		update(u),update(v),update(u),update(v);
		isP[p]=false;
	}
	if(mark)
	{
		int cnt=find(p,1,1),a;
		if(cnt>1)
			Fail();
		if(!check(p,x))
		{
			Reverse(p);
			if(!check(p,x))
				Fail();
		}
		if(cnt)
		{
			for(a=start[p];!have[to[a]][0]||!have[to[a]][1];a=next[a]);
			work(to[a],x,dep+1);
		}
	}
	static int tmp[maxn];
	int a,tot=0;
	for(a=start[p];a&&(!have[to[a]][0]||!have[to[a]][1]);a=next[a])
		tmp[++tot]=to[a];
	while(tot)
		son[--l]=tmp[tot--];
	for(;a&&have[to[a]][0]&&have[to[a]][1];a=next[a])
		pool_p[++n_p]=to[a];
	for(;a;a=next[a])
		son[++r]=to[a];
	clean(p);
	if(dep==1)
	{
		for(int i=r;i>=l;--i)
			make(p,son[i]);
		l=10001,r=10000;
	}
}
void Insert(int *a,int m)
{
	if(m<=1)
		return ;
	static int p_none[maxn],p_half[maxn],p_all[maxn],tmp[maxn];
	static bool col[maxc];
	memset(col,false,sizeof(col));
	for(int i=1;i<=m;++i)
		col[a[i]]=true;
	static int queue[maxn],pos[maxn];
	int front=0,rear=1;
	queue[rear]=rt;
	while(front<rear)
	{
		int p=queue[++front];
		have[p][0]=have[p][1]=0;
		for(int i=start[p];i;i=next[i])
		{
			queue[++rear]=to[i];
			pos[to[i]]=p==rt?to[i]:pos[p];
		}
	}
	for(int i=rear;i>=1;--i)
	{
		int p=queue[i];
		if(!start[p])
			have[p][col[p]]=1;
		update(p);
	}
	int p=rt;
	while(find(p,1,1)+find(p,0,1)<2)
	{
		int cnt=0,a;
		for(int i=start[p];i;i=next[i])
			if(have[to[i]][1])
				++cnt,a=to[i];
		p=a;
	}
	if(find(p,1,1)>2)
		Fail();
	if(!find(p,1,1))
	{
		if(!isP[p])
		{
			static int ans[maxn];
			int t=0;
			print(rt,ans,t);
			int c=0;
			for(int i=1;i<=n;++i)
				c+=col[ans[i]]&&!col[ans[i-1]];
			if(c>1)
				Fail();
		}
		else
		{
			if(find(p,0,1)==1)
				return ;
			int u=newnode(),n1=0,n3=0;
			for(int i=start[p];i;i=next[i])
			{
				if(have[to[i]][1])
					p_all[++n3]=to[i];
				else
					p_none[++n1]=to[i];
			}
			clean(p);
			for(int i=1;i<=n3;++i)
				make(u,p_all[i]);
			make(p,u);
			for(int i=1;i<=n1;++i)
				make(p,p_none[i]);
		}
		return ;
	}
	if(!isP[p])
	{
		int a;
		int nson=0,cnt=find(p,1,1);
		for(a=start[p];a&&!have[to[a]][1];a=next[a])
			tmp[++nson]=to[a];
		if(have[to[a]][1]&&!have[to[a]][0]&&cnt)
		{
			Reverse(p),nson=0;
			for(a=start[p];a&&!have[to[a]][1];a=next[a])
				tmp[++nson]=to[a];
		}
		if(cnt==1)
		{
			work(to[a],0,1);
			for(int i=start[to[a]];i;i=next[i])
				tmp[++nson]=to[i];
			pool_p[++n_p]=to[a];
			a=next[a];
			for(;a&&have[to[a]][1]&&!have[to[a]][0];a=next[a])
				tmp[++nson]=to[a];
			for(;a;a=next[a])
			{
				if(have[to[a]][1])
					Fail();
				tmp[++nson]=to[a];
			}
		}
		else
		{
			work(to[a],0,1);
			for(int i=start[to[a]];i;i=next[i])
				tmp[++nson]=to[i];
			pool_p[++n_p]=to[a];
			a=next[a];
			for(;a&&have[to[a]][1]&&!have[to[a]][0];a=next[a])
				tmp[++nson]=to[a];
			if(!have[to[a]][1]||!have[to[a]][0])
				Fail();
			work(to[a],1,1);
			for(int i=start[to[a]];i;i=next[i])
				tmp[++nson]=to[i];
			pool_p[++n_p]=to[a];
			a=next[a];
			for(;a;a=next[a])
			{
				if(have[to[a]][1])
					Fail();
				tmp[++nson]=to[a];
			}
		}
		clean(p);
		for(int i=nson;i>=1;--i)
			make(p,tmp[i]);
	}
	else
	{
		int n1=0,n2=0,n3=0;
		for(int i=start[p];i;i=next[i])
		{
			int x=to[i];
			if(have[x][0]&&!have[x][1])
				p_none[++n1]=x;
			if(have[x][0]&&have[x][1])
				p_half[++n2]=x;
			if(!have[x][0]&&have[x][1])
				p_all[++n3]=x;
		}
		if(n2>2)
			Fail();
		clean(p);
		if(n2>1)
			work(p_half[2],1,1),make(p,p_half[2]);
		for(int i=n3;i>=1;--i)
			make(p,p_all[i]);
		if(n2)
			work(p_half[1],0,1),make(p,p_half[1]);
		for(int i=n1;i>=1;--i)
			make(p,p_none[i]);
		int u,v;
		if(n3>1)
		{
			clean(p);
			u=newnode();
			if(n2>1)
				make(p,p_half[2]);
			make(p,u);
			if(n2)
				make(p,p_half[1]);
			for(int i=n1;i>=1;--i)
				make(p,p_none[i]);
			for(int i=n3;i>=1;--i)
				make(u,p_all[i]);
			update(u);
		}
		if(n2==1&&!n3)
			return ;
		if(n2==0)
			return ;
		v=newnode();
		isP[v]=false;
		int nson=0;
		for(int i=start[p_half[1]];i;i=next[i])
			son[++nson]=to[i];
		clean(p_half[1]),pool_p[++n_p]=p_half[1];
		if(n3>0)
			son[++nson]=n3>1?u:p_all[1];
		if(n2>1)
		{
			for(int i=start[p_half[2]];i;i=next[i])
				son[++nson]=to[i];
			for(;nson;--nson)
				make(v,son[nson]);
			clean(p_half[2]),pool_p[++n_p]=p_half[2];
		}
		for(;nson;--nson)
			make(v,son[nson]);
		clean(p);
		if(!n1)
		{
			pool_p[++n_p]=p;
			if(p==rt)
				rt=v;
			else
			{
				int q=father[p],nson=0;
				for(int i=start[q];i;i=next[i])
					son[++nson]=to[i]==p?v:to[i];
				clean(q);
				for(;nson;--nson)
					make(q,son[nson]);
			}
		}
		else
		{
			for(int i=n1;i>=1;--i)
				make(p,p_none[i]);
			make(p,v);
		}
	}
}
void read()
{
	scanf("%d",&n);
	for(int i=10*n;i>=1;--i)
		pool_p[++n_p]=i,pool_e[++n_e]=i;
	for(int i=1;i<=n;++i)
		newnode();
	rt=newnode();
	for(int i=1;i<=n;++i)
		make(rt,i);
	static char map[maxc][maxc];
	static int a[maxc];
	for(int i=1;i<=n;++i)
	{
		scanf("%s",map[i]+1);
		int tot=0;
		for(int j=1;j<=n;++j)
			if(map[i][j]=='1')
				a[++tot]=j;
		Insert(a,tot);
		/*
		printf("YES\n");
		static int ans[maxn];
		int t=0;
		print(rt,ans,t);
		for(int j=1;j<=i;++j,printf("\n"))
			for(int k=1;k<=n;++k)
				printf("%c",map[j][ans[k]]);
		printf("\n");
		print(rt);
		printf("\n\n");
		*/
	}
	printf("YES\n");
	static int ans[maxn];
	int tot=0;
	print(rt,ans,tot);
	for(int i=1;i<=n;++i,printf("\n"))
		for(int j=1;j<=n;++j)
			printf("%c",map[i][ans[j]]);
	/*
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
	printf("\n");
	*/
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
