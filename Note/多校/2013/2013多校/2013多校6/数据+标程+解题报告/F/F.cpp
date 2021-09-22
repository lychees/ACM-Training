#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 1010
#define M_PI		3.14159265358979323846
struct P
{
	int x,y;
	P(){}
	P(int _x,int _y):x(_x),y(_y){}
	void get(){scanf("%d%d",&x,&y);}
	P operator + (const P&a) const {return P(x+a.x,y+a.y);}
	P operator - (const P&a) const {return P(x-a.x,y-a.y);}
}a[N];
int n,ne[N*N],p[N],s[N*N];double t[N];
bool cmp(int x,int y){return t[x]<t[y];}
int get(int x,int y)
{
	if(y<x)return x*(n-1)+y;
	return x*(n-1)+y-1;
}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)a[i].get();
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
				if(j<i)p[j]=j;else if(j>i)p[j-1]=j;
			for(int j=0;j<n;j++)if(j!=i)
			{
				t[j]=atan2((double)(a[j].y-a[i].y),(double)(a[j].x-a[i].x));
				if(t[j]<0)t[j]+=M_PI;
			}
			sort(p,p+n-1,cmp);
			for(int j=0;j<n-1;j++)
				ne[get(p[j],i)]=get(i,p[(j+1)%(n-1)]);
		}
		memset(s,0,(sizeof(int))*n*(n-1));
		ll S=0;
		for(int i=0;i<n*(n-1);i++)if(!s[i])
		{
			int t=1;
			for(int j=ne[i];j!=i;j=ne[j])t++;
			s[i]=t;
			for(int j=ne[i];j!=i;j=ne[j])s[j]=t;
			S+=(ll)t*t;
		}
		int T=n*(n-1),z=gcd(S%T,T);
		S/=z,T/=z;
		if(T==1)printf("%d\n",S);else printf("%I64d/%d\n",S,T);
	}
	return 0;
}