#include <iostream>
#include <cstdio>
using namespace std;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=1000003,mod=1000000007;
int s[maxn],Pow[maxn],n,m,k,l=maxn,r=0,ans;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get(),k=get();
	for(int i=1;i<=m;i++)
	{
		int x=get(),y=get();
		if(x+1==y)continue;
		if(x+k+1!=y)return puts("0"),0;
		if(x<l)l=x;
		if(x>r)r=x;
		s[x]=1;
	}
	Pow[0]=1;ans=r?0:1;
	for(int i=1;i<=n;i++)s[i]+=s[i-1],Pow[i]=Pow[i-1]<<1,Pow[i]-=Pow[i]>=mod?mod:0;
	for(int i=1,j;i+k+1<=n&&i<=l;i++)
		if(i<=l&&r<=(j=i+k<n-k-1?i+k:n-k-1))ans+=Pow[j-i-(s[j]-s[i])],ans-=ans>=mod?mod:0;
	cout<<ans<<endl;
	return 0;
}
