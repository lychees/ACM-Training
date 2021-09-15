#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<vector>
#define each(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define maxn 400010
#define P 101
using namespace std;
typedef unsigned long long ULL;
ULL val1[maxn],val2[maxn],Power[maxn*2],sum[maxn*2];
vector<int> p1[maxn],p2[maxn];
int n,m,s[10][10],nC1,nC2,go[maxn];
bool cmp1(int i,int j)
{
	return val1[i]<val1[j];
}
bool cmp2(int i,int j)
{
	return val2[i]<val2[j];
}
void Fail()
{
	printf("No solution\n");
	exit(0);
}
void make(int a,int b)
{
	go[a]=b,go[b]=a;
}
int ID1(int x,int y)
{
	if(x<=2)
		return (x-1)*n+y;
	return 2*n+(x-3)*m+y;
}
pair<int,int> ID2(int p)
{
	if(p<=2*n)
		return make_pair((p-1+n)/n,(p-1)%n+1);
	return make_pair(2+(p-2*n-1+m)/m,(p-2*n-1)%m+1);
}
int trans(char p)
{
	if(p=='L')
		return 1;
	if(p=='R')
		return 2;
	if(p=='T')
		return 3;
	return 4;
}
void read()
{
	scanf("%d %d",&n,&m);
	char c1,c2;
	int a,b;
	for(int i=1;i<=n+m;++i)
	{
		for(c1=getchar();!isalpha(c1);c1=getchar());
		for(c2=getchar();!isalpha(c2);c2=getchar());
		scanf("%d",&a);
		scanf("%d",&b);
		int ida=trans(c1),idb=trans(c2);
		make(ID1(ida,a),ID1(idb,b));
		make(ID1(idb,b),ID1(ida,a));
		if(ida>idb)
			swap(ida,idb);
		++s[ida][idb];
	}
}
ULL gethash(int l,int r)
{
	return sum[r]-sum[l-1]*Power[r-l+1];
}
bool cmp(int l1,int l2,int n,int *a)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		gethash(l1,l1+mid-1)==gethash(l2,l2+mid-1)?l=mid+1:r=mid;
	}
	return a[l1+l-1]<a[l2+l-1];
}
int getmin(int *a,int n)
{
	for(int i=1;i<=n*2;++i)
		sum[i]=sum[i-1]*P+a[i];
	int ans=1;
	for(int i=2;i<=n;++i)
		if(gethash(ans,ans+n-1)!=gethash(i,i+n-1)&&cmp(i,ans,n,a))
			ans=i;
	return ans;
}
bool cmp(int *a,int *b,int n)
{
	for(int i=1;i<=n;++i)
		if(a[i]!=b[i])
			return a[i]<b[i];
	return true;
}
void GetHash(ULL *v,int &tot,vector<int> *p)
{
	static bool use[maxn];
	static int a[maxn*2],b[maxn*2],ta[maxn*2],tb[maxn*2];
	memset(use,false,sizeof(use));
	for(int i=1;i<=n+n+m+m;++i)
		if(!use[i])
		{
			int j=i,k,t=0;
			do
			{
				use[j]=true;
				a[++t]=ID2(j).first,b[t]=j;
				k=go[j],use[k]=true;
				pair<int,int> vk=ID2(k);
				a[++t]=vk.first,b[t]=k;
				vk.first+=vk.first&1?1:-1;
				j=ID1(vk.first,vk.second);
			}while(j!=i);
			for(int j=1;j<=t;++j)
				ta[j]=a[t-j+1],tb[j]=b[t-j+1];
			for(int j=t+1;j<=t+t;++j)
				a[j]=a[j-t],b[j]=b[j-t],ta[j]=ta[j-t],tb[j]=tb[j-t];
			int id1=getmin(a,t),id2=getmin(ta,t);
			if(cmp(a+id1-1,ta+id2-1,t))
			{
				++tot;
				for(int j=id1;j<id1+t;++j)
					v[tot]=v[tot]*P+a[j],p[tot].push_back(b[j]);
			}
			else
			{
				++tot;
				for(int j=id2;j<id2+t;++j)
					v[tot]=v[tot]*P+ta[j],p[tot].push_back(tb[j]);
			}
		}
}
void print()
{
	if(s[1][2]&&s[3][4])
		Fail();
	if(s[1][3]!=s[2][4])
		Fail();
	if(s[1][4]!=s[2][3])
		Fail();
	GetHash(val1,nC1,p1);
	for(int i=1;i<=s[1][3];++i)
		make(ID1(1,i),ID1(3,i)),make(ID1(3,i),ID1(1,i));
	for(int i=1;i<=s[2][3];++i)
		make(ID1(2,i),ID1(3,m-i+1)),make(ID1(3,m-i+1),ID1(2,i));
	for(int i=1;i<=s[1][4];++i)
		make(ID1(1,n-i+1),ID1(4,i)),make(ID1(4,i),ID1(1,n-i+1));
	for(int i=1;i<=s[2][4];++i)
		make(ID1(2,n-i+1),ID1(4,m-i+1)),make(ID1(4,m-i+1),ID1(2,n-i+1));
	for(int i=1;i<=s[1][2];++i)
		make(ID1(1,s[1][3]+i),ID1(2,s[2][3]+i)),make(ID1(2,s[2][3]+i),ID1(1,s[1][3]+i));
	for(int i=1;i<=s[3][4];++i)
		make(ID1(3,s[1][3]+i),ID1(4,s[1][4]+i)),make(ID1(4,s[1][4]+i),ID1(3,s[1][3]+i));
	GetHash(val2,nC2,p2);
	if(nC1!=nC2)
		Fail();
	static int id1[maxn],id2[maxn],ans1[maxn],ans2[maxn];
	for(int i=1;i<=nC1;++i)
		id1[i]=i,id2[i]=i;
	sort(id1+1,id1+nC1+1,cmp1),sort(id2+1,id2+nC2+1,cmp2);
	for(int i=1;i<=nC1;++i)
	{
		if(val1[id1[i]]!=val2[id2[i]])
			Fail();
		for(int j=0;j<(int)p1[id1[i]].size();++j)
		{
			pair<int,int> t=ID2(p2[id2[i]][j]);
			if(t.first==1)
				ans1[t.second]=ID2(p1[id1[i]][j]).second;
			if(t.first==3)
				ans2[t.second]=ID2(p1[id1[i]][j]).second;
		}
	}
	for(int i=1;i<=n;++i)
		printf("%d%c",ans1[i],i<n?' ':'\n');
	for(int i=1;i<=m;++i)
		printf("%d%c",ans2[i],i<m?' ':'\n');
}
void Prepare()
{
	Power[0]=1;
	for(int i=1;i<=n+n+m+m;++i)
		Power[i]=Power[i-1]*P;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	Prepare();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
