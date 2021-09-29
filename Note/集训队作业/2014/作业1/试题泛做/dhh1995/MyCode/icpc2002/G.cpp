#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,flag; char s[25][99],*t[25];
int main()
{
	while (scanf("%d%d",&m,&n),n||m){
		++n,++m,gets(s[0]);
		rep(i,n){
			gets(s[i]),t[i]=s[i]+m*2; s[i][m*4-1]='\0';
			rep(j,m+m-1){
				char x=s[i][j],y=t[i][j];
				if (y!=' ') s[i][j]=y;
				if (x==' ') t[i][j]=x;
			}
		}
		do{
			flag=0;
			rep(i,n) rep(j,m+m-1){
				if (i && i+1<n && t[i][j]=='_')
					if ((t[i][j-1]!='|' || t[i+1][j-1]!='|') && (j<2 || t[i][j-2]!='_') ||
						(t[i][j+1]!='|' || t[i+1][j+1]!='|') && t[i][j+2]!='_' )
						t[i][j]=' ',flag=1;
				if (j && j+2<m+m && t[i][j]=='|')
					if ((t[ i ][j-1]!='_' || t[ i ][j+1]!='_') && t[i+1][j]!='|' ||
						(t[i-1][j-1]!='_' || t[i-1][j+1]!='_') && t[i-1][j]!='|' )
						t[i][j]=' ',flag=1;
			}
		}while (flag);
		printf("Case %d:\n",++Case); rep(i,n) puts(s[i]); puts("");
	}
	return 0;
}
