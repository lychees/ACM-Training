#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;
typedef long long ll;
void wej(int &n){
	char c;while((c=getchar())<'0'||c>'9');n=c-'0';
	while((c=getchar())>='0' && c<='9')n=n*10+c-'0';
}
int k,n;
struct pkt{
	int x,y,id;
	pkt operator-(const pkt& b)const{
		return (pkt){x-b.x,y-b.y};
	}
	ll operator*(const pkt& b)const{
		return 1ll*x*b.y-1ll*y*b.x;
	}
}p[3005];
int qu[3005][3005],sz[3005],st[3005];
ll su[3005][3005];
int cmpx(const pkt&a,const pkt&b){
	if(a.x==b.x)return a.y<b.y;
	else return a.x<b.x;
}
int cmpy(const pkt&a,const pkt&b){return a.y<b.y;}
void work(){
	sort(p+1,p+1+n,cmpx);
	for (int i=1;i<=n;i++){
		int q=0;
		for (int j=1;j<i;j++){
			if(p[j].y>p[i].y)continue;
			while(q && (p[qu[i][q]]-p[i])*(p[j]-p[i])<=0)q--;
			qu[i][++q]=j;
		}
		sz[i]=q;st[i]=1;
	}
	for (int i=1;i<=n;i++){
		for (int j=i;j<=n;j++)while(st[j]<=sz[j] && p[qu[j][st[j]]].x<p[i].x)st[j]++;
		su[p[i].id][p[i].id]=0;
		for (int j=i+1;j<=n;j++){
			int pr=qu[j][st[j]];
			su[p[i].id][p[j].id]=su[p[i].id][p[pr].id]+p[j]*p[pr];
		}
	}
}
struct pyt{int x1,x2,y1,y2,id;}py[1000005];ll ans[1000005]={0};
int upp[1000005],low[1000005],lef[1000005],rig[1000005];
int cmpx1(const pyt&a,const pyt&b){return a.x1<b.x1;}
int cmpx2(const pyt&a,const pyt&b){return a.x2<b.x2;}
int cmpy1(const pyt&a,const pyt&b){return a.y1<b.y1;}
int cmpy2(const pyt&a,const pyt&b){return a.y2<b.y2;}
int seg[2222222];
int l1,r1,v,I;
void upd(int l,int r,int x){
	seg[x]=v;
	if(l!=r){
		int mid=l+r>>1;
		if(I<=mid)upd(l,mid,x<<1);
		else upd(mid+1,r,x<<1|1);
	}
}
int que(int l,int r,int x){
	if(l1<=l && r<=r1)return seg[x];
	else{
		int mid=l+r>>1,ret=0;
		if(l1<=mid)ret=max(ret,que(l,mid,x<<1));
		if(r1>mid)ret=max(ret,que(mid+1,r,x<<1|1));
		return ret;
	}
}
int tmp=0;
int tme1=0;
int main()
{

	scanf("%d%d",&k,&n);
	for (int i=1;i<=n;i++)wej(p[i].x),wej(p[i].y),p[i].id=i;
	int m;scanf("%d",&m);
	for (int i=1;i<=m;i++)wej(py[i].x1),wej(py[i].x2),wej(py[i].y1),wej(py[i].y2),py[i].id=i;
	
	
	sort(p+1,p+1+n,cmpy);
	sort(py+1,py+1+m,cmpy2);
	memset(seg,0,sizeof(seg));
	for (int i=1,cur=1;i<=m;i++){
		while(cur<=n && p[cur].y<=py[i].y2)I=p[cur].x,v=cur,upd(0,k,1),cur++;
		l1=py[i].x1,r1=py[i].x2;upp[py[i].id]=p[que(0,k,1)].id;
	}
	sort(py+1,py+1+m,cmpy1);
	memset(seg,0,sizeof(seg));
	for (int i=m,cur=n;i>=1;i--){
		while(cur>=1 && p[cur].y>=py[i].y1)I=p[cur].x,v=n-cur+1,upd(0,k,1),cur--;
		l1=py[i].x1,r1=py[i].x2;low[py[i].id]=p[n-que(0,k,1)+1].id;
	}
	sort(p+1,p+1+n,cmpx);
	sort(py+1,py+1+m,cmpx2);
	memset(seg,0,sizeof(seg));
	for (int i=1,cur=1;i<=m;i++){
		while(cur<=n && p[cur].x<=py[i].x2)I=p[cur].y,v=cur,upd(0,k,1),cur++;
		l1=py[i].y1,r1=py[i].y2;rig[py[i].id]=p[que(0,k,1)].id;
	}
	sort(py+1,py+1+m,cmpx1);
	memset(seg,0,sizeof(seg));
	for (int i=m,cur=n;i>=1;i--){
		while(cur>=1 && p[cur].x>=py[i].x1)I=p[cur].y,v=n-cur+1,upd(0,k,1),cur--;
		l1=py[i].y1,r1=py[i].y2;lef[py[i].id]=p[n-que(0,k,1)+1].id;
	}

	work();
	for (int i=1;i<=m;i++)ans[i]+=su[lef[i]][upp[i]];
	for (int i=1;i<=n;i++){
		int x=p[i].x,y=p[i].y;
		p[i].x=-y,p[i].y=x;
	}
	work();
	for (int i=1;i<=m;i++)ans[i]+=su[upp[i]][rig[i]];
	for (int i=1;i<=n;i++){
		int x=p[i].x,y=p[i].y;
		p[i].x=-y,p[i].y=x;
	}
	work();
	for (int i=1;i<=m;i++)ans[i]+=su[rig[i]][low[i]];
	for (int i=1;i<=n;i++){
		int x=p[i].x,y=p[i].y;
		p[i].x=-y,p[i].y=x;
	}
	work();
	for (int i=1;i<=m;i++)ans[i]+=su[low[i]][lef[i]];
	for (int i=1;i<=m;i++){
		printf("%lld",ans[i]>>1);
		if(ans[i]&1)printf(".5\n");
		else printf(".0\n");
	}

	return 0;
}