#include<cstdio>
#define rep(i,n) for (int i=0;i<n;++i)
long long f[1005][8][2]; int n,Case;
long long work(int n,int m)
{
	rep(i,n+1) rep(j,7) rep(k,2) f[i][j][k]=0; f[0][!m][m]=1;
	rep(i,n) rep(j,7){f[i+1][j+1][0]+=f[i][j][0]+f[i][j][1]; if (j) f[i+1][j-1][1]+=f[i][j][0];}
	return f[n][5][0]*!m+f[n][5][1];
}
int main()
{
	while (scanf("%d",&n),n) printf("Case %d: %lld\n",++Case,n&1?0:(work(n,0)-work(n-1,1)));
	return 0;
}
