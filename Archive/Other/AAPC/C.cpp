#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
template<class T> inline bool checkMax(T &a,const T b){return a < b ? a = b, 1 : 0;}
template<class T> inline bool checkMin(T &a,const T b){return b < a ? a = b, 1 : 0;}

#define lx (x<<1)
#define rx (lx|1)
#define ml (l+r>>1)
#define mr (ml+1)
#define lc lx, l, ml
#define rc rx, ml, r
#define root 1, 0, P.size()-1

const int N = int(1e6) + 9;
int C[4*N], C1[4*N], S[4*N];
vector<int> P;


int A, B;
#define a A
#define b B
void upd(int x){
    C1[x] = C1[lx] + C1[rx];
    S[x] = S[lx] + S[rx];
}

void Clear(int x, int l, int r){
    //cout << x << " "<< l << " " << r << endl;
    C[x] == 0;
    C[lx] = C[rx] = 0;
    if (l + 1 == r){
        C[lx] = C[rx] = 0;
    }
    else{
        Clear(lc); Clear(rc);
    }
}


void Build(int x, int l, int r){
    if (l + 1 == r){
        if (C[x] == 1) C1[x] = P[r] - P[l];
        else C1[x] = 0;
        if (C[x]) S[x] = P[r] - P[l];
        else S[x] = 0;

        //cout << S[x] << " " << l << " " << r << " " << P[r] << " " << P[l] << "???" << endl;
    }
    else{
        C[lx] += C[x]; C[rx] += C[x];
        Build(lc); Build(rc);
        upd(x);
        //cout << S[x] << " " << l << " " << r << " " << P.size() << endl;
    }
}

int Query(int x, int l, int r){
    if (r <= a || b <= l) return 0;
    if (a <= l && r <= b){
        return C1[x];
    }
    else{
        return Query(lc) + Query(rc);
    }
}

void Insert(int x, int l, int r){

    //cout << l << " " << r << endl;

    if (r <= a || b <= l) return;

    //cout << l << " "<< r << " " <<a << " " << b << endl;

    if (a <= l && r <= b){
        C[x] += 1;
    }
    else{
        Insert(lc); Insert(rc);
    }
}

#undef a
#undef b

int main(){


#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif


    int T; cin >> T; for (int cas=1;cas<=T;++cas){
        long long n, x1, y1, a, b, c1, c2, m;
        cin >> n >> x1 >> y1 >> a >> b >> c1 >> c2 >> m;

        vector<pair<int, int> > L;
        L.push_back(make_pair(min(x1,y1), max(x1, y1)+1));

        for (int i=1;i<n;++i){
            long long xx = (a*x1 + b*y1 + c1) % m;
            long long yy = (a*y1 + b*x1 + c2) % m;
            x1 = xx; y1 = yy;
            L.push_back(make_pair(min(x1,y1), max(x1, y1)+1));
        }

        P.clear();
        for (int i=0;i<L.size();++i){
            P.push_back(L[i].fi);
            P.push_back(L[i].se);
        }
        sort(P.begin(), P.end());

        P.resize(unique(P.begin(), P.end()) - P.begin() );


        memset(C, 0, sizeof(C));
        Clear(root);

        for (int i=0;i<L.size();++i){
            L[i].fi = lower_bound(P.begin(), P.end(), L[i].fi) - P.begin();
            L[i].se = lower_bound(P.begin(), P.end(), L[i].se) - P.begin();
            A = L[i].fi, B = L[i].se;
            //cout << A << " " << B << endl;
            Insert(root);
        }
        Build(root);
        //cout << S[1] << endl;

        int z = 0x3f3f3f3f;

        for (int i=0;i<L.size();++i){
            A = L[i].fi, B = L[i].se;
            //cout << " " << S[1] - Query(root) << endl;
            checkMin(z, S[1] - Query(root));
        }

        printf("Case #%d: %d\n", cas, z);

       // break;
    }
}
