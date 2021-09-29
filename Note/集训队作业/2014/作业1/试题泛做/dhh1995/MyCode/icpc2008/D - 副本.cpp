#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=305;
int Case,n=100,np,m,nc,D,S,T,dir,x,y,z,d1,d2,hare,hound;
int a[N],son[N],ed[N],next[N],data[N],c[N],d[N]; bool b[N],e[N];
void add(int x,int y,int z,int dir){ed[++l]=y,d[l]=dir,c[l]=z+1,data[l]=z,next[l]=son[x],son[x]=l;}
void find(int x,int dir,int last,bool flag)
{
	if (x==T && !flag) return; int opt=360,q;
	if (flag<0 && !b[x] || flag>0 && (b[x] || !next[son[x]])){
		int q=a[l--]; hound+=data[q]*2,find(ed[q^1],(d[q]+180)%360,q,-1); return;
		}
	if (flag<0 && b[x]) flag=1;
	if (!flag && b[x]){for (int p=son[x];p;p=next[p]) e[p]=1; e[last]=0; find(x,dir,last,1);}
	for (int p=son[x];p;p=next[p]) if (!flag || e[p]){
		int diff=d[p]-dir; if (diff>180) diff-=360; if (diff<-180) diff+=360;
		if (abs(diff)<abs(opt) || abs(diff)==abs(opt) && diff<0) opt=diff,q=p;
	}
	if (!flag) a[++l]=q,find(ed[q],(d[q^1]+180)%360,q^1,flag);
	else {
		if (c[q])
		}
}
int main()
{
	while (scanf("%d%d%d%d%d%d%d",&np,&m,&nc,&D,&S,&T,&dir),S){
		//printf("Case %d:",++Case);
		rep(i,n) b[i]=son[i]=0; l=1;
		rep(i,np) scanf("%d",&x),b[x]=1;
		rep(i,m) scanf("%d%d%d%d%d",&x,&y,&d1,&d2,&z),add(x,y,z,d1),add(y,x,z,d2);
		rep(i,nc) scanf("%d%d%d",&x,&y,&z),y*=2,y^=ed[y]==x,
			c[y]=min(c[y],z),c[y^1]=min(c[y^1],data[y]-z);
		l=hare=hound=0,find(S,dir,0,0); rep(i,l) hare+=data[a[i]],hound+=data[a[i]];
		printf("Length of hare's route is %d\n",hare);
		printf("Length of hound's search is %d\n",hound);
		printf("Route:"); rep(i,l) printf(" %d",a[i]/2); puts(""); 
	}
	return 0;
}
