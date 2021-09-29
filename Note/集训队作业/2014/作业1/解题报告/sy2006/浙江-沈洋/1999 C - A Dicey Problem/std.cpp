#include <cstdio>
#define pack(x, y, z) ((x)<<9)|((y)<<5)|(z)
#define unpack(cur) x=cur>>9, y=(cur>>5)&15, z=cur&31 
using namespace std;

const int N = 12;
const int dx[4] = {-1,0,1,0}, dy[4] = {0,1,0,-1};
const int tr[24][4] = {
	{16, 9, 6,15},//0
	{12,17,10, 7},//1
	{ 4,13,18,11},//2
	{ 8, 5,14,19},//3
	{20,12, 2, 8},//4
	{ 9,21,13, 3},//5
	{ 0,10,22,14},//6
	{15, 1,11,23},//7
	{23, 4, 3,16},//8
	{17,20, 5, 0},//9
	{ 1,18,21, 6},//10
	{ 7, 2,19,22},//11
	{21,16, 1, 4},//12
	{ 5,22,17, 2},//13
	{ 3, 6,23,18},//14
	{19, 0, 7,20},//15
	{22, 8, 0,12},//16
	{13,23, 9, 1},//17
	{ 2,14,20,10},//18
	{11, 3,15,21},//19
	{18,15, 4, 9},//20
	{10,19,12, 5},//21
	{ 6,11,16,13},//22
	{14, 7, 8,17} //23
};
//order: U R D L
int n, m, x0, y0, T, F, a[N][N];
int fr[6000], l[6000], v[N][N];
int GetSta(int T, int F) {
	--T, --F;
	for (int j=0; j<4; ++j) {
		if (tr[(T<<2)|j][0]>>2 == F)
			return (T<<2)|j; 
	}
}
void bfs(int sta) {
	int ls=0, le=0, x, y, z, tx, ty, ts;
	l[0] = sta;
	for (; ls<=le && !v[x0][y0]; ++ls) {
		unpack(l[ls]);
		for (int j=0; j<4; ++j) {
			tx = x + dx[j], ty = y + dy[j];
			if (a[tx][ty]==-1 || a[tx][ty]-1==(z>>2)) {
				ts = pack(tx, ty, tr[z][j]);
				if (!fr[ts])
					l[++le] = v[tx][ty] = ts,
					fr[ts] = l[ls];
			}
		}
	}
	if (v[x0][y0]) {
		le = 0;
		for (int i=fr[v[x0][y0]]; i!=sta; i=fr[i])
			l[++le] = i;
		l[++le] = sta;
		int cnt = 0;
		for (int i=le; i; --i) {
			unpack(l[i]);
			printf("(%d,%d),", x, y);
			if (!(++cnt % 9)) puts("");
		}
		printf("(%d,%d)\n", x0, y0);
	} else
		puts("No Solution Possible");
}
void run() {
	scanf("%d%d%d%d%d%d", &n, &m, &x0, &y0, &T, &F);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=m; ++j)
			scanf("%d", &a[i][j]);
	bfs(pack(x0, y0, GetSta(T, F)));
}
int main() {
	run();
	return 0;
}
