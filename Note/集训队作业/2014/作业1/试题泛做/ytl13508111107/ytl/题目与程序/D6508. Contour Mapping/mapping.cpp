#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define N 120
using namespace std;

int s, p, d, h, he[N][N];
double get2(int a, int b, int c) {
	if(b > c) {
		swap(b, c);
	}
	if(a % h == 0 && a > b && a < c) {
		double len = (double)d / (c - b);
		len = len * (a - b);
		return sqrt(len * len + d * d - d * len);
	}
	return 0;
}
double get1(int a, int b, int c) {
	if(b > c) {
		swap(b, c);
	}
	if(b <= a && c >= a) {
		return 0;
	}
	if(b > a && c > a) {
		double l1 = (double)d / (b - a), l2 = (double)d / (c - a);
		int s = (a / h + 1) * h, t = b / h;
		if(b % h == 0) {
			t--;
		}
		t = t - (a / h + 1) + 1;
		if(t == 0) {
			return 0;
		}
		double len1 = l1 * (s - a), len2 = l2 * (s - a);
		double x1 = sqrt(len1 * len1 + len2 * len2 - len1 * len2);
		double x2 = x1 + (t - 1) * (h * l1 * x1 / len1);
		return (x1 + x2) * t / 2;
	}
	if(b < a && c < a) {
		double l1 = (double)d / (a - b), l2 = (double)d / (a - c);
		int s = (c / h + 1) * h, t = a / h;
		if(a % h == 0) {
			t--;
		}
		t = t - (c / h + 1) + 1;
		if(t == 0) {
			return 0;
		}
		double len1 = l1 * (a - s), len2 = l2 * (a - s);
		double x1 = sqrt(len1 * len1 + len2 * len2 - len1 * len2);
		double x2 = x1 - (t - 1) * (h * l1 * x1 / len1);
		return (x1 + x2) * t / 2;
	}
	return 0;
}
double work(int a, int b, int c) {
	double ans = 0;
	ans += get1(a, b, c) + get2(a, b, c);
	ans += get1(b, a, c) + get2(b, a, c);
	ans += get1(c, a, b) + get2(c, a, b);
	return ans;
}
void do_work() {
	for(int i = 1; i <= s; i++) {
		int stop = p;
		if(i % 2 == 0) {
			stop++;
		}
		for(int j = 1; j <= stop; j++) {
			scanf("%d", &he[i][j]);
		}
		he[i][0] = he[i][stop + 1] = -1;
	}
	for(int i = 0; i <= p + 1; i++) {
		he[0][i] = he[s + 1][i] = -1;
	}
	double ans = 0;
	for(int i = 2; i <= s; i++) {
		if(i % 2 == 0) {
			for(int j = 1; j <= p; j++) {
				ans += work(he[i][j], he[i][j + 1], he[i - 1][j]);
			}
			for(int j = 2; j <= p; j++) {
				ans += work(he[i][j], he[i - 1][j], he[i - 1][j - 1]);
			}
			for(int j = 1; j <= p; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i - 1][j] && (he[i][j] != he[i][j + 1] || he[i][j] != he[i - 1][j - 1])) {
					ans += d;
				}
			for(int j = 2; j <= p + 1; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i - 1][j - 1] && (he[i][j] != he[i][j - 1] || he[i][j] != he[i - 1][j])) {
					ans += d;
				}
		} else {
			for(int j = 1; j <= p; j++) {
				ans += work(he[i][j], he[i - 1][j], he[i - 1][j + 1]);
			}
			for(int j = 1; j < p; j++) {
				ans += work(he[i][j], he[i][j + 1], he[i - 1][j + 1]);
			}
			for(int j = 1; j <= p; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i - 1][j + 1] && (he[i][j] != he[i][j + 1] || he[i][j] != he[i - 1][j])) {
					ans += d;
				}
			for(int j = 1; j <= p; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i - 1][j] && (he[i][j] != he[i][j - 1] || he[i][j] != he[i - 1][j + 1])) {
					ans += d;
				}
		}
	}
	for(int i = 1; i <= s; i++) {
		if(i % 2 == 0) {
			for(int j = 1; j <= p; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i][j + 1] && (he[i][j] != he[i - 1][j] || he[i][j] != he[i + 1][j])) {
					ans += d;
				}
		} else {
			for(int j = 1; j < p; j++)
				if(he[i][j] % h == 0 && he[i][j] == he[i][j + 1] && (he[i][j] != he[i - 1][j + 1] || he[i][j] != he[i + 1][j + 1])) {
					ans += d;
				}
		}
	}
	printf("%.0lf\n", ans);
}
int main() {
    freopen("mapping.in","r",stdin);
    freopen("mapping.out","w",stdout);
	int T = 0;
	while(scanf("%d%d%d%d", &s, &p, &d, &h) != EOF) {
		if(s == 0) {
			return 0;
		}
		T++;
		do_work();
	}
	return 0;
}
