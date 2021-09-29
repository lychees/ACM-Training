#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=450033,mod=1000003;
typedef long long LL;
int n=1,cnt[30],a[30],m=0,T;
LL f[30][110],inv[maxn],fac[maxn];
char s[maxn];
LL Pow(LL a,int b)
{
	LL res=1;
	for(;b;b/=2,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
inline LL C(int n,int k){return fac[n]*inv[n-k]*inv[k]%mod;}
int main()
{
	while(isalpha(s[n]=getchar()))n++;
	n--;fac[0]=f[1][1]=1;
	for(int i=1;i<=n;i++)
		cnt[s[i]-'a']++,fac[i]=fac[i-1]*i%mod,m+=(s[i]!=s[i-1]);
	inv[n]=Pow(fac[n],mod-2);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	n=0;
	for(int i=0;i<26;i++)
		if(cnt[i])a[++n]=cnt[i];
	for(int i=1,s=a[1];i<n;i++,s+=a[i])
		for(int j=i;j<=m;j++)
			for(int k=f[i][j]?0:m;j+k<=m&&k<=j+1;k++)
				for(int l=k?0:1,p=min(min((m-j-k)/2,s-j),a[i+1]-k);l<=p;l++)
					(f[i+1][j+k+2*l]+=C(j+1,k)*C(s-j,l)*C(a[i+1]-1,k+l-1)%mod*f[i][j])%=mod;
	printf("%d\n",int(f[n][m]));
	return 0;
}
