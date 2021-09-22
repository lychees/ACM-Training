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
#define MaxN 123456
#define MaxNode 1020304
#define MD 1000000007

struct Tflow {
	int v[MaxN],next[MaxN],h[MaxN],tot,c[MaxN],in[MaxN],out[MaxN];
	void clr() { Fill(h,tot = 0); Fill(in,0); Fill(out,0); }
	void add(int b,int e,int f) { //cerr << b << ' ' << e << ' ' << f << endl;
		v[++tot] = e; next[tot] = h[b]; h[b] = tot; c[tot] = f;
		v[++tot] = b; next[tot] = h[e]; h[e] = tot; c[tot] = 0;
	}
	int S,T,d[MaxN],flow,found,gap[MaxN],cur[MaxN],ans;
	void aug(int i) {
		if (i == T) {
			ans += flow; found = true;
			return ;
		}
		int mind = T, tf = flow, z;
		for (z = cur[i]; z; z = next[z]) if (c[z]) {
			if (d[v[z]] + 1 == d[i]) {
				flow = min(flow,c[z]); cur[i] = z;
				aug(v[z]);
				if (found) break ; if (d[S] >= T) return ;
				flow = tf; 
			} mind = min(mind,d[v[z]]);
		}
		if (found) {
			c[z] -= flow; c[(z & 1) ? (z + 1) : (z - 1)] += flow;
		} else {
			if (--gap[d[i]] == 0) d[S] = T;
			for (int z = h[i]; z; z = next[z]) if (c[z]) mind = min(mind,d[v[z]]);
			++gap[d[i] = mind + 1]; cur[i] = h[i];
		}
	}	
	void isap() {
		ans = 0; Fill(d,0); Fill(gap,0); gap[0] = T; For(i,1,T) cur[i] = h[i];
		while (d[S] < T) {
			flow = INF; found = false ;
			aug(S);
		}
	}
	int Sol(int _s,int _t) {
		S = _s; T = _t;
		isap();
		return ans;
	}
} TF;

int n,m;
int code(PII s) {
	return (s.FI - 1) * 20 + s.SE;
}

PII dec(int r) {
	int j = r % 20; if (!j) j = 20;
	int i = (r - j) / 20 - 1;
	return MP(i,j);
}

const int pi[] = {0,1,0,-1};
const int pj[] = {1,0,-1,0};

int vis[22][22], A[22][22]; PII q[MaxN];
void spfa(PII s,int *D) {
	int hd = 0, tl = 1; For(i,1,400) D[i] = INF; D[code(s)] = A[s.FI][s.SE];
	Fill(vis,0); q[1] = s; vis[s.FI][s.SE] = true;
	while (hd < tl) { //cerr << hd << endl;
		PII vex = q[++hd]; vis[vex.FI][vex.SE] = false ;
		For(p,0,3) {
			int ni = vex.FI + pi[p], nj = vex.SE + pj[p];
			if (!(ni && ni <= 20 && nj && nj <= 20)) continue ;
			PII np = MP(ni,nj); int tp = code(np);
			if (D[tp] > D[code(vex)] + A[ni][nj]) {
				D[tp] = D[code(vex)] + A[ni][nj];
				if (!vis[ni][nj]) {
					vis[ni][nj] = true;
					q[++tl] = MP(ni,nj);
				}
			}
		}
	}
}
				
int H,a[MaxN],b[MaxN],D[MaxN],cas[MaxN],cont[1020][5],cs[1020][5],cnt[1020],d[444],d2[444],d1[444],ct[1020],app[3030];
int main() {
	while (cin >> n >> m >> H) {
		int sm = 0;
		For(i,1,n) scanf("%d%d%d",&a[i],&b[i],&D[i]), sm += D[i];  
		For(F,1,m) { //cerr << F << endl;
			PII s,s1 = MP(-1,-1),s2; int has = 0;
			For(i,1,20) For(j,1,20) {
				scanf("%d",&A[i][j]);
				if (A[i][j] > 200000) { cas[F] = 2; //这层是要是还是撬棍还是啥也没 
					if (s1.FI != -1) s2 = MP(i,j); else s1 = MP(i,j);
					cont[F][++has] = A[i][j] - 200000; A[i][j] = 0; continue ;
				}
				if (A[i][j] > 100000) { cas[F] = 1;
					if (s1.FI != -1) s2 = MP(i,j); else s1 = MP(i,j);
					if (A[i][j] - 100000 == 100000) {
						int z = i;
					}
					cont[F][++has] = A[i][j] - 100000; A[i][j] = 0; continue ;
				}
				if (A[i][j] < 0) {
					s = MP(i,j); A[i][j] = 0;
				}
			}
			if (has == 0) {//没有工具 无视掉 
				cas[F] = 0; continue ;
			}
			if (has == 1) {
				spfa(s,d);//一个，单源最短路 
				cs[F][1] = d[code(s1)]; cnt[F] = 1;
				continue ;
			}
			if (has == 2) {
				spfa(s,d); spfa(s1,d1); spfa(s2,d2); cnt[F] = 2;
				cs[F][1] = d[code(s1)]; cs[F][2] = d[code(s2)];
				int ans = INF;
				For(i,1,20) For(j,1,20) {
					int t = code(MP(i,j));
					ans = min(ans,d[t] + d1[t] + d2[t] - 2 * A[i][j]);
				}
				cs[F][3] = ans;
				//For(j,1,3) printf("%d ",cs[F][j]); puts("");
			}	
		}
		int l = 0, r = m + 1; int ansp;
		while (l < r) { //cerr << mid << endl;
			int mid = l + r >> 1;
			Fill(ct,INF);
			For(i,1,mid) {
				if (!cas[i]) continue ;
				if (cnt[i] == 2) ct[i] = cs[i][3];
			}
			int S = m * 3 + 1, T = S + 1; TF.clr();
			For(i,1,mid) if (cas[i] == 1)TF.add(S,i,ct[i]); else if (cas[i] == 2) TF.add(i,T,ct[i]); Fill(app,0);
			For(i,1,mid) {
				if (!cas[i]) continue ;
				For(j,1,cnt[i]) app[cas[i] * m + cont[i][j]] = true;
				if (cas[i] == 1) {
					For(j,1,cnt[i]) TF.add(i,m + cont[i][j],cs[i][j]);
				} else {
					For(j,1,cnt[i]) TF.add(m + m + cont[i][j],i,cs[i][j]);
				}
			}
			For(i,1,m) if (!app[m + i]) TF.add(S,m + i,INF);
			For(i,1,m) if (!app[m + m + i]) TF.add(m + m + i,T,INF);
			For(i,1,n) TF.add(m + a[i],m + m + b[i],D[i]);
			int Ans = TF.Sol(S,T); //cout << Ans << endl;
			if (Ans < H) r = mid; else l = mid + 1;
		}
		{
			int mid = l;
			Fill(ct,INF);
			For(i,1,mid) {
				if (!cas[i]) continue ;
				if (cnt[i] == 2) ct[i] = cs[i][3];
			}
			int S = m * 3 + 1, T = S + 1; TF.clr();
			For(i,1,mid) if (cas[i] == 1)TF.add(S,i,ct[i]); else if (cas[i] == 2) TF.add(i,T,ct[i]); Fill(app,0);
			For(i,1,mid) {
				if (!cas[i]) continue ;
				For(j,1,cnt[i]) app[cas[i] * m + cont[i][j]] = true;
				if (cas[i] == 1) {
					For(j,1,cnt[i]) TF.add(i,m + cont[i][j],cs[i][j]);
				} else {
					For(j,1,cnt[i]) TF.add(m + m + cont[i][j],i,cs[i][j]);
				}
			}
			For(i,1,m) if (!app[m + i]) TF.add(S,m + i,INF);
			For(i,1,m) if (!app[m + m + i]) TF.add(m + m + i,T,INF);
			For(i,1,n) TF.add(m + a[i],m + m + b[i],D[i]);
			ansp = TF.Sol(S,T); //cout << Ans << endl;	
		}
		if (l > m) puts("Impossible."); else cout << l << ' ' << ansp << endl;
	}
	return 0;
}

