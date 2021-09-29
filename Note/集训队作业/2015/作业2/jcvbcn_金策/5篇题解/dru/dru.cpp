#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#define N 1048576
#define mo 1000000007
using namespace std;
int n;
void gn(int &x){
	char c;while((c=getchar())<'0'||c>'9');x=c-'0';
	while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';
}
struct data{
	int a,v;
	inline data operator+(const data&b)const{
		if(b.a==a)return (data){a,v+b.v>=mo?v+b.v-mo:v+b.v};
		else if(b.a>a)return b;
		else return (data){a,v};
	}
	inline void operator+=(const data&b){
		if(b.a==a){
			v+=b.v;if(v>=mo)v-=mo;
		}else if(b.a>a) a=b.a,v=b.v;
	}
	inline data operator+(int x)const{
		if(v)return (data){x+a,v};
		else return (data){0,0};
	}
	inline data operator*(int x)const{
		if(x==1)return (data){a,v};
		return (data){a,1ll*v*x%mo};
	}
};
int c[N],d[N];
int sma[2*N];
data dp[N],seg[2*N],tag[2*N];
int lef[N],rig[N],qu[N];
int l1,r1;data v;
void buildma(int x,int l,int r){
	if(l==r)sma[x]=l;
	else{
		int mid=l+r>>1;
		buildma(x<<1,l,mid);
		buildma(x<<1|1,mid+1,r);
		sma[x]=sma[x<<1|(c[sma[x<<1]]<c[sma[x<<1|1]])];
	}
}
int qmax(int x,int l,int r){
	if(l1<=l && r<=r1)return sma[x];
	else{
		int ma=0,t,mid=l+r>>1;
		if(l1<=mid)t=qmax(x<<1,l,mid),ma=c[t]>c[ma]?t:ma;
		if(r1>mid)t=qmax(x<<1|1,mid+1,r),ma=c[t]>c[ma]?t:ma;
		return ma;
	}
}
void query(int x,int l,int r){
	if(l1<=l && r<=r1)v+=seg[x];
	else{
		v+=tag[x]*(min(r,r1)-max(l,l1)+1);
		int mid=l+r>>1;
		if(l1<=mid)query(x<<1,l,mid);
		if(r1>mid)query(x<<1|1,mid+1,r);
	}
}
void cover(int x,int l,int r){
	if(l1<=l && r<=r1)seg[x]+=v*(r-l+1),tag[x]+=v;
	else{
		seg[x]+=v*(min(r,r1)-max(l,l1)+1);
		int mid=l+r>>1;
		if(l1<=mid)cover(x<<1,l,mid);
		if(r1>mid)cover(x<<1|1,mid+1,r);
	}
}
void init(){
	buildma(1,1,n);
	int p=0,q=0;
	for (int i=1,j=0;i<=n;i++){
		while(j+1<=n)
			if((j+1-i+1)<=min(d[j+1],p==q?N:d[qu[p]])){
				lef[++j]=i;
				while(p!=q && d[j]<d[qu[q-1]])q--;
				qu[q++]=j;
			}else break;
		rig[i]=j;
		if(qu[p]==i)p++;
	}
}
struct stack{int i,j,k,p;}st[N];int top=0;
void calc(int q){
	int i=st[q].i,j=st[q].j;
	if(st[q].p==0){
		st[q].p++;
		l1=i,r1=j;st[q].k=qmax(1,1,n);
		if(i<=st[q].k-1)st[++top]=(stack){i,st[q].k-1,0,0};
	}else if(st[q].p==1){
		st[q].p++;
		int k=st[q].k,x=c[k];
		int l=max(k,i+x-1),prelef=max(lef[l],i);
		l1=max(i,lef[l])-1,r1=l-x-1,v=(data){0,0};if(l1<=r1)query(1,0,n);v=v+1;
		for(int up=min(k+x,j+1);l<up;l++){
			if(lef[l]<=i || lef[l]==prelef){
				if(l-x+1>=lef[l] && l-x+1>=i)v+=(dp[l-x]+1);
			}else{
				l1=lef[l]-1;r1=l-x;v=(data){0,0};if(l1<=r1)query(1,0,n);v=v+1;
				prelef=lef[l];
			}
			dp[l]+=v;
		}
		if(k+x<=j){
			if(j-k<k-i)
				for (;l<=j;l++){
					if(lef[l]>i && lef[l]!=prelef){
						l1=lef[l]-1;r1=k-1;v=(data){0,0};if(l1<=r1)query(1,0,n);v=v+1;
						prelef=lef[l];
					}
					dp[l]+=v;
				}
			else{
				v=(data){0,0};
				for (l=i;l<=k;l++){
					if(rig[l]<k+x)continue;
					if(l>i && min(j,rig[l])!=min(j,rig[l-1])){
						l1=k+x,r1=min(j,rig[l-1]),v=v+1;if(l1<=r1)cover(1,0,n);
						v=dp[l-1];
					}else v+=dp[l-1];
				}
				l1=k+x,r1=min(rig[k],j),v=v+1;if(l1<=r1)cover(1,0,n);
			}
		}
		l1=r1=k,v=dp[k];cover(1,0,n);
		v=(data){0,0};query(1,0,n);dp[k]=v;
		if(k+1<=j)st[++top]=(stack){k+1,j,0,0};
	}else top--;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)gn(c[i]),gn(d[i]);
	init();
	dp[0]=(data){0,1};
	st[top=1]=(stack){1,n,0,0};
	while(top) calc(top);
	if(dp[n].a==0)printf("NIE\n");
	else printf("%d %d\n",dp[n].a,dp[n].v);
	return 0;
}
