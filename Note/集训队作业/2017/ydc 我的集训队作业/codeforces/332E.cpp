#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1000010
#define maxm 210
#define maxk 2010
using namespace std;
char str1[maxn],str2[maxm],ans[maxk];
int m,n1,n2;
bool Judge(int len)
{
	if((n2/len-1)*m+n2%len>n1)
		return false;
	if(((n2-1)/len+2)*m<n1)
		return false;
	return true;
}
bool check(int x,int y,int len)
{
	int i,j;
	for(i=x,j=y;i<=n1&&j<=n2;i+=m,j+=len)
		if(str1[i]!=str2[j])
			return false;
	return i>n1&&j>n2;
}
void print()
{
	ans[1]='2';
	static char out[maxk];
	for(int i=1;i<=n2;++i)
		if(Judge(i))
		{
			fill(out+1,out+m+1,'0');
			bool mark=true;
			int id=m;
			for(int j=i;j>=1&&mark;--j)
			{
				while((id>=1&&!check(id,j,i))||(j<=n2%i&&id>(n1-1)%m+1)||id>n1)
					--id;
				if(id<1)
					mark=false;
				out[id]='1',--id;
			}
			if(!mark)
				continue;
			if(strcmp(ans+1,out+1)>0)
				for(int j=1;j<=m;++j)
					ans[j]=out[j];
		}
	printf("%s\n",ans[1]=='2'?"0":ans+1);
}
void read()
{
	char c;
	for(c=getchar();c>=32&&c<=126;c=getchar())
		str1[++n1]=c;
	for(c=getchar();c>=32&&c<=126;c=getchar())
		str2[++n2]=c;
	scanf("%d",&m);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
