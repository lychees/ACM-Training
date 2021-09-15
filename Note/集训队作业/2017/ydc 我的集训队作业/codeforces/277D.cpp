#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1010
#define maxm 1600
#define eps 1e-10
using namespace std;
typedef long double ld;
int dcmp(ld p)
{
	if(abs(p)<eps)
		return 0;
	return p>eps?1:-1;
}
struct Prob
{
	int scoreA,scoreB;
	int TimeA,TimeB;
	ld fst;
	void Read()
	{
		cin>>scoreA>>scoreB>>TimeA>>TimeB>>fst;
	}
	friend bool operator < (const Prob &a,const Prob &b)
	{
		return a.TimeB*(1-a.fst)*b.fst+(a.TimeB+b.TimeB)*(1-b.fst)<b.TimeB*(1-b.fst)*a.fst+(a.TimeB+b.TimeB)*(1-a.fst);
	}
}p[maxn];
int n,T;
void read()
{
	scanf("%d %d",&n,&T);
	for(int i=1;i<=n;++i)
		p[i].Read();
	sort(p+1,p+n+1);
}
void Dp()
{
	static ld f[maxn][maxm],g[maxn][maxm];
	ld ans1=0,ans2=1e100;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=T;++j)
		{
			f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
			if(j>=p[i].TimeA)
			{
				ld cost=f[i-1][j-p[i].TimeA]+p[i].scoreA;
				if(dcmp(f[i][j]-cost)<0)
					f[i][j]=f[i-1][j-p[i].TimeA]+p[i].scoreA,g[i][j]=g[i-1][j-p[i].TimeA]+p[i].TimeA;
				else if(!dcmp(f[i][j]-cost))
					g[i][j]=min(g[i][j],g[i-1][j-p[i].TimeA]+p[i].TimeA);
			}
			if(j>=p[i].TimeA+p[i].TimeB)
			{
				ld cost=f[i-1][j-p[i].TimeA-p[i].TimeB]+p[i].scoreA+p[i].scoreB*(1-p[i].fst);
				if(dcmp(f[i][j]-cost)<0)
				{
					f[i][j]=f[i-1][j-p[i].TimeA-p[i].TimeB]+p[i].scoreA+p[i].scoreB*(1-p[i].fst);
					g[i][j]=(g[i-1][j-p[i].TimeA-p[i].TimeB]+p[i].TimeA)*p[i].fst+j*(1-p[i].fst);
				}
				else if(!dcmp(f[i][j]-cost))
					g[i][j]=min(g[i][j],(p[i].TimeA+g[i-1][j-p[i].TimeA-p[i].TimeB])*p[i].fst+j*(1-p[i].fst));
			}
			if(dcmp(ans1-f[i][j])<0)
				ans1=f[i][j],ans2=g[i][j];
			else if(!dcmp(ans1-f[i][j]))
				ans2=min(ans2,g[i][j]);
		}
	printf("%.20f %.20f\n",(double)ans1,(double)ans2);
}
int main()
{
	freopen("input.txt","r",stdin);
	read();
	Dp();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
