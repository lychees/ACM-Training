#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
#define rep(i,a,b) for (int i=a;i<=b;++i)
const int N=62,M=22,u[4]={1,0,-1,0},v[4]={0,1,0,-1};
int Case,n,a[3][N],c[3][N],t[3][N],xl[M],xr[M],yl[M],yr[M];
bool b[3][N]; string s[M]; pair<int,string> o[M];
int main()
{
	while (scanf("%d",&n),n){
		rep(i,0,2) rep(j,0,61) b[i][j]=t[i][j]=0;
		rep(k,1,n){
			cin>>s[k]>>yl[k]>>yr[k];
			rep(i,1,1) rep(j,yl[k],yr[k]) b[i][j]=1;
		}
		rep(k,1,n){
			rep(i,0,2) rep(j,0,61) c[i][j]=0;
			rep(i,1,1) rep(j,yl[k],yr[k]) c[i][j]=1000000; int flag,T=0;
			do{
				flag=0,++T;
				rep(i,1,1) rep(j,1,60) if (b[i][j]){
					int C=c[i][j]/1000;
					rep(d,0,3) if (b[i+u[d]][j+v[d]]) a[i+u[d]][j+v[d]]+=C,a[i][j]-=C;
				}
				rep(i,1,1) rep(j,1,60) if (b[i][j]){
					if (!c[i][j] && a[i][j]) t[i][j]=max(t[i][j],T);
					c[i][j]+=a[i][j],flag|=!c[i][j],a[i][j]=0;
				}
			}while (flag);
			printf("%d\n",T);
		}
		rep(k,1,n){
			int T=0;
			rep(i,1,1) rep(j,yl[k],yr[k]) T=max(T,t[i][j]);
			o[k]=make_pair(T,s[k]);
		}
		printf("%d\n",n);
		sort(o+1,o+n+1); printf("Case Number %d\n",++Case);
		rep(i,1,n) cout<<"   "<<o[i].second<<"   "<<o[i].first<<endl;
	}
	return 0;
}
