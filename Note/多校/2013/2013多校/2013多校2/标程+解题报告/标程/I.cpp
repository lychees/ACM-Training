#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 2222;
const int M = 111;

int n, m, f[N], s[N];
vector<int> g[M][M];

int find(int x){
    if(f[x] != x){
        f[x] = find(f[x]);
    }
    return f[x];
}

void merge(int x, int y){
    if(find(x) != find(y)){
        s[find(x)] += s[find(y)];
        f[find(y)] = find(x);
    }
}

int main(){
    while(scanf("%d%d", &n, &m) == 2 and n + m){
        for(int i = 0; i < M; ++ i){
            for(int j = 0; j < M; ++ j){
                g[i][j].clear();
            }
        }
        for(int i = 0; i < n; ++ i){
            int x, y;
            scanf("%d%d", &x, &y);
            g[x][y].push_back(i);
            g[x + 1][y].push_back(i);
        }
        for(int i = 0; i < m; ++ i){
            int x, y;
            scanf("%d%d", &x, &y);
            g[x][y].push_back(n + i);
            g[x][y + 1].push_back(n + i);
        }
        n += m;
        for(int i = 0; i < n; ++ i){
            f[i] = i;
            s[i] = 1;
        }
        for(int i = 0; i < M; ++ i){
            for(int j = 0; j < M; ++ j){
                if((int)g[i][j].size() == 2){
                    merge(g[i][j][0], g[i][j][1]);
                }
            }
        }
        int result = 0;
        for(int i = 0; i < n; ++ i){
            if(f[i] == i){
                result += (s[i] + 1) >> 1;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}    
