#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
int get()
{
	int f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=53,maxd=10033;
int Link[maxd],t[maxd],pre[maxd],m,s[maxn],tot;
LL s1,s2,n,p1,p2,A,lim;
void add(int x,int y)
{
	pre[++tot]=Link[x]; Link[x]=tot; t[tot]=y;
	if(x>lim)lim=x;
}
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	int T=get();
	for(int _=1;_<=T;_++)
	{
		n=get(),m=get();
		s1=s2=tot=lim=p1=p2=0;
		memset(s,0,sizeof(s));
		memset(Link,0,sizeof(Link));
		for(int i=1,j;i<=m;i++)
			for(add(1,i),j=get()-1;j;j--)add(get(),i);
		lim=min(lim,n);
		for(int i=1;i<=lim;i++)
		{
			LL delta,cnt=0;
			for(int j=Link[i];j;j=pre[j])++cnt;
			delta=s2*cnt;
			for(int j=Link[i];j;j=pre[j])
			{
				int x=t[j];
				delta+=s2+cnt-1-s[x]-s[x];
				s[x]++;
			}
			s1+=delta;s2+=cnt;
			p1+=s1,p2+=s2;
		}
		LL tp=n*n;
		p2+=s2*(n-lim);
		A=p2/n+p1/tp;
		p2%=n;p1%=tp;
		LL res=0,g;
		for(LL i=n-lim,a=s1%tp,TA=s1/tp;i;i/=2)
		{
			if(i&1)res+=a,A+=TA;
			if(res>=tp)A++,res-=tp;
			a*=2;TA*=2;
			if(a>=tp)TA++,a-=tp;
		}
		p1+=res+p2*n;
		A+=p1/tp,p1%=tp;
		g=gcd(p1,tp);
		cout<<"Case #"<<_<<": "<<A<<"+"<<p1/g<<"/"<<tp/g<<endl;
	}
	return 0;
}
