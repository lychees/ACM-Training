#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=200005,M=2000005;
int x[N],y[N],a[N],b[N],p[N],c[M],d[M],n,m,z,Case;
void read(int &x)
{
	#define CH getchar()
	char ch; bool y=0; x=0; for (ch=CH;ch<'0' || ch>'9';ch=CH) if (ch=='-') y=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH); if (y) x=-x;
}
void add(int *c,int x,int v){if (!x) z+=v; else for (;x<=m;x+=x&-x) c[x]+=v;}
int get(int *c){int x=0; for (int i=20;i>=0;--i) if (x+(1<<i)<=m && !c[x+(1<<i)]) x+=1<<i; return x+1;}
bool cmp(const int &i,const int &j){return a[i]<a[j];}
bool check(int r)
{
	int l=0,w,flag=0;
	rep(i,n) if (x[i]>=-2*r && x[i]<=2*r && y[i]>=-2*r && y[i]<=2*r)
		b[l]=y[i],a[l++]=x[i]-r,b[l]=y[i],a[l++]=x[i]+r+1;
	w=l,a[l++]=-M*2,a[l++]=M*2;
	rep(i,l) p[i]=i; sort(p,p+l,cmp); m=r*2;
	rep(k,l){
		int i=p[k],Y=b[i];
		if (!flag && k && a[i]!=a[p[k-1]]) if (a[p[k-1]]<=r && a[i]>-r)
			if (!z && get(c)+get(d)>m+1) flag=1;
		if (i<w) if (Y>=0) add(c,Y,i&1?-1:1); else add(d,-Y,i&1?-1:1);
	}
	return flag;
}
int main()
{
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	while (read(n),n>=0){
		int l=0,r=0,mid;
		rep(i,n) read(x[i]),read(y[i]),r=max(r,max(abs(x[i]),abs(y[i])));
		printf("Case %d: ",++Case);
		if (check(r)){puts("never"); continue;}
		while (l<r) mid=l+r+1>>1,check(mid)?l=mid:r=mid-1; printf("%d\n",l+1);
	}
	return 0;
}
