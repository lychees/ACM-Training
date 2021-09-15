#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
#define maxm 1000010
using namespace std;
int n,a[maxn];
int tot,ans[maxm][2];
void read()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
}
int find(int &n1,int &n2,int &n3)
{
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(a[i])
		{
			++cnt;
			if(cnt==1)
				n1=i;
			else if(cnt==2)
				n2=i;
			else if(cnt==3)
				n3=i;
		}
	return cnt;
}
void move(int i,int j)
{
	a[j]-=a[i],a[i]<<=1;
	++tot,ans[tot][0]=i,ans[tot][1]=j;
}
void work()
{
	int id1,id2,id3;
	while(find(id1,id2,id3)>=3)
		while(1)
		{
			if(a[id1]>a[id2])
				swap(id1,id2);
			if(a[id1]>a[id3])
				swap(id1,id3);
			if(a[id2]>a[id3])
				swap(id2,id3);
			if(!a[id1])
				break;
			for(int i=a[id2]/a[id1];i;i>>=1)
				move(id1,i&1?id2:id3);
		}
	if(find(id1,id2,id3)<=1)
		tot=-1;
}
void print()
{
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d %d\n",ans[i][0],ans[i][1]);
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	work();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
