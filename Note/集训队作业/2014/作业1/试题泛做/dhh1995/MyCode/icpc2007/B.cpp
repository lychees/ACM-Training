#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,ans,c,p; char s[1005]; int f[1005];
int main()
{
	while (scanf("%s",s),*s!='e'){
		n=strlen(s),ans=c=0; rep(i,n) f[i]=0;
		rep(i,n){rep(j,i) if (s[j]<s[i]) f[i]=max(f[i],f[j]); ++f[i]; ans=max(ans,f[i]);}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
