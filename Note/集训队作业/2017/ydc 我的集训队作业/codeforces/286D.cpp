#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#define maxn 100010
using namespace std;
int x[maxn*2],tot,m,n,l[maxn],r[maxn],T[maxn],q[maxn];
int sum1[maxn],sum2[maxn];
void read()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d %d %d",l+i,r+i,T+i);
		x[++tot]=l[i],x[++tot]=r[i];
	}
	sort(x+1,x+tot+1),tot=unique(x+1,x+tot+1)-x-1;
	for(int i=1;i<=m;++i)
		l[i]=lower_bound(x+1,x+tot+1,l[i])-x,r[i]=lower_bound(x+1,x+tot+1,r[i])-x;
	for(int i=1;i<=n;++i)
		scanf("%d",q+i);
}
bool cmp(int i,int j)
{
	return T[i]<T[j];
}
void Query()
{
	static int id[maxn],col[maxn*2];
	static set<int>::iterator stack[maxn*2];
	memset(col,-1,sizeof(col));
	set<int> Tp;
	for(int i=1;i<=tot+1;++i)
		Tp.insert(i);
	for(int i=1;i<=m;++i)
		id[i]=i;
	sort(id+1,id+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		int top=0,x=id[i];
		for(set<int>::iterator it=Tp.upper_bound(l[x]);*it<=r[x];++it)
			col[*it]=T[x],stack[++top]=it;
		while(top)
			Tp.erase(stack[top--]);
	}
	for(int i=2;i<=tot;++i)
		if(~col[i])
		{
			int l=x[i-1],r=x[i],t=col[i];
			int L=lower_bound(q+1,q+n+1,t-r)-q,R=upper_bound(q+1,q+n+1,t-l)-q-1;
			if(L==1)
				++i,--i;
			sum1[L]+=1,sum1[R+1]-=1,sum2[L]+=r-t,sum2[R+1]-=r-t;
			sum2[R+1]+=r-l;
		}
	for(int i=2;i<=n;++i)
		sum1[i]+=sum1[i-1],sum2[i]+=sum2[i-1];
}
void print()
{
	for(int i=1;i<=n;++i)
		printf("%d\n",sum1[i]*q[i]+sum2[i]);
}
int main()
{
	read();
	Query();
	print();
	return 0;
}
