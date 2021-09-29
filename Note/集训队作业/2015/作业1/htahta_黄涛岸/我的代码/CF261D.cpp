#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=100033;
int s[maxn],f[maxn],n,T,maxb,t,a[maxn];
int solve()
{
	for(int i=1;i<=n;i++)a[i]=get(),f[i]=0;
	if(t>=n||t>=maxb)return sort(a+1,a+1+n),unique(a+1,a+1+n)-a-1;
	int len=0;
	for(int i=1;i<=t;++i)
		for(int j=1;j<=n;++j)
		{
			while(s[f[j]]<a[j]&&f[j]<=len)++f[j];
			s[f[j]]=a[j];
			if(f[j]>len)len=f[j];
		}
	return len;
}

int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	T=get(),n=get(),maxb=get(),t=get();
	while(T--)printf("%d\n",solve());
	return 0;
}
