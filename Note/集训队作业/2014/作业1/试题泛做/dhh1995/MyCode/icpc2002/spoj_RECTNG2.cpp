#include <cstdio>
#include <cstring>
#define maxn 50

typedef bool Tflg[maxn][maxn];
Tflg v1,v2,v3,h1,h2,h3;
int w,h;
char ch;

inline void solve(int x1,int y1,int x2,int y2)
{
	for (int i=x1+1;i<=x2;++i)
	{
		bool fl=true;
		for (int j=y1;j<=y2;++j)
		if (!v1[i][j] || !v2[i][j])
		{
			fl=false;
			break;
		}
		if (fl)
		{
			for (int j=y1;j<=y2;++j)
				v3[i][j]=true;
			solve(x1,y1,i-1,y2);
			solve(i,y1,x2,y2);
			return;
		}
	}
	for (int j=y1+1;j<=y2;++j)
	{
		bool fl=true;
		for (int i=x1;i<=x2;++i)
		if (!h1[i][j] || !h2[i][j])
		{
			fl=false;
			break;
		}
		if (fl)
		{
			for (int i=x1;i<=x2;++i)
				h3[i][j]=true;
			solve(x1,y1,x2,j-1);
			solve(x1,j,x2,y2);
			return;
		}
	}
}

int main()
{
	for (int T=1;scanf("%d%d",&w,&h) && w+h;++T)
	{
		char s[100];
		memset(v1,false,sizeof(v1));
		memset(h1,false,sizeof(h1));
		memset(v2,false,sizeof(v2));
		memset(h2,false,sizeof(h2));
		for (int j=1;j<=h+1;++j)
		{
			gets(s);
			for (int i=1;i<=w+1;++i)
			{
				scanf("%c",&ch);
				v1[i][j-1]=ch=='|';
				if (i==w+1) break;
				scanf("%c",&ch);
				h1[i][j]=ch=='_';
			}
			scanf("%c",&ch);
			for (int i=1;i<=w+1;++i)
			{
				scanf("%c",&ch);
				v2[i][j-1]=ch=='|';
				if (i==w+1) break;
				scanf("%c",&ch);
				h2[i][j]=ch=='_';
			}
		}
		
		memset(v3,false,sizeof(v3));
		memset(h3,false,sizeof(h3));
		for (int i=1;i<=w;++i)
			h3[i][1]=h3[i][h+1]=true;
		for (int i=1;i<=h;++i)
			v3[1][i]=v3[w+1][i]=true;
		
		solve(1,1,w,h);
		
		printf("Case %d:\n",T);
		for (int j=1;j<=h+1;++j)
		{
			for (int i=1;i<=w+1;++i)
			{
				if (v1[i][j-1] || v2[i][j-1]) printf("|");
				else printf(" ");
				if (i==w+1) break;
				if (h1[i][j] || h2[i][j]) printf("_");
				else printf(" ");
			}
			printf(" ");
			for (int i=1;i<=w+1;++i)
			{
				if (v3[i][j-1]) printf("|");
				else printf(" ");
				if (i==w+1) break;
				if (h3[i][j]) printf("_");
				else printf(" ");
			}
			puts("");
		}
		puts("");
	}
	return 0;
}
