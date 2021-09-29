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
int n,d[2003],k;
long long s[2003],ans=0;
int C(int n,int k)
{
	if(k>2)k=n-k;
	return !k?1:(k==1?n:n*(n-1)/2);
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),k=get();
	for(int i=1;i<=n;ans+=s[i]*C(d[i]-1,k-1),i++)
		for(int j=i+1,x;j<=n;j++)
			if((x=get())!=-1)s[i]+=x,s[j]+=x,++d[i],++d[j];
	printf("%I64d\n",ans/C(n,k));
	return 0;
}
