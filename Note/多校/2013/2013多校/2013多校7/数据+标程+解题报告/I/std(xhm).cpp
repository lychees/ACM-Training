#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
#include<map>
#include<string>
#include<vector>
#include<set>

using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)
#define Cor(i,l,r) for (int i = l; i >= r; --i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define FI first
#define SE second
#define MP make_pair
#define PII pair<int,int>
#define flt double
#define INF (0x3f3f3f3f)
#define MaxN 1020304
#define MaxNode 1020304
#define MD 1000000007

int v[MaxN],next[MaxN],h[MaxN],tot = 0; 
void add(int b,int e) {
	v[++tot] = e; next[tot] = h[b]; h[b] = tot;
	v[++tot] = b; next[tot] = h[e]; h[e] = tot;
}

int dfn[MaxN],low[MaxN],instack[MaxN],stack[MaxN],top,dd,cnt,clr[MaxN];
void tarjan(int i,int fa) { //cerr << i << endl;
	//if (dd > 100000) cerr << dd << endl;
	if (dd == 102211) {
		int z = dd;
	}
	dfn[i] = low[i] = ++dd; instack[stack[++top] = i] = true;
	for (int z = h[i]; z; z = next[z]) if (z != fa) {
		if (!dfn[v[z]]) {
			tarjan(v[z],(z & 1) ? (z + 1) : (z - 1));
			low[i] = min(low[i],low[v[z]]);
		} else if (instack[v[z]]) low[i] = min(low[i],dfn[v[z]]);
	}
	if (dfn[i] == low[i]) {
		++cnt;
		while (instack[i]) {
			clr[stack[top]] = cnt;
			instack[stack[top--]] = false ;
		}
	}
}

int fa[MaxN][21],d[MaxN]; PII fap[MaxN];
int oa,ob,crop; bool ans,cro;
int lca(int x,int y) {
	bool fl = false; 
	if (d[x] > d[y]) fl = true, swap(x,y); int ty = y;
	Cor(i,20,0) if (d[fa[y][i]] > d[x]) y = fa[y][i];
	if (fa[y][0] == x) {
		oa = fap[y].SE; ob = fap[ty].FI;
		if (fl) swap(oa,ob);
		return x;
	}
	oa = fap[x].FI, ob = fap[ty].FI; if (d[y] > d[x]) y = fa[y][0]; if (fl) swap(oa,ob);
	Cor(i,20,0) if (fa[y][i] != fa[x][i]) y = fa[y][i], x = fa[x][i];
	cro = fap[x].SE == fap[y].SE; crop = fap[x].SE;
	return fa[x][0];
}

PII E[MaxN];
int n,m,Q,q[MaxN],vis[MaxN]; int cache[MaxN],Tot = 0;
int main() {
	int CNT = 0;
	while (cin >> n >> m) {
		Fill(h,tot = 0);
		For(i,1,m) {
				int b,e;
			scanf("%d%d",&b,&e); 
			//if (TTT == 10) cerr << b << ' ' << e << endl;
			add(b,e); //s[b].insert(e); s[e].insert(b);
		}
		Fill(dfn,dd =  0); Fill(instack,top = 0); cnt = 0; Fill(clr,0);
		tarjan(1,0);
		Fill(fa,0);
		int hd = 0, tl = 1; Fill(vis,0); vis[q[1] = 1] = true; d[clr[1]] = 1; 
		while (hd < tl) {
			int vex = q[++hd];
			for (int z = h[vex]; z; z = next[z]) if (!vis[v[z]]) {
				if (clr[v[z]] != clr[vex]) {
					fa[clr[v[z]]][0] = clr[vex]; fap[clr[v[z]]] = MP(v[z],vex);
					d[clr[v[z]]] = d[clr[vex]] + 1;
				}
				vis[q[++tl] = v[z]] = true;
			}
		}
		For(i,1,20) For(j,1,cnt) fa[j][i] = fa[fa[j][i - 1]][i - 1];
		cin >> Q;
		//if (dd == n) {
		//	cout << n << ' ' << m << endl; ++CNT;
		//	For(i,1,m) printf("%d %d\n",E[i].FI,E[i].SE);
		//	cout << Q << endl;
		//}
		For(QQ,1,Q) { //cerr << QQ << endl;
				int x,y,p;
			scanf("%d%d%d",&x,&y,&p);
			
			//if (dd == n) printf("%d %d %d\n",x,y,p);
			//continue ;
			
			
			//	if (TTT == 10 && QQ == 30) {
			//		int z = QQ;
			//	}
			if (x == y) {
				if (p == x) puts("Yes"); else puts("No");
				continue ;
			}
			if (clr[x] == clr[y]) {
				if (clr[p] == clr[x]) puts("Yes"); else puts("No"); continue ;
			}//特判 
			int tx = clr[x], cp = clr[p]; int inp,outp;//从p所在的环的进出点 
			Cor(i,20,0) if (d[fa[tx][i]] > d[cp]) tx = fa[tx][i];
			int anc = lca(clr[x],clr[y]);
			if (x == oa && p != x && cp == clr[x]) {
				puts("No"); continue ;
			}//出不去 
			if (y == ob && p != y && cp == clr[y]) {
				puts("No"); continue ;
			}//同上 
			if (cp == clr[y] || cp == clr[x]) {
				puts("Yes"); continue ;
			}//其余情况下p在u or v所在的环内肯定是Yes 
			if (d[cp] < d[anc]) {
				puts("No"); continue ;
			}//不在路径上 
			if (fa[tx][0] != cp) {
				int ty = clr[y];
				Cor(i,20,0) if (d[fa[ty][i]] > d[cp]) ty = fa[ty][i];
				if (fa[ty][0] != cp) {
					puts("No"); continue ;
				} else {
					inp = fap[ty].SE; outp = fap[cp].FI;
				}
			} else {
				inp = fap[tx].SE; outp = fap[cp].FI;
			}//检查p是否在路径上，求出进出cp的点 
			if (cp == anc) {
				if (cro && crop != p) puts("No"); else puts("Yes"); continue ;
			}//当p在lca上时inp outp求的不准，特判 
			if (inp == outp && p != inp) puts("No"); else puts("Yes");
		}
	}	
	//For(i,1,Tot) cout << cache[i] << endl;
	return 0;
}

