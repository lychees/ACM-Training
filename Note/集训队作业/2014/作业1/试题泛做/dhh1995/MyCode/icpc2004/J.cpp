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
px a[N],A,B,C,O,center,opt; int Case,n,m,s,flag,p[N],ans[N],cnt[N]; double r,rr,dx,dy;
bool cmp(const px &i,const px &j){return fabs(Y(i)-Y(j))<eps?X(i)>X(j):Y(i)>Y(j);}
bool cmpp(const int &i,const int &j){return fabs(norm(a[i]-O)-norm(a[j]-O))<eps?cmp(a[i],a[j]):norm(a[i]-O)<norm(a[j]-O);}
bool cal(px B,px C,px &A,px &O)
{
	if (fabs(Y(conj(B-A)*(C-A)))<eps) return 0; px D,E;
	D.X()=Y(B-A),D.Y()=X(A-B),E.X()=Y(C-A),E.Y()=X(A-C),B=(A+B)/2.,C=(A+C)/2.,E+=C;
	double s1=Y(conj(D)*(C-B)),s2=Y(conj(D)*(E-B)); return O=(C*s2-E*s1)/(s2-s1),1;
}
int main()
{
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	while (scanf("%d%d",&n,&m),n||m){
		rep(i,n) R(a[i]),p[i]=i,ans[i]=0; flag=1;
		rep(i,m){
			scanf("%d",&s),opt=px(-1e18,-1e18),rr=1e18; R(A),R(B);
			if (!flag) continue; bool bo=0;
			rep(j,n) if (cal(A,B,a[j],O)){
				r=norm(O-A); if (r>rr) continue;
				int cnt=0; rep(k,n) if (norm(a[k]-O)<r-eps) cnt++; if (cnt>s) continue;
				cnt=0; rep(k,n) if (norm(a[k]-O)<r+eps) cnt++; if (cnt<s) continue;
				nth_element(p,p+s,p+n,cmpp);
				if (!s){if (norm(a[p[0]]-O)>r-eps) bo=1; continue;}
				nth_element(p,p+s-1,p+s,cmpp); C=a[p[s-1]];
				if (norm(C-O)<r+eps && norm(a[p[s]]-O)>r-eps){
					rep(k,s) if (cmp(a[p[k]],C)) C=a[p[k]]; bo=1;
					if (r<rr || fabs(r-rr)<eps && cmp(C,opt)) rr=r,opt=C,center=O;
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
