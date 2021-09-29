#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int L[25],v[25],e[25],f[25][25],gi[25][25],gx[25][25],gy[25][25],p[100005],q[100005];
int Case,n,m,ans,x,y,z,ox,oy,h,t; char s[2005];
int main()
{
	rep(i,21) e[i]=(1<<i)-1;
	while (ans=1<<20,m=h=t=0,scanf("%d",&n),n){
		rep(i,n){
			scanf("%s",s),v[i]=0,L[i]=strlen(s),p[++t]=i,q[t]=0,gx[i][0]=-1;
			rep(j,L[i]) v[i]=v[i]*2+s[j]-48,f[i][j]=1<<20; f[i][0]=L[i];
		}
		while (h<t){
			x=p[++h],y=q[h],z=f[x][y]; if (z>=ans) continue;
			rep(i,n){
				if (L[i]>L[x]-y){
					if ((v[i]>>L[i]-L[x]+y&e[L[x]-y])==(v[x]&e[L[x]-y]) && z+L[i]-L[x]+y<f[i][L[x]-y])
						p[++t]=i,q[t]=L[x]-y,f[i][q[t]]=z+L[i]-L[x]+y,gx[i][q[t]]=x,gy[i][q[t]]=y;
				}else if (L[i]<L[x]-y){
					if ((v[i]&e[L[i]])==(v[x]>>L[x]-y-L[i]&e[L[i]]) && z<f[x][y+L[i]])
						p[++t]=x,q[t]=y+L[i],f[x][q[t]]=z,gi[x][q[t]]=i,gx[x][q[t]]=x,gy[x][q[t]]=y;
				}else if (i!=x && (v[i]&e[L[i]])==(v[x]&e[L[i]])) ans=z,ox=x,oy=y;
			}
		}
		for (z=1;;z^=ox!=x){
			x=ox,y=oy,ox=gx[x][y],oy=gy[x][y];
//			printf("%d %d %d %d %d  %d\n",x,y,ox,oy,z,f[x][y]);
			if (z && ox!=x) rep(i,L[x]) s[++m]=(v[x]>>i&1)+48;
			if (!z && ox==x) rep(i,L[gi[x][y]]) s[++m]=(v[gi[x][y]]>>i&1)+48;
			if (!y) break;
		}
		printf("Code %d: %d bits\n",++Case,ans);
		rep(i,m){printf("%c",s[m-i]); if (i%20==19 || i+1==m) puts("");} puts("");
	}
	return 0;
}
