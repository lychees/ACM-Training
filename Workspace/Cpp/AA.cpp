#include <lastweapon/io>
using namespace lastweapon;

const int N = 30;

map<vector<PII>, int> D;
vector<vector<PII>> Q; VI P, O;
char Map[N][N]; string OP;
int n, m;

char get(int i) {
    if (i == 0) return 'W';
    if (i == 1) return 'S';
    if (i == 2) return 'D';
    return 'A';
}

void gao(int x) {
    if (x) {
        OP.PB(get(O[x]));
        gao(P[x]);
    } else {
        RVS(OP);
        cout << OP << endl;
    }

    char o1 = Map[Q[x][0].fi][Q[x][0].se];
    char o2 = Map[Q[x][1].fi][Q[x][1].se];
    char o3 = Map[Q[x][2].fi][Q[x][2].se];

    Map[Q[x][0].fi][Q[x][0].se] = 'x';
    Map[Q[x][1].fi][Q[x][1].se] = 'y';
    Map[Q[x][2].fi][Q[x][2].se] = 'z';
    REP(i, n) cout << Map[i] << endl;
    Map[Q[x][0].fi][Q[x][0].se] = o1;
    Map[Q[x][1].fi][Q[x][1].se] = o2;
    Map[Q[x][2].fi][Q[x][2].se] = o3;
    cout << endl;
}

bool ok(PII u) {
    return Map[u.fi][u.se] != '#';
}

void bfs() {
    int cz = 0;
    Q.PB({{4,3},{4,4},{5,7}});
    P.PB(-1); O.PB(-1);
    D[{{4,3},{4,4},{5,7}}] = 0;


    while (cz < Q.size()) {
        PII u1 = Q[cz][0], u2 = Q[cz][1], u3 = Q[cz][2];

        REP(i, 4) {
            PII v1 = {u1.fi + dx[i], u1.se + dy[i]};
            PII v2 = {u2.fi + dx[i], u2.se + dy[i]};
            PII v3 = {u3.fi + dx[i], u3.se + dy[i]};

            if (!ok(v1)) v1 = u1; if (!ok(v2)) v2 = u2; if (!ok(v3)) v3 = u3;

            if (v3 == u3) {
                if (v1 == u3) v1 = u1;
                if (v2 == u3) v2 = u2;
            }

            if (v1 == v2) {
                if (dx[i] == 1) {
                    if (u1.fi > u2.fi) v2 = u2;
                    else v1 = u1;
                } else if (dx[i] == -1) {
                    if (u1.fi > u2.fi) v1 = u1;
                    else v2 = u2;
                } else if (dy[i] == 1) {
                    if (u1.se > u2.se) v2 = u2;
                    else v1 = u1;
                } else {
                    if (u1.se > u2.se) v1 = u1;
                    else v2 = u2;
                }
            }


            vector<PII> t = {v1,v2,v3};
            if (CTN(D, t)) continue;
            D[{v1,v2,v3}] = D[{u1,u2,u3}] + 1;

            //cout << D[{v1,v2,v3}] << endl;


            P.PB(cz);
            O.PB(i);
            Q.PB({v1,v2,v3});

            if (Map[v1.fi][v1.se] == 'o' && Map[v2.fi][v2.se] == 'o') {
                cout << D[{v1,v2,v3}] << endl;
                gao(Q.size()-1);
                return;
            }


        }
        ++cz;
    }
}



int main() {

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif

    RD(n, m); REP(i, n) RS(Map[i]);
    bfs();
}
