#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100004,M=400004,oo=2100000000;
int n,m,D[N],L[N];
int c[M],st[M],ql,qr,qx,qv;
int q(int o,int l,int r)
{
	if (c[o]>=qv) return 0;
	if (l==r) return 1;
	int m=(l+r)/2;
	if (qv<=c[o*2+1]) return q(o*2,l,m);
	return q(o*2+1,m+1,r)+st[o]-st[o*2+1];
}
void build(int o,int l,int r)
{
	if (l==r) {c[o]=L[l-1]+D[l]; st[o]=1; return;}
	int m=(l+r)/2;
	build(o*2,l,m); build(o*2+1,m+1,r);
	c[o]=min(c[o*2],c[o*2+1]);
	qv=c[o*2+1]; st[o]=st[o*2+1]+q(o*2,l,m);
}
void update(int o,int l,int r)
{
	if (l==r) {c[o]+=qv; return;}
	int m=(l+r)/2;
	if (qx<=m) update(o*2,l,m); else update(o*2+1,m+1,r);
	c[o]=min(c[o*2],c[o*2+1]);
	qv=c[o*2+1]; st[o]=st[o*2+1]+q(o*2,l,m);
}
int qmin(int o,int l,int r)
{
	if ((ql<=l)&&(r<=qr)) return c[o];
	int m=(l+r)/2,ret=oo;
	if (ql<=m) ret=min(ret,qmin(o*2,l,m));
	if (m<qr) ret=min(ret,qmin(o*2+1,m+1,r));
	return ret;
}
int qstep(int o,int l,int r)
{
	if ((ql<=l)&&(r<=qr))
	{
		int ret=q(o,l,r);
		if (c[o]<qv) qv=c[o];
		return ret;
	}
	int m=(l+r)/2,ret=0;
	if (m<qr) ret+=qstep(o*2+1,m+1,r);
	if (ql<=m) ret+=qstep(o*2,l,m);
	return ret;
}
int main()
{
	freopen("god.in","r",stdin);
	freopen("god.out","w",stdout);
	int i; scanf("%d%d",&n,&m); n++;
	for (i=1;i<n;i++) scanf("%d",&D[i]);
	D[n]=0; for (i=n-1;i;i--) D[i]+=D[i+1];
	for (i=0;i<n;i++) scanf("%d",&L[i]);
	build(1,1,n);
	for (i=1;i<=m;i++)
	{
		int type,a,b; scanf("%d%d%d",&type,&a,&b);
		if (!type)
		{
			qx=a+1; qv=b-L[a]; update(1,1,n);
			L[a]=b;
		}
		else if (type==1)
		{
			int k; scanf("%d",&k);
			ql=b-k+1; qr=b+1;
			printf("%d\n",qmin(1,1,n)-D[b+1]);
		}
		else if (type==2)
		{
			int x0,l=a-1,r=b;
			scanf("%d",&x0);
			while (l+1<r)
			{
				int m=(l+r)/2;
				ql=m+1; qr=b+1;
				if (qmin(1,1,n)>=x0+D[m]) r=m; else l=m;
			}
			ql=r+1; qr=b+1; int ret=min(qmin(1,1,n),x0+D[r]);
			if (r<b) ql=r+2,qr=b+1,ret=max(ret,min(qmin(1,1,n),x0+D[r+1]));
			if (r>a) ql=r,qr=b+1,ret=max(ret,min(qmin(1,1,n),x0+D[r-1]));
			printf("%d\n",ret-D[b+1]);
		}
		else
		{
			ql=a; qr=b; qv=L[b]+D[b+1];
			printf("%d\n",qstep(1,1,n)+(L[b-1]+D[b]>=L[b]+D[b+1]));
		}
	}
	fclose(stdin); fclose(stdout);
	return 0;
}
