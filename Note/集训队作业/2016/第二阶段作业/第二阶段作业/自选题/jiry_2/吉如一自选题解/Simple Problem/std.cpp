#pragma comment(linker, "/STACK:25600000,25600000")
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct bian{
	int next,point;
}b[210000];
struct tree{
	int ma0,ma1,tot,rev,a0,a1,size;
}t[510000];
int p[110000],len,d[110000],father[1100000],n,size[110000],where[110000],l[110000],dfs[110000],sign,now,x[110000];
const int lim=1e9;
void ade(int k1,int k2){
	b[++len].next=p[k1]; b[len].point=k2; p[k1]=len;
}
void add(int k1,int k2){
	ade(k1,k2); ade(k2,k1);
}
void dfs1(int k1,int k2){
	size[k1]=1; d[k1]=d[k2]+1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2) {dfs1(j,k1); size[k1]+=size[j];}
	}
}
void dfs2(int k1,int k2){
//	cout<<k1<<" "<<k2<<endl;
	dfs[k1]=++sign; int k=0; x[sign]=k1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2&&size[j]>size[k]) k=j;
	}
	if (k==0) return;
	where[k]=where[k1]; dfs2(k,k1);
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2&&j!=k){
			l[++now]=j; where[j]=now; dfs2(j,k1);
		}
	}
}
void buildtree(int k1,int k2,int k3){
	t[k1].ma0=0; t[k1].ma1=0; t[k1].tot=0; t[k1].rev=0; t[k1].a0=0; t[k1].a1=0; t[k1].size=k3-k2+1;
	if (k2==k3){
		if (d[x[k2]]&1) t[k1].ma0=-1;
		else t[k1].ma1=-1;
		return;
	}
	int mid=k2+k3>>1;
	buildtree(k1*2,k2,mid); buildtree(k1*2+1,mid+1,k3);
}
void add0(int k1,int k2){
	t[k1].a0+=k2; /*t[k1].mi0+=k2;*/ if (t[k1].ma0!=-1) t[k1].ma0+=k2;
}
void add1(int k1,int k2){
	t[k1].a1+=k2; /*t[k1].mi1+=k2;*/ if (t[k1].ma1!=-1) t[k1].ma1+=k2;
}
void reverse(int k1){
	t[k1].rev^=1; t[k1].tot=t[k1].size-t[k1].tot;
}
void pushdown(int k1){
	if (t[k1].a0!=0){
		add0(k1*2,t[k1].a0); add0(k1*2+1,t[k1].a0); t[k1].a0=0;
	}
	if (t[k1].a1!=0){
		add1(k1*2,t[k1].a1); add1(k1*2+1,t[k1].a1); t[k1].a1=0;
	}
	if (t[k1].rev){
		reverse(k1*2); reverse(k1*2+1); t[k1].rev=0;
	}
}
void change(int k1){
	t[k1].tot=t[k1*2].tot+t[k1*2+1].tot;
//	t[k1].mi0=min(t[k1*2].mi0,t[k1*2+1].mi0);
	t[k1].ma0=max(t[k1*2].ma0,t[k1*2+1].ma0);
//	t[k1].mi1=min(t[k1*2].mi1,t[k1*2+1].mi1);
	t[k1].ma1=max(t[k1*2].ma1,t[k1*2+1].ma1);
}
int find0(int k1,int k2,int k3,int k4,int k5){
	if (k2>k5||k3<k4) return 0;
//	cout<<"find0 "<<k1<<" "<<k2<<" "<<k3<<" "<<k4<<" "<<k5<<" "<<t[k1].ma0<<" "<<t[k1].ma1<<endl;
	if (abs(t[k1].ma0)==1&&(t[k1].ma1==0||t[k1].ma1<0)) return max(k2,k4);
	if (k2==k3) return 0;
	pushdown(k1);
	int mid=k2+k3>>1; int k6=find0(k1*2+1,mid+1,k3,k4,k5);
	if (k6==mid+1||mid>=k5){
		int k7=find0(k1*2,k2,mid,k4,k5); if (k7) return k7; return k6;
	} return k6;
}
int find1(int k1,int k2,int k3,int k4,int k5){
	if (k2>k5||k3<k4) return 0;
//	cout<<"find1 "<<k1<<" "<<k2<<" "<<k3<<" "<<k4<<" "<<k5<<" "<<t[k1].ma0<<" "<<t[k1].ma1<<endl;
	if (abs(t[k1].ma1)==1&&(t[k1].ma0==0||t[k1].ma0<0)) return max(k2,k4);
	if (k2==k3) return 0;
	pushdown(k1);
	int mid=k2+k3>>1; int k6=find1(k1*2+1,mid+1,k3,k4,k5);
	if (k6==mid+1||mid>=k5){
		int k7=find1(k1*2,k2,mid,k4,k5); if (k7) return k7; return k6;
	} return k6;
}
void reverse(int k1,int k2,int k3,int k4,int k5){
	if (k2>k5||k3<k4) return;
//	cout<<"reverse "<<k1<<" "<<k2<<" "<<k3<<endl;
	if (k2>=k4&&k3<=k5){reverse(k1); return;}
	int mid=k2+k3>>1; pushdown(k1);
	reverse(k1*2,k2,mid,k4,k5);
	reverse(k1*2+1,mid+1,k3,k4,k5);
	change(k1);
}
void addall0(int k1,int k2,int k3,int k4,int k5,int k6){
	if (k2>k5||k3<k4) return;
	if (k2>=k4&&k3<=k5){add0(k1,k6); return;}
	int mid=k2+k3>>1; pushdown(k1);
	addall0(k1*2,k2,mid,k4,k5,k6);
	addall0(k1*2+1,mid+1,k3,k4,k5,k6);
	change(k1);
}
void addall1(int k1,int k2,int k3,int k4,int k5,int k6){
	if (k2>k5||k3<k4) return;
	if (k2>=k4&&k3<=k5){add1(k1,k6); return;}
	int mid=k2+k3>>1; pushdown(k1);
	addall1(k1*2,k2,mid,k4,k5,k6);
	addall1(k1*2+1,mid+1,k3,k4,k5,k6);
	change(k1);
}
void change0(int k){
	k=father[k];
	while (k){
		//cout<<"now "<<k<<endl;
		int k1=find0(1,1,n,dfs[l[where[k]]],dfs[k]);
		int flag=0; if (k1!=0) reverse(1,1,n,k1,dfs[k]);
		if (k1==0){flag=1; k1=dfs[k];} else if (k1!=dfs[l[where[k]]]) {flag=1; k1--;}
		addall1(1,1,n,k1,dfs[k],1); //cout<<"change "<<k1<<" "<<dfs[k]<<endl;
		addall0(1,1,n,k1,dfs[k],-1); if (flag) return;
		k=father[l[where[k]]];
	}
}
void change1(int k){
	k=father[k];// cout<<"solve "<<k<<endl;
	while (k){
		//cout<<"now "<<k<<endl;
		int k1=find1(1,1,n,dfs[l[where[k]]],dfs[k]);
		int flag=0; if (k1!=0) reverse(1,1,n,k1,dfs[k]); 
		if (k1==0){flag=1; k1=dfs[k];} else if (k1!=dfs[l[where[k]]]) {flag=1; k1--;}
		addall0(1,1,n,k1,dfs[k],1); //cout<<"change "<<k1<<" "<<dfs[k]<<endl;
		addall1(1,1,n,k1,dfs[k],-1); if (flag) return;
		k=father[l[where[k]]];
	}
}
void solve(){
	for (int i=1;i<=n;i++){
		p[i]=0; father[i]=0; d[i]=0; dfs[i]=0; where[i]=0; l[i]=0; size[i]=0;
	}
	len=0;
	for (int i=2;i<=n;i++){
		scanf("%d",&father[i]); father[i]++; add(father[i],i);
	}
	dfs1(1,0); now=1; l[1]=1; where[1]=1; sign=0; dfs2(1,0);
//	for (int i=1;i<=n;i++) cout<<dfs[i]<<" "<<where[i]<<" "<<l[i]<<" "<<d[i]<<endl;
	buildtree(1,1,n);
	for (int i=2;i<=n;i++){
	//	cout<<"solve "<<i<<" "<<d[i]<<endl;
		if (d[i]&1) change1(i);  else change0(i); 
	//	cout<<"fin "<<i<<endl;
		printf("%d\n",i-t[1].tot);
	}
//	cout<<"fin"<<endl;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	while (scanf("%d",&n)!=EOF) solve();
	return 0;
}
