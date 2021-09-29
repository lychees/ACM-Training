#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=5003;
char s[maxn];
int sg[maxn],tmp[maxn],n,L[maxn],pos[maxn],cnt[maxn],N=0,res=0;
inline int f(int x,int y){return sg[max(x,0)]^sg[max(y,0)];}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=2,j;i<=n;i=j+1)
	{
		int tp=0;
		for(j=i;j<=n&&s[j-1]==s[j+1];j++)pos[j]=++tp;
		for(int k=i;k<j;k++)L[k]=tp;
		N=max(N,tp),cnt[tp]^=1;
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=i;j++)tmp[f(j-2,i-j-1)]=i;
		for(;tmp[sg[i]]==i;sg[i]++);
		if(cnt[i])res^=sg[i];
	}
	if(!res)return puts("Second"),0;
	puts("First");
	for(int i=2;i<=n;i++)
		if(L[i]&&!(res^sg[L[i]]^f(pos[i]-2,L[i]-pos[i]-1))){res=i;break;}
	printf("%d\n",res);
	return 0;
}

