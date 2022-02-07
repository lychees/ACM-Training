#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


const int N = int(4e5) + 9;
int n,m,cnt;
struct node{int last,x,fx;}a[N];
inline int find(int now,int x)
{
    if(!now)return x;
    if(x!=a[now].x)return find(a[now].last,x);
    return a[now].fx;
}
inline int getfather(int x)
{
    if(x==find(cnt,x))return x;
    return getfather(find(cnt,x));
}



map<int, int> flowers[N];
int best[N];

inline void merge(int p, int q){
    
    if (flowers[p].size() < flowers[q].size()){
        swap(p, q);
    }
    
    for(auto it: flowers[q]){
        int t = flowers[p][it.first] += it.second;
        if (t > flowers[p][best[p]] || t == flowers[p][best[p]] && it.first < best[p]){
            best[p] = it.first;
        }
    }
    flowers[q].clear();
    
    a[cnt]=(node){cnt-1,q,p};
}

int last_ans;

int color[N];
tuple<int, int, int> E[N];
vector<pair<int, int> > state[N];
vector<int> aa;

void Kruskal(){
    
    sort(E, E+m);
    
    for (int i=1;i<=n;++i){
        flowers[i].clear(); state[i].clear();
        flowers[i][color[i]] = 1; best[i] = color[i];
        state[i].push_back(make_pair(0, best[i]));
    }
    
    aa.clear(); aa.push_back(0); cnt = 0;
    
    for (int i=0;i<m;++i){
        int x = get<1>(E[i]), y = get<2>(E[i]), w = get<0>(E[i]);
        int xx = getfather(x), yy = getfather(y);
        if (xx != yy){
            aa.push_back(w); ++cnt; a[cnt] = a[cnt-1]; merge(xx, yy);
            xx = getfather(xx);
            state[xx].push_back(make_pair(w, best[xx]));
        }
    }
}

void init(){
    scanf("%d%d",&n, &m);
    for (int i=1;i<=n;++i){
        scanf("%d", &color[i]);
    }
    for (int i=0;i<m;++i){
        int x, y, w; scanf("%d %d %d", &x, &y, &w);
        E[i] = make_tuple(w, x, y);
    }
}

void solve(){
    Kruskal(); last_ans = 0;
    
    int q; scanf("%d", &q); while (q--){
        int x, w;
        scanf("%d %d", &x, &w);
        x ^= last_ans, w ^= last_ans;
        cnt = upper_bound(aa.begin(), aa.end(), w) - aa.begin() - 1;
        int p = getfather(x);
        /*cout << x << " " << p << " ";
         cout << state[p].size() << " " << w << endl;
         for (auto it: state[p]){
         cout << " " << it.first << " " << it.second << endl;
         }*/
        last_ans =  (--lower_bound(state[p].begin(), state[p].end(), make_pair(w+1, 0))) ->second;
        printf("%d\n", last_ans);
    }
}


int main(){
    
#ifndef ONLINE_JUDGE
    //freopen("/users/minakokojima/ACM-Training/Workspace/in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    
    int T; cin >> T; for (int t=1;t<=T;++t){
        printf("Case #%d:\n", t);
        init(); solve();
    }
}