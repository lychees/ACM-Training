#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 10010
#define mod 1000000007
using namespace std;
typedef long long LL;
int cnt[3],dp[maxn][5];
int n,p,a[maxn],b[maxn],tot;
void add(int &a,int b)
{
	a+=b;
	if(a>=mod)
		a-=mod;
}
int getsum(LL L,LL R)
{
	LL l=p-R+1,r=p-L+1;
	return (l+r)*(r-l+1)/2%mod;
}
int f1(int n)
{
	return (n-1)/3+1;
}
int f2(int n)
{
	return n-(n-1)/3;
}
int get(int p)
{
	return lower_bound(a+1,a+tot+1,p)-a;
}
int binary(int l,int r,int p1,int p2)
{
	while(l<r)
	{
		int mid=(l+r)>>1;
		get(f1(mid))==p1&&get(f2(mid))==p2?l=mid+1:r=mid;
	}
	return l-1;
}
void Prepare()
{
	tot=1,a[1]=min(3,p),a[0]=1;
	while(a[tot]<p)
	{
		int x=get(f1(a[tot]+1)),y=get(f2(a[tot]+1));
		int next=binary(a[tot]+1,p+1,x,y);
		a[++tot]=next;
		for(b[tot]=0;b[tot]==b[x]||b[tot]==b[y];++b[tot]);
		if(b[tot]==b[tot-1])
			a[--tot]=next;
	}
	for(int i=1;i<=tot;++i)
		add(cnt[b[i]],getsum(a[i-1]+1,a[i]));
}
void Dp()
{
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=3;++j)
			for(int k=0;k<=3;++k)
				add(dp[i][k],(LL)dp[i-1][k^j]*cnt[j]%mod);
	int ans=0;
	for(int i=1;i<=3;++i)
		add(ans,dp[n][i]);
	cout<<ans<<endl;
}
int main()
{
	freopen("input.txt","r",stdin);
	cin>>n>>p;
	Prepare();
	Dp();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
