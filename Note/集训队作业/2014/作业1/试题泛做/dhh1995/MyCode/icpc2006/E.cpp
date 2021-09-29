#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int Case,n,m,L,ans; char s[55];
void dfs(int i,int x,int y)
{
	if (x>n || x-y>m || ans>1) return;
	if (i>=L){if (x+x-y==n+m) ++ans; return;}
	if (s[i]=='0') dfs(i+1,x+1,y+1);
	else {
		int c=1,b=1;
		for (int j=i+1;j<=L;++j){
			if (s[j]=='0'){
				if (b && j-i<3) dfs(j,x+j-i,y);
				if (c>2) dfs(j,x+c,y);
			}
			c=c*2+(s[j]=='1'),b&=s[j]=='1';
		}
	}
}
int main()
{
	while (scanf("%d%d",&n,&m),n||m){
		scanf("%s",s),L=strlen(s),s[L]='0',ans=0,dfs(0,0,0);
		printf("Case #%d: %s\n",++Case,ans==2?"NOT UNIQUE":ans?"YES":"NO");
	}
	return 0;
}
