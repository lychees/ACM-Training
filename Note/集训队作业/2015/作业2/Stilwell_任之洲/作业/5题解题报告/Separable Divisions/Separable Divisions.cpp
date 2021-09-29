#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct huge{
	#define N_huge 1001
	#define base 100000000
	static char s[N_huge*10];
	typedef long long value;
	value a[N_huge];int len;
	void clear(){len=1;a[len]=0;}
	huge(){clear();}
	huge(value x){*this=x;}
	huge operator =(const huge &b){
		len=b.len;for (int i=1;i<=len;++i)a[i]=b.a[i]; return *this;
	}
	huge operator +(const huge &b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>len)tmp.a[i]+=b.a[i];
			else if (i>b.len)tmp.a[i]+=a[i];
			else tmp.a[i]+=a[i]+b.a[i];
			if (tmp.a[i]>=base){
				tmp.a[i]-=base;++tmp.a[i+1];
			}
		}
		if (tmp.a[L+1])tmp.len=L+1;
			else tmp.len=L;
		return tmp;
	}
	huge operator -(huge b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>b.len)b.a[i]=0;
			tmp.a[i]+=a[i]-b.a[i];
			if (tmp.a[i]<0){
				tmp.a[i]+=base;--tmp.a[i+1];
			}
		}
		while (L>1&&!tmp.a[L])--L;
		tmp.len=L;
		return tmp;
	}
	huge operator *(const huge &b)const{
		int L=len+b.len;huge tmp;
		for (int i=1;i<=L;++i)tmp.a[i]=0;
		for (int i=1;i<=len;++i)
			for (int j=1;j<=b.len;++j){
				tmp.a[i+j-1]+=a[i]*b.a[j];
				if (tmp.a[i+j-1]>=base){
					tmp.a[i+j]+=tmp.a[i+j-1]/base;
					tmp.a[i+j-1]%=base;
				}
			}
		tmp.len=len+b.len;
		while (tmp.len>1&&!tmp.a[tmp.len])--tmp.len;
		return tmp;
	}
	huge operator /(value x){
		value d=0;huge tmp;
		for (int i=len;i;--i){
			d=d*base+a[i];
			tmp.a[i]=d/x;d%=x;
		}
		tmp.len=len;
		while (tmp.len>1&&!tmp.a[tmp.len])--tmp.len;
		return tmp;
	}
	huge &operator +=(const huge &b){*this=*this+b;return *this;}
	huge &operator -=(const huge &b){*this=*this-b;return *this;}
	huge &operator *=(const huge &b){*this=*this*b;return *this;}
	huge &operator ++(){huge T;T=1;*this=*this+T;return *this;}
	huge &operator --(){huge T;T=1;*this=*this-T;return *this;}
	huge operator +(value x){huge T;T=x;return *this+T;}
	huge operator -(value x){huge T;T=x;return *this-T;}
	huge operator *(value x){huge T;T=x;return *this*T;}
	huge operator *=(value x){*this=*this*x;return *this;}
	huge operator +=(value x){*this=*this+x;return *this;}
	huge operator -=(value x){*this=*this-x;return *this;}
	huge operator /=(value x){*this=*this/x;return *this;}
	huge operator =(value x){
		len=0;
		while (x)a[++len]=x%base,x/=base;
		if (!len)a[++len]=0;
		return *this;
	}
	void print(){
		printf("%d",(int)a[len]);
		for (int i=len-1;i;--i){
			for (int j=base/10;j>=10;j/=10){
				if (a[i]<j)printf("0");
					else break;
			}
			printf("%d",(int)a[i]);
		}
		printf("\n");
	}
};char huge::s[N_huge*10];

int n,m,i,j,k;
huge ans,tmp,a[105];

int main()
{
	scanf("%d%d",&n,&m);
	if(n>m)swap(n,m);
	if(n==1)
	{
		printf("%d\n",m-1);
		return 0;
	}
	tmp=1;
	a[0]=1;
	for(i=1;i<=n;++i)a[i]=a[i-1]*(m-1);
	for(i=1;i<n;++i)
	{
		tmp=(n-i)*4;
		ans+=tmp*a[i];
	}
	ans+=a[n];
	ans+=2*n;
	for(i=1;i<=m;++i)a[i]=a[i-1]*(n-1);
	for(i=1;i<m;++i)
	{
		tmp=(m-i)*4;
		ans+=tmp*a[i];
	}
	ans+=a[m];
	ans+=2*m;
	ans*=2;
	
	for(i=0;i<=m;++i)a[i]=1;
	for(i=1;i<n;++i)
	for(j=m;j;--j)
	a[j-1]+=a[j];
	for(i=0;i<=m;++i)ans-=a[i]*2;
	
	for(i=0;i<=n;++i)a[i]=1;
	for(i=1;i<m;++i)
	for(j=n;j;--j)
	a[j-1]+=a[j];
	for(i=0;i<=n;++i)ans-=a[i]*2;
	
	ans/=2;
	
	ans.print();
}

