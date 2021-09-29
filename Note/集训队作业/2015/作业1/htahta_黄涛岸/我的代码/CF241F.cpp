#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int x[33],y[33],n,m,k,X,Y,L;
char s[1003],a[103][103];
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int j,i=1;i<=n;i++)
		for(scanf("%s",a[i]+1),j=1;j<=m;j++)
			if(isalpha(a[i][j]))x[a[i][j]-'a']=i,y[a[i][j]-'a']=j,a[i][j]=1;
			else a[i][j]-='0';
	scanf("%d%d%s%d%d",&X,&Y,s+1,&x[26],&y[26]);
	L=strlen(s+1)+1;s[L]=26;
	for(int i=1;i<L;i++)s[i]-='a';
	for(int i=1;i<=L&&k>0;i++)
		while(!(X==x[s[i]]&&Y==y[s[i]]))
		{
			k-=a[X][Y];
			if(k<0)break;
			if(X>x[s[i]])--X;
			if(X<x[s[i]])++X;
			if(Y>y[s[i]])--Y;
			if(Y<y[s[i]])++Y;
		}
	cout<<X<<" "<<Y<<endl;
	return 0;
}
