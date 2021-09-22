#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define N 2010
int n,a[N],b[N][4],L[N],p[N],pL,ul[N],ur[N],uL,opl[N],opr[N],op[N];
int he[N],ne[N*N],ad[N*N],t;
int st[N],sn,c[N],mk;bool v[N];
int px[N*N],py[N*N],eL,d[N],q[N],le,ri;bool w[N];vector<int> C[N];
void addE(int x,int y)
{
	++t,ne[t]=he[x],ad[t]=y,he[x]=t;
}
bool ints(int l0,int r0,int l1,int r1)
{
	return l0<l1&&r1<r0||l1<l0&&r0<r1;
}
bool ints(int i,int j)
{
	bool Fi=0,Fj=0;
	if(op[i]!=-1)Fi=1;
	if(op[j]!=-1)Fj=1;
	if(ints(ul[i],ur[i],ul[j],ur[j]))return 1;
	if(Fi&&ints(opl[i],opr[i],ul[j],ur[j]))return 1;
	if(Fj&&ints(ul[i],ur[i],opl[j],opr[j]))return 1;
	if(Fi&&Fj&&ints(opl[i],opr[i],opl[j],opr[j]))return 1;
	return 0;
}
void ff(int x)
{
	v[x]=1;
	for(int p=he[x];p;p=ne[p])
		if(!v[ad[p]])ff(ad[p]);
	st[sn++]=x;
}
void gg(int x)
{
	v[x]=0;c[x]=mk;
	for(int p=he[x];p;p=ne[p])
		if(v[ad[p]])gg(ad[p]);
}
void hh(int x)
{
	v[x]=1;
	for(int p=he[x];p;p=ne[p])
		if(!v[ad[p]])hh(ad[p]);
}
int main()
{
	freopen("1011.in","r",stdin);
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)scanf("%d",a+i);
		pL=0;for(int i=0;i<n;i++)p[pL++]=a[i];
		sort(p,p+pL),pL=unique(p,p+pL)-p;
		for(int i=0;i<n;i++)a[i]=lower_bound(p,p+pL,a[i])-p;
		memset(L,0,sizeof L);
		for(int i=0;i<n;i++)b[a[i]][L[a[i]]++]=i;
		uL=0;memset(op,-1,sizeof op);
		for(int i=0;i<pL;i++)
		{
			ul[uL]=b[i][0],ur[uL]=b[i][1];uL++;
			if(L[i]==4)
			{
				op[uL-1]=uL,op[uL]=uL-1;
				opl[uL-1]=b[i][2],opr[uL-1]=b[i][3];
				opl[uL]=b[i][1],opr[uL]=b[i][3];
				ul[uL]=b[i][0],ur[uL]=b[i][2];uL++;
			}
		}
		t=0;memset(he,0,sizeof he);eL=0;
		for(int i=0;i<uL;i++)
			for(int j=i+1;j<uL;j++)
				if(op[i]!=j&&ints(i,j))
				{
					if(op[j]!=-1)addE(i,op[j]),px[eL]=i,py[eL]=op[j],eL++;
					if(op[i]!=-1)addE(j,op[i]),px[eL]=j,py[eL]=op[i],eL++;
				}
		memset(v,0,sizeof v);sn=0;mk=0;
		for(int i=0;i<uL;i++)if(!v[i])ff(i);
		t=0,memset(he,0,sizeof he);
		for(int i=0;i<eL;i++)addE(py[i],px[i]);
		for(int i=sn-1;i>=0;i--)if(v[st[i]])gg(st[i]),mk++;
		t=0,memset(he,0,sizeof he);memset(d,0,sizeof d);
		for(int i=0;i<eL;i++)
			if(c[px[i]]!=c[py[i]])addE(c[py[i]],c[px[i]]),d[c[px[i]]]++;
		for(int i=0;i<mk;i++)C[i].clear();
		for(int i=0;i<uL;i++)C[c[i]].push_back(i);
		le=0,ri=0;
		for(int i=0;i<mk;i++)if(d[i]==0)q[ri++]=i;
		memset(v,0,sizeof v);
		memset(w,0,sizeof w);
		while(le<ri)
		{
			int x=q[le++];
			for(int p=he[x];p;p=ne[p])
			{
				d[ad[p]]--;
				if(!d[ad[p]])q[ri++]=ad[p];
			}
			if(!v[x])
			{
				w[x]=1;
				for(vector<int>::iterator i=C[x].begin();i!=C[x].end();i++)
					if(op[*i]!=-1)if(!v[c[op[*i]]])hh(c[op[*i]]);
			}
		}
		memset(v,0,sizeof v);
		for(int i=0;i<uL;i++)if(w[c[i]])
		{
			v[ur[i]]=1;
			if(op[i]!=-1)v[opr[i]]=1;
		}
		for(int i=0;i<n;i++)printf("%d",v[i]);puts("");
	}
	return 0;
}