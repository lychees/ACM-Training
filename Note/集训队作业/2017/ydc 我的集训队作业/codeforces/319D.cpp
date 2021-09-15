#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 50010
#define P 101
using namespace std;
typedef unsigned long long ULL;
ULL Power[maxn],sumhash[maxn];
char str[maxn];
int n;
ULL gethash(int l,int r)
{
	return sumhash[r]-sumhash[l-1]*Power[r-l+1];
}
int LCP(int i,int j)
{
	int l=1,r=n-max(i,j)+2;
	while(l<r)
	{
		int mid=(l+r)>>1;
		gethash(i,i+mid-1)==gethash(j,j+mid-1)?l=mid+1:r=mid;
	}
	return l-1;
}
int LCS(int i,int j)
{
	int l=1,r=min(i,j)+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		gethash(i-mid+1,i)==gethash(j-mid+1,j)?l=mid+1:r=mid;
	}
	return l-1;
}
void Prepare()
{
	Power[0]=1;
	for(int i=1;i<=n;++i)
		Power[i]=Power[i-1]*P,sumhash[i]=sumhash[i-1]*P+str[i];
}
bool check(int L)
{
	for(int i=1;i+L-1<=n;i+=L)
		if(str[i]==str[i+L]&&LCP(i,i+L)+LCS(i,i+L)-1>=L)
			return true;
	return false;
}
void print()
{
	static int use[maxn],id;
	for(int i=1;i*2<=n;++i)
		if(check(i))
		{
			++id;
			for(int j=1;j+2*i-1<=n;++j)
				if(use[j]!=id&&gethash(j,j+i-1)==gethash(j+i,j+2*i-1))
					for(int k=j;k<i+j;++k)
						use[k]=id;
			int m=0;
			for(int j=1;j<=n;++j)
				if(use[j]!=id)
					str[++m]=str[j];
			n=m;
			Prepare();
		}
	str[n+1]=0;
	printf("%s\n",str+1);
}
int main()
{
	freopen("input.txt","r",stdin);
	scanf("%s",str+1);
	n=strlen(str+1);
	Prepare();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
