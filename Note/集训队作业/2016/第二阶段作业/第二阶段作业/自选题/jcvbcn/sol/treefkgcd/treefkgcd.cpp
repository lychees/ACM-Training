#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstdio>
//#include<ctime>
#define MAX 200005
using namespace std;
int n;
struct edge{int v,next;}e[MAX];int etot=0;int g[MAX];
void ae(int u,int v){
	e[etot].v=v;e[etot].next=g[u];g[u]=etot++;
}
typedef long long ll;
ll ans[MAX]={0};
ll ans2[MAX]={0};
int h[MAX],pre[MAX];
int off[MAX]={0};

int qu[MAX],sz[MAX],bo[MAX];
int findc(int rt){
	int p=0,q=0;qu[q++]=rt;
	while(p!=q){
		int u=qu[p++];
		bo[u]=sz[u]=1;
		for (int i=g[u];~i;i=e[i].next)if(!off[e[i].v])
			qu[q++]=e[i].v;
	}
	for (int i=q-1;i>=0;i--){
		if(bo[qu[i]] && sz[qu[i]]*2>=q)return qu[i];
		sz[pre[qu[i]]]+=sz[qu[i]];
		if(sz[qu[i]]*2>q)bo[pre[qu[i]]]=0;
	}
}
int nu[MAX];
int bfs(int rt,int *nu,int hh){
	int p=0,q=0;qu[q++]=rt;
	while(p!=q){
		int u=qu[p++];
		for (int i=g[u];~i;i=e[i].next)if(!off[e[i].v])qu[q++]=e[i].v;
	}
	int hmax=h[qu[q-1]]-h[rt]+hh;
	for (int i=0;i<=hmax;i++)nu[i]=0;
	for (int i=0;i<q;i++)nu[h[qu[i]]-h[rt]+hh]++;
	return hmax;
}
int tmp[MAX];ll tmpsq[MAX];
int nsu[MAX];
int tmpnu[MAX],*start[MAX],tmph[MAX];
int ord[MAX];int cmp(int i,int j){return tmph[i]<tmph[j];}
int ind=0;
int check[MAX]={0},val[MAX];
void work(int rt){
	int c=findc(rt);
	off[c]=1;
	int hmax=0;
	for (int i=g[c];~i;i=e[i].next)if(!off[e[i].v]){
		int h=bfs(e[i].v,nu,1);
		if(h>hmax){
			for (int j=hmax+1;j<=h;j++)nsu[j]=0,tmp[j]=tmpsq[j]=1;
			hmax=h;
		}
		for (int j=1;j<=h;j++){
			nsu[j]+=nu[j];
			int s=0;
			for (int k=j;k<=h;k+=j)s+=nu[k];
			tmp[j]+=s;tmpsq[j]+=1ll*s*s;
		}
	}
	for (int i=1;i<=hmax;i++)ans[i]+=(1ll*tmp[i]*tmp[i]-tmpsq[i])>>1;
	nsu[0]=1;
	int u,num=0;int *st=tmpnu;
	for (u=pre[c];u && !off[u];u=pre[u]){
		off[u]=1;
		start[++num]=st;ord[num]=num;
		tmph[num]=bfs(u,st,0);
		st+=tmph[num]+1;
	}
	for (int v=pre[c];v!=u;v=pre[v])off[v]=0;
	for (int i=0;i<=hmax;i++){
		ans2[i+1]+=nsu[i];
		ans2[i+num+1]-=nsu[i];
	}
	sort(ord+1,ord+1+num,cmp);
	int tms=0;
	for (int h=1,cur=1;cur<=num;h++){
		ind++;
		while(cur<=num && tmph[ord[cur]]<h)cur++;
		for (int i=cur;i<=num;i++){
			int s=0,t;
			for (int j=h;j<=tmph[ord[i]];j+=h)s+=start[ord[i]][j];
			if(check[ord[i]%h]==ind)t=val[ord[i]%h],tms++;
			else{
				int ss=h-(ord[i]-1)%h-1;t=0;
				for (int j=ss;j<=hmax;j+=h)t+=nsu[j],tms++;
				check[ord[i]%h]=ind;
				val[ord[i]%h]=t;
			}
			ans[h]+=1ll*s*t;
		}
	}
	if(c!=rt)work(rt);
	for (int i=g[c];~i;i=e[i].next)if(!off[e[i].v])work(e[i].v);
}

int main()
{
	//freopen("gcd_sample3.in","r",stdin);
	//freopen("gcd_sample3.out","w",stdout);
	//int cl=clock();
	memset(g,-1,sizeof(g));
	scanf("%d",&n);
	for (int i=2;i<=n;i++){
		int x;scanf("%d",&x);
		h[i]=h[x]+1;pre[i]=x;
		ae(x,i);
		if(x>=i)return 0;
	}
	work(1);
	for (int i=n-1;i>=1;i--){
		for (int j=2*i;j<=n-1;j+=i)ans[i]-=ans[j];
	}
	for (int i=2;i<=n-1;i++)ans2[i]+=ans2[i-1];
	for (int i=1;i<=n-1;i++)printf("%lld\n",ans[i]+ans2[i]);
	//cl=clock()-cl;
	return 0;
}

