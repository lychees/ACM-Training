#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;

const ll inf=ll(1e18);

const int N=105,M=255;

struct node;
struct edge{
	node *ed;
	edge *next;
	ll cap,cost;
} E[M<<1],*newE=E;
struct node{
	edge *son,*pre;
	ll dist;
	bool inq;
	int cnt;
} V[N],*newV=V;

void addedge(node *u,node *v,ll cap,ll cost){
	*newE=(edge){v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){u,v->son,0,-cost},v->son=newE++;
}

ll maxcostflow(){
	ll ans=0;
	while(true){
		static node* q[N];
		int head=0,tail=0;
		for(node *u=V;u<newV;u++){
			u->dist=0;
			u->inq=true;
			q[tail++]=u;
			u->cnt=0;
		}
		node *x=NULL;
		while(head!=tail){
			node *u=q[head]; if(++head==N) head=0; u->inq=false;
			for(edge *e=u->son;e;e=e->next) if(e->cap){
				node *v=e->ed;
				if(u->dist+e->cost>v->dist){
					v->dist=u->dist+e->cost;
					v->pre=e;
					if(!v->inq){
						v->inq=true;
						q[tail]=v;
						if(++tail==N) tail=0;
						if(++v->cnt>=(newV-V)){
							x=v;
							goto out;
						}
					}
				}
			}
		}
		out:;
		if(x==NULL) break;
		while(head!=tail){
			q[head]->inq=false;
			if(++head==N) head=0;
		}
		for(;!x->inq;x=E[(x->pre-E)^1].ed){
			x->inq=true;
		}
		node *u=x;
		ll cap=inf;
		do{
			cap=min(cap,u->pre->cap);
			u=E[(u->pre-E)^1].ed;
		} while(u!=x);
		do{
			ans+=cap*u->pre->cost;
			u->pre->cap-=cap;
			E[(u->pre-E)^1].cap+=cap;
			u=E[(u->pre-E)^1].ed;
		} while(u!=x);
	}
	return ans;
}

struct Farmville{
	int minTime(vector <string> s, vector <int> time, vector <int> cost, int budget){
		int l=-1,r=1250;
		newV=V+2*(1+s.size());
		while(r-l>1){
			int lambda=(l+r)/2;
			for(node *u=V;u<newV;u++) u->son=NULL;
			newE=E;
			for(int i=0;i<s.size();i++)
				for(int j=0;j<s[i].size();j++)
					if(s[i][j]=='1'){
						addedge(&V[(j+1)*2+1],&V[(i+1)*2],inf,0);
					}
			for(int i=0;i<s.size();i++) if(V[(i+1)*2].son==NULL){
				addedge(&V[1],&V[(i+1)*2],inf,0);
			}
			for(int i=0;i<s.size();i++) if(V[(i+1)*2+1].son==NULL){
				addedge(&V[(i+1)*2+1],&V[0],inf,0);
			}
			for(int i=0;i<s.size();i++){
				addedge(&V[(i+1)*2],&V[(i+1)*2+1],inf,0);
			}
			for(int i=0;i<s.size();i++){
				addedge(&V[(i+1)*2],&V[(i+1)*2+1],cost[i],time[i]);
			}
			addedge(&V[0],&V[1],inf,-lambda);
			ll ans=maxcostflow();
			if(ans<=budget)
				r=lambda;
			else
				l=lambda;
		}
		return r;
	}
};
