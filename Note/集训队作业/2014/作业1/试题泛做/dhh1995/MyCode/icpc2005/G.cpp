#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
int Case,n,sum,tmp,c[105],d[105],a[55],b[55],x[55],y[55],c0[4],c1[4]; char dir;
int chg(char dir){return dir=='N'?0:dir=='S'?1:dir=='E'?2:3;}
bool get(int i,int j,int m,int &L)
{
	L=0;
	while (j<=m){
		L+=b[j]; if (x[i]!=y[j]) return 0;
		if (j==m) return a[i]>=b[j];
		if (a[i++]!=b[j++]) return 0;
	}
	return 1;
}
bool dfs(int t,int p,int r)
{
	int L; if (t && get(p,1,r,L)) return 1; if (t>1) return 0;
	rep(j,1,r) if (y[j]==x[p] && b[j]>=a[p] && get(p+1,j+1,r,L)){
		int i=p; L+=a[i]; while (a[i]<=L) L-=a[i++];
		b[j]-=a[p],a[i]-=L; if (dfs(t+1,i,j-!b[j])) return 1; b[j]+=a[p],a[i]+=L;
	}
	return 0;
}
bool work()
{
	rep(i,1,n) c[i+n]=c[i],d[i+n]=d[i];
	rep(k,1,n){
		int s=0,flag=0; *a=*b=0; rep(i,0,3) c0[i]=c1[i]=0;
		rep(i,k,k+n-1)
			if (s<sum)
				if (s+c[i]<=sum) c0[d[i]]+=a[++*a]=c[i],x[*a]=d[i],s+=c[i];
				else c0[d[i]]+=a[++*a]=sum-s,x[*a]=d[i],
					c1[d[i]^1]+=b[++*b]=s+c[i]-sum,y[*b]=d[i]^1,s=sum;
			else c1[d[i]^1]+=b[++*b]=c[i],y[*b]=d[i]^1;
		rep(i,0,3) if (c0[i]!=c1[i]) flag=1; if (flag) continue;
		reverse(b+1,b+*b+1),reverse(y+1,y+*b+1);
		if (dfs(0,1,*b)) return 1;
	}
	return 0;
}
int main()
{
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	while (scanf("%d",&n),n){
		sum=0,d[0]=-1;
		rep(i,1,n){
			scanf("%*c%c%d",&dir,c+i),sum+=c[i],d[i]=chg(dir);
			if (d[i]==d[i-1]) c[i-1]+=c[i],--i,--n;
		}
		if (n>1 && d[1]==d[n]) c[1]+=c[n--]; sum/=2; bool flag=work();
		reverse(c+1,c+n+1),reverse(d+1,d+n+1),flag|=work();
		printf("Polygon %d: %s\n",++Case,flag?"Possible":"Impossible");
	}
	return 0;
}
