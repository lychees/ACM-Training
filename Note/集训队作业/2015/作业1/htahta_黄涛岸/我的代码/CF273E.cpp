#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=1003,mod=1000000007;
typedef long long LL;
int n,p,f[maxn][4],a[maxn],sg[maxn];
LL v[4];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&p);
	int N,i,j,k,p1,p2;
	for(i=j=N=1,a[1]=2,p1,p2;a[N]<p;i+=(p1<=p2),j+=(p2<=p1))
	{
		p1=(a[i]+1)*3-1,p2=a[j]/2*3+a[j]%2;
		sg[++N]=sg[i]&&sg[j]?0:(sg[i]+sg[j]==1?2:1);
		if(sg[N]==sg[N-1])--N;
		a[N]=min(p1,p2);
	}
	a[N]=p;
	for(int i=1;i<=N;i++)
		(v[sg[i]]+=LL(2*p-a[i]-a[i-1]-1)*(a[i]-a[i-1])/2)%=mod;
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<3;k++)
				f[i][j]=(LL(v[k])*f[i-1][j^k]+f[i][j])%mod;
	cout<<((f[n][1]+f[n][2])%mod+f[n][3])%mod<<endl;
	return 0;
}
