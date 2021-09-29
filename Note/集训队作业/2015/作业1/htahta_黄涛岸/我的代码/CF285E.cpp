#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=1003,mod=1000000007;
typedef long long LL;
int f[maxn][maxn][4],C[maxn][maxn],n,m;
LL a[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&m);
	f[0][0][1]=1;
	for(int i=0;i<n;++i)
		for(int j=0;j<=i;++j)
			for(int s=0;s<4;s++)
			{
				if(!f[i][j][s])continue;
				int v=f[i][j][s];
				if(!(s&1))(f[i+1][j+1][s/2]+=v)%=mod;
				if(i+1<n)(f[i+1][j+1][s/2+2]+=v)%=mod;
				(f[i+1][j][s/2]+=v)%=mod;
			}
	for(int i=0,j;i<=n;i++)
		for(j=C[i][0]=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=n,c=1;i>=m;i--)
	{
		for(int j=0;j<4;j++)a[i]+=f[n][i][j];
		c=LL(c)*max(n-i,1)%mod;a[i]=a[i]%mod*c%mod;
		for(int j=i+1;j<=n;j++)(a[i]-=a[j]*C[j][i])%=mod;
	}
	cout<<(a[m]+mod)%mod<<endl;
	return 0;
}

