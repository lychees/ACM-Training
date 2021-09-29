#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=1000003;
long long ans=0;
int s[maxn][3][3],f[100],n,m;
char a[maxn],b[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1);
	f['R']=1,f['G']=2;b[1]=f[b[1]];
	for(int i=2;i<=m;i++)
	{
		b[i]=f[b[i]];
		memcpy(s[i],s[i-1],36);
		++s[i][b[i-1]][b[i]];
	}
	for(int i=1,l=1,r=1;i<=n&&l<=m;i++)
	{
		a[i]=f[a[i]];
		while(r<m&&a[i]!=b[r])++r;
		ans+=r-l+1;
		if(i>1&&a[i]!=a[i-1])ans-=s[r][a[i]][a[i-1]]-s[l-1][a[i]][a[i-1]];
		l+=(a[i]==b[l]),r+=(r<m&&a[i]==b[r]);
	}
	cout<<ans<<endl;
	return 0;
}
