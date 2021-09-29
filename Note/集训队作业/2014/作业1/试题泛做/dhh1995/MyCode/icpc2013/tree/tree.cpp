#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const string out[3]={"Pre","In","Post"};
string a[4]; int n,t[8],c[8],p[255],q[255]; char rt;
struct str{
	int m,l,r; str(){} str(int _m,int _l,int _r):m(_m),l(_l),r(_r){}
	void trans(int ls,bool side){//ls=left size,side=0 -> left
		if (m==0) ++l,side?l+=ls:r=l+ls;
		else if (m==2) --r,side?l+=ls:r=l+ls;
			else side?l+=ls+1:r=l+ls;
		m=t[2*m+side];
	}
	bool operator <(const str &A) const{return m==A.m?l==A.l?r<A.r:l<A.l:m<A.m;}
	bool operator ==(const str &A) const{return m==A.m && l==A.l && r==A.r;}
	void prt(){printf("%d %d %d ",m,l,r);}
};
struct sta{
	str f[3];
	sta(str f0,str f1,str f2){f[0]=f0,f[1]=f1,f[2]=f2;}
	sta split(int ls,bool side){sta A=*this; rep(i,3) A.f[i].trans(ls,side); return A;}
	char Root(){rep(i,3) if (f[i].m!=1) return f[i].m?a[i][f[i].r-1]:a[i][f[i].l]; return '~';}
	bool vaild(char rt){
		rep(i,3) if (f[i].m!=1) if (f[i].m?a[i][f[i].r-1]!=rt:a[i][f[i].l]!=rt) return 0;
		int size=f[0].r-f[0].l;
		rep(i,size){
			char now=a[0][f[0].l+i];
			if (p[now]<f[1].l || p[now]>=f[1].r || q[now]<f[2].l || q[now]>=f[2].r) return 0;
		}
		return 1;
	}
	bool operator <(const sta &A) const{
		return f[0]==A.f[0]?f[1]==A.f[1]?f[2]<A.f[2]:f[1]<A.f[1]:f[0]<A.f[0];
	}
	void prt(){rep(i,3){f[i].prt(); printf("%s",i<2?" ":"\n");} }
};
struct seq{
	string g[3]; seq(){} void init(){rep(i,3) g[i]="~";}
	seq(string g0,string g1,string g2){g[0]=g0,g[1]=g1,g[2]=g2;}
	bool operator <(const seq &A) const{rep(i,3) if (g[i]!=A.g[i]) return g[i]<A.g[i]; return 0;}
	void prt(){rep(i,3) cout<<g[i]<<endl;}
};
seq merge(const seq &L,const seq &R,char rt)
{return seq(rt+L.g[0]+R.g[0],L.g[1]+rt+R.g[1],L.g[2]+R.g[2]+rt);}
map<sta,seq> H;
bool dfs(sta s,seq &ans)
{
	if (s.f[0].l==s.f[0].r) return ans=seq("","",""),1;
	map<sta,seq> ::iterator it=H.find(s); ans.init();
	if (it!=H.end()){ans=it->second; return ans.g[0]!="~";}
	char rt=s.Root(); if (!s.vaild(rt)) return H[s]=ans,0;
	int size=s.f[0].r-s.f[0].l; seq left,right;
	if (size==1){
		if (rt=='~') rt=a[0][s.f[0].l]; string tmp=""; tmp+=rt;
		return H[s]=ans=seq(tmp,tmp,tmp),1;
	}
	rep(i,size) if (dfs(s.split(i,0),left) && dfs(s.split(i,1),right))
		ans=min(ans,merge(left,right,rt=='~'?a[0][s.f[0].l+i]:rt));	
	H[s]=ans; return ans.g[0]!="~";
}
void work(int x)
{
	if (x==6){
		seq ans; H.clear();
		if (dfs(sta(str(0,0,n),str(1,0,n),str(2,0,n)),ans)){
			rep(i,6){cout<<out[t[i]]; if (i<5) cout<<" "; else cout<<endl;} ans.prt();
			}
		return;
		}
	rep(i,3) if (c[i]<2) t[x]=i,++c[i],work(x+1),--c[i];
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	while (cin>>a[0]>>a[1]>>a[2]){n=a[0].size(); rep(i,n) p[a[1][i]]=i,q[a[2][i]]=i; work(0);}
	return 0;
}
