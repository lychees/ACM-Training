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
const int maxn=100002;
int s[maxn],f[maxn],g[maxn],q[maxn],n,v[maxn];
int main()
{
	n=get();
	for(int i=1;i<=n;++i)s[i]=s[i-1]+get();
	int front=1,rear=1;
	q[front]=n+1;v[n+1]=s[n];
	for(int i=n;i;--i)
	{
		while(front<rear&&v[q[front+1]]>=s[i-1])front++;
		f[i]=s[q[front]-1]-s[i-1],g[i]=g[q[front]]+1;v[i]=s[i-1]-f[i];
		while(front<rear&&v[i]>v[q[rear]])rear--;
		q[++rear]=i;
	}
	printf("%d\n",g[1]);
	return 0;
}
