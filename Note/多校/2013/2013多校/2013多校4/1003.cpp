/*
 *  Author:kuangbin
 *  1003.cpp
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <math.h>
using namespace std;

char g[220][220];
int sx,sy,ex,ey;
int n,m;
int keynum;
int key_s[220][220];
int move[][2] = {{0,1},{0,-1},{1,0},{-1,0}};
struct Node
{
    int key;//Ô¿³×µÄ×´Ì¬
    int num;//ÒÆ¶¯Êý
    int x,y;
};
queue<Node>q;
bool used[202][202][1<<7];
bool used2[202][202][1<<7][4];
int bfs()
{
    while(!q.empty())q.pop();
    Node tmp,now;
    tmp.key = 0;
    tmp.num = 0;
    tmp.x = sx;
    tmp.y = sy;
    q.push(tmp);
    memset(used,false,sizeof(used));
    memset(used2,false,sizeof(used2));
    used[sx][sy][0] = true;
    while(!q.empty())
    {
        tmp = q.front();
        q.pop();
        for(int i = 0;i < 4;i++)
        {
            int mx = move[i][0];
            int my = move[i][1];
            int x = tmp.x;
            int y = tmp.y;
            int ss = tmp.key;
            while(1)
            {
                if(g[x][y] =='L')
                {
                    mx = 0; my = -1;
                }
                if(g[x][y] == 'U')
                {
                    mx = -1;my = 0;
                }
                if(g[x][y] == 'D')
                {
                    mx = 1;my = 0;
                }
                if(g[x][y] == 'R')
                {
                    mx = 0; my = 1;
                }
                int dir;
                if(mx==-1&&my==0)dir=0;
                else if(mx==1&&my==0)dir=1;
                else if(mx==0&&my==1)dir=2;
                else if(mx==0&&my==-1)dir=3;
                if(used2[x][y][ss][dir])break;
                used2[x][y][ss][dir] = true;
                x += mx;
                y += my;
                if(x < 0 || y < 0 || x >= n || y >= m)break;
                if(g[x][y] =='#')break;
                if( x == ex && y== ey && ss ==((1<<keynum)-1) )
                    return tmp.num+1;
                if(g[x][y] =='L')
                {
                    mx = 0; my = -1;
                }
                if(g[x][y] == 'U')
                {
                    mx = -1;my = 0;
                }
                if(g[x][y] == 'D')
                {
                    mx = 1;my = 0;
                }
                if(g[x][y] == 'R')
                {
                    mx = 0; my = 1;
                }
                if(g[x][y] == 'K')
                    ss |= key_s[x][y];
                if(x+mx >=0 && x+mx < n && y+my>=0 && y+my < m && g[x+mx][y+my]=='#')
                {
                    if(used[x][y][ss])break;
                    now.x = x;now.y = y;
                    now.key = ss;
                    now.num = tmp.num + 1;
                    q.push(now);
                    used[x][y][ss] = true;
                    break;
                }
            }
        }
    }
    return -1;
}


int main()
{
    //freopen("1003.in","r",stdin);
   // freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m)==2)
    {
        keynum = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%s",g[i]);
            for(int j = 0;j < m;j++)
            {
                if(g[i][j] == 'S')
                {
                    sx = i;sy = j;
                }
                if(g[i][j] == 'E')
                {
                    ex = i;ey = j;
                }
                if(g[i][j] == 'K')
                {
                    key_s[i][j] = (1<<keynum);
                    keynum++;
                }
            }
        }
        printf("%d\n",bfs());
    }
    return 0;
}
