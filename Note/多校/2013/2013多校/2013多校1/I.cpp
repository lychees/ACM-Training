#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <math.h>
using namespace std;
const int MAXN = 100010;
char str[MAXN];
int a[MAXN];
int len;
int calc()
{
    int sum = 0;
    for(int i = 0;i < len;i++)
        sum+=a[i];
    sum%=10;
    return sum;
}
void add()
{
    int c = 1;
    for(int i = 0;;i++)
    {
        int tmp = a[i]+c;
        a[i] = tmp%10;
        c = tmp/10;
        if(c==0)break;
    }
    if(a[len]!=0)len++;
}


int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(a,0,sizeof(a));
        scanf("%s",str);
        len = strlen(str);
        for(int i = 0;i < len;i++)
            a[i] = str[len-1-i]-'0';
        add();
        int cc = 0;
        while(calc()!=0)
        {
        add();
        }
        for(int i = len-1;i>=0;i--)
            printf("%d",a[i]);
        printf("\n");

    }
    return 0;
}





