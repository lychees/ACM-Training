#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
char s[5],a[5],b[5],f[9][5],g[9][5]; int o,F=1;
const int t[7]={0,2,2,1,2,2,2},
	u[2][12]={{3,3,4,4,5,6,6,7,7,1,1,2},{2,4,-4,5,6,5,7,-7,1,-1,2,3}},
	v[2][12]={{1,2,1,2,1,1,2,1,2,1,2,1},{2,0,-1,0,0,2,0,-1,0,-1,0,0}};
void chg(char s[5],int x,int y){int i=1; s[0]=x+64; if (y!=1) s[i++]=y?'#':'b'; s[i]='\0';}
bool dfs(int i,int k,int d,int c,int z)
{
	if (i==7){o=z; return 1;} k=(k+t[i])%12;
	rep(j,2) if (u[j][k]>0){
		int x=u[j][k],y=v[j][k];
		if (!(d>>x&1) && (y==1 || !(c>>2-y&1))) if (dfs(i+1,k,d|1<<x,c|1<<y,z|j<<i)) return 1;
	}
	return 0;
}
bool Major(char *a,char f[9][5])
{
	int x=*a-64,y=a[1]=='#'?2:a[1]=='b'?0:1,z,k;
	rep(i,2) rep(j,12) if (u[i][j]==x && v[i][j]==y) z=i,k=j;
	if (!dfs(1,k,1<<x,1<<y,z)) return 0;
	rep(i,7) k=(k+t[i])%12,chg(f[i],u[o>>i&1][k],v[o>>i&1][k]); return 1;
}
int Find(){rep(i,7) if (!(strcmp(s,f[i]))) return i; return -1;}
int main()
{
	while (scanf("%s",a),*a!='*'){
		scanf("%s",b); bool flag=0; if (F) F=0; else puts("");
		if (!Major(a,f)) printf("Key of %s is not a valid major key\n",a);
		else if (!Major(b,g)) printf("Key of %s is not a valid major key\n",b);
		else printf("Transposing from %s to %s:\n",a,b),flag=1;
		while (scanf("%s",s),*s!='*') if (flag){
			int w=Find();
			if (w<0) printf("  %s is not a valid note in the %s major scale\n",s,a);
			else printf("  %s transposes to %s\n",s,g[w]);
		}
	}
	return 0;
}
