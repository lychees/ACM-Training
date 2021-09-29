#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int Case,n,a[8],ans,res,Time; bool b[8],u[155]; char t[8]; double R;
int L,Lm,Lh,LM,LH; char s[15],m[15],h[15],M[15],H[15];
bool find(double R){int A=int(R+.5); if (R-A>1e-8 || A>120) return 0; return u[A];}
string get(int Lm,char *m,int Lh,char *h)
{
	string t="";
	rep(i,Lm) if (m[i]!='-' && m[i]!='*') t+=m[i];
	rep(i,Lh) if (h[i]!='-' && h[i]!='*') t+=h[i];
	return t;
}
void update(int y,int z)
{
	if (y<ans || z<res || get(Lm,m,Lh,h)<get(LM,M,LH,H))
		ans=y,res=z,LM=Lm,LH=Lh,memcpy(M,m,sizeof(M)),memcpy(H,h,sizeof(H));
}
void dfs(int xm,double Rm,int xh,double Rh,int y,int z)
{
	if (y>ans || y==ans && z>res) return;
	int cost=0,flagm=(Lm<2 || m[Lm-2]=='-') && fabs(Rm-24)<1e-8,flagh=(Lh<2 || h[Lh-2]=='-') && fabs(Rh-2)<1e-8;
	if (flagm && flagh){update(y,z); return;}
	if (Rm<0) if (find(-Rm*xm/24)) ++cost; else cost+=2+(Lm>1 && m[Lm-2]!='-'); else if (!flagm) cost+=2;
	if (Rh<0) if (find(-Rh*xh/2)) ++cost; else cost+=2+(Lh>1 && h[Lh-2]!='-'); else if (!flagh) cost+=2;
	if (z+cost>n) return;
	rep(i,n) if (!b[i]){
		b[i]=1;
		if (flagm){
			if (Lh<2 || h[Lh-1]=='-' || h[Lh-2]=='-')
				h[Lh++]=t[i],dfs(xm,Rm,a[i],Rh,y,z+1),--Lh;
			if (Lh>1 && (Lh<5 || h[Lh-2]!='-' || h[Lh-4]!='-'))
				h[Lh++]='-',h[Lh++]=t[i],dfs(xm,Rm,a[i],-Rh*xh/a[i],y+1,z+1),Lh-=2;
		}else{
			if (Lm<2 || m[Lm-1]=='-' || m[Lm-2]=='-')
				m[Lm++]=t[i],dfs(a[i],Rm,xh,Rh,y,z+1),--Lm;
			if (Lm>1 && (Lm<5 || m[Lm-2]!='-' || m[Lm-4]!='-'))
				m[Lm++]='-',m[Lm++]=t[i],dfs(a[i],-Rm*xm/a[i],xh,Rh,y+1,z+1),Lm-=2;
		}
		b[i]=0;
	}
}
void dfs(int x,double R,int y,int z)
{
	if (y>ans || y==ans && z>res) return;
	int flagm=fabs(R-24)<1e-8,flagh=fabs(R-2)<1e-8,cost=0;
	if (R<0) if (find(-R*x/24) || find(-R*x/2)) ++cost; else cost+=2+(L>1 && s[L-2]!='-');
	else if (!flagm || !flagh) cost+=2;
	if (z+cost>n) return; Lm=Lh=L,memcpy(m,s,sizeof(m)),memcpy(h,s,sizeof(h)),dfs(x,R,x,R,y,z);
	if (flagm || flagh) return;
	rep(i,n) if (!b[i]){
		b[i]=1;
		if (L<2 || s[L-1]=='-' || s[L-2]=='-') s[L++]=t[i],dfs(a[i],R,y,z+1),--L;
		if (L>1 && (L<5 || s[L-2]!='-' || s[L-4]!='-'))
			s[L++]='-',s[L++]=t[i],dfs(a[i],-R*x/a[i],y+1,z+1),L-=2;
		b[i]=0;
	}
}
int main()
{
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	*u=1;
	while (scanf("%d",&n)!=EOF && n){
		scanf("%lf",&R); rep(i,n) scanf("%*c%c%d",t+i,a+i),u[a[i]]=1;
		ans=8,L=1,*s='*',dfs(0,R,0,0),M[LM]=H[LH]='\0';
		if (Case) puts(""); printf("Trial %d",++Case);
		if (ans>=8) puts(" IS IMPOSSIBLE");
		else printf("\nMinutes: %s\nHours:   %s\n",M,H);
		rep(i,n) u[a[i]]=0;
	}
	return 0;
}
