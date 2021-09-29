#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<iostream>
#define int64 long long
#define sqr(x) (x)*(x)
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rep(i,x,y) for(int i=(x);i<=(y);++i)
#define VI vector<int>
#define VI64 vector<int64>
#define VS vector<string>
#define PII pair<int,int>
#define PDD pair<double,double>
#define VPII vector< PII >
#define SZ(x) ((int)(x).size())
#define N 210000
using namespace std;
unsigned int read[N][4],W[N],P[N];
int n;
struct seg_tree{
	int maxx[N*4],pos[N*4],key[N*4];
	
	int calc(int p,int start){
		if(start>=maxx[p])return 0;
		if(key[p]==1)return 1;
		if(start>=maxx[p*2])return calc(p*2+1,start);
		return calc(p*2,start)+key[p]-key[p*2];
	}
	void renew(int p){
		maxx[p]=maxx[p*2]; pos[p]=pos[p*2];
		if(maxx[p*2+1]>maxx[p]){
			maxx[p]=maxx[p*2+1];
			pos[p]=pos[p*2+1];
		}
		key[p]=key[p*2]+calc(p*2+1,maxx[p*2]);
	}
	PII Getmax(int p,int l,int r,int x,int y){
		if(x<=l && y>=r)return mk(maxx[p],pos[p]);
		int mid=(l+r)/2;
		PII ans=mk(-100,-100);
		if(x<=mid)ans=max(ans,Getmax(p*2,l,mid,x,y));
		if(y>mid)ans=max(ans,Getmax(p*2+1,mid+1,r,x,y));
		return ans;
	}
	void insert(int p,int l,int r,int x,int y){
		if(l==r){
			pos[p]=l;
			maxx[p]=y;
			key[p]=1;
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)insert(p*2,l,mid,x,y);
		else insert(p*2+1,mid+1,r,x,y);
		renew(p);
	}
	void del(int p,int l,int r,int x){
		if(l==r){
			pos[p]=0;
			maxx[p]=0;
			key[p]=0;
			return;
		}
		int mid=(l+r)/2;
		if(x<=mid)del(p*2,l,mid,x);
		else del(p*2+1,mid+1,r,x);
		renew(p);
	}
	int query(int p,int l,int r,int x,int y,int &start){
		if(x<=l && y>=r){
			int ans=calc(p,start);
			start=max(start,maxx[p]);
			return ans;
		}
		int mid=(l+r)/2,ans=0;
		if(x<=mid)ans+=query(p*2,l,mid,x,y,start);
		if(y>mid)ans+=query(p*2+1,mid+1,r,x,y,start);
		return ans;
	}
}Left,Right;
int Getans(int x){
	int start=0,ans=0;
	ans+=Left.query(1,1,n,n-x+1,n,start);
	start=0;
	ans+=Right.query(1,1,n,x,n,start);
	return ans-2;
}
int Find(unsigned int *a,unsigned int b){
	return lower_bound(a+1,a+n+1,b)-a;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%u",&read[i][0]);
		int u=(read[i][0]==1?1:2);
		rep(j,1,u)scanf("%u",&read[i][j]);
		P[i]=read[i][1];
		W[i]=read[i][2];
	}
	sort(P+1,P+n+1);
	sort(W+1,W+n+1);
	rep(i,1,n){
		if(read[i][0]==0){
			int x=Find(P,read[i][1]),
				y=Find(W,read[i][2]);
			Left.insert(1,1,n,n-x+1,y);
			Right.insert(1,1,n,x,y);
		}
		if(read[i][0]==1){
			int x=Find(P,read[i][1]);
			Left.del(1,1,n,n-x+1);
			Right.del(1,1,n,x);
		}
		if(read[i][0]==2){
			int x=Find(P,read[i][1]),
				y=Find(P,read[i][2]);
			if(x>y)swap(x,y);
			int lca=Right.Getmax(1,1,n,x,y).se;
			printf("%d\n",Getans(x)+Getans(y)-2*Getans(lca));
		}
	}
}
