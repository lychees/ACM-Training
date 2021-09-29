#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
int Case,n,c[28],v[28],d[8],p[8],e[2]; char s[9];
char read(int &x)
{
	#define CH getchar()
	char ch; x=0; for (ch=CH;ch<'0' || ch>'9';ch=CH);
	for (;ch>='0' && ch<='9';x=x*10+ch-48,ch=CH); return ch=='R';
}
int get(int f,int x,int y,int z)
{
	e[0]=e[1]=0,++e[c[x]],++e[c[y]],++e[c[z]];
	return (e[f]>e[!f]?1:-1)*(v[x]+v[y]+v[z]);
}
int dfs(int f,int i,int x,int y,int z,int a,int b)
{
	if (i>n) return z+(x?f==c[x]?v[x]:-v[x]:0)+(y?f==c[y]?v[y]:-v[y]:0); int res;
	if (!x){res=-dfs(!f,i+1,y,i,-z,-b,-a); if (0&&res>=b) return b; if (res>a) a=res;}
	rep(j,5) if (d[j] && !d[j+1]){
		int X=p[j],Y=p[j+1];
		if (X){
			p[j]=0,p[j+1]=i;
			res=-dfs(!f,i+1,y,x,-z-get(f,X,Y,i),-b,-a);
			p[j]=X,p[j+1]=Y;
			if (res>=b) return b; if (res>a) a=res;
			if (x){
				p[j]=0,p[j+1]=x;
				res=-dfs(!f,i+1,y,i,-z-get(f,X,Y,x),-b,-a);
				p[j]=X,p[j+1]=Y;
				if (res>=b) return b; if (res>a) a=res;
			}
		}else if (x){
			p[j]=i,p[j+1]=x,d[j]=0,d[j+1]=1;
			res=-dfs(!f,i+1,y,0,-z-get(f,x,i,Y),-b,-a);
			p[j]=X,p[j+1]=Y,d[j]=1,d[j+1]=0;
			if (res>=b) return b; if (res>a) a=res;
			p[j]=x,p[j+1]=i,d[j]=0,d[j+1]=1;
			res=-dfs(!f,i+1,y,0,-z-get(f,x,i,Y),-b,-a);
			p[j]=X,p[j+1]=Y,d[j]=1,d[j+1]=0;
			if (res>=b) return b; if (res>a) a=res;
		}
	}
	return a;
}
int main()
{
	while (scanf("%s",s),*s!='E'){
		read(n),n*=2; rep(i,n) c[i]=read(v[i]); rep(i,6) d[i]=i&1,p[i]=i+1;
		int ans=dfs(c[1],9,0,0,0,-1<<9,1<<9);
		if (!c[1]) ans=-ans; if (*s=='B') ans=-ans;
		printf("Case %d: ",++Case);
		if (!ans) puts("Axel and Birgit tie");
		else printf("%s %s %d\n",s,ans>0?"wins":"loses",abs(ans));
	}
	return 0;
}
