#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int L[25],v[25],e[25],p[100005],q[100005];
int Case,n,m,x,y,h,t; string s[25],f[25][25],z,tmp,ans;
bool small(string a,string b){return b.size()?a.size()==b.size()?a<b:a.size()<b.size():1;}
int main()
{
	rep(i,21) e[i]=(1<<i)-1;
	while (ans="",h=t=0,cin>>n,n){
		rep(i,n){
			cin>>s[i],v[i]=0,L[i]=s[i].size(),p[++t]=i,q[t]=0;
			rep(j,L[i]) v[i]=v[i]*2+s[i][j]-48,f[i][j]=""; f[i][0]=s[i];
		}
		while (h<t){
			x=p[++h],y=q[h],z=f[x][y]; if (!small(z,ans)) continue;
			rep(i,n){
				if (L[i]>L[x]-y){
					tmp=s[i].substr(L[x]-y);
					if ((v[i]>>L[i]-L[x]+y&e[L[x]-y])==(v[x]&e[L[x]-y]) && small(z+tmp,f[i][L[x]-y]))
						p[++t]=i,q[t]=L[x]-y,f[i][q[t]]=z+tmp;
				}else if (L[i]<L[x]-y){
					if (v[i]==(v[x]>>L[x]-y-L[i]&e[L[i]]) && small(z,f[x][y+L[i]]))
						p[++t]=x,q[t]=y+L[i],f[x][q[t]]=z;
				}else if (i!=x && v[i]==(v[x]&e[L[i]])) ans=z;
			}
		}
		printf("Code %d: %d bits\n",++Case,m=ans.size());
		rep(i,m){printf("%c",ans[i]); if (i%20==19 || i+1==m) puts("");} puts("");
	}
	return 0;
}
