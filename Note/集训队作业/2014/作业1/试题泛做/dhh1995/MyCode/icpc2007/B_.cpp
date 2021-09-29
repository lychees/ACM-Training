#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,ans,c,p; char s[1005]; bool b[1005];
int main()
{
	while (scanf("%s",s),*s!='e'){
		n=strlen(s),ans=c=0; rep(i,n) b[i]=1;
		while (c<n){
			++ans,p=n;
			while (p){
				char m='a'; rep(i,p) if (b[i] && s[i]<m) m=s[i];
				for (int i=p-1;i>=0;--i) if (b[i] && s[i]==m) b[i]=0,++c,p=i;
				while (p && !b[p-1]) --p;
			}
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
