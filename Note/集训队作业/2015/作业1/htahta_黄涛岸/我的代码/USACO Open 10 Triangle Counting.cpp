#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=200333;
struct Tpoint
{
	int x,y;double ang;
	void getp(){x=get(),y=get(),ang=atan2(y,x);}
	inline bool operator <(const Tpoint &b)const{return ang<b.ang;}
	inline LL operator *(const Tpoint &b)const{return LL(x)*b.y-LL(y)*b.x;}
}a[maxn];
int n;LL ans=0;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)a[i].getp();
	sort(a+1,a+1+n);
	for(int i=1,s=0,j=1;i<=n;i++)
	{
		a[i+n]=a[i];
		while(j+1<i+n&&a[i]*a[j+1]>=0)j++,s++;
		ans+=LL(s)*(s-1)/2;s--;
	}
	cout<<LL(n)*(n-1)*(n-2)/6-ans<<endl;
	return 0;
}
