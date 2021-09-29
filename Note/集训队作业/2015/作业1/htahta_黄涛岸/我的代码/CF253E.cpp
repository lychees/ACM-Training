#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define mp make_pair
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
LL get()
{
	LL f=0,v=0;char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else v=ch-'0';
	while(isdigit(ch=getchar()))v=v*10+ch-'0';
	if(f)return -v;else return v;
}
const int maxn=50033;
struct data
{
	int t,s,p;
}a[maxn];
pii b[maxn],c[maxn];
priority_queue<pii> Q;
int n,p,s[maxn];
LL T,t[maxn],v[maxn];
void work()
{
	LL tot=0;
	for(int i=1;i<=n;i++)
	{
		Q.push(mp(a[b[i].y].p,b[i].y));
		s[b[i].y]=a[b[i].y].s;tot=b[i].x;
		while(!Q.empty()&&(i==n||b[i+1].x-tot>0))
		{
			int c=Q.top().y,d=s[c];
			if(i<n)d=min(d,int(b[i+1].x-tot));
			v[c]+=max(0ll,min(tot+d,T)-max(LL(a[p].t),tot));
			tot+=d;s[c]-=d;
			if(!s[c])t[c]=tot,Q.pop();
		}
	}
}
int main()
{
	freopen("tmp.in","r",stdin);
	freopen("tmp.out","w",stdout);
	n=get();
	for(int i=1;i<=n;i++)
	{
		b[i]=mp(a[i].t=get(),i),a[i].s=get(),c[i]=mp(a[i].p=get(),i);
		if(a[i].p==-1)p=i;
	}
	T=get();
	sort(b+1,b+1+n);
	sort(c+1,c+1+n);
	work();
	LL tp=0;int k=1;
	while(tp<a[p].s)tp+=v[c[k].y],k++;
	if(c[k-1].x==-1)tp=1;else tp=c[k-1].x+1;
	while(k<=n&&c[k].x==tp)tp++,k++;
	a[p].p=tp;
	work();
	printf("%d\n",a[p].p);
	for(int i=1;i<=n;i++)printf("%I64d%c",t[i],i==n?'\n':' ');
	return 0;
}

