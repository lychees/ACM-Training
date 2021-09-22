/*
 *  Author:kuangbin
 *  1011.cpp
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

int main()
{
    //freopen("in.txt","r",stdin);
   // freopen("out.txt","w",stdout);
    int T;
    int a;
    scanf("%d",&T);
    while(T--)
    {
        int sum = 0;
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
        {
            scanf("%d",&a);
        }
        if(a)printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}
