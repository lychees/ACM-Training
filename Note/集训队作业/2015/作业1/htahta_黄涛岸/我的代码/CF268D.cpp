#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long LL;
const int mod=1000000009;
LL f[2][31][31][31][2],ans=0;
int n,h;
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d",&n,&h);
	f[1][1][1][1][1]=4;
	for(int i=1;i<n;++i)
		for(int a=1;a<=h;++a)
			for(int b=1;b<=h;++b)
				for(int c=1;c<=h;++c)
					for(int j=0;j<2;++j)
					{
						LL v=f[i&1][a][b][c][j];
						if(!v)continue;
						f[i&1][a][b][c][j]=0;v%=mod;
						if(!v)continue;
						int x=a<h?a+1:h,y=b<h?b+1:h,z=c<h?c+1:h,w=j?1:h,k=(i+1)&1;
						f[k][y][z][w][a<h]+=v;
						f[k][x][z][w][b<h]+=v;
						f[k][x][y][w][c<h]+=v;
						f[k][x][y][z][j]+=v;
					}
	for(int a=1;a<=h;++a)
		for(int b=1;b<=h;++b)
			for(int c=1;c<=h;++c)
				for(int j=0;j<2;++j)
					if(j||a+b+c<3*h)ans+=f[n&1][a][b][c][j];
	cout<<ans%mod<<endl;
	return 0;
}
