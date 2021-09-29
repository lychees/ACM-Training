#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef unsigned int uint;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=50003;
struct Trie
{
	int l,r,next[2];
}g[maxn*31];
int s[maxn][31],n,tot=1,b[maxn],t=0;
uint m=0,a[maxn],T,res=0;
LL sum=0;
int main()
{
	//freopen("tmp.in","r",stdin);
	//freopen("tmp.out","w",stdout);
	n=get();T=get();
	for(int i=1;i<=n;i++)a[i]=get(),m=max(m,a[i]),b[i]=1;
	sort(a+1,a+1+n);
	for(a[0]=m,m=-1;a[0];a[0]/=2,++m);
	g[1].l=1,g[1].r=n;
	for(int i=1;i<=n;i++)
	{
		int k=1,v;
		for(int j=m;j>=0;j--)
		{
			s[i][j]=s[i-1][j]+(v=(a[i]>>j)&1);
			if(!g[k].next[v])g[k].next[v]=++tot,g[tot].l=i;
			k=g[k].next[v];g[k].r=i;
		}
	}
	for(int i=m;i>=0;i--)
	{
		uint cnt=0,k,l,r;
		for(int j=1;j<=n;j++)
			k=g[b[j]].next[((a[j]>>i)&1)^1],k?cnt+=g[k].r-g[k].l+1:0;
		if((res+cnt)/2<=T)
		{
			res+=cnt;
			for(int j=1;j<=n;j++)
			{
				k=g[b[j]].next[((a[j]>>i)&1)^1];
				if(!k)continue;
				l=g[k].l,r=g[k].r;
				sum+=LL(t|(1<<i))*(r-l+1);
				for(int p=0;p<i;p++)
					cnt=s[r][p]-s[l-1][p],sum+=LL(((a[j]>>p)&1)?r-l+1-cnt:cnt)<<p;
			}
		}else t|=1<<i;
		for(int j=1;j<=n;j++)b[j]=g[b[j]].next[((a[j]^t)>>i)&1];
	}
	cout<<(sum/2+LL(T-res/2)*t)%1000000007<<endl;
	return 0;
}
