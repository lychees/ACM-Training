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
const int maxn=100333,inf=1000000000;
int a[maxn],b[maxn],s[maxn],n1,n2,c1,c2,c3,n;
inline int g(int &a,int &b)
{
	int c=a<b?a:b;
	return a-=c,b-=c,c;
}
inline int f(int S)
{
	int ans=S*c3,t=0;
	for(int i=1,j=1;i<=n;i++)
	{
		int cnt=a[i],tp;
		b[i]=cnt;
		g(cnt,S);
		for(;i-j>=n2&&cnt;!b[j]?j++:0)
			if(b[j])tp=g(cnt,b[j]),ans+=tp*c2;
		if(i>n1&&b[i-n1])s[++t]=i-n1;
		while(t&&cnt)
		{
			tp=g(cnt,b[s[t]]),ans+=tp*c1;
			if(!b[s[t]])t--;
		}
		if(cnt)return inf;
	}
	return ans;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	int l=0,r=0;
	n=get();n1=get(),n2=get(),c1=get(),c2=get(),c3=get();
	for(int i=1;i<=n;i++)r+=a[i]=get();
	if(n1>n2)swap(n1,n2),swap(c1,c2);
	if(c1<c2)c2=c1;
	while(l<r)
	{
		int mid=(l+r)/2,v=f(mid);
		if(v==inf||v>f(mid+1))l=mid+1;else r=mid;
	}
	printf("%d\n",f(l));
	return 0;
}
