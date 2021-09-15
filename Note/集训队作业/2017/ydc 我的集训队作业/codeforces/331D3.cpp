#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#define INF 1000000000000001LL
#define maxn 100010
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
typedef long long LL;
template<class T>
void Read(T &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct Point
{
	int x,y;
	Point() {}
	Point(int x,int y): x(x),y(y) {}
	friend Point operator - (Point a,Point b)
	{
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator + (Point a,Point b)
	{
		return Point(a.x+b.x,a.y+b.y);
	}
	friend Point operator * (Point a,int p)
	{
		return Point(a.x*p,a.y*p);
	}
	friend Point operator / (Point a,int p)
	{
		return Point(a.x/p,a.y/p);
	}
	friend bool operator <= (Point a,Point b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<=b.y);
	}
	friend bool operator < (Point a,Point b)
	{
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
};
typedef Point Vector;
int Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
int dist(Point a,Point b)
{
	return abs(a.x-b.x)+abs(a.y-b.y);
}
Point getInter(Point a,Vector v1,Point b,Vector v2)
{
	Vector v3=a-b;
	int t=Cross(v2,v3)/Cross(v1,v2);
	return a+v1*t;
}
struct Seg
{
	int x0,y0,x1,y1;
}L[maxn];
vector< pair<pair<int,int>,int> > row[maxn],col[maxn];
vector<int> toL[maxn],toR[maxn],toQ[maxn];
set< pair<int,int> >T;
int n,m;
struct msgnode
{
	int to;
	Point p;
	LL dis;
}F[80][maxn];
Point p[maxn][2];
Vector vec[maxn];
void read()
{
	Read(n),Read(m);
	for(int i=0;i<=m;++i)
	{
		row[i].push_back(make_pair(make_pair(-1<<30,-1),0));
		row[i].push_back(make_pair(make_pair(1<<30,1<<30|1),0));
		col[i].push_back(make_pair(make_pair(-1<<30,-1),0));
		col[i].push_back(make_pair(make_pair(1<<30,1<<30|1),0));
	}
	for(int i=1;i<=n;++i)
	{
		Read(L[i].x0),Read(L[i].y0),Read(L[i].x1),Read(L[i].y1);
		p[i][0]=Point(L[i].x0,L[i].y0),p[i][1]=Point(L[i].x1,L[i].y1);
		vec[i]=(p[i][1]-p[i][0])/dist(p[i][0],p[i][1]);
		if(L[i].y0==L[i].y1)
		{
			pair<pair<int,int>,int> v=make_pair(make_pair(L[i].x0,L[i].x1),i);
			if(v.first.first>v.first.second)
				swap(v.first.first,v.first.second);
			row[L[i].y0].push_back(v);
		}
		else
		{
			pair<pair<int,int>,int> v=make_pair(make_pair(L[i].y0,L[i].y1),i);
			if(v.first.first>v.first.second)
				swap(v.first.first,v.first.second);
			col[L[i].x0].push_back(v);
		}
	}
	for(int i=0;i<=m;++i)
		sort(row[i].begin(),row[i].end()),sort(col[i].begin(),col[i].end());
}
void Prepare()
{
	static int to[maxn];
	T.insert(make_pair(-1<<30,0));
	T.insert(make_pair(1<<30,0));
	for(int i=1;i<=n;++i)
	{
		if(L[i].y0!=L[i].y1)
			toQ[L[i].x0].push_back(i);
		else
		{
			toL[min(L[i].x0,L[i].x1)].push_back(i);
			toR[max(L[i].x0,L[i].x1)].push_back(i);
		}
	}
	for(int i=0;i<=m;++i)
	{
		each(x,toL[i])
			T.insert(make_pair(L[*x].y0,*x));
		each(x,toQ[i])
		{
			set< pair<int,int> >::iterator it1=T.upper_bound(make_pair(L[*x].y1,0));
			if(L[*x].y0>L[*x].y1)
				--it1;
			vector< pair<pair<int,int>,int> >::iterator it2;
			it2=upper_bound(col[L[*x].x0].begin(),col[L[*x].x1].end(),make_pair(make_pair(L[*x].y1,1<<30),0));
			if(L[*x].y0>L[*x].y1)
				it2-=2;
			if(L[*x].y0<L[*x].y1)
				to[*x]=it1->first<it2->first.first?it1->second:it2->second;
			else
				to[*x]=it1->first>it2->first.first?it1->second:it2->second;
		}
		each(x,toR[i])
			T.erase(make_pair(L[*x].y0,*x));
		toL[i].clear(),toR[i].clear(),toQ[i].clear();
	}
	for(int i=1;i<=n;++i)
	{
		if(L[i].x0!=L[i].x1)
			toQ[L[i].y0].push_back(i);
		else
		{
			toL[min(L[i].y0,L[i].y1)].push_back(i);
			toR[max(L[i].y0,L[i].y1)].push_back(i);
		}
	}
	for(int i=0;i<=m;++i)
	{
		each(x,toL[i])
			T.insert(make_pair(L[*x].x0,*x));
		each(x,toQ[i])
		{
			set< pair<int,int> >::iterator it1=T.upper_bound(make_pair(L[*x].x1,0));
			if(L[*x].x0>L[*x].x1)
				--it1;
			vector< pair<pair<int,int>,int> >::iterator it2;
			it2=upper_bound(row[L[*x].y0].begin(),row[L[*x].y1].end(),make_pair(make_pair(L[*x].x1,1<<30),0));
			if(L[*x].x0>L[*x].x1)
				it2-=2;
			if(L[*x].x0<L[*x].x1)
				to[*x]=it1->first<it2->first.first?it1->second:it2->second;
			else
				to[*x]=it1->first>it2->first.first?it1->second:it2->second;
		}
		each(x,toR[i])
			T.erase(make_pair(L[*x].x0,*x));
		toL[i].clear(),toR[i].clear(),toQ[i].clear();
	}
	for(int i=1;i<=n;++i)
	{
		F[0][i].to=to[i];
		if(to[i])
		{
			if(Cross(vec[i],vec[to[i]]))
			{
				Point inter=getInter(p[i][0],vec[i],p[to[i]][0],vec[to[i]]);
				F[0][i].dis=min(dist(p[i][0],inter),dist(p[i][1],inter));
				F[0][i].p=inter;
			}
			else
			{
				F[0][i].dis=1<<30;
				for(int b=0;b<=1;++b)
					if(F[0][i].dis>dist(p[i][1],p[to[i]][b]))
						F[0][i].dis=dist(p[i][1],p[to[i]][b]),F[0][i].p=p[to[i]][b];
			}
		}
		else
		{
			Point &go=F[0][i].p;
			if(vec[i].x==1)
				go=Point(m,p[i][0].y);
			if(vec[i].x==-1)
				go=Point(0,p[i][0].y);
			if(vec[i].y==1)
				go=Point(p[i][0].x,m);
			if(vec[i].y==-1)
				go=Point(p[i][0].x,0);
			F[0][i].dis=dist(go,p[i][1]);
		}
	}
	for(int i=1;i<=70;++i)
		for(int j=1;j<=n;++j)
		{
			F[i][j].to=F[i-1][F[i-1][j].to].to;
			Point tmp=F[i-1][j].p;
			if(F[i][j].to)
			{
				F[i][j].p=F[i-1][F[i-1][j].to].p;
				int sum=dist(tmp,p[F[i-1][j].to][1]);
				F[i][j].dis=F[i-1][j].dis+sum+F[i-1][F[i-1][j].to].dis;
			}
			else
			{
				F[i][j].p=F[i-1][j].to?F[i-1][F[i-1][j].to].p:F[i-1][j].p;
				if(F[i-1][j].to)
				{
					int sum=dist(tmp,p[F[i-1][j].to][1]);
					F[i][j].dis=F[i-1][j].dis+sum+F[i-1][F[i-1][j].to].dis;
				}
				else
					F[i][j].dis=F[i-1][j].dis;
			}
			F[i][j].dis=min(F[i][j].dis,INF);
		}
}
bool On(vector< pair<pair<int,int>,int> >::iterator &it,vector< pair<pair<int,int>,int> > &c,int y)
{
	it=upper_bound(c.begin(),c.end(),make_pair(make_pair(y,1<<30),1<<30))-1;
	return it->first.first<=y&&it->first.second>=y;
}
Point calc(Point a,int x,LL T,Vector v)
{
	if(!x)
	{
		LL px=a.x+v.x*T,py=a.y+v.y*T;
		px=max(px,0LL),px=min(px,(LL)m);
		py=max(py,0LL),py=min(py,(LL)m);
		return Point((int)px,(int)py);
	}
	Point tmp;
	if(Cross(v,vec[x]))
		tmp=getInter(a,v,p[x][0],vec[x]);
	else if(min(p[x][0],p[x][1])<=a&&a<=max(p[x][0],p[x][1]))
		tmp=a;
	else
		tmp=dist(p[x][0],a)<dist(p[x][1],a)?p[x][0]:p[x][1];
	if(dist(a,tmp)>=T)
		return a+v*T;
	T-=dist(a,tmp),a=tmp;
	if(dist(a,p[x][1])>=T)
		return a+vec[x]*T;
	T-=dist(a,p[x][1]),a=p[x][1];
	for(int i=70;i>=0;--i)
		if(F[i][x].dis<=T)
		{
			a=F[i][x].p,T-=F[i][x].dis;
			int b=F[i][x].to;
			if(b==0)
				return a;
			if(dist(a,p[b][1])>=T)
				return a+vec[b]*T;
			T-=dist(a,p[b][1]),a=p[b][1],x=b;
		}
	return a+vec[x]*T;
}
void Query()
{
	static Point ans[maxn],que[maxn];
	static Vector vec[maxn];
	static LL que_T[maxn];
	int nQ;
	Read(nQ);
	for(int i=1;i<=nQ;++i)
	{
		char c;
		Read(que[i].x),Read(que[i].y);
		for(c=getchar();c<'A'||c>'Z';c=getchar());
		if(c=='U')
			vec[i]=Vector(0,1);
		if(c=='D')
			vec[i]=Vector(0,-1);
		if(c=='L')
			vec[i]=Vector(-1,0);
		if(c=='R')
			vec[i]=Vector(1,0);
		Read(que_T[i]);
	}
	for(int i=1;i<=nQ;++i)
		if(vec[i].x==0)
			toQ[que[i].x].push_back(i);
	for(int i=1;i<=n;++i)
		if(p[i][0].y==p[i][1].y)
		{
			toL[min(p[i][0].x,p[i][1].x)].push_back(i);
			toR[max(p[i][0].x,p[i][1].x)].push_back(i);
		}
	for(int i=0;i<=m;++i)
	{
		each(x,toL[i])
			T.insert(make_pair(L[*x].y0,*x));
		each(x,toQ[i])
		{
			set< pair<int,int> >::iterator it1=T.lower_bound(make_pair(que[*x].y,0));
			if(vec[*x].y==-1&&it1->first!=que[*x].y)
				--it1;
			vector< pair<pair<int,int>,int> >::iterator it2;
			it2=upper_bound(col[que[*x].x].begin(),col[que[*x].x].end(),make_pair(make_pair(que[*x].y,1<<30),0));
			if(vec[*x].y==-1)
				--it2;
			int go;
			if(vec[*x].y==1)
				go=it1->first<it2->first.first?it1->second:it2->second;
			else
				go=it1->first>it2->first.first?it1->second:it2->second;
			if(On(it2,col[que[*x].x],que[*x].y))
				go=it2->second;
			if(On(it2,row[que[*x].y],que[*x].x))
				go=it2->second;
			ans[*x]=calc(que[*x],go,que_T[*x],vec[*x]);
		}
		each(x,toR[i])
			T.erase(make_pair(L[*x].y0,*x));
		toL[i].clear(),toR[i].clear(),toQ[i].clear();
	}
	for(int i=1;i<=nQ;++i)
		if(vec[i].y==0)
			toQ[que[i].y].push_back(i);
	for(int i=1;i<=n;++i)
		if(p[i][0].x==p[i][1].x)
		{
			toL[min(p[i][0].y,p[i][1].y)].push_back(i);
			toR[max(p[i][0].y,p[i][1].y)].push_back(i);
		}
	for(int i=0;i<=m;++i)
	{
		each(x,toL[i])
			T.insert(make_pair(L[*x].x0,*x));
		each(x,toQ[i])
		{
			set< pair<int,int> >::iterator it1=T.lower_bound(make_pair(que[*x].x,0));
			if(vec[*x].x==-1&&it1->first!=que[*x].x)
				--it1;
			vector< pair<pair<int,int>,int> >::iterator it2;
			it2=upper_bound(row[que[*x].y].begin(),row[que[*x].y].end(),make_pair(make_pair(que[*x].x,1<<30),0));
			if(vec[*x].x==-1)
				--it2;
			int go;
			if(vec[*x].x==1)
				go=it1->first<it2->first.first?it1->second:it2->second;
			else
				go=it1->first>it2->first.first?it1->second:it2->second;
			if(On(it2,col[que[*x].x],que[*x].y))
				go=it2->second;
			if(On(it2,row[que[*x].y],que[*x].x))
				go=it2->second;
			ans[*x]=calc(que[*x],go,que_T[*x],vec[*x]);
		}
		each(x,toR[i])
			T.erase(make_pair(L[*x].x0,*x));
	}
	for(int i=1;i<=nQ;++i)
		printf("%d %d\n",(int)ans[i].x,(int)ans[i].y);
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	Prepare();
	Query();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
