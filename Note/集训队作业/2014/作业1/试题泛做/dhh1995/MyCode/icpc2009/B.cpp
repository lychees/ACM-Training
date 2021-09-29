#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,m,L,Q,x,y,z,a[22][2],v[35],g[22],o[1<<9]; char type[22][2],ch;
int get(char c,int x,int y){return c=='a'?x&y:c=='o'?x|y:c=='x'?x^y:!x;}
bool check(int x,int y)
{
	rep(k,1<<n) if (o[k]>=0){
		rep(i,m) v[i]=-1; rep(i,n) v[m+i]=k>>i&1; int c=0;
		while (c<m){
			rep(i,m) if (v[i]<0 && v[*a[i]]>=0 && (*type[i]=='n' || v[a[i][1]]>=0)){
				v[i]=get(*type[i],v[*a[i]],v[a[i][1]]),++c;
				if (i==x) if (y<0) v[i]^=1; else v[i]=y;
			}
		}
		rep(i,L) if ((o[k]>>i&1)!=v[g[i]]) return 0;
	}
	return 1;
}
int main()
{
	while (scanf("%d%d%d",&n,&m,&L),n||m||L){
		rep(i,m){
			scanf("%s %c%d",type[i],&ch,a[i]),*a[i]+=ch=='i'?m-1:-1;
			if (*type[i]!='n') scanf(" %c%d",&ch,a[i]+1),a[i][1]+=ch=='i'?m-1:-1;
		}
		rep(i,L) scanf("%d",g+i),--g[i]; scanf("%d",&Q); rep(i,1<<n) o[i]=-1; bool flag=0;
		rep(i,Q){
			x=y=0; rep(j,n) scanf("%d",&z),x|=z<<j; rep(j,L) scanf("%d",&z),y|=z<<j;
			if (o[x]<0) o[x]=y; else if (o[x]!=y) flag=1;
		}
		printf("Case %d: ",++Case);
		if (flag) puts("Unable to totally classify the failure");
		else{
			if (check(-1,-1)) puts("No faults detected");
			else{
				x=-1; rep(i,m) rep(j,3) if (check(i,j-1)) if (x<0) x=i,y=j-1; else flag=1;
				if (x<0 || flag) puts("Unable to totally classify the failure");
				else{
					printf("Gate %d is failing; ",x+1);
					if (y<0) puts("output inverted"); else printf("output stuck at %d\n",y); 
				}
			}
		}
	}
	return 0;
}
