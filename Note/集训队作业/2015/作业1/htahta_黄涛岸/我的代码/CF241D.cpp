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
const int maxp=50003,maxn=33;
int n,p,a[maxn],m=0,f[maxn][maxp][maxn],inf,id[maxn],res[maxn];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),p=get();
	memset(f,120,sizeof(f));
	f[0][0][0]=0;inf=f[1][1][1];
	for(int i=1;i<=n;i++)
	{
		int x=get(),b=10;
		if(x>31)continue;
		a[++m]=x,id[m]=i;
		if(x>9)b=100;
		for(int j=0,v,k;j<p;j++)
			for(k=0,v=(j*b+x)%p;k<32;k++)
				if(f[m-1][j][k]!=inf)
				{
					f[m][v][k^x]=j;
					if(f[m][j][k]==inf)f[m][j][k]=-1;
				}
	}
	int x=0,y=0;
	for(;m;--m)
		if(f[m][x][y]!=inf&&f[m][x][y]!=-1)res[++res[0]]=id[m],x=f[m][x][y],y^=a[m];
	if(res[0])
	{
		printf("Yes\n%d\n",res[0]);
		for(int i=res[0];i;i--)printf("%d%c",res[i],i==1?'\n':' ');
	}else puts("No");
	return 0;
}
