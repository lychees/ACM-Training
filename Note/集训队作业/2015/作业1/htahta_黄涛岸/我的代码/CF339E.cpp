#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <ctime>
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
const int maxn=1003;
int a[maxn],pos[maxn],l[5],r[5],n;
bool dfs(int x)
{
	bool flag=1;
	for(int i=1;i<=n&&flag;i++)flag&=a[i]==i;
	if(flag)return printf("%d\n",x-1),1;
	if(x>3)return 0;
	for(int i=0;i<=n;i++)
	{
		int l=pos[i],r=pos[i+1];
		if(l>r)swap(l,r);
		if(r-l==1)continue;else ++l;
		reverse(a+l,a+r+1);
		for(int j=l;j<=r;j++)pos[a[j]]=j;
		if(dfs(x+1))return printf("%d %d\n",l,r),1;
		reverse(a+l,a+r+1);
		for(int j=l;j<=r;j++)pos[a[j]]=j;
	}
	return 0;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();a[n+1]=pos[n+1]=n+1;
	for(int i=1;i<=n;i++)a[i]=get(),pos[a[i]]=i;
	dfs(1);
	return 0;
}
