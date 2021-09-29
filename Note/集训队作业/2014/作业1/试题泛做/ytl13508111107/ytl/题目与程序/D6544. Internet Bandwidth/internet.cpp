#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 105
#define M (N*N)
using namespace std;

int n,m;
const int inf=0x7fffffff/3;
namespace Dinic{
	namespace Graph{
		int head[N],head2[N],gt=1;
		struct Rec{int go,nex,c;}eg[M*2];
		void build(int a,int b,int c){
			eg[++gt]=(Rec){b,head[a],-c};
			head[a]=gt;
			eg[++gt]=(Rec){a,head[b],0};
			head[b]=gt;
		}
		void initGraph(){
			memset(head,0,sizeof(head));
			gt=1;
		}
	}
	using namespace Graph;
	int dis[N],Q[N],s[N],S,T,stop,ans;
	bool bfs(){
		memset(dis,0,sizeof(dis));
		dis[T]=1;
		Q[1]=T;
		for (int p1=1,p2=1;p1<=p2;p1++){
			for (int i=head[Q[p1]];i;i=eg[i].nex)
				if (eg[i^1].c<0&&!dis[eg[i].go]){
					dis[eg[i].go]=dis[Q[p1]]+1;
					Q[++p2]=eg[i].go;
				}
		}
		if (!dis[S]) return false;
		memcpy(head2,head,sizeof(head));
		return true;
	}
	bool dinic(int p,int top){
		if (p==T){
			int x=inf;
			for (int i=1;i<=top-1;i++) if (-eg[s[i]].c<x) x=-eg[s[i]].c,stop=i;
			for (int i=1;i<=top-1;i++) eg[s[i]].c+=x,eg[s[i]^1].c-=x;
			ans+=x;
			return true;
		}
		for (int &i=head2[p];i;i=eg[i].nex){ 
			if (eg[i].c<0&&dis[eg[i].go]==dis[p]-1){
				s[top]=i;
				if (dinic(eg[i].go,top+1)&&top!=stop) return true;
			}
		}
		return false;
	}
	int ask(){
		ans=0;
		while (bfs()) dinic(S,1);
		return ans;	
	}
	void init(int _S,int _T){
		S=_S,T=_T;
	}
	void initDinic(){
		initGraph();
	}
}
using namespace Dinic;

int main(){
	freopen("internet.in","r",stdin);
	freopen("internet.out","w",stdout);
	scanf("%d",&n);
	scanf("%d%d%d",&S,&T,&m);
	for (int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		build(a,b,c);
		build(b,a,c);
	}	
	printf("%d\n",ask());
	return 0;
}
