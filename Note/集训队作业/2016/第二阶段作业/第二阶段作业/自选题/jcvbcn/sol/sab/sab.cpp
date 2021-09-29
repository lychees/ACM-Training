#include "sabotaz.h"
#include "message.h"
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
ll n,M;
struct edge{
	int v,next;
}e[7000005];int etot;int g[222222];
void ae(int u,int v){
	e[etot].v=v;e[etot].next=g[u];g[u]=etot++;
}

int dfn[222222],low[222222],id[222222];int ind,bcctot;
int stk[222222],inst[222222];int top;


void initgraph(){
	etot=0;ind=0;top=0;bcctot=0;
	for (int i=0;i<n;i++)g[i]=-1,dfn[i]=0;
}
void dfs(int u,int pr=-1){
	dfn[u]=low[u]=++ind;
	inst[u]=1;stk[++top]=u;
	for (int i=g[u];~i;i=e[i].next)if(i!=pr){
		if(!dfn[e[i].v]){
			dfs(e[i].v,i^1);			
			low[u]=min(low[u],low[e[i].v]);
		}else if(inst[e[i].v])low[u]=min(low[u],dfn[e[i].v]);
	}
	if(dfn[u]==low[u]){
		bcctot++;
		while(stk[top]!=u){
			inst[stk[top]]=0;
			id[stk[top--]]=bcctot;
		}
		inst[stk[top]]=0;
		id[stk[top--]]=bcctot;
	}
}
void tarjan(){
	for (int i=0;i<n;i++)if(!dfn[i])dfs(i);
}

int lu[555555],lv[555555];int ne;

int fir[222222],las[222222];
void outedges(){
	ne=0;
	for (int i=1;i<=bcctot;i++)las[i]=fir[i]=-1;
	for (int u=0;u<n;u++){
		if(fir[id[u]]==-1){
			fir[id[u]]=las[id[u]]=u;
		}else{
			lu[++ne]=u;
			lv[ne]=las[id[u]];
			las[id[u]]=u;
		}
		for (int i=g[u];~i;i=e[i].next)if(e[i].v>u){
			if(id[u]!=id[e[i].v]){
				lu[++ne]=u;
				lv[ne]=e[i].v;
			}
		}
	}
	for (int i=1;i<=bcctot;i++)if(las[i]!=fir[i]){
		lu[++ne]=las[i];
		lv[ne]=fir[i];
	}
}
		
int lis[105];int ltot;
int tmplis[105];int tmptot;
int main() {
	n=NumberOfIsles();
	M = NumberOfBridges();
	int totnd=NumberOfNodes();
	initgraph();
	ll bg=1ll*MyNodeId()*M/totnd,ed=1ll*(MyNodeId()+1)*M/totnd;
	for (ll i=bg;i<ed;i++){
		int u= BridgeEndA(i);
		int v= BridgeEndB(i);
		if(u!=v){
			ae(u,v);
			ae(v,u);
			//cout<<MyNodeId() << "has "<<u<<" "<<v<<endl;
		}
	}

	ltot=0;
	for (int i=0;i<NumberOfNodes();i++)lis[++ltot]=i;
	while(ltot>1){
		for (int i=1;i<ltot;i+=2)if(MyNodeId()==lis[i]){
			tarjan();
			outedges();
			//cout<<MyNodeId() << "send to "<<lis[i] <<" "<< ne<<" edges"<<endl;
			for (int k=1;k<=ne;k+=400){
				int ed=min(ne,k+400-1);
				PutInt(lis[i+1],ed-k+1);
				for (int j=k;j<=ed;j++)
					PutInt(lis[i+1],lu[j]),PutInt(lis[i+1],lv[j]);
				Send(lis[i+1]);
			}
			PutInt(lis[i+1],0);
			Send(lis[i+1]);
		}
		tmptot=0;
		for (int i=2;i<=ltot;i+=2)tmplis[++tmptot]=lis[i];
		for (int i=2;i<=ltot;i+=2)if(MyNodeId()==lis[i]){
			while(1){
				Receive(lis[i-1]);
				int t=GetInt(lis[i-1]);
				if(t==0)break;
				while(t--){
					int u=GetInt(lis[i-1]),v=GetInt(lis[i-1]);
					ae(u,v);
					ae(v,u);
				//	cout<<MyNodeId() << "receive "<<u<<" "<<v<<endl;
				}
			}
		}
		if(ltot%2==1)tmplis[++tmptot]=lis[ltot];
		for (int i=1;i<=tmptot;i++)lis[i]=tmplis[i];
		ltot=tmptot;
	}
	if (MyNodeId() == lis[1]) { 
		tarjan();
		int nu=0;
		for (int u=0;u<n;u++){
			for (int i=g[u];~i;i=e[i].next)if(e[i].v>u){
				if(id[u]!=id[e[i].v]){
					nu++;
				}
			}
		}
		cout << nu << endl;
	}
	return 0;
}
