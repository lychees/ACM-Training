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
const int maxn=2003,maxN=2003*2003;
typedef unsigned int uint;
uint mu[maxn],f[maxN],ans=0,g[maxn][maxn],a,b,c,N;;
inline uint gcd(int x,int y)
{
	if(g[x][y])return g[x][y];
	g[x][y]=g[y][x]=y?gcd(y,x%y):x;
	return g[x][y];
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	a=get(),b=get(),c=get();
	if(a>c)swap(a,c);
	if(b>c)swap(b,c);
	mu[1]=1;N=a*b;
	for(int i=1;i<=c;i++)
	{
		if(!mu[i])continue;
		uint t=c/i;
		for(int j=i+i;j<=c;j+=i)t+=c/j,mu[j]-=mu[i];
		t*=mu[i];
		for(int j=i;j<=N;j+=i)f[j]+=t;
	}
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			if(gcd(i,j)==1)ans+=f[i*j]*(a/i)*(b/j);
	cout<<(ans%(1<<30))<<endl;
	return 0;
}

