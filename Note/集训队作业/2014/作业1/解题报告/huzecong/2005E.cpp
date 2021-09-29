//ACM/ICPC World Finals 2005 E Lots of Sunlight
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

//05:37 to 18:17, 45600 seconds
#define N 100
const double PI = 3.1415926535897932384626433832795;
int n, w, h, m[N + 1], d[N + 1];
struct point {
	int x, y;
	point() {}
	point(int _x, int _y) : x(_x), y(_y) {}
} ;

inline int cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

inline double len(const point &a) {
	return sqrt((double)a.x * a.x + (double)a.y * a.y);
}

inline void print(int x) {
	int h = 5 + x / 3600;
	int m = 37 + (x % 3600) / 60;
	int s = x % 60;
	if (m >= 60) m -= 60, ++h;
	printf("%02d:%02d:%02d", h, m, s);
}

int main(int argc, char* argv[]) {
#ifdef KANARI
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	
	int Case = 0;
	while (scanf("%d", &n), n != 0) {
		scanf("%d%d", &w, &h);
		scanf("%d", m + 1);
		for (int i = 2; i <= n; ++i) scanf("%d%d", d + i, m + i);
		for (int i = 1; i <= n; ++i) d[i] += d[i - 1] + w;
		printf("Apartment Complex: %d\n", ++Case);
		
		int num;
		while (scanf("%d", &num), num != 0) {
			printf("Apartment %d: ", num);
			int build = num % 100, floor = num / 100;
			if (build > n || build < 1 || floor < 1 || floor > m[build]) {
				printf("Does not exist\n");
				continue;
			}
			
			int x = d[build] - w, y = h * (floor - 1);
			point left = point(-1, 0);
			for (int i = 1; i < build; ++i) {
				point cur = point(d[i] - x, m[i] * h - y);
				if (cross(left, cur) < 0) left = cur;
			}
			point right = point(1, 0);
			for (int i = build + 1; i <= n; ++i) {
				point cur = point(d[i] - x - 2 * w, m[i] * h - y);
				if (cross(cur, right) < 0) right = cur;
			}
			
			int l = (int)(asin((double)abs(cross(point(-1, 0), left)) / len(left)) * 45600.0 / PI);
			int r = 45600 - (int)ceil(asin((double)abs(cross(point(1, 0), right)) / len(right)) * 45600.0 / PI);
			
			print(l);
			printf(" - ");
			print(r);
			printf("\n");
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

