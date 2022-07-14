#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cctype>
#define mod 1000003
#define maxn 110
#define maxm 500000
using namespace std;
typedef long long LL;
int n,m,cnt[30],dp[30][maxn],fact[maxm],anti[maxm];
int Power(int p,int n)
{
	int ans=1;
	for(;n;n>>=1,p=(LL)p*p%mod)
		if(n&1)
			ans=(LL)ans*p%mod;
	return ans;
}
void read()
{
	static char str[maxm];
	scanf("%s",str+1);
	for(int i=1;isalpha(str[i]);++i)
		++n,m+=str[i]!=str[i-1],++cnt[str[i]-'a'+1];
	fact[0]=1;
	for(int i=1;i<=n;++i)
		fact[i]=(LL)fact[i-1]*i%mod;
	anti[n]=Power(fact[n],mod-2);
	for(int i=n-1;i>=0;--i)
		anti[i]=(LL)anti[i+1]*(i+1)%mod;
}
int C(int n,int m)
{
	if(n<m)
		return 0;
	return (LL)fact[n]*anti[m]*anti[n-m]%mod;
}
int Dp()
{
	dp[0][0]=1;
	for(int i=1,s=cnt[1];i<=26;s+=cnt[++i])
	{
		if(!cnt[i])
		{
			for(int j=0;j<=m;++j)
				dp[i][j]=dp[i-1][j];
			continue;
		}
		for(int j=0;j<=m&&j<=s;++j)
			for(int x=0;x<=cnt[i]&&2*x<=j;++x)
				for(int y=0;x+y<=cnt[i]&&2*x+y<=j;++y)
					if(x+y-1>=0)
						dp[i][j]=(dp[i][j]+(LL)dp[i-1][j-2*x-y]*C((s-cnt[i])-(j-2*x-y),x)%mod*C(j-2*x-y+1,y)*C(cnt[i]-1,x+y-1))%mod;
	}
	return dp[26][m];
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	printf("%d\n",Dp());
	return 0;
}
