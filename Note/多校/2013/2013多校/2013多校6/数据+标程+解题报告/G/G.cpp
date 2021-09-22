#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define P 1000000007
#define N 1000010
int n,F[N],I[N],he[N],ad[N*2],ne[N*2],t,fa[N],q[N],s[N],fd[N],gd[N],fu[N];
void addE(int x,int y)
{
	++t,ne[t]=he[x],he[x]=t,ad[t]=y;
}
inline int sqr(int x){return (ll)x*x%P;}
int main()
{
	F[0]=1;for(int i=1;i<N;i++)F[i]=(ll)F[i-1]*i%P;
	I[1]=1;for(int i=2;i<N;i++)I[i]=(ll)P/i*(P-I[P%i])%P;
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		t=0,memset(he,0,sizeof(int)*n);
		for(int i=1,x,y;i<n;i++)
			scanf("%d%d",&x,&y),--x,--y,addE(x,y),addE(y,x);
		int le=0,ri=1;q[0]=0;fa[0]=-1;
		while(le<ri)
		{
			int x=q[le++];
			for(int p=he[x];p;p=ne[p])
				if(ad[p]!=fa[x])fa[ad[p]]=x,q[ri++]=ad[p];
		}
		memset(s,0,sizeof(int)*n);
		for(int i=0;i<n;i++)fd[i]=gd[i]=1;
		for(int i=n-1;i>=0;i--)
		{
			int x=q[i];s[x]++;
			fd[x]=(ll)fd[x]*s[x]%P,gd[x]=(ll)gd[x]*I[s[x]]%P;
			int y=fa[x];
			if(y==-1)break;
			s[y]+=s[x],fd[y]=(ll)fd[y]*fd[x]%P,gd[y]=(ll)gd[y]*gd[x]%P;
		}
		fu[0]=1;
		for(int i=0;i<n;i++)
		{
			int x=q[i],z=(ll)fu[x]*gd[x]%P*s[x]%P;
			for(int p=he[x];p;p=ne[p])
				if(ad[p]!=fa[x])fu[ad[p]]=(ll)z*fd[ad[p]]%P*I[n-s[ad[p]]]%P;
		}
		//for(int i=0;i<n;i++)printf("%d\n",i,(ll)F[n]*fu[i]%P*gd[i]%P);
		int S=0;
		for(int i=0;i<n;i++)
			S=(S+sqr((ll)F[n]*fu[i]%P*gd[i]%P*s[i]%P*I[n]%P))%P;
		printf("%d\n",S);
	}
	return 0;
}