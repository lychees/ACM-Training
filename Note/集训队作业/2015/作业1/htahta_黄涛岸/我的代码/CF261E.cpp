#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=3000005,inf=1000000000;
typedef long long LL;
int f[maxn],a[maxn],l,r,p,n=1,prime[100],totp=0;
bool check[maxn];
void dfs(int k,LL v)
{
	if(k>totp)a[++n]=v,f[n]=inf;
	else for(;v<=r;v*=prime[k])dfs(k+1,v);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&l,&r,&p);
	a[n]=1;
	for(int i=2;i<p;i++)
	{
		if(check[i])continue;else prime[++totp]=i;
		for(int j=i+i;j<=p;j+=i)check[j]=1;
	}
	dfs(1,1);
	sort(a+1,a+1+n);
	for(int i=1;i<=p;i++)check[i]=0;
	check[1]=1,f[1]=0;
	for(int i=2;i<p;i++)
		for(int j=1,lim=a[n]/i,k=1;a[j]<=lim;j++)
		{
			if(f[j]+i>=p)continue;
			while(a[k]<a[j]*i)k++;
			if(f[j]<f[k])f[k]=f[j]+1;
			check[k]=1;
		}
	r=0;
	for(int i=1;i<=n;i++)r+=a[i]>=l&&check[i];
	printf("%d\n",r);
	return 0;
}
