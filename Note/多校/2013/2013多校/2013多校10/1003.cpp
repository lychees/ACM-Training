#include<iostream>
#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

#define x    first
#define y    second

typedef long long int64;

typedef pair<int64, int64> pll;

const int mod = (1000000007);

const int N = 5050;

pll points[N];

int64 n, m, k;

int64 add(int64 &a, int64 &b){
    int64 ret = a+b;
    return ret>=mod?(ret-mod):ret;
}
int64 mul(int64 a, int64 b){
    int64 ret = a*b;
    if(ret>=mod) ret%=mod;
    return ret;
}
void modify(int64 &a){
    a%= mod;
    if(a<0)a+=mod;
}

int64 solve(int64 Y, int64 X, pll p[]){
    int64 ret = 0ll;
    int64 shift = Y*(Y+1)/2;
    modify(shift);

    ret = p[0].x*(p[0].x-1)/2 + (X-p[k-1].x+1)*(X-p[k-1].x)/2;
    modify(ret);
    for(int i=1;i<k;i++)if(p[i].x!=p[i-1].x){
        ret += (p[i].x-p[i-1].x) * (p[i].x-p[i-1].x-1)/2;
        modify(ret);
    }
    ret = mul(ret, shift);
    return ret;
}
int main()
{
//freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
   // int64 a = 1000000;
    //int64 aa = ((a+1)*a/2)%mod;
    //a--;
  //  aa = mul(((a+1)*a/2)%mod, ((a+1)*a/2)%mod);
//    aa = mul(aa, 2ll);
//    cout<<aa<<endl;

        while(scanf("%I64d%I64d%I64d", &n, &m, &k)!=EOF){
            int64 cct0 = (n+1)*n/2, cct1=(m+1)*m/2;
            modify(cct0);modify(cct1);
            int64 ans = mul(cct0, cct1);

            if(k == 0ll){
                printf("0\n");
                continue;
            }
            for(int i=0;i<k;i++){
                scanf("%I64d%I64d", &points[i].x, &points[i].y);
            }

            map<pll, bool> mp;

            sort(points, points+k);
/*
            for(int i=1;i<k;i++){
                if(points[i].x == points[i-1].x)
                {
                    if(points[i].y == points[i-1].y){
                        for(int j=i;j<k-1;j++)
                            points[j] = points[j+1];
                        k--;
                        i--;
                        continue;
                    }
                }
                //mp[make_pair(points[i].x, points[i].y)]=true;
            }*/
            for(int i=0;i<k;i++)
                mp[make_pair(points[i].x, points[i].y)]=true;
            int64 p1 = 0ll, p2 = 0ll;
            vector<int64> xx, yy;
            xx.push_back(0ll), xx.push_back(n+1);
            yy.push_back(0ll), yy.push_back(m+1);
            for(int i=0;i<k;i++){
                xx.push_back(points[i].x);
                yy.push_back(points[i].y);
            }

            sort(xx.begin(), xx.end());
            sort(yy.begin(), yy.end());


            int64 intersect = 0ll;
            for(int i=1;i<xx.size();i++)if(xx[i]!=xx[i-1])
            {
                for(int j=1;j<yy.size();j++)if(yy[j]!=yy[j-1]){

                    if(xx[i]!=0 && xx[i]!=n+1 && yy[j]!=0 && yy[j]!=m+1 && mp[make_pair(xx[i], yy[j])]==false)
                    {
                        intersect ++;
                    }
                    int64 dx = xx[i]-xx[i-1], dy = yy[j]-yy[j-1];
                    int64 temp1 = (dx*(dx-1)/2)%mod;
                    int64 temp2 = (dy*(dy-1)/2)%mod;

                    temp1 = mul(temp1, temp2);
//                    cout<<"hehe "<<dx<<' '<<dy<<" "<<temp<<endl;
                    p2 = add(p2, temp1);
                }
            }



            sort(points, points+k);


            p1 = solve(m,n,points);
            for(int i=0;i<k;i++){
                swap(points[i].x,points[i].y);
            }
            sort(points, points+k);
            p1 += solve(n,m,points);
            modify(p1);
            modify(ans);
            //cout<<p1<<' '<<p2<<' '<<ans<<endl;
            ans = ans - p1 + p2 - intersect;
            modify(ans);
            printf("%I64d\n",ans);
        }
}
