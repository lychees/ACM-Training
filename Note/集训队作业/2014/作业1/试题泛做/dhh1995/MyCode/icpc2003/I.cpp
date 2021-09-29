#include<cstdio>
#include<cmath>
int Case,a1,b1,t1,a2,b2,t; long double pi=acos(-1.),eps=1e-15;
int main()
{
	freopen("solar.in","r",stdin);
	freopen("solar.out","w",stdout);
	while (scanf("%d%d%d%d%d%d",&a1,&b1,&t1,&a2,&b2,&t),a1||b1||t1||a2||b2||t){
		long double F=sqrt(1.*a2*a2-1.*b2*b2),t2=sqrt(1.*a2/a1*a2/a1*a2/a1*t1*t1);
		long double p=t/t2-int(t/t2),l=0,r=2*pi,m;
		while (l+eps<r){
			m=(l+r)/2;
			if (m-F*sin(m)/a2<p*2*pi) l=m; else r=m;
			}
		printf("Solar System %d: %.3lf %.3lf\n",++Case,double(cos(l)*a2),double(sin(l)*b2));
		}
	return 0;
}
