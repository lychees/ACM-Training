#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
struct TOb {
	double x, y;
	double r, h;
} p[1010];
double L, R;
int i, n, T;
double v1, v2, v, t, x, tt, t1, t2, t3, x1, x2, y;
double l, r, mid;
double ans, px, tim;
bool boo;
int main() {
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v, &t, &x);
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%lf%lf%lf%lf", &p[i].x, &p[i].y, &p[i].r, &p[i].h);
		tt = t;
		tt += v1 * t / (v2 - v1);
		L = x - v1 * tt;
		R = x;
		//printf("%lf %lf\n", L, R);
		for (tim = 0; tim <= tt; tim += 0.007) {
			px = x - tim * v1;
			boo = false;
			for (i = 0; i < n; i++) {
				if (boo)
					break;
				x1 = p[i].x - p[i].r;
				x2 = p[i].x + p[i].r;
				y = p[i].y - tim * v;
				//	printf("%lf %lf %lf\n", x1, x2, px);
				//printf("%lf\n", y);
				if (x1 <= px && px <= x2) {
					if (y > 0 && y * y + fabs(px - p[i].x) * fabs(px - p[i].x)
							<= p[i].r * p[i].r)
						boo = true;
					if (y < 0) {
						x1 = p[i].x + (p[i].y + p[i].h - v * tim) / p[i].h
								* p[i].r;
						x2 = p[i].x - (p[i].y + p[i].h - v * tim) / p[i].h
								* p[i].r;
						//	printf("%lf %lf %lf\n", x1, x2, px);
						if (x1 >= px && px >= x2)
							boo = true;
					}
				}
			}
			//boo=true;
			if (boo)
				ans += 0.007;
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
