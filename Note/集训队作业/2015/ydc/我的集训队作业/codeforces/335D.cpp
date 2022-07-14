#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#define maxn 100010
#define maxm 3010
using namespace std;
const int N=3005;
void Read(int &digit)
{
	digit=0;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';digit=digit*10+c-'0',c=getchar());
}
struct Rect
{
	int x1,y1,x2,y2;
}rec[maxn];
vector<int> row[maxn];
int cnt1[maxm][maxm],cnt2[maxm][maxm],cnt3[maxm][maxm],n;
void read()
{
	Read(n);
	for(int i=1;i<=n;++i)
	{
		Rect &r=rec[i];
		Read(r.x1),Read(r.y1),Read(r.x2),Read(r.y2);
		++r.x1,++r.y1,++r.x2,++r.y2;
		row[r.x1].push_back(r.y1),row[r.x1].push_back(r.y2);
		row[r.x2].push_back(r.y1),row[r.x2].push_back(r.y2);
		for(int j=r.x1+1;j<=r.x2;++j)
			for(int k=r.y1+1;k<=r.y2;++k)
				++cnt1[j][k];
		for(int j=r.y1+1;j<=r.y2;++j)
			cnt2[r.x1][j]=1,cnt2[r.x2][j]=1;
		for(int j=r.x1+1;j<=r.x2;++j)
			cnt3[r.y1][j]=1,cnt3[r.y2][j]=1;
	}
	for(int i=1;i<=N;++i)
	{
		sort(row[i].begin(),row[i].end());
		row[i].resize(unique(row[i].begin(),row[i].end())-row[i].begin());
		for(int j=1;j<=N;++j)
		{
			cnt1[i][j]+=cnt1[i-1][j]+cnt1[i][j-1]-cnt1[i-1][j-1];
			cnt2[i][j]+=cnt2[i][j-1],cnt3[i][j]+=cnt3[i][j-1];
		}
	}
}
void print(int a,int b,int c,int d)
{
	static int ans[maxn];
	int tot=0;
	for(int i=1;i<=n;++i)
		if(rec[i].x1>=a&&rec[i].y1>=b&&rec[i].x2<=c&&rec[i].y2<=d)
			ans[++tot]=i;
	printf("YES %d\n",tot);
	for(int i=1;i<=tot;++i)
		printf("%d%c",ans[i],i<tot?' ':'\n');
	exit(0);
}
void print()
{
	for(int i=1;i<=N;++i)
		for(int j=0;j<(int)row[i].size();++j)
			for(int k=j+1;k<(int)row[i].size();++k)
			{
				int x1=i,y1=row[i][j],y2=row[i][k],x2=x1+y2-y1;
				if(x2>N)
					continue;
				if(cnt1[x2][y2]-cnt1[x1][y2]-cnt1[x2][y1]+cnt1[x1][y1]!=(x2-x1)*(y2-y1))
					continue;
				if(cnt2[x1][y2]-cnt2[x1][y1]!=y2-y1||cnt2[x2][y2]-cnt2[x2][y1]!=y2-y1)
					continue;
				if(cnt3[y1][x2]-cnt3[y1][x1]!=x2-x1||cnt3[y2][x2]-cnt3[y2][x1]!=x2-x1)
					continue;
				print(x1,y1,x2,y2);
			}
	printf("NO\n");
}
int main()
{
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read();
	print();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
