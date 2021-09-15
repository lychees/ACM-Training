#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 5010
using namespace std;
typedef long long LL;
struct Seg
{
	LL l,r,y;
	Seg() {}
	Seg(LL l,LL r,LL y): l(l),r(r),y(y) {}
}L[maxn];
int nC,tot,tot2;
LL n,m,ey[maxn],ans;
LL inT[maxn],in[maxn],out[maxn];
void read()
{
	cin>>nC>>m>>n;
	for(int i=1;i<=nC;++i)
		cin>>in[i]>>out[i]>>inT[i];
}
void work(LL x,LL y)
{
	if(x<1||x>n||y<0||y>m)
		return ;
	LL l=0,r=m;
	for(int i=1;i<=tot;++i)
		if(L[i].l-L[i].y==x-y&&x-L[i].l>=0&&x-L[i].l<=L[i].r-L[i].l)
			return ;
	for(int i=1;i<=tot;++i)
	{
		LL tx=x,ty=y;
		if(y+x<L[i].y)
		{
			y+=x,x=n;
			LL k=(L[i].y-y)/n;
			y+=k*n;
		}
		if(y-(n-x+1)>L[i].y+L[i].r-L[i].l)
		{
			y-=n-x+1,x=1;
			LL k=(y-(L[i].y+L[i].r-L[i].l))/n;
			y-=k*n;
		}
		LL v;
		v=L[i].l-L[i].y+x+y;
		if(L[i].l*2<=v&&L[i].r*2>=v)
		{
			if(L[i].l-L[i].y==x-y)
			{
				if(y>ty)
					r=min(r,y-1);
				else
					l=max(l,y+1);
			}
			else
			{
				LL px;
				px=x*2<=v?(v-1)/2:v/2+1;
				if(y+x-px<ty)
					l=max(l,y+x-px);
				else if(y+x-px>ty)
					r=min(r,y+x-px);
				else if(x*2<=v)
					l=ty;
				else
					r=ty;
			}
		}
		y+=x,x=n;
		v=L[i].l-L[i].y+x+y;
		if(L[i].l*2<=v&&L[i].r*2>=v)
		{
			if(L[i].l-L[i].y==x-y)
			{
				if(y>ty)
					r=min(r,y-1);
				else
					l=max(l,y+1);
			}
			else
			{
				LL px;
				px=x*2<=v?(v-1)/2:v/2+1;
				if(y+x-px<ty)
					l=max(l,y+x-px);
				else if(y+x-px>ty)
					r=min(r,y+x-px);
				else if(x*2<=v)
					l=ty;
				else
					r=ty;
			}
		}
		y-=n+1,x=1;
		v=L[i].l-L[i].y+x+y;
		if(L[i].l*2<=v&&L[i].r*2>=v)
		{
			if(L[i].l-L[i].y==x-y)
			{
				if(y>ty)
					r=min(r,y-1);
				else
					l=max(l,y+1);
			}
			else
			{
				LL px;
				px=x*2<=v?(v-1)/2:v/2+1;
				if(y+x-px<ty)
					l=max(l,y+x-px);
				else if(y+x-px>ty)
					r=min(r,y+x-px);
				else if(x*2<=v)
					l=ty;
				else
					r=ty;
			}
		}
		x=tx,y=ty;
		if(r-l<=ans)
			return ;
	}
	for(int i=1;i<=tot2;++i)
	{
		LL tx=x,ty=y;
		y+=x-1,x=1;
		if((ey[i]-y)%n==0)
		{
			if(ey[i]>ty)
				r=min(r,ey[i]);
			else
				l=max(l,ey[i]+1);
		}
		x=tx,y=ty;
		if(r-l<=ans)
			return ;
	}
	ans=r-l;
}
LL work()
{
	tot=tot2=0;
	for(int i=1;i<=nC;++i)
	{
		if(in[i]<=out[i])
			L[++tot]=Seg(in[i],out[i],inT[i]);
		else
		{
			L[++tot]=Seg(in[i],n,inT[i]),L[++tot]=Seg(1,out[i],inT[i]+n-in[i]+1);
			++tot2,ey[tot2]=inT[i]+n-in[i];
		}
	}
	ans=0;
	for(int i=1;i<=tot;++i)
		for(int j=-1;j<=1;++j)
			for(int k=-1;k<=1;++k)
			{
				work(L[i].l+j,L[i].y+k);
				work(L[i].r+j,L[i].y+L[i].r-L[i].l+k);
			}
	work(1,0);
	work(n,0);
	work(1,m);
	work(n,m);
	return ans;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		cout<<"Case #"<<(++C)<<": "<<work()<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
