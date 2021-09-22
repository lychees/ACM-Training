#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 505;
const int M = 3000000;
const int INF = 100000;
const double eps = 1e-7;
inline int dcmp(double d){
    return d < -eps? -1 : d > eps;
}
inline double sqr(double d){
    return d * d;
}
struct Point {
    double x, y;
    Point (){}
    Point (double _x,double _y):x(_x),y(_y){}
    inline bool operator == (const Point &p)const {
        return (dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0);
    }
    inline Point operator - (const Point &p)const {
        return Point(x - p.x,y - p.y);
    }
    inline double operator * (const Point &p)const {
        return x * p.y - y * p.x;
    }
    inline double operator / (const Point &p)const {
        return x * p.x + y * p.y;
    }
    inline double Distance(Point p){
        return sqrt(sqr(p.x - x) + sqr(p.y - y));
    }
    void input(){
        scanf ("%lf %lf", &x, &y);
    }
}p[N];
struct Line{
    Point a,b;
    void input(){
        a.input();
        b.input();
    }
    Line(){}
    Line(Point _a,Point _b):a(_a),b(_b){}
    inline bool operator == (const Line &l) const{
        return (a == l.a && b == l.b) || (a == l.b && b == l.a);
    }
    inline double operator * (const Point &p)const {
        return (b - a) * (p - a);
    }
    inline double operator / (const Point &p)const {
        return (p - a) / (p - b);
    }
    inline int SegCrossSeg(const Line &v){
        int d1 = dcmp((*this) * v.a);
        int d2 = dcmp((*this) * v.b);
        int d3 = dcmp(v * a);
        int d4 = dcmp(v * b);
        if((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
        return ((d1 == 0 && dcmp((*this) / v.a) <= 0)
            ||(d2 == 0 && dcmp((*this) / v.b) <= 0)
            ||(d3 == 0 && dcmp(v / a) <= 0)
            ||(d4 == 0 && dcmp(v / b) <= 0) );
    }
}l[N];
int n , m , K , seq[N];
int match[N], vis[N];
double dist[N][N];
int tot , start[N];
struct Edge {
    int v, next;
}e[N * N];
void _add (int u , int v) {
    e[tot].v = v;
    e[tot].next = start[u];
    start[u] = tot ++;
}
bool dfs (int u) {
    for (int i = start[u] ; i != -1 ; i = e[i].next) {
        int v = e[i].v;
        if (! vis[v]) {
            vis[v] = 1;
            if(match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungry () {
    int ans = 0;
    memset (match , -1, sizeof(match)) ;
    for (int i = 1 ; i <= n ; i ++) {
        memset (vis , 0 , sizeof(vis));
        if (dfs(i)) ans ++;
    }
    return ans;
}
bool check (double mid) {
    tot = 0 ;
    memset (start , -1 , sizeof(start));
    for (int i =1 ; i <= n ; i ++) {
        for (int j = i + 1 ; j <= n ; j ++) {
            if(dist[seq[i]][seq[j]] <= mid)
                _add (seq[i] , seq[j] + n);
        }
    }
    return n - hungry() <= K;
}
double solve(){
    double l = 0 , r = INF;
    double ans = -1;
    int cnt = 50;
    while(cnt --){
        double mid = (l + r) * 0.5;
        if(check(mid)){
            ans = mid;
            r = mid;
        }
        else l = mid;
    }
    return ans;
}
int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out2.txt","w",stdout);
    int t;
    scanf ("%d", &t);
    while (t --){
        scanf ("%d%d%d", &n, &m, &K);
        for (int i = 1 ; i <= n ; i ++){
            p[i].input();
        }
        for (int i = 1 ; i <= m ; i ++){
            l[i].input();
            p[n + (i - 1) * 2 + 1] = l[i].a;
            p[n + i * 2] = l[i].b;
        }
        for (int i = 1 ; i <= n + m * 2 ; i ++){
            for (int j = 1 ; j <= n + m * 2 ; j ++){
                if(i == j) dist[i][j] = 0.0;
                else {
                    bool flag = false;
                    for (int k = 1 ; k <= m ; k ++){
                        if(l[k] == Line(p[i] , p[j])) continue;
                        if (l[k].SegCrossSeg(Line(p[i] , p[j])) == 2) {
                            flag = true;
                            break ;
                        }
                    }
                    if(flag) dist[i][j] = 1e9;
                    else dist[i][j] = p[i].Distance(p[j]);
                    //printf("%lf %lf %lf %lf\n",p[i].x,p[i].y,p[j].x,p[j].y);
                    //cout<<dist[i][j]<<endl;
                }
            }
        }
        for(int i = 1;i <= n;i ++){
            scanf("%d",&seq[i]);
        }
        for (int k = 1 ; k <= n + m * 2 ; k ++) {
            for (int i = 1 ; i <= n + m * 2 ; i ++) {
                for (int j = 1 ; j <= n + m * 2 ;j ++ ){
                    dist[i][j] = fmin(dist[i][j] , dist[i][k] + dist[k][j]);
                }
            }
        }
        /*
        for (int i = 1 ; i <= n + m * 2 ; i ++) {
                for (int j = 1 ; j <= n + m * 2 ;j ++ ){
                    cout<<dist[i][j]<<endl;
                }
            }
            */
        double ans = solve();
        printf("%.2f\n",ans);
    }
    return 0;
}
