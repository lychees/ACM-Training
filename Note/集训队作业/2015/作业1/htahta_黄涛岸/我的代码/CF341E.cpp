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
const int maxn=1003;
int a[maxn],n,c=0,X[maxn*400],Y[maxn*400];
inline void f(int i,int j)
{
	a[j]-=a[i],a[i]<<=1;
	X[++c]=i,Y[c]=j;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)a[i]=get(),a[i]?c++:0;
	if(c<=1)return puts("-1"),0;
	c=0;
	for(int k=1,j=2,i,x=3,y;x<=n;x++)
	{
		i=x;
		while(1)
		{
			if(a[i]>a[j])swap(i,j);
			if(a[i]>a[k])swap(i,k);
			if(a[j]>a[k])swap(j,k);
			if(!a[i])break;
			for(y=a[j]/a[i];y;y/=2)
				if(y&1)f(i,j);else f(i,k);
		}
	}
	printf("%d\n",c);
	for(int i=1;i<=c;i++)printf("%d %d\n",X[i],Y[i]);
	return 0;
}
