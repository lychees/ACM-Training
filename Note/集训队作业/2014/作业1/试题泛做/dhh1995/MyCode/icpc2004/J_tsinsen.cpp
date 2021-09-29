#include<cstdio>
#include<cstring>
#include<algorithm>
#include<complex>
#include<cmath>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
#define px complex<double>
#define X real
#define Y imag
#define eps 1e-5
#define R(a) scanf("%lf%lf",&dx,&dy),a=px(dx,dy)
#define P(a) printf("%.3lf %.3lf\n",X(a),Y(a))
#define N 105
px a[N],A,B,C,O,center,opt; int Case,n,m,s,flag,p[N],q[N],ans[N],cnt[N]; double r,dx,dy;
bool cmp(const px &i,const px &j){return fabs(Y(i)-Y(j))<eps?X(i)>X(j):Y(i)>Y(j);}
bool cmpid(const int &i,const int &j){return cmp(a[i],a[j]);}
bool cmpp(const int &i,const int &j){return fabs(norm(a[i]-O)-norm(a[j]-O))<eps?cmp(a[i],a[j]):norm(a[i]-O)<norm(a[j]-O);}
bool cal(px B,px C,px &A,px &O)
{
	if (fabs(Y(conj(B-A)*(C-A)))<eps) return 0; px D,E;
	D.X()=Y(B-A),D.Y()=X(A-B),E.X()=Y(C-A),E.Y()=X(A-C),B=(A+B)/2.,C=(A+C)/2.,E+=C;
	double s1=Y(conj(D)*(C-B)),s2=Y(conj(D)*(E-B)); return O=(C*s2-E*s1)/(s2-s1),1;
}
bool better(int *p,int *q,int s)
{
	rep(i,s)
		if (cmpid(p[i],q[i])) return 1;
		else if (cmpid(q[i],p[i])) return 0;
	return 0;
}
int main()
{
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,n) R(a[i]),p[i]=i,ans[i]=0; flag=1; a[n]=px(-1e18,-1e18);
		rep(i,m){
			scanf("%d",&s); R(A),R(B); rep(j,s) q[j]=n;
			if (!flag) continue; bool bo=0;
			if (s) rep(j,n) if (cal(A,B,a[j],O)){
				r=norm(O-A);
				int cnt=0; rep(k,n) if (norm(a[k]-O)<r-eps) cnt++; if (cnt>s) continue;
				cnt=0; rep(k,n) if (norm(a[k]-O)<r+eps) cnt++; if (cnt<s) continue;
				nth_element(p,p+s-1,p+n,cmpp); C=a[p[s-1]];
				if (fabs(norm(C-O)-r)<eps){
					sort(p,p+s,cmpid); bo=1;
					if (better(p,q,s)){rep(j,s) q[j]=p[j]; center=O;}
					}
				}
			O=center; sort(p,p+n,cmpp); rep(i,s) ans[p[i]]++; flag&=bo;
			}
		rep(i,m+1) cnt[i]=0; rep(i,n) cnt[ans[i]]++;
		printf("Trial %d:  ",++Case);
		if (!flag) puts("Impossible");
		else {rep(i,m+1) printf("%d  ",cnt[i]); puts("");}
		puts("");
		}
	return 0;
}
