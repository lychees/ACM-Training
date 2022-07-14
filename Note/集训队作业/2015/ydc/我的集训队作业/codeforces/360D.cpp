#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
typedef long long LL;
LL n,m,mod,a[maxn],b[maxn],val[maxn];
pair<LL,int> sorted[1000010];
int N=1000000;
int power(LL p,LL n)
{
	LL ans=1;
	for(;n;n>>=1,p=p*p%mod)
		if(n&1)
			ans=ans*p%mod;
	return ans;
}
void read()
{
	cin>>n>>m>>mod;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=m;++i)
		cin>>b[i];
}
int Primitive_Root(LL p)
{
	static int d[maxn];
	int tot=0;
	for(int i=2;i*i<=p-1;++i)
		if((p-1)%i==0)
		{
			d[++tot]=i;
			if((p-1)/i!=i)
				d[++tot]=(p-1)/i;
		}
	for(int i=2;i<p-1;++i)
	{
		bool mark=true;
		for(int j=1;j<=tot&&mark;++j)
			if(power(i,d[j])==1)
				mark=false;
		if(mark)
			return i;
	}
	return p-1;
}
int Anti(LL p)
{
	return power(p,mod-2);
}
int Log(int p,LL x)
{
	p=Anti(power(p,N));
	for(int i=0;;++i)
	{
		pair<LL,int> it=make_pair(x,-1);
		int id=lower_bound(sorted,sorted+N,it)-sorted;
		if(sorted[id].first==x)
			return i*N+sorted[id].second;
		x=x*p%mod;
	}
	return 0;
}
int lcm(int a,int b)
{
	return a/__gcd(a,b)*b;
}
void work()
{
	LL g=Primitive_Root(mod);
	sorted[0]=make_pair(1,0);
	for(int i=1;i<N;++i)
		sorted[i]=make_pair(sorted[i-1].first*g%mod,i);
	sort(sorted,sorted+N);
	LL t=mod-1;
	for(int i=1;i<=m;++i)
		t=__gcd(t,b[i]);
	for(int i=1;i<=n;++i)
		val[i]=__gcd(Log(g,a[i])*t,mod-1);
	sort(val+1,val+n+1);
	n=unique(val+1,val+n+1)-val-1;
	int top=0;
	for(int i=1;i<=n;++i)
	{
		bool mark=true;
		for(int j=1;j<=top&&mark;++j)
			if(val[i]%val[j]==0)
				mark=false;
		if(mark)
			val[++top]=val[i];
	}
	static bool mark[maxn];
	static int c[maxn],sum[maxn];
	int tot=0,total=0;
	for(int i=1;i*i<=mod-1;++i)
		if((mod-1)%i==0)
		{
			c[++tot]=i;
			if(i*i!=mod-1)
				c[++tot]=(mod-1)/i;
		}
	sort(c+1,c+tot+1);
	for(int i=1;i<=top;++i)
		for(int j=1;j<=tot;++j)
			if(c[j]%val[i]==0)
				mark[j]=1;
	for(int i=tot;i>=1;--i)
		if(mark[i])
		{
			sum[i]=(mod-1)/c[i];
			for(int j=i+1;j<=tot;++j)
				if(c[j]%c[i]==0)
					sum[i]-=sum[j];
			total+=sum[i];
		}
	cout<<total<<endl;
}
int main()
{
	read();
	work();
	return 0;
}
