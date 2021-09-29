#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include "worldline.h"
using namespace std;

namespace mywork{

const int maxn=10005;
int n,m,p,ans[maxn],used[maxn];
int s1[maxn],s2[maxn],*s;
int f1[maxn],f2[maxn],*f;

int nex[maxn],pre[maxn];

int getf(int x)
{return f[x]?f[x]=getf(f[x]):x;}

void del(int p)
{
	nex[pre[p]]=nex[p];
	pre[nex[p]]=pre[p];
}

void getfs(int *ff,int *ss)
{
	f=ff;s=ss;
	for(int i=1;i<=n;i++)f[i]=0,s[i]=1,nex[i]=i+1,pre[i]=i-1;
	nex[0]=1,pre[n+1]=n;
	for(int i=1;i<=n;i++)
		if(!f[i])
		{
			del(i);
			for(int j=nex[i];j<=n;j=nex[j])
				if(query(i,j))
				{
					s[i]+=s[j];f[j]=i;
					del(j);
				}
		}
	for(int i=1;i<=n;i++)
		s[i]=s[getf(i)];
}

void work0()
{
	new_round();
	for(int i=1,sum=0;i<m;sum+=i,i++)
		for(int j=1;j<=i;j++)
			addedge(sum+j,sum+i+j);
	next_step();
	getfs(f1,s1);
	
	new_round();
	for(int i=1,sum=0;i<=m;sum+=i,i++)
		for(int j=1;j<i;j++)
			addedge(sum+j,sum+j+1);
	next_step();
	getfs(f2,s2);
	for(int i=1;i<=n;i++)
	{
		int x=s1[i],y=s2[i];
		ans[y*(y-1)/2+(m-x+1)]=i;
	}
}

void work1()
{
	memset(ans,0,n+1<<2);
	memset(used,0,n+1<<2);
	new_round();
	for(int i=1,sum=0;i<=m;sum+=i,i++)
		for(int j=1;j<=i;j++)
			if(sum+i+j<n)
				addedge(sum+j,sum+i+j);
	next_step();
	getfs(f1,s1);
	
	new_round();
	for(int i=1,sum=0;i<=m;sum+=i,i++)
		for(int j=1;j<i;j++)
			addedge(sum+j,sum+j+1);
	for(int i=1;i<p;i++)addedge(n-i,n-i+1);
	next_step();
	getfs(f2,s2);
	
	for(int i=1;i<=n;i++)
		if(s2[i]==p&&s1[i]==1)
		{
			ans[n]=i;
			used[i]=1;
			f=f2;
			for(int j=1;j<=n;j++)
				if(getf(j)==getf(i))
				{
					ans[m*(m+1)/2+m-s1[j]+2]=j;
					used[j]=1;
				}
			break;
		}
	for(int i=1;i<=n;i++)
		if(!used[i])
		{
			int x,y;
			if(s1[i]>=m-p+3)y=m-s1[i]+2;
			else y=m-s1[i]+1;
			x=s2[i];
			ans[x*(x-1)/2+y]=i;
			used[i]=1;
		}
}

void workspc()
{
	memset(ans,0,n+1<<2);
	memset(used,0,n+1<<2);
	new_round();
	for(int i=1,sum=0;i<=m;sum+=i,i++)
		for(int j=1;j<=i;j++)
			if(sum+i+j<n-1)
				addedge(sum+j,sum+i+j);
	next_step();
	getfs(f1,s1);
	
	new_round();
	for(int i=1,sum=0;i<=m;sum+=i,i++)
		for(int j=1;j<i;j++)
			addedge(sum+j,sum+j+1);
	for(int i=1;i<p-1;i++)addedge(n-1-i,n-1-i+1);
	next_step();
	getfs(f2,s2);
	
	for(int i=1;i<=n;i++)
		if(s2[i]==p-1&&s1[i]==1)
		{
			ans[n-1]=i;
			used[i]=1;
			f=f2;
			for(int j=1;j<=n;j++)
				if(getf(j)==getf(i))
				{
					ans[m*(m+1)/2+m-s1[j]+2]=j;
					used[j]=1;
				}
			break;
		}
	for(int i=1;i<=n;i++)
		if(!used[i]&&(s1[i]+s2[i]>2))
		{
			int x,y;
			if(s1[i]>=m-p+4)y=m-s1[i]+2;
			else y=m-s1[i]+1;
			x=s2[i];
			ans[x*(x-1)/2+y]=i;
			used[i]=1;
		}
	for(int i=1;i<=n;i++)
		if(s1[i]==1&&s2[i]==1){ans[n]=i;break;}
}

void work5()
{
	new_round();
	addedge(1,2),addedge(3,4);
	next_step();
	getfs(f1,s1);
	new_round();
	addedge(2,3),addedge(4,5);
	next_step();
	getfs(f2,s2);
	for(int i=1;i<=n;i++)
		if(s1[i]==1)ans[5]=i;
		else if(s2[i]==1)ans[1]=i;
	for(int i=1;i<=n;i++)
	{
		f=f1;
		if(i!=ans[1]&&getf(i)==getf(ans[1]))ans[2]=i;
		f=f2;
		if(i!=ans[5]&&getf(i)==getf(ans[5]))ans[4]=i;
	}
	ans[3]=15-ans[1]-ans[2]-ans[4]-ans[5];
}

void solve(int n_,int *res)
{
	n=n_; 
	int sum=0;
	for(m=1;sum+m<=n;m++)
		sum+=m;
	m--;p=n-sum;
	if(n==5)work5();
	else if(p==0)work0();
	else if(p<m)work1();
	else workspc();
	for(int i=1;i<=n;i++)res[i]=ans[i];
}

}

int query_permutation(int n,int ans[])
{
	if(n==2)return 0;
	if(n==1)ans[1]=1;
	else mywork::solve(n,ans);
	return 1;
}

