#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
int id[1<<22],V[205][100005],Q[205][100005],T[205],b[25],e[25],Case,n,m,h,w,o,*p,*q,*u,*v;
char G[205][100005],a[25][15],*f,*g;
void upd(int u,int s,char f)
{
	int &t=T[w];
	if (id[s]<0) g[t]=f,q[t]=s,v[t]=u,id[s]=t++;
	else if (f>g[id[s]]) g[id[s]]=f,v[id[s]]=u;
}
bool check(int s){rep(i,m+1) if ((s>>i+i&3)>1) return 0; return (s>>m+m+2)==3;}
int main()
{
	rep(i,1<<22) id[i]=-1;
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,n) scanf("%s",a[i]); G[0][0]=0,Q[0][0]=3,*T=1;
		rep(i,n){
			rep(j,m){
				w=i*m+j,f=G[w],p=Q[w],u=V[w],h=T[w],g=G[++w],q=Q[w],v=V[w]; T[w]=0;
				rep(k,h){
					int d=j+j,s=p[k],F=f[k],x=s>>d&3,z=s>>d+2&3,y=s>>d+4&3; e[*e=1]=1;
					for (int c=0;c<=m+m+2;c+=2){
						if ((s>>c&3)==2) e[++*e]=c;
						if ((s>>c&3)==3) b[c]=e[(*e)--],b[b[c]]=c;
					}
					s^=x+z*4<<d;
					if (a[i][j]=='.' && x!=1 && y!=1){
						if (!x && !y){if (z!=1) upd(k,s^14<<d,F+1);}
						else if (!x) upd(k,s^y+4<<d,F+1),upd(k,s^y*4+1<<d,F+1);
						else if (!y) upd(k,s^x+4<<d,F+1),upd(k,s^x*4+1<<d,F+1);
						else if (x==3 && y==2) upd(k,s^5<<d,F+1);
						else if (x==2 && y==2) upd(k,s^5<<d^1<<b[d+4],F+1);
						else if (x==3 && y==3) upd(k,s^5<<d^1<<b[d],F+1);
					}
					if (x+y<2 || x==1 && y==1 && z) upd(k,s,F);
				}
				rep(k,T[w]) id[q[k]]=-1;
			}
			w=i*m+m,f=G[w],p=Q[w],u=V[w]; int &h=T[w]; g=G[++w],q=Q[w],v=V[w]; T[w]=0;
			rep(k,h) if ((p[k]>>m+m&3)<2) upd(u[k],(p[k]<<4)&((1<<m+m+4)-1),f[k]);
			h=0; rep(k,T[w]) id[q[k]]=-1,f[h]=g[k],p[h]=q[k],u[h++]=v[k];
		}
		w=n*m,o=-1; rep(i,T[w]) if (check(Q[w][i]) && (o<0 || G[w][i]>G[w][o])) o=i;
		while (w--){if (G[w+1][o]>G[w][V[w+1][o]]) a[w/m][w%m]='C'; o=V[w+1][o];}
		printf("Case %d:\n",++Case); rep(i,n) puts(a[i]); puts("");
	}
	return 0;
}
