#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 100010
using namespace std;
typedef long long LL;
vector<int> p1[maxn*2],p2[maxn*2];
vector< pair<int,int> > A[maxn*2],B[maxn*2];
int n,m,nb;
int movex[]={-1,-1,1,1};
int movey[]={1,-1,1,-1};
bool count(int x,int y)
{
	return *lower_bound(p1[x+y].begin(),p1[x+y].end(),x)==x;
}
int ID(char *a)
{
	if(a[0]=='N'&&a[1]=='E')
		return 0;
	if(a[0]=='N'&&a[1]=='W')
		return 1;
	if(a[0]=='S'&&a[1]=='E')
		return 2;
	// a[0]=='S'&&a[1]=='W'
	return 3;
}
void read()
{
	scanf("%d %d %d",&n,&m,&nb);
	for(int i=0;i<=n+1;++i)
	{
		p1[i+0].push_back(i);
		p1[i+m+1].push_back(i);
		p2[i-0+m+1].push_back(i);
		p2[i-(m+1)+m+1].push_back(i);
	}
	for(int i=1;i<=m;++i)
	{
		p1[0+i].push_back(0);
		p1[n+1+i].push_back(n+1);
		p2[0-i+m+1].push_back(0);
		p2[n+1-i+m+1].push_back(n+1);
	}
	for(int i=1,x,y;i<=nb;++i)
	{
		scanf("%d %d",&x,&y);
		p1[x+y].push_back(x),p2[x-y+m+1].push_back(x);
	}
	for(int i=0;i<=n+m+2;++i)
		sort(p1[i].begin(),p1[i].end()),sort(p2[i].begin(),p2[i].end());
}
void Run(int x,int y,int d)
{
	int sx=x,sy=y,cur=0;
	while(1)
	{
		vector<int> &v=d==1||d==2?p2[x-y+m+1]:p1[x+y];
		vector<int>::iterator it=upper_bound(v.begin(),v.end(),x);
		if(d<=1)
			--it;
		int px=*it,py=d==1||d==2?px-(x-y):x+y-px;
		int px1=px,py1=py-movey[d],px2=px-movex[d],py2=py;
		bool c1=count(px1,py1),c2=count(px2,py2);
		//for sample example:
		//c1: left is black
		//c2: up is black
		vector< pair<int,int> > &v1=d==1||d==2?B[x-y+m+1]:A[x+y];
		int lx=x,ly=y,rx=px,ry=py;
		if(c1&&c2)
			v1.push_back(make_pair(px2,x)),x=px2,y=py1,d=3-d;
		else if(c1&&!c2)
			v1.push_back(make_pair(px2,x)),x=px2,y=py2,d^=2;
		else if(!c1&&c2)
			v1.push_back(make_pair(px2,x)),x=px1,y=py1,d^=1;
		else
			v1.push_back(make_pair(px2,x)),x=px2,y=py1,d=3-d;
		if(lx>rx)
			swap(lx,rx),swap(ly,ry);
		if(lx-ly==rx-ry&&lx-ly==sx-sy&&lx<=x&&x<=rx)
			++cur;
		if(lx+ly==rx+ry&&lx+ly==sx+sy&&lx<=x&&x<=rx)
			++cur;
		if(cur>4)
			break;
	}
}
int calc(vector< pair<int,int> > &v)
{
	each(x,v)
		if(x->first>x->second)
			swap(x->first,x->second);
	sort(v.begin(),v.end());
	int R=-1,L=0,ans=0;
	each(x,v)
	{
		if(x->first>R)
			ans+=R-L+1,L=x->first,R=x->second;
		else
			R=max(R,x->second);
	}
	return ans+R-L+1;
}
void work()
{
	char str[10];
	int x,y;
	scanf("%d %d %s",&x,&y,str);
	Run(x,y,ID(str));
	LL ans=0;
	for(int i=0;i<=n+m+2;++i)
		ans+=calc(A[i])+calc(B[i]);
	cout<<ans<<endl;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	work();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
