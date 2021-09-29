#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=10004,mod=1000000007;
int f[maxn][9],n,x,y,ans=0;
char a[maxn][3],b[maxn][3];
inline bool ok(int x,int y){return 0<x&&x<=n&&b[x][y]!='X';}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	cin>>n;
	for(int j=0;j<3;j++)
		for(int i=1;i<=n;i++)
		{
			scanf(" %c",&a[i][j]);
			if(a[i][j]=='O')x=i,y=j;
		}
	for(int S=1,c,v;S<8;S++)
	{
		v=-1,memcpy(b,a,sizeof(b));
		if(S&1)
		{
			if(y==1||!ok(x,0)||!ok(x,1)||!ok(x,2))continue;
			b[x][0]=b[x][1]=b[x][2]='X';v=-v;
		}
		if(S&2)
		{
			if(!ok(x-1,y)||!ok(x-2,y))continue;
			b[x-1][y]=b[x-2][y]='X';v=-v;
		}
		if(S&4)
		{
			if(!ok(x+1,y)||!ok(x+2,y))continue;
			b[x+1][y]=b[x+2][y]='X';v=-v;
		}
		b[x][y]='X',f[0][7]=1;
		for(int i=1,j;i<=n;i++)
		{
			for(j=c=0;j<3;j++)c+=(1<<j)*(b[i][j]=='X');
			for(j=0;j<8;j++)
			{
				f[i][j]=0;
				if((j&c)!=c)continue;
				f[i][j]=f[i-1][j^c^7];
				if(((j^c)&3)==3)f[i][j]+=f[i-1][j^c^3^7],f[i][j]>=mod?f[i][j]-=mod:0;
				if(((j^c)&6)==6)f[i][j]+=f[i-1][j^c^6^7],f[i][j]>=mod?f[i][j]-=mod:0;
			}
		}
		(ans+=v*f[n][7])%=mod;
	}
	cout<<(ans+mod)%mod<<endl;
	return 0;
}
