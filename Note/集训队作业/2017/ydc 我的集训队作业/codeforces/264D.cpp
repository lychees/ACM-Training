#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
using namespace std;
typedef long long LL;
char s1[maxn],s2[maxn];
int sum[maxn][3][3],n1,n2;
int hash(char p)
{
	if(p=='R')
		return 0;
	return p=='G'?1:2;
}
void read()
{
	scanf("%s %s",s1+1,s2+1);
	n1=strlen(s1+1),n2=strlen(s2+1);
	for(int i=1;i<=n1;++i)
		s1[i]=hash(s1[i]);
	for(int i=1;i<=n2;++i)
		s2[i]=hash(s2[i]);
	for(int i=1;i<n2;++i)
	{
		memcpy(sum[i+1],sum[i],sizeof(sum[i]));
		++sum[i+1][s2[i]][s2[i+1]];
	}
}
LL work()
{
	LL ans=0;
	for(int i=1,l=1,r=1;i<=n1&&l<=n2;++i)
	{
		while(r<n2&&s2[r]!=s1[i])
			++r;
		ans+=r-l+1;
		if(i<n1&&s1[i]!=s1[i+1])
			ans-=sum[r][s1[i+1]][s1[i]]-sum[l][s1[i+1]][s1[i]];
		if(r<n2)
			++r;
		if(s2[l]==s1[i])
			++l;
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
