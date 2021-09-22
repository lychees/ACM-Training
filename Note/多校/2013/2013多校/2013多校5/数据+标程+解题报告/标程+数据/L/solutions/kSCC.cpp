#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std; 

#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fi(i,a,b) for(int i=a;i>=b;i--)

#define MP make_pair
#define PB push_back

const int MAXN = 309 ;

int N , K ;

int A[MAXN][MAXN] , B[MAXN][MAXN] ;
bool vis[MAXN] ;

int Fa[MAXN] ;
int FindFather(int x) { return Fa[x] = (Fa[x] == x ? x : FindFather(Fa[x])) ; }

int tot , Set[MAXN] ;
bool inset[MAXN] ;

void FindSet(int s) {
	fo(i,1,N) inset[i] = false ;
	inset[s] = true ; Set[tot=1] = s ;
	for ( int i = 1 ; i <= tot ; i ++ ) {
		fo(j,1,N) if ( A[Set[i]][j] != 0 && !inset[j] ) {
			inset[j] = true ;
			Set[++tot] = j ;
		}
	}
}

bool inL[MAXN] ;
int L[MAXN] , dis[MAXN] ;

pair<int,int> Prim(int s) {
	fo(i,1,tot) inL[Set[i]] = false ;
	inL[s] = true ;
	L[L[0]=1] = s ;
	fo(i,1,tot) if ( !vis[Set[i]] && !inL[Set[i]] ) dis[Set[i]] = B[s][Set[i]] ;
	for(;;) {
		int Max = 0 , j ;
		fo(i,1,tot) if (!vis[Set[i]] && !inL[Set[i]] && Max<dis[Set[i]]) Max = dis[j=Set[i]] ;
		if ( Max == 0 ) break ;
		inL[j] = true ; L[++L[0]] = j ;
		fo(i,1,tot) if (!vis[Set[i]] && !inL[Set[i]] ) dis[Set[i]] += B[j][Set[i]] ;
	}
	if ( L[0] == 1 ) return make_pair(-1,L[1]) ;
	else             return make_pair(L[L[0]-1],L[L[0]]) ;
}

bool oneset[MAXN] ;
bool vis_ever[MAXN] ;

void StoerWagner() {
	fo(i,1,N) Fa[i] = i ;
	fo(i,1,N) {
		vis[i] = false ;
		if ( vis_ever[i] ) vis[i] = true ;
	}
	fo(i,1,N) fo(j,1,N) B[i][j] = A[i][j] ;
	
	for(;;) {
		int s = 1 ;
		while ( vis[s] && s <= N ) s ++ ;
		if ( s > N ) break ;

		FindSet(FindFather(s)) ; if (tot==1) { vis[s] = true ; continue ; }
		int ans = -1 ;
		vector<int> ansp ;
		for (;;) {
			pair<int,int> p = Prim(FindFather(s)) ;
			if ( p.first == -1 ) { vis[p.second] = true ; break ; }
			int cntvalue = 0 ;
			fo(i,1,tot) if ( !vis[Set[i]] ) {
				cntvalue += B[p.second][Set[i]] ;
				if ( Set[i] == p.first ) continue ;
				B[p.first][Set[i]] += B[p.second][Set[i]] ;
				B[Set[i]][p.first]  = B[p.first][Set[i]] ;
			}
			if ( ans == -1 || ans > cntvalue ) {
				ans = cntvalue ; ansp.clear() ;
				fo(i,1,tot) if ( FindFather(Set[i]) == p.second ) ansp.PB(Set[i]) ;
			}
			vis[p.second] = true ;
			Fa[FindFather(p.second)] = p.first ;
		}
		
		if ( ans >= K ) {
			fo(i,1,tot) vis_ever[Set[i]] = true ;
			continue ;
		}
		fo(i,1,tot) oneset[Set[i]] = true ;
		fo(j,0,ansp.size()-1) oneset[ansp[j]] = false ;
		fo(i,1,tot) if ( oneset[Set[i]] )
			fo(j,0,ansp.size()-1)
				A[Set[i]][ansp[j]] = A[ansp[j]][Set[i]] = 0 ;
	}
}

int col[MAXN] , colnum ;

void Color(int x , int c) {
	if ( col[x] != -1 ) return ;
	col[x] = c ;
	for ( int i = 1 ; i <= N ; i ++ ) if ( A[x][i] != 0 ) Color(i,c) ;
}

int main() {
	int M ;
	while ( 3 == scanf("%d%d%d" , &N , &M , &K) && (N || M || K) ) {
		fo(i,1,N) fo(j,1,N) A[i][j] = 0 ;
		fo(i,1,M) {
			int u , v ;
			scanf("%d%d" , &u , &v) ;
			A[u][v] ++ ; A[v][u] ++ ;
		}
		fo(i,1,N) vis_ever[i] = false ;
		fo(i,1,N)
			StoerWagner() ;
		
		colnum = 0 ;
		fo(i,1,N) col[i] = -1 ;
		fo(i,1,N) if (col[i] == -1) Color(i,++colnum) ;
		//fo(i,1,N) printf("%d " , col[i]) ;
		//puts("") ;
		printf("%d\n",colnum) ;
	}
}



