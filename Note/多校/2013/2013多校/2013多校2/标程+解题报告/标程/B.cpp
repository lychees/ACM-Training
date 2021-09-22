#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 222222;
const int M = 2222222;
const int INF = 111111111;

int n, m, edgeCnt, firstEdge[N], to[M], nextEdge[M], dfnCnt, dfn[N], low[N], dp[N][2], result;
bool visit[M];

void addEdge(int u, int v){
    to[edgeCnt] = v;
    nextEdge[edgeCnt] = firstEdge[u];
    firstEdge[u] = edgeCnt ++;
}

void dfs(int u){
    dfn[u] = low[u] = dfnCnt ++;
    dp[u][0] = dp[u][1] = 0;
    for(int iter = firstEdge[u]; iter != -1; iter = nextEdge[iter]){
        if(not visit[iter >> 1]){
            visit[iter >> 1] = true;
            int v = to[iter];
            if(dfn[v] == -1){
                dfs(v);
                result += dfn[u] < low[v];
                int temp = dp[v][0] + (dfn[u] < low[v]);
                if(temp > dp[u][0]){
                    dp[u][1] = dp[u][0];
                    dp[u][0] = temp;
                }else if(temp > dp[u][1]){
                    dp[u][1] = temp;
                }
                low[u] = min(low[u], low[v]);
            }else{
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
}

int main(){
	int size = 256 << 20; // 256MB
	char *p = (char*)malloc(size) + size;
	__asm__("movl %0, %%esp\n" :: "r"(p) );

    while(scanf("%d%d", &n, &m) == 2 and n + m){
        result = 0;
        edgeCnt = 0;
        memset(firstEdge, -1, sizeof(firstEdge));
        for(int i = 0; i < m; ++ i){
            int a, b;
            scanf("%d%d", &a, &b);
            addEdge(a - 1, b - 1);
            addEdge(b - 1, a - 1);
        }
        dfnCnt = 0;
        memset(dfn, -1, sizeof(dfn));
        memset(visit, 0, sizeof(visit));
        dfs(0); 
        int temp = 0;
        for(int i = 0; i < n; ++ i){
//            printf("%d: %d %d\n", i + 1, dp[i][0], dp[i][1]);
            temp = max(temp, dp[i][0] + dp[i][1]);
        }
        printf("%d\n", result - temp);
        //  printf("%d %d\n",result, temp);
    }
    return 0;
}