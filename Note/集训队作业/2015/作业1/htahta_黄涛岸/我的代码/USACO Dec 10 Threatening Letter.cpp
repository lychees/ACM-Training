#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
const int maxn=100333;
int rank[maxn],rank2[maxn],sa[maxn],tp[maxn],h[maxn],n,m,len=0,a[maxn],Link[maxn],pre[maxn];
char s[maxn];
inline bool cmp(int a,int b){return s[a]<s[b];}
void make_SuffixArray(int n)
{
	for(int i=1;i<=n;i++)sa[i]=i;
	sort(sa+1,sa+1+n,cmp);
	int cnt=1; rank[sa[1]]=1;
	for(int i=2;i<=n;i++)
		if(s[sa[i]]==s[sa[i-1]])rank[sa[i]]=cnt;else rank[sa[i]]=++cnt;
	for(int j=1;cnt!=n;j+=j)
	{
		memcpy(rank2+1,rank+1+j,4*(n-j));
		memset(rank2+n-j+1,0,4*j);
		memset(Link,0,4*(n+1));cnt=0;
		for(int i=1;i<=n;i++)pre[i]=Link[rank2[i]],Link[rank2[i]]=i;
		for(int i=0;i<=n;i++)
			for(int k=Link[i];k;k=pre[k])tp[++cnt]=k;
		memset(Link,0,4*(n+1));cnt=0;
		for(int i=n;i>=1;i--)pre[tp[i]]=Link[rank[tp[i]]],Link[rank[tp[i]]]=tp[i];
		for(int i=0;i<=n;i++)
			for(int k=Link[i];k;k=pre[k])sa[++cnt]=k;
		cnt=1; tp[sa[1]]=1;
		for(int i=2;i<=n;i++)
			if(rank[sa[i]]==rank[sa[i-1]]&&rank2[sa[i]]==rank2[sa[i-1]])tp[sa[i]]=cnt;else tp[sa[i]]=++cnt;
		memcpy(rank+1,tp+1,4*n);
	}
}
void make_HeightArray()
{
	for(int i=1,j,k=0;i<=len;h[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
}
void work()
{
	int i=1,p,k,j,lcp=len;
	while(sa[i]>n)i++;
	for(j=i-1;j;j--)
		p=sa[j]-n-1,
		lcp=min(lcp,h[j+1]),
		a[p]=max(a[p],lcp);
	while(sa[i]<=n&&i<=len)i++;
	for(;i<=len;i=j)
	{
		j=i+1;
		while(sa[j]>n&&j<=len)j++;
		lcp=len;
		for(k=i;k<j;k++)
			p=sa[k]-n-1,
			lcp=min(lcp,h[k]),
			a[p]=max(a[p],lcp);
		if(j>len)break;else lcp=len;
		for(k=j-1;k>=i;k--)
			p=sa[k]-n-1,
			lcp=min(lcp,h[k+1]),
			a[p]=max(a[p],lcp);
		while(sa[j]<=n&&j<=len)j++;
	}
	int ans=0;
	for(int i=1;i<=m;i+=a[i])ans++;
	printf("%d\n",ans);
}
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		while(!isalpha(s[i]=getchar()));
	s[n+1]='~';
	for(int i=n+2;i<=n+1+m;i++)
		while(!isalpha(s[i]=getchar()));
	len=n+m+1;
}
int main()
{
	init();
	make_SuffixArray(len);
	make_HeightArray();
	work();
	return 0;
}

