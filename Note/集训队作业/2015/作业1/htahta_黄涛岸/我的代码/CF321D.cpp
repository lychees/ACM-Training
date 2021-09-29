#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=35;
int a[maxn][maxn],b[maxn],n,m,ans=-100000000,c[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	cin>>n,m=n/2+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
	for(int S=0;S<(1<<m);S++)
	{
		int sum=0,s1,s2;
		for(int i=m;i>=1;i--)
		{
			b[i]=(S>>(i-1))&1?-1:1,b[i+m]=b[m]*b[i];
			sum+=a[i][m]*b[i]+a[i+m][m]*b[i+m];
		}
		for(int i=1;i<m;i++)
		{
			for(int j=1;j<=n;j++)c[j]=a[j][i]+b[j]*a[j][i+m];
			s1=s2=0;
			for(int j=1;j<m;j++)s1+=abs(c[j]+c[j+m]),s2+=abs(c[j]-c[j+m]);
			sum+=max(s1+c[m],s2-c[m]);
		}
		ans=max(ans,sum);
	}
	cout<<ans<<endl;
	return 0;
}

