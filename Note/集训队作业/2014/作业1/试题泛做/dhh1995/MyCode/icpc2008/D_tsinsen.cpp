#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=305;
int Case,n=100,np,m,nc,D,S,T,l,dis,dir,x,y,z,d1,d2,hare,hound;
int a[N*N],son[N],ed[N],next[N],data[N],c[N],d[N]; bool b[N],e[N];
void add(int x,int y,int z,int dir){ed[++l]=y,d[l]=dir,c[l]=data[l]=z,next[l]=son[x],son[x]=l;}
bool Find(int x,int dir,bool flag)
{
//	printf("%d %d %d\n",x,dir,flag);
	if (x==T && !flag && l) return 1; if (flag && (b[x] || !next[son[x]])) return 0;
	if (!flag && b[x]){
		for (int p=son[x];p;p=next[p]) e[p]=1; e[a[l]^1]=0;
		for (;;){
			int opt=360,q,w=l;
			for (int p=son[x];p;p=next[p]) if (e[p]){
				int diff=d[p]-dir; if (diff>180) diff-=360; if (diff<-180) diff+=360;
				if (abs(diff)<abs(opt) || abs(diff)==abs(opt) && diff>0) opt=diff,q=p;
			}
			dis=c[q],a[++l]=q;
			if (c[q]>D) dis=D; else if (Find(ed[q],(d[q^1]+180)%360,c[q]==data[q])) return 1;
			hound+=dis*2,l=w,dir=(d[q]+180)%360,e[q]=0;
		}
	}
	int opt=360,q;
	for (int p=son[x];p;p=next[p]){
		int diff=d[p]-dir; if (diff>180) diff-=360; if (diff<-180) diff+=360;
		if (abs(diff)<abs(opt) || abs(diff)==abs(opt) && diff>0) opt=diff,q=p;
	}
	if (flag && dis+c[q]>D) return dis=D,0;
	return dis+=data[q],a[++l]=q,Find(ed[q],(d[q^1]+180)%360,flag && c[q]==data[q]);
}
int main()
{
	while (scanf("%d%d%d%d%d%d%d",&np,&m,&nc,&D,&S,&T,&dir)!=EOF){
		rep(i,n) b[i]=son[i]=0; l=1;
		rep(i,np) scanf("%d",&x),b[x]=1;
		rep(i,m) scanf("%d%d%d%d%d",&x,&y,&d1,&d2,&z),add(x,y,z,d1),add(y,x,z,d2);
		rep(i,nc) scanf("%d%d%d",&x,&y,&z),y*=2,y^=ed[y]==x,
			c[y]=min(c[y],z),c[y^1]=min(c[y^1],data[y]-z);
		l=hare=hound=0,Find(S,dir,0); rep(i,l) hare+=data[a[i]],hound+=data[a[i]];
		printf("Length of hare's route is %d\n",hare);
		printf("Length of hound's search is %d\n",hound);
		printf("Route:"); rep(i,l) printf(" %d",a[i]/2); puts(""); 
	}
	return 0;
}
