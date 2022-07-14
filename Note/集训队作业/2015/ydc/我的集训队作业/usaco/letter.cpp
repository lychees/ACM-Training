#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int lena,lenb,sum[maxn],Sa[maxn],rank[maxn],height[maxn];
int same1[maxn],same2[maxn],same[maxn],front[maxn],rear[maxn],ans;
char a[maxn],b[maxn];
bool mark[maxn];
void read()
{
	int n,m;
	static char temp[maxn];
	scanf("%d %d",&n,&m);
	while(lena<n)
	{
		scanf("%s",temp);
		strcat(a,temp),lena+=strlen(temp);
	}
	while(lenb<m)
	{
		scanf("%s",temp);
		strcat(b,temp),lenb+=strlen(temp);
	}
	strcat(a,"$"),strcat(a,b),lena=lena+lenb+1;
}
void sort(int a[],int b[],int c[],int n,int m)
{
	memset(sum,0,sizeof(sum));
	for(int i=0;i<n;i++)
		sum[c[a[i]]]++;
	for(int i=1;i<=m;i++)
		sum[i]+=sum[i-1];
	for(int i=n-1;i>=0;i--)
		b[--sum[c[a[i]]]]=a[i];
}
void make_Sa()
{
	int x[maxn],y[maxn];
	for(int i=0;i<lena;i++)
		x[i]=a[i],rank[i]=i;
	sort(rank,Sa,x,lena,256);
	rank[Sa[0]]=1;
	for(int i=1;i<lena;i++)
		rank[Sa[i]]=rank[Sa[i-1]]+(x[Sa[i]]!=x[Sa[i-1]]);
	for(int i=1;i<=lena;i<<=1)
	{
		for(int j=0;j<lena;j++)
			x[j]=rank[j],y[j]=j+i<lena?rank[j+i]:0,Sa[j]=j;
		sort(Sa,rank,y,lena,lena),sort(rank,Sa,x,lena,lena);
		rank[Sa[0]]=1;
		for(int j=1;j<lena;j++)
			rank[Sa[j]]=rank[Sa[j-1]]+(x[Sa[j]]!=x[Sa[j-1]]||y[Sa[j]]!=y[Sa[j-1]]);
		if(rank[Sa[lena-1]]==lena)  break;
	}
}
void make_height()
{
	for(int i=0,j=0;i<lena;i++)
	{
		if(j!=0)  j--;
		while(rank[i]!=1&&a[i+j]==a[Sa[rank[i]-2]+j])
			j++;
		height[rank[i]]=j;
	}
}
void solve()
{
	for(int i=0;i<lena-lenb-1;i++)
		mark[rank[i]-1]=true;
	front[0]=mark[0]==true?0:-1,rear[lena-1]=mark[lena-1]==true?lena-1:-1;
	for(int i=1;i<lena;i++)
	{
		front[i]=mark[i]==true?i:front[i-1];
		if(mark[i]==false)  same1[i]=mark[i-1]==true?height[i+1]:min(height[i+1],same1[i-1]);
	}
	for(int i=lena-2;i>=0;i--)
	{
		rear[i]=mark[i]==true?i:rear[i+1];
		if(mark[i]==false)  same2[i]=mark[i+1]==true?height[i+2]:min(height[i+2],same2[i+1]);
	}
	for(int i=0;i<lena;i++)
		if(mark[i]==false)
			same[i]=max(same1[i],same2[i]);
	for(int i=lena-lenb;i<lena;ans++)
		i+=same[rank[i]-1];
}
int main()
{
	freopen("input.txt","r",stdin);
 	read();
 	make_Sa();
 	make_height();
 	solve();
 	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
 	return 0;
}
