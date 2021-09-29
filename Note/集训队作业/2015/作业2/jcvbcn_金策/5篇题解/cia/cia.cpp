#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<iostream>
#define inf 1000000000000000000ll
using namespace std;
typedef long long ll;
int n;
struct col{
	int id[6];ll a[6];int rev,i;
}t[100005];
int tmp[6];ll val[6];
void rev(int i){
	for (int j=1;j<=2;j++)swap(t[i].id[j],t[i].id[6-j]),swap(t[i].a[j],t[i].a[6-j]);
	for (int j=1;j<=5;j++)t[i].a[j]*=-1;t[i].rev*=-1;
}	
int cmp(int i,int j){
	return val[i]<val[j];
}
ll ans=inf;
int ansarr[100005],tmpl[100005];
ll rr[6]={0};
void work1(int j){
	memset(rr,0,sizeof(rr));
	for (int i=1;i<=n;i++){
		if(t[i].id[5]==j)rev(i);
		if(t[i].id[1]==j){
			rr[j]+=t[i].a[2]-t[i].a[1];
			for (int k=2;k<=5;k++)rr[t[i].id[k]]+=t[i].a[k]-t[i].a[2];
		}else{
			int l;
			for (int k=1;k<=5;k++)if(t[i].id[k]==j){l=k;break;}
			tmpl[i]=l;
			for (int k=1;k<=5;k++)rr[t[i].id[k]]+=abs(t[i].a[k]-t[i].a[l]);
		}
	}
	ll a=rr[j],b=0;
	for (int i=1;i<=5;i++)if(i!=j && rr[i]>b)b=rr[i];
	ll mi,x;
	if(b>=a)mi=b,x=0;
	else mi=(a+b+1)>>1,x=mi-b;
	if(mi<ans){
		ans=mi;
		for (int i=1;i<=n;i++){
			if(t[i].id[1]!=j)
				ansarr[i]=t[i].a[tmpl[i]]*t[i].rev;
			else{
				int del=min(x,t[i].a[2]-t[i].a[1]);
				x-=del;
				ansarr[i]=t[i].rev*(t[i].a[2]-del);
			}
		}
	}
}
ll c[6]={0},r[6]={0};
ll r1[6]={0};
ll x[6]={0};

ll f(int j,int l,ll t,int upd=0){
	ll su=0;
	if(upd)x[l]=t;
	for (int k=1;k<=5;k++)if(k!=j && k!=l){
		ll tmp=min(r[k],t-max(0ll,(c[k]-c[l]+1)/2));
		su+=tmp;
		if(upd)x[k]=tmp;
	}
	ll r2=(c[l]-c[j])/2;
	if(su>r2){
		ll lef=su-r2;
		su=r2;
		if(upd){
			for (int k=1;k<=5;k++)if(k!=j && k!=l){
				ll del=min(lef,x[k]);
				lef-=del;
				x[k]-=del;
			}
		}
	}
	return t-su;
}
ll mi;
ll solve(int j){
	ll lef=0,rig=0,suu=0,mid;
	for (int k=1;k<=5;k++)if(k!=j)suu+=r[k];
	rig=suu;
	while(lef<=rig){
		mid=lef+rig>>1;
		int bo=1;
		for (int k=1;k<=5;k++)if(k!=j){
			r1[k]=min(r[k],mid-max(0ll,(c[k]-c[j]+1)/2));
			if(r1[k]<0){
				bo=0;
				break;
			}
		}
		if(bo==0){
			lef=mid+1;
			continue;
		}
		ll su=0;
		for (int k=1;k<=5;k++)if(k!=j)su+=r1[k];
		if(su>=mid)rig=mid-1;
		else lef=mid+1;
	}
	if(lef<=suu){
		if(lef+c[j]<mi){
			for (int k=1;k<=5;k++)if(k!=j)
				r1[k]=min(r[k],lef-max(0ll,(c[k]-c[j]+1)/2));			
			mi=lef+c[j];
			for (int k=1;k<=5;k++)if(k!=j){
				ll del=min(lef,r1[k]);
				x[k]=del;
				lef-=del;
			}
		}
	}
	for (int l=1;l<=5;l++)if(l!=j){
		if(c[l]-c[j]<0)continue;
		ll rig=r[l],lef=-inf,mid;
		for (int k=1;k<=5;k++)if(k!=l && k!=j)lef=max(lef,max(0ll,(c[k]-c[l]+1)/2));
		if(lef>rig)continue;
		rig--;
		while(lef<=rig){
			mid=lef+rig>>1;
			ll dx=f(j,l,mid+1)-f(j,l,mid);
			if(dx>0)rig=mid-1;
			else lef=mid+1;
		}
		ll tmp=c[l]+f(j,l,lef);
		if(tmp<mi){
			mi=tmp;
			f(j,l,lef,1);
		}
	}
	return mi;
}
void work2(int j){
	mi=inf;
	memset(c,0,sizeof(c));
	memset(r,0,sizeof(r));
	memset(r1,0,sizeof(r1));
	memset(x,0,sizeof(x));
	for (int i=1;i<=n;i++){
		if(t[i].id[5]==j || t[i].id[4]==j)rev(i);
		if(t[i].id[3]==j){
			for (int k=1;k<=5;k++)c[t[i].id[k]]+=abs(t[i].a[k]-t[i].a[3]);
		}else{
			int l=t[i].id[1]+t[i].id[2]-j;
			r[l]+=t[i].a[3]-t[i].a[2];
			c[t[i].id[1]]+=t[i].a[2]-t[i].a[1];
			for (int k=3;k<=5;k++)c[t[i].id[k]]+=t[i].a[k]-t[i].a[2];
		}
	}
	solve(j);
	if(mi<ans){
			for (int i=1;i<=n;i++){
				if(t[i].id[3]==j){
					ansarr[i]=t[i].rev*t[i].a[3];
				}else{
					int l=t[i].id[1]+t[i].id[2]-j;
					ll del=min(x[l],t[i].a[3]-t[i].a[2]);
					x[l]-=del;
					ansarr[i]=t[i].rev*(t[i].a[2]+del);
				}
			}
			ans=mi;
	}
}
int bo[6];

void work3(){
	memset(r,0,sizeof(r));
	memset(c,0,sizeof(c));
	int isu=0;for (int i=1;i<=5;i++)isu+=bo[i]*i;
	for (int i=1;i<=n;i++){
		if(bo[t[i].id[4]] && bo[t[i].id[5]])rev(i);
		if(bo[t[i].id[1]] && bo[t[i].id[2]]){
			int l=isu-t[i].id[1]-t[i].id[2];
			r[l]+=t[i].a[3]-t[i].a[2];			
		}
		for (int k=1;k<=5;k++)c[t[i].id[k]]+=abs(t[i].a[k]-t[i].a[3]);		
	}
	ll cc=-inf;
	for (int i=1;i<=5;i++)if(!bo[i])cc=max(cc,c[i]);
	
	int j;for (int k=1;k<=5;k++)if(!bo[k]){j=k;break;}
	int l;for (int k=5;k>=1;k--)if(!bo[k]){l=k;break;}
	r[l]=0;c[l]=c[j]=cc;
	mi=inf;
	solve(j);
	if(mi<ans){
			for (int i=1;i<=n;i++){
				ll del;
				if(bo[t[i].id[1]] && bo[t[i].id[2]]){
					int l=isu-t[i].id[1]-t[i].id[2];
					del=min(x[l],t[i].a[3]-t[i].a[2]);
					x[l]-=del;		
				}else del=0;
				ansarr[i]=t[i].rev*(t[i].a[3]-del);				
			}
			ans=mi;
	}	
}	
int main()
{
	int k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=k;i++)
		for (int j=1;j<=n;j++){
			int x;scanf("%d",&x);
			t[j].a[i]=x;
		}
	for (int i=k+1;i<=5;i++)
		for (int j=1;j<=n;j++){
			t[j].a[i]=t[j].a[i-1];
		}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=5;j++)tmp[j]=j,val[j]=t[i].a[j];
		sort(tmp+1,tmp+5+1,cmp);
		for (int j=1;j<=5;j++){
			t[i].id[j]=tmp[j];
			t[i].a[j]=val[tmp[j]];
		}
		t[i].rev=1;t[i].i=i;
	}
	for (int i=1;i<=5;i++){
		work1(i);
		work2(i);
	}
	for (int i=1;i<=5;i++)
		for (int j=i+1;j<=5;j++)
			for (int k=j+1;k<=5;k++){
				memset(bo,0,sizeof(bo));
				bo[i]=bo[j]=bo[k]=1;
				work3();
			}
	for (int i=1;i<=n;i++){
		if(i>1)putchar(' ');
		printf("%d",ansarr[i]);
	}
	return 0;
}
	
	