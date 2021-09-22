#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <utility>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;

#define forEach(it,v) for(__typeof__((v).begin()) it = (v).begin();it != (v).end();++it)
#define ALL(v) (v).begin(),(v).end()
#define two(x) (1<<(x))
typedef __int64 ll;

const int maxn = 25000;

typedef complex<double> point;
#define X real()
#define Y imag()
const double eps = 1e-9;
bool graham_cp(const point& p1,const point& p2) {
    return (p1.X < p2.X - eps ) || (fabs(p1.X - p2.X)<eps && p1.Y < p2.Y - eps);
}

double ccw(const point &p1,const point& p2,const point& org) {
    return (p1.X - org.X) * (p2.Y - org.Y) - (p1.Y - org.Y) * (p2.X - org.X);
}

void graham(int n,point *p,int& s,point *ch) {
    sort(p,p + n,graham_cp);
    int i,s2;
    ch[0] = p[0];
    s = 1;
    for(i = 1;i < n;i++) {
        while(s > 1 && ccw(p[i],ch[s - 1],ch[s - 2])<eps)s--;
        ch[s++] = p[i];
    }
    s2 = s;
    for(int i = n - 2;i>=0;i--) {
        while(s>s2 && ccw(p[i],ch[s - 1],ch[s - 2])<eps)s--;
        ch[s++] = p[i];
    }
}

double getAngle(const point& p1,const point& p2) {
    double dot = p1.X * p2.X + p1.Y * p2.Y;
    dot /= abs(p1) * abs(p2);
    return dot;
}



point pat[maxn],sample[maxn];
point tbPat[maxn],tbSample[maxn];
double patAngle;
int cntTbPat,cntTbSample;
int n,m;
int cntSample;

void printPoint(const point& p){
    cout<<p.X<<' '<<p.Y<<endl;
}
bool check(const point& org,const point& trans) {
    for(int i = 0;i<m;i++) {
        if(!binary_search(pat,pat + n,(sample[i] - org) * trans + tbPat[0],graham_cp))return false;
    }
    return true;
}

void work() {
    scanf("%d",&m);
    for(int i = 0 ;i<m;i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        sample[i] = point(x,y);
    }
    if(n!=m) {
        puts("No");
        return;
    }
    if(n==1){
        puts("Yes");
        return;
    }
    graham(m,sample,cntTbSample,tbSample);
    cntTbSample--;
    /*cout<<"==========="<<endl;
    for(int i = 0;i<cntTbSample;i++) {
        printf("%lf %lf\n",tbSample[i].X,tbSample[i].Y);
    }*/
    double curAngle;
    point org,trans;
    point A,B,C;
    for(int i = 0;i<cntTbSample;i++) {
        B = tbSample[i];
        A = tbSample[(cntTbSample + i - 1) % cntTbSample];
        C = tbSample[(i + 1) % cntTbSample];
        curAngle = getAngle(A - B,C - B);
        if(fabs(curAngle - patAngle)<eps) {
            org = B;
            trans =  (tbPat[1] - tbPat[0]) / (A - B);
            /*printPoint(A - B);
            printPoint(tbPat[1] - tbPat[0]);*/
            if(check(org,trans)) {
                puts("Yes");
                return;
            }
            trans = (tbPat[1] - tbPat[0]) / (C - B);
            if(check(org,trans)) {
                puts("Yes");
                return;
            }
        }
    }
    for(int i = 0;i<m;i++) {
        sample[i].X = -sample[i].X;
    }
    for(int i = 0;i<cntTbSample;i++)
        tbSample[i].X = -tbSample[i].X;
    for(int i = 0;i<cntTbSample;i++) {
        B = tbSample[i];
        A = tbSample[(cntTbSample + i - 1) % cntTbSample];
        C = tbSample[(i + 1) % cntTbSample];
        curAngle = getAngle(A - B,C - B);
        if(fabs(curAngle - patAngle)<eps) {
            org = B;
            trans =  (tbPat[1] - tbPat[0]) / (A - B);
            /*printPoint(A - B);
            printPoint(tbPat[1] - tbPat[0]);*/
            if(check(org,trans)) {
                puts("Yes");
                return;
            }
            trans = (tbPat[1] - tbPat[0]) / (C - B);
            if(check(org,trans)) {
                puts("Yes");
                return;
            }
        }
    }
    puts("No");
}

int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--) {
        scanf("%d",&n);
        int x,y;
        for(int i =0;i<n;i++) {
            scanf("%d%d",&x,&y);
            pat[i] = point(x,y);
        }
        if(n>1) {
            graham(n,pat,cntTbPat,tbPat);
            cntTbPat--;
            patAngle = getAngle(tbPat[1] - tbPat[0],tbPat[cntTbPat - 1] - tbPat[0]);
            /*for(int i = 0;i<cntTbPat;i++) {
                printf("%lf %lf\n",tbPat[i].X,tbPat[i].Y);
            }
            printf("%lf\n",patAngle);*/
        }
        scanf("%d",&cntSample);
        for(int i =0 ;i<cntSample;i++) {
            work();     
        }
        puts("");
    }
    return 0;
            cntTbPat--;
}
