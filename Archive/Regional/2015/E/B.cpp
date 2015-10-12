#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back
#define SZ size()
#define AA first
#define BB second
#define OP begin()
#define BG begin()
#define ED end()
#define SQ(x) ((x)*(x))
#define cmin(x,y) x=min(x,y)
#define cmax(x,y) x=max(x,y)

#define NAME ""
typedef long long LL;
typedef pair<int,int> PII;
const int INF = 100000000;
const double eps = 1e-10;
const double PI = acos(-1.);
int sign( double x ) {return x<-eps?-1:x>eps;}
struct point {
    double x, y;
    point( double _x=0, double _y=0 ) : x( _x ), y( _y ) {}
    point operator - ( point p ) {return point( x-p.x,y-p.y );}
    point operator + ( point p ) {return point( x+p.x,y+p.y );}
    point operator * ( double d ) {return point( x*d,y*d );}
    point operator / ( double d ) {return point( x/d,y/d );}
    bool operator < ( const point &p ) const {
        return sign( x - p.x ) == 0 ? sign( y - p.y ) <= 0 : sign( x - p.x ) <= 0;
    }
    double operator *( point p ) {return x*p.x+y*p.y;}//dot
    double operator ^( point p ) {return x*p.y-y*p.x;}//det
    double len() {return sqrt( x*x+y*y );}
    double arc() {return atan2( y, x );}
    point normal() {return ( *this ) / this->len();}
    point rotate() {return point( -y, x );}
    point rotate( double arc )
    {return point( x*cos( arc ) - y*sin( arc ),x*sin( arc ) + y*cos( arc ) );}
    double dis( point p ) {return ( *this - p ).len();}
    double dis2( point p ) {p = p - ( *this ); return p*p;}
    void read() {scanf( "%lf%lf", &x, &y );}
    void write( char *s="" ) {printf( "(%f,%f)%s",x,y,s );}
} Orz( 0,0 );
bool isLL( point p1, point p2, point q1, point q2 ,point &is ) {
    double m=( q2-q1 )^( p1-q1 ),n=( q2-q1 )^( p2-q1 );
    if ( sign( n-m )==0 )return 0;
    is= ( p1*n-p2*m )/( n-m );
    return 1;
}
double r;   //O(0,0)
double area2( point pa,point pb ) {
//    pa.write();pb.write();
    if ( pa.len()<pb.len() )swap( pa,pb );
    if ( pb.len()<eps ){
        return 0;
    }
    double a,b,c,B,C,sinB,cosB,sinC,cosC,S,h,theta;
    a=pb.len(),b=pa.len(),c=( pb-pa ).len();
    cosB=pb*( pb-pa )/a/c;
    B=acos( cosB );
    cosC=pa*pb/a/b;
    C=acos( cosC );
    if ( a>r ) {
        S=C*r;
        h=a*b*sin( C )/c;
        if ( h<r&&B<PI/2 ){
            double D=acos(h/r);
            S-=2*D*r;
            //S+=2*sqrt(r*r-h*h);
        }

    } else if ( b>r ) {
        theta=PI-B-asin( sin( B )/r*a );
        double x=r/sin(B)*sin(theta);
        S=(C-theta)*r;
    }// else S=(pa-pb).len();
//    printf("%.2f\n",S);
    return S;
}
double play(point pa,point pb){
//    pa.write();pb.write("\n");
    if ( pa.len()<pb.len() )swap( pa,pb );//pa>pb
    if ( pb.len()<eps ){
//        printf("%.2f\n",min(pa.len(),r));
        return min(pa.len(),r);
    }
    double a,b,c,B,C,sinB,cosB,sinC,cosC,S,h,theta;
    a=pb.len(),b=pa.len(),c=( pb-pa ).len();
    cosB=pb*( pb-pa )/a/c;
    B=acos( cosB );
    cosC=pa*pb/a/b;
    C=acos( cosC );
    if ( a>r ) {
        h=a*b*sin( C )/c;
        if ( h<r&&B<PI/2 ){
            S=2*sqrt(r*r-h*h);
        }else S=0;
    } else if ( b>r ) {
        theta=PI-B-asin( sin( B )/r*a );
        double x=r/sin(B)*sin(theta);
        S=x;
    }else S=(pa-pb).len();
//    printf("%.2f\n",S);
    return fabs(S);
}
point info[1005];
double area(int n) {
    double S=0;

    S = 0;
    cout << (LL)S <<endl;
    for ( int i=0; i<n; i++ ){
        S+=area2( info[i],info[i+1] )*sign( info[i]^info[i+1] );
        cout << (LL)S <<endl;
        //cout << area2( info[i],info[i+1] )*sign( info[i]^info[i+1] ) <<endl;
        //cout << "    " <<S << " " << LL(area2( info[i],info[i+1] )*sign( info[i]^info[i+1] )) << endl;
    }
    S=fabs(S);

    cout << S << " " << LL(S) << endl;

    double SS = 0;
    //cout << S <<" ";

// 6.28318
// 3.14159
    for(int i=0;i<n;i++){
//        cout<<S<<"\t";
        point pa=info[i],pb=info[i+1];
        SS+=play(pa,pb);
    }



    cout << SS << " " << " " << LL(S) << endl;
    S += SS;

//    cout<<S<<"\n";
    return fabs( S );
}
int main() {


#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
        //freopen("out.txt", "w", stdout);
#endif
    int i, j, k, u, v, w;
    int te;
    int n;
    while(~scanf("%d",&n)&&n) {
        for(i=0;i<n;i++)info[i].read();
        double p,q;
        scanf("%lf%lf%lf",&p,&q,&r);
        for(i=0;i<n;i++)info[i].x-=p;
        for(i=0;i<n;i++)info[i].y-=q;
        info[n]=info[0];
        double ans=area(n);
        printf("%d\n",(int)(round(ans)+eps));
    }
    return 0;
}
