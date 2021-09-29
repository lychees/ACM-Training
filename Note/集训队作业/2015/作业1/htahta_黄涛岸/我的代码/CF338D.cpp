#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#define KILL return puts("NO"),0
using namespace std;
typedef long long LL;
LL get()
{
	LL f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=10004;
LL n,m,m1,a1,m2,a2,x,y,gcd,lcm,tp,a[maxn];
LL extgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0){x=1,y=0;return a;}
	LL tp,gcd=extgcd(b,a%b,x,y);
	tp=x;x=y;y=tp-a/b*y;
	return gcd;
}
int k;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get(),k=get();
	a[0]=m1=get(),a1=0;
	if(m1>n)KILL;
	for(int i=1;i<k;i++)
	{
		a[i]=m2=get(),a2=-i;
		gcd=extgcd(m1,m2,x,y);
		if((a2-a1)%gcd)KILL;
		if(n/(m1/gcd)<m2)KILL;else lcm=m1/gcd*m2;
		tp=m2/gcd;
		(a1+=m1*((a2-a1)/gcd%tp*x%tp))%=lcm;
		if(a1<0)a1+=lcm;m1=lcm;
	}
	if(!a1)a1=m1;
	if(a1+k-1>m)KILL;
	for(int i=0;i<k;i++)
		if(extgcd(m1,a1+i,x,y)!=a[i])KILL;
	puts("YES");
	return 0;
}
