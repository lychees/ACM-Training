#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
typedef long long LL;
string str;
int n,m,x,y;
int use[maxn][4];
int movex[]={-1,-1,1,1};
int movey[]={-1,1,-1,1};
int Judge(int x,int y)
{
	int ans;
	if(x==1)
		ans=use[y][0]++;
	if(x==n)
		ans=use[y][1]++;
	if(y==1)
		ans=use[x][2]++;
	if(y==m)
		ans=use[x][3]++;
	return ans;
}
LL work()
{
	LL ans=1;
	int cnt=0,dir=(str[0]=='D')*2+(str[1]=='R');
	for(int i=1;i<=n;++i)
		cnt+=(((i+m)&1)==((x+y)&1))+(((i+1)&1)==((x+y)&1));
	for(int i=2;i<m;++i)
		cnt+=(((i+n)&1)==((x+y)&1))+(((i+1)&1)==((x+y)&1));
	cnt-=Judge(x,y)==0;
	while(1)
	{
		int d1=dir>>1,d2=dir&1,newx,newy;
		if(d1==0&&d2==0)
		{
			newx=1,newy=y-x+1;
			if(newy<1)
				newx+=1-newy,newy=1;
		}
		if(d1==0&&d2==1)
		{
			newx=1,newy=x+y-1;
			if(newy>m)
				newx+=newy-m,newy=m;
		}
		if(d1==1&&d2==0)
		{
			newx=n,newy=x+y-n;
			if(newy<1)
				newx-=1-newy,newy=1;
		}
		if(d1==1&&d2==1)
		{
			newx=n,newy=y-x+n;
			if(newy>m)
				newx-=newy-m,newy=m;
		}
		ans+=abs(newx-x),x=newx,y=newy;
		int vec=0;
		if(x+movex[dir]<1||x+movex[dir]>n)
			vec^=2;
		if(y+movey[dir]<1||y+movey[dir]>m)
			vec^=1;
		dir^=vec;
		int c=Judge(x,y);
		cnt-=c==0;
		if(cnt==0)
			break;
		if(c==4)
			return -1;
	}
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m>>x>>y>>str;
	cout<<work()<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
