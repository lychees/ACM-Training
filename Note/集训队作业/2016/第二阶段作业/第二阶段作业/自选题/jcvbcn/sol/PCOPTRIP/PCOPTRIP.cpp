#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<iostream>
#include<ctime>
#define MAXN 150005
using namespace std;
typedef long long ll;
int mu[MAXN];
int premu[MAXN];
int p[MAXN],bo[MAXN]={0},mip[MAXN],ptot=0;
int id[MAXN],nsq[MAXN],sqtot=0;
int sqfr[MAXN];
void sieve(int n){
	mu[1]=sqfr[1]=1;
	for (int i=2;i<=n;i++){
		if(!bo[i]){
			mu[i]=-1;
			p[++ptot]=i;
			mip[i]=i;
			sqfr[i]=i;
		}
		for (int j=1;j<=ptot && p[j]*i<=n;j++){
			bo[i*p[j]]=1;
			mip[i*p[j]]=p[j];
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				sqfr[i*p[j]]=sqfr[i];
				break;
			}else{
				mu[i*p[j]]=-mu[i];
				sqfr[i*p[j]]=p[j]*sqfr[i];
			}
		}
	}
	for (int i=1;i<=n;i++)if(mu[i]!=0){
		id[i]=++sqtot;
		nsq[sqtot]=i;
	}
	premu[1]=1;
	for (int i=2;i<=n;i++)premu[i]=mu[i]+premu[i-1];
}
int to[MAXN]={0};int stot=0;int tseq[MAXN];
int f[150000][1200]={0};//stot,sqtot
int g[150000][1200]={0};

int tmp[150005];
int main()
{

	int _t;
	scanf("%d",&_t);
	sieve(100000);
	while(_t--){
		//int cl=clock();
		int a,b,c;
		//printf("time sieve %d\n",clock()-cl);
		scanf("%d",&a);
		b=c=a;
		if(b>c)swap(b,c);
		//cl=clock();	
		ll ans=0;
		for (int i=1;i<=b;i++)to[b/i]=1;
		for (int i=1;i<=c;i++)to[c/i]=1;

		stot=0;
		for (int i=1;i<=b|| i<=c;i++)if(to[i])tseq[to[i]=++stot]=i;

		//printf("stot %d sqtot %d\n",stot,sqtot);
		for (int si=1;si<=sqtot && nsq[si]<=a;si++){
			if(si==1){
				for (int xi=1;xi<=stot;xi++)f[si][xi]=tseq[xi],g[si][xi]=premu[tseq[xi]];
			}else{
				int s=nsq[si],p=mip[s],nsi=id[s/p];
				for (int xi=1;xi<=stot;xi++){
					int x=tseq[xi];
					f[si][xi]=f[nsi][xi]-f[nsi][to[x/p]];
					g[si][xi]=g[nsi][xi]+g[si][to[x/p]];
				}
			}
		}
		//printf("time dp %d\n",clock()-cl);cl=clock();
		for (int i=1;i<=a;i++){
			int nex;int ii=id[sqfr[i]];
			for (int d=1;d<=b;d=nex+1){
				nex=min(b/(b/d),c/(c/d));
				ans=(ans+1ll*(g[ii][to[nex]]-g[ii][to[d-1]])*f[ii][to[b/d]]*f[ii][to[c/d]]);
			}
		}
		//printf("time add %d\n",clock()-cl);
		cout<<ans<<endl;
	}
	return 0;
}

