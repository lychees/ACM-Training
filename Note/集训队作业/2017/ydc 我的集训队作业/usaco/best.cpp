#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn 30010
#define P 101
using namespace std;
typedef unsigned long long ULL;
int n;
char ch[maxn];
ULL Power[maxn],sum1[maxn],sum2[maxn];
void read()
{
	scanf("%d",&n);
	Power[0]=1;
	for(int i=1;i<=n;++i)
		Power[i]=Power[i-1]*P;
	for(int i=1;i<=n;++i)
	{
		char &c=ch[i];
		for(c=getchar();!isalpha(c);c=getchar());
		sum1[i]=sum1[i-1]*P+c;
	}
	reverse(ch+1,ch+n+1);
	for(int i=1;i<=n;++i)
		sum2[i]=sum2[i-1]*P+ch[i];
	reverse(ch+1,ch+n+1);
}
ULL getHash(ULL *sum,int l,int r)
{
	return sum[r]-sum[l-1]*Power[r-l+1];
}
int LCP(int a,int b)
{
	if(ch[a]!=ch[b])
		return 0;
	int l=1,r=b-a+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		getHash(sum1,a,a+mid)==getHash(sum2,n-b+1,n-(b-mid)+1)?l=mid+1:r=mid;
	}
	return l;
}
void work()
{
	static char ans[maxn];
	int l=1,r=n,tot=0;
	while(l<=r)
	{
		int len=LCP(l,r);
		if(ch[l+len]<ch[r-len])
			ans[++tot]=ch[l++];
		else
			ans[++tot]=ch[r--];
	}
	for(int i=1;i<=n;++i)
	{
		printf("%c",ans[i]);
		if(i%80==0||i==n)
			printf("\n");
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
