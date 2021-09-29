#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
bool visited[10][11][100000];
long N,D;
struct node
{
    long F, S, M;
    long n1, n2;
    node() {}
    node(int f)
    {
        F = f;
        S = -1;
        M = f%N;
        n1 = 1, n2 = 0;
    }
    node (long f, long s, long m, long nn1, long nn2)
    {
        F = f, S = s, M = m, n1 = nn1, n2 = nn2;
    }
};
queue <node> Q;
bool check(node nn)
{
    if (nn.n1 + nn.n2 > D) return true;
    long num = 0;
    while(nn.n1--) num = num*10 + nn.F;
    while(nn.n2--) num = num*10 + nn.S;
    if (num>N) return true;
    return false;
}
bool eqcheck(node nn)
{
    if (nn.n1 + nn.n2 != D) return true;
    long num = 0;
    while(nn.n1--) num = num*10 + nn.F;
    while(nn.n2--) num = num*10 + nn.S;
    if (num==N) return false;
    return true;
}
node bfs()
{
    long i;
    while(!Q.empty()) Q.pop();
    memset(visited, false, sizeof(visited));
    for (i=1; i<=9; ++i) 
    {
        visited[i][10][i%N] = true;
        Q.push(node(i));
    }
    node now, temp;
    long mod;
    while(!Q.empty())
    {
        now = Q.front();
        if (now.S != -1 && now.M == 0 && check(now)) return now;
        Q.pop();
        if (now.S == -1)
        {
            for (i=0; i<=9; ++i)
            {
                if (i==now.F) 
                {
                    mod = ((now.M)*10 + now.F)%N;
                    if (!visited[now.F][10][mod])
                    {
                        visited[now.F][10][mod] = true;
                        temp = node(now.F, -1, mod, now.n1+1, 0);
                        Q.push(temp);
                    }
                }
                else
                {
                    mod = ((now.M)*10 + i)%N;
                    if (!visited[now.F][i][mod])
                    {
                        temp = node(now.F, i, mod, now.n1, 1);
                        if (eqcheck(temp)) visited[now.F][i][mod] = true;
                        if (mod == 0 && check(temp)) return temp;
                        Q.push(temp);
                    }
                }
            }
        }
        else
        {
            mod = ((now.M)*10 + now.S)%N;
            if (!visited[now.F][now.S][mod])
            {
                temp = node(now.F, now.S, mod, now.n1, now.n2+1);
                if (eqcheck(temp)) visited[now.F][now.S][mod] = true;
                if (mod == 0 && check(temp)) return temp;
                Q.push(temp);
            }
        }
    }
}
int main()
{
    freopen("number.in","r",stdin);
    freopen("bc2.out","w",stdout);
    node ans;
    long n;
    while(scanf("%ld",&N) && N>0)
    {
        n = N, D = 0;
        while(n)
        {
            n /= 10;
            ++D;
        }
        ans = bfs();
        printf("%ld: %ld %ld %ld %ld\n",N, ans.n1, ans.F, ans.n2, ans.S);
    }
    return 0;
}
