#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 200010
#define each(e,x) for(__typeof(x.begin()) e=x.
#define lowbit(x) (x&-x)
using namespace std;
typedef long long LL;
int n,sum[maxn],pos[maxn],match[maxn],contain[maxn],inter[maxn];
void add(int p,int x)
{
	for(int i=p;i<=n;i+=lowbit(i))
		sum[i]+=x;
}
int getsum(int p)
{
	int ans=0;
	for(int i=p;i;i-=lowbit(i))
		ans+=sum[i];
	return ans;
}
int getsum(int l,int r)
{
	return getsum(r)-getsum(l-1);
}
void read()
{
	scanf("%d",&n);
	n<<=1;
	for(int i=1,a,b;i<=n/2;++i)
	{
		scanf("%d %d",&a,&b);
		pos[a]=pos[b]=i;
		match[a]=b,match[b]=a;
	}
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		if(match[i]>i)
		{
			inter[pos[i]]+=getsum(i,match[i]);
			add(match[i],1);
		}
		else
			add(i,-1);
	}
	for(int i=n;i>=1;--i)
	{
		if(match[i]<i)
		{
			inter[pos[i]]+=getsum(match[i],i);
			add(match[i],1);
		}
		else
			add(i,-1);
	}
	for(int i=1;i<=n;++i)
		if(match[i]<i)
		{
			contain[pos[i]]=getsum(match[i],i);
			add(match[i],1);
		}
	LL ans1=0,ans2=0,total=(LL)n/2*(n/2-1)*(n/2-2)/6;
	for(int i=1;i<=n/2;++i)
	{
		ans1+=(LL)inter[i]*(n/2-inter[i]-1);
		ans2+=(LL)contain[i]*(n/2-inter[i]-1-contain[i]);
	}
	cout<<total-ans1/2-ans2<<endl;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
