#include<cstdio>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=1;i<=n;++i)
const int N=100005;
int ed[N],data[N],tmp[N],next[N],son[N],f[N*10],d[N],b[N],e[N],s[N],x[N],y[N],z[N];
int n,m,c,l,ans,now;
void add(int x,int y,int z){ed[++l]=y,data[l]=z,next[l]=son[x],son[x]=l;}
bool build()
{
	rep(i,n) b[i]=-1; int h=0,t=1,flag=!now && s[1]; b[1]=0,f[1]=1;
	while (h<t){
		int x=f[++h];
		for (int p=son[x];p;p=next[p]) if (data[p]){
			int y=ed[p];
			if (d[y]<=now && b[y]<0){
				b[y]=b[x]+1,f[++t]=y;
				if (d[y]==now && s[y]) flag=1;
			}
		}
	}
	return flag;
}
int dinic(int x,int low)
{
	int w=0,res; if (d[x]==now){res=min(s[x],low),s[x]-=res; return res;}
	for (int p=son[x];p && w<low;p=next[p]) if (data[p]){
		int y=ed[p];
		if (b[y]==b[x]+1 && (res=dinic(y,min(low-w,data[p]))))
			data[p]-=res,data[p^1]+=res,w+=res;		
	}
	if (!w) b[x]=-1; return w;
}
int main()
{
	freopen("congest.in","r",stdin);
	freopen("congest.out","w",stdout);
	while (scanf("%d%d%d",&n,&m,&c)!=EOF){
		rep(i,n) son[i]=0,s[i]=0,b[i]=0,d[i]=1<<30; l=1,ans=0;
		rep(i,m) scanf("%d%d%d",x+i,y+i,z+i),add(x[i],y[i],z[i]),add(y[i],x[i],z[i]);
		rep(i,c) scanf("%d",e+i),++s[e[i]];
		int h=0,t=1; f[1]=1,d[1]=0;
		while (h<t){
			int x=f[++h]; b[x]=0;
			for (int p=son[x];p;p=next[p]){
				int y=ed[p];
				if (d[x]+data[p]<d[y]){
					d[y]=d[x]+data[p];
					if (!b[y]) b[y]=1,f[++t]=y;
				}
			}
		}
		rep(i,n) son[i]=0; l=1;
		rep(i,m){
			if (d[x[i]]>d[y[i]]) swap(x[i],y[i]);
			if (d[x[i]]+z[i]==d[y[i]]) add(x[i],y[i],1),add(y[i],x[i],0);
		}
		rep(j,l) tmp[j]=data[j+1];
		rep(i,c) if (s[e[i]]){
			now=d[e[i]]; rep(j,l) data[j+1]=tmp[j];
			while (build()) ans+=dinic(1,c);
			rep(j,c) if (d[e[j]]==now) s[e[j]]=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
