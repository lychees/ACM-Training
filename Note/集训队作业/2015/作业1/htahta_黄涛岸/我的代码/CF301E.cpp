#include <iostream>
#include <cstdio>
using namespace std;
const int mod=1000000007;
int f[52][52][52][103],n,m,c,C[103][103];
typedef long long LL;
LL ans=0;
inline void add(int &x,const int &y){x+=y;x>=mod?x-=mod:0;}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&n,&m,&c);
	for(int i=0,j;i<=n;i++)
		for(j=C[i][0]=1;j<=i;j++)C[i][j]=min(c+1,C[i-1][j]+C[i-1][j-1]);
	n/=2;
	for(int i=1;i<=n;i++)f[i][i][1][1]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=n&&k<m;++k)
				for(int x=1,v;x<=c;++x)
				{
					if(!(v=f[i][j][k][x]))continue;
					ans+=LL(m-k)*v;ans%=mod;
					for(int y=1,t;i+y<=n;++y)
						if((t=x*C[j+y-1][j-1])<=c)add(f[i+y][y][k+1][t],v);
				}
	cout<<ans%mod<<endl;
	return 0;
}
