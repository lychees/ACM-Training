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
const int maxn=1<<21;
const double pi=acos(-1.0);
struct data
{
	double r,i;
	data(){}
	inline data(double _r,double _i){r=_r,i=_i;}
	inline data operator +(const data &b)const{return data(r+b.r,i+b.i);}
	inline data operator -(const data &b)const{return data(r-b.r,i-b.i);}
	inline data operator *(const data &b)const{return data(r*b.r-i*b.i,r*b.i+i*b.r);}
}a[maxn+10],b[maxn+10];
int n,m,lim,ref[maxn],N,c[maxn],Tc=0;
bool f[maxn];
void FFT(const data a[],data b[],int inv)
{
	for(int i=0;i<N;i++)b[i]=a[ref[i]];
	for(int i=1;i<=lim;i++)
	{
		int d=1<<i;
		data w0=data(cos(2*pi/d*inv),sin(2*pi/d*inv)),w,u,v;
		for(int j=0,k;j<N;j+=d)
			for(w=data(1,0),k=j;k<j+d/2;++k)
			{
				u=b[k],v=w*b[k+d/2];
				b[k]=u+v,b[k+d/2]=u-v;
				w=w*w0;
			}
	}
	if(inv==1)return;
	for(int i=0;i<N;i++)b[i].r/=N;
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get(),m=get();
	for(int i=1,x;i<=n;i++)f[x=get()]=1,a[x]=data(1,0);
	for(N=2,lim=1;N<=m+m;N*=2,++lim);
	for(int i=0;i<N;i++)
		for(int j=0;j<lim;j++)ref[i]|=(1<<j)*((i>>(lim-j-1))&1);
	FFT(a,b,1);
	for(int i=0;i<N;i++)b[i]=b[i]*b[i];
	FFT(b,a,-1);
	for(int i=1;i<=m;i++)
	{
		if(!f[i]&&a[i].r>0.5)return puts("NO"),0;
		if(f[i]&&a[i].r<0.5)c[++Tc]=i;
	}
	printf("YES\n%d\n%d",Tc,c[1]);
	for(int i=2;i<=Tc;i++)printf(" %d",c[i]);
	return puts(""),0;
}
