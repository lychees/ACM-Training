#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<iostream>
#define MAX 222222 
using namespace std;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
struct edge{int u,v,w;}e[MAX];
int n,m,q;

int fa[MAX],g[MAX]={0},bo[MAX]={0};
int gf(int x){return x==fa[x]?x:fa[x]=gf(fa[x]);}
int fa2[MAX*2];
int gf2(int x){return x==fa2[x]?x:fa2[x]=gf2(fa2[x]);}
void un(int x,int y,int C){
	x=gf(x);y=gf(y);fa[x]=y;
	g[y]=gcd(gcd(g[y],g[x]),C);
}
int un2(int x,int y,int C){
	if(C){
		if(gf2(x)==gf2(y))return 0;
		fa2[gf2(x)]=gf2(y+n);
		fa2[gf2(y)]=gf2(x+n);
	}else{
		if(gf2(x)==gf2(y+n))return 0;
		fa2[gf2(x)]=gf2(y);
		fa2[gf2(x+n)]=gf2(y+n);
	}
	return 1;
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n;i++)fa[i]=i,fa2[i]=i,fa2[i+n]=i+n;
	for (int i=1;i<=m;i++){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		if(rand()&1)swap(x,y);
		un(x,y,w);		
		e[i]=(edge){x,y,w};
	}
	for (int i=1;i<=m;i++){
		int t=g[gf(e[i].u)];t=t&-t;
		int ret=un2(e[i].u,e[i].v,e[i].w&t);
		if(!ret)bo[gf(e[i].u)]=1;
	}
	while(q--){
		int x,y,mo;scanf("%d%d%d",&x,&y,&mo);
		if(gf(x)!=gf(y)){
			printf("NIE\n");
		}else{
			int d=gcd(g[gf(x)],mo);
			if((mo/d)&1)printf("0\n");
			else{
				int t=g[gf(x)]/d;
				if(bo[gf(x)])printf("0\n");
				else{
					if(gf2(x)==gf2(y))printf("0\n");
					else printf("%d\n",d);
				}
			}
		}
	}
	return 0;
}
				
				
	
