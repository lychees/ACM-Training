#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,m,cnt,v[maxn][4];
int go1[maxn][4],go2[maxn][4][4],go3[maxn][4][4][4];
void read()
{
	scanf("%d %d %d",&n,&m,&cnt);
	for(int i=1;i<=n;++i)
		for(int j=0;j<m;++j)
			scanf("%d",&v[i][j]);
}
void work()
{
	int ans=0,ansl,ansr;
	for(int i=n;i>=1;--i)
		for(int j=0;j<m;++j)
		{
			go1[i][j]=i;
			if(i<n)
			{
				int p=find(v[i+1],v[i+1]+m,v[i][j])-v[i+1];
				if(p<m)
					go1[i][j]=go1[i+1][p];
			}
			if(ans<=go1[i][j]-i+1)
				ans=go1[i][j]-i+1,ansl=i,ansr=go1[i][j];
			if(cnt>1&&go1[i][j]!=n)
			{
				int x=go1[i][j]+1;
				for(int k=0;k<m;++k)
				{
					int y=go1[x][k];
					go2[i][j][k]=y;
					if(y<n)
					{
						int p=find(v[y+1],v[y+1]+m,v[i][j])-v[y+1];
						if(p<m)
							go2[i][j][k]=go2[x][k][p];
					}
					if(ans<=go2[i][j][k]-i+1)
						ans=go2[i][j][k]-i+1,ansl=i,ansr=go2[i][j][k];
					if(cnt>2&&go2[i][j][k]!=n)
					{
						int a=go2[i][j][k]+1;
						for(int l=0;l<m;++l)
						{
							int b=go1[a][l];
							go3[i][j][k][l]=b;
							if(b<n)
							{
								int p,q;
								p=find(v[b+1],v[b+1]+m,v[i][j])-v[b+1];
								if(p<m)
								{
									int next=go2[a][l][p];
									go3[i][j][k][l]=max(go3[i][j][k][l],next);
									if(next<n)
									{
										q=find(v[next+1],v[next+1]+m,v[x][k])-v[next+1];
										if(q<m)
											go3[i][j][k][l]=max(go3[i][j][k][l],go3[a][l][p][q]);
									}
								}
								p=find(v[b+1],v[b+1]+m,v[x][k])-v[b+1];
								if(p<m)
								{
									int next=go2[a][l][p];
									go3[i][j][k][l]=max(go3[i][j][k][l],next);
									if(next<n)
									{
										q=find(v[next+1],v[next+1]+m,v[i][j])-v[next+1];
										if(q<m)
											go3[i][j][k][l]=max(go3[i][j][k][l],go3[a][l][p][q]);
									}
								}
							}
							if(ans<=go3[i][j][k][l]-i+1)
								ans=go3[i][j][k][l]-i+1,ansl=i,ansr=go3[i][j][k][l];
						}
					}
				}
			}
		}
	printf("%d %d\n",ansl-1,ansr-1);
}
int main()
{
	freopen	("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T,C=0;
	for(cin>>T;T;--T)
	{
		read();
		printf("Case #%d: ",++C);
		work();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
