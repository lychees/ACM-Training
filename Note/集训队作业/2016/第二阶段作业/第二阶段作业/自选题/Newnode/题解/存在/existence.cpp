#include<algorithm>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include    <queue>
#include      <map>
#include      <set>
using namespace std;

typedef long long LL;

const int N=17000005;

LL n;

int p[N/10],m,f[N],F[N];

char mu[N],P[N];

void sieve(int n)
{
	mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!P[i])
			p[++m]=i,mu[i]=-1;
		for(int j=1;j<=m&&i*p[j]<=n;j++)
		{
			int k=i*p[j];
			P[k]=1;
			if(i%p[j]==0)
			{
				mu[k]=0;break;
			}
			mu[k]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++)
		f[i]=f[i-1]+mu[i];
}

void solve1()
{
	sieve(sqrt(n));
	LL Ans=0;
	for(LL i=1;i*i<=n;i++)
		Ans+=mu[i]*(n/i/i);
	cout<<Ans<<endl;
}

void solve2()
{
	int A=exp(log(n)/5),B=sqrt(n/A);
	LL Ans=0;
	sieve(B);
	for(int i=1;i<=B;i++)
		Ans+=mu[i]*(n/i/i);
	for(int i=A;i;i--)
	{
		int w=sqrt(n/i),x=0;
		for(int k,j=2;j<=w;j=k+1)
		{
			int t=w/j;k=w/t;
			if(t<=B)
				x+=f[t]*(k-j+1);
			else
				x+=F[j*j*i]*(k-j+1);
		}
		F[i]=1-x;
		if(i==A)
			Ans-=(A-1)*(LL)F[i];
		else
			Ans+=F[i];
	}
	cout<<Ans<<endl;
}

int main()
{
	freopen("existence.in","r",stdin);
	freopen("existence.out","w",stdout);
	scanf("%lld",&n);
	solve2();
	return 0;
}

