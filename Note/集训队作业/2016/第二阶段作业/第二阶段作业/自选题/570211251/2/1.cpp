/* This is sample grader for the contestant */
#include "worldline.h"
#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define rep(i,a,n) for(int i=(a);i<=(n);++i)
#define dep(i,a,n) for(int i=(a);i>=(n);--i)
typedef pair<int,int> pii;
#ifdef LOCAL
#include <stdio.h>
#include <assert.h>

#define maxN 20010

static int t,flag,tot_query,tot_addedge,father[maxN],height[maxN];
static int A[maxN],ans[maxN],turn,step,n;

void next_step(){
	if (step!=1) flag=1; step++;
}

int findfather(int k){
	if (father[k]==k) return k;
	father[k]=findfather(father[k]);
	return father[k];
}

void addedge(int u,int v){
	if (step!=1) flag=0; tot_addedge++;
	if (u<0||u>n||v<0||v>n) return;
	u=findfather(u); v=findfather(v);
	if (u!=v){
		if (height[u]<height[v]){
			int t=u; u=v; v=t;
		}
		father[v]=u; if (height[u]==height[v]) height[u]++;
	}
}

void new_round(){
	if (turn==2||step!=2) flag=1;
	turn++; step=1;
	for (int i=1;i<=n+n;i++) father[i]=i,height[i]=1;
	rep(i,1,n)father[i]=n+A[i];
}

int query(int u,int v){
	if (step!=2) flag=0; tot_query++;
	if (u<0||u>n||v<0||v>n) return 0;
	u+=n;v+=n;
	u=findfather(u); v=findfather(v);
	return u==v;
}
#endif






#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define rep(i,a,n) for(int i=(a);i<=(n);++i)
#define dep(i,a,n) for(int i=(a);i>=(n);--i)
typedef pair<int,int> pii;
const int N=111111,M=111111;
vector<int>p1[N],p2[N];
pii pt[N];
int lst[N],tot,t1[N],t2[N],res[N],to[N];
set<pii>S;
int query_permutation(int n,int ans[]){
	if(n==1){ans[1]=1;return 1;}
	if(n==2)return 0;
	rep(i,1,n){
		pt[i]=mp(pt[i-1].X,pt[i-1].Y+1);
		if(pt[i].Y>pt[i].X)pt[i].X++,pt[i].Y=1;
	}
	int tmp=pt[n].Y,flag=pt[n].Y==pt[n].X-1,bj;
	if(flag){rep(i,1,n)if(pt[i]==mp(pt[n].X,1))pt[i].Y=pt[i].X,bj=i;}
	else pt[n].Y=pt[n].X;
	rep(i,1,n)to[pt[i].X*300+pt[i].Y]=i;
	rep(i,1,n)p1[i].clear(),p2[i].clear(),lst[i]=res[i]=0;
	new_round();
	rep(i,1,n){if(lst[pt[i].X])addedge(lst[pt[i].X],i);lst[pt[i].X]=i;}
	next_step();
	tot=0;S.clear();
	rep(i,1,n){
		int bo=0;
		for(auto x:S){if(query(p1[x.Y][0],i)){p1[x.Y].pb(i),t1[i]=x.Y;bo=1;break;}}
		if(bo){S.erase(mp(-(p1[t1[i]].size()-1),t1[i]));S.insert(mp(-p1[t1[i]].size(),t1[i]));continue;}
		p1[++tot].pb(i),t1[i]=tot;
		S.insert(mp(-1,t1[i]));
	}
	new_round();
	rep(i,1,n)lst[i]=0;
	rep(i,1,n){if(lst[pt[i].Y])addedge(lst[pt[i].Y],i);lst[pt[i].Y]=i;}
	next_step();
	tot=0;S.clear();
	rep(i,1,n){
		int bo=0;
		rep(j,1,tot)if(query(p2[j][0],i)){p2[j].pb(i),t2[i]=j;bo=1;break;}
		if(bo){S.erase(mp(-(p2[t2[i]].size()-1),t2[i]));S.insert(mp(-p2[t2[i]].size(),t2[i]));continue;}
		p2[++tot].pb(i),t2[i]=tot;
		S.insert(mp(-1,t2[i]));
	}
	if(flag){
		rep(i,1,n)if(p2[t2[i]].size()==1)ans[bj]=i;
		for(int x:p1[t1[p2[t2[ans[bj]]][0]]])if(x!=ans[bj])ans[pt[n].X-p2[t2[x]].size()+(n-tmp+1)]=x;
		rep(i,1,n)if(ans[i])p1[t1[ans[i]]].pop_back(),p2[t2[ans[i]]].pop_back(),res[ans[i]]=i;
		rep(i,1,n)if(!res[i])ans[to[p1[t1[i]].size()*300+pt[n].X-p2[t2[i]].size()]]=i;
	}else{
		rep(i,1,n)if(p2[t2[i]].size()==1&&p1[t1[p2[t2[i]][0]]].size()==tmp)ans[n]=i;
		for(int x:p1[t1[p2[t2[ans[n]]][0]]])if(x!=ans[n])ans[pt[n].X-p2[t2[x]].size()+(n-tmp+1)]=x;
		rep(i,1,n)if(ans[i])p1[t1[ans[i]]].pop_back(),p2[t2[ans[i]]].pop_back(),res[ans[i]]=i;
		rep(i,1,n)if(!res[i])ans[to[p1[t1[i]].size()*300+pt[n].X-p2[t2[i]].size()]]=i;
	}
	return 1;
}







#ifdef LOCAL
int main()
{
	t=10;
	rep(_,9990,10000){
		n=_;//n=10000;
		rep(i,1,n)A[i]=i;random_shuffle(A+1,A+1+n);
		printf("n=%d:",n);
		//scanf("%d",&n);
		//for (int i=1;i<=n;i++) scanf("%d",&A[i]);
		for (int i=1;i<=n;i++) ans[i]=0;
		flag=1; tot_query=0; tot_addedge=0; turn=0; step=0;
		int res=query_permutation(n,ans);
		rep(i,1,n)if(A[i]!=ans[i])flag=0;
		if(flag==1||n==2&&res==0){printf("OK %d\n",tot_query);continue;}
		else puts("");
		printf("%d %d %d %d\n",flag,res,tot_query,tot_addedge);
		if (res==0){
			for (int i=1;i<=n;i++) printf("? "); printf("\n");
		} else {
			for (int i=1;i<=n;i++) printf("%d ",ans[i]); printf("\n");
			for (int i=1;i<=n;i++) printf("%d ",A[i]); printf("\n");
		}
	}
	return 0;
}
#endif
