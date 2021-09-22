/*
 *  Author:kuangbin
 *  1002.cpp
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
const int MOD = 10007;
long long pow_m(long long a,long long n)
{
    long long ret = 1;
    long long tmp = a%MOD;
    while(n)
    {
        if(n&1)
        {
            ret *= tmp;
            ret %=MOD;
        }
        tmp *= tmp;
        tmp %=MOD;
        n >>= 1;
    }
    return ret;
}
//求ax = 1( mod m) 的x值，就是逆元(0<a<m)
long long inv(long long a,long long m)
{
    if(a == 1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}


int b[100];
int c[100];

void rr()
{
    for(int i = 1;i <= 54;i++)
        c[i] = b[i];
    for(int i = 1;i <= 27;i++)
        b[i+9] = c[i];
    for(int i = 1;i <= 9;i++)
        b[i] = c[27+i];
    b[39] = c[37];
    b[42] = c[38];
    b[45] = c[39];
    b[44] = c[42];
    b[43] = c[45];
    b[40] = c[44];
    b[37] = c[43];
    b[38] = c[40];
    b[41] = c[41];


    b[54] = c[52];
    b[51] = c[53];
    b[48] = c[54];
    b[47] = c[51];
    b[46] = c[48];
    b[49] = c[47];
    b[52] = c[46];
    b[53] = c[49];
    b[50] = c[50];

}
void up()
{
    for(int i = 1;i <= 54;i++)
        c[i] = b[i];
    for(int i = 1;i <= 9;i++)
        b[i] = c[45+i];
    for(int i = 37;i <= 45;i++)
        b[i] = c[i-36];
    for(int i = 19;i <= 27;i++)
        b[i] = c[64-i];
    for(int i = 46;i <= 54;i++)
        b[i] = c[73-i];

    b[10] = c[12];
    b[13] = c[11];
    b[16] = c[10];
    b[17] = c[13];
    b[18] = c[16];
    b[15] = c[17];
    b[12] = c[18];
    b[11] = c[15];
    b[14] = c[14];

    b[28] = c[34];
    b[29] = c[31];
    b[30] = c[28];
    b[33] = c[29];
    b[36] = c[30];
    b[35] = c[33];
    b[34] = c[36];
    b[31] = c[35];
    b[32] = c[32];

}

bool used[1000];

int calc()
{
    memset(used,false,sizeof(used));

    int ret = 0;
    for(int i = 1;i <= 54;i++)
        if(!used[i])
    {
        ret++;
        int tmp = i;
        while(!used[tmp])
        {
            used[tmp] = true;
            tmp = b[tmp];
        }
    }
    return ret;

}


void rr2()
{
    for(int i = 1;i <= 12;i++)
        c[i] = b[i];
    b[1] = c[4];
    for(int i = 2;i <= 4;i++)
        b[i] = c[i-1];
    b[5] = c[8];
    for(int i = 6;i <= 8;i++)
        b[i] = c[i-1];
    b[9] = c[12];
    for(int i = 10;i <= 12;i++)
        b[i] = c[i-1];
}
void up2()
{
        for(int i = 1;i <= 12;i++)
        c[i] = b[i];
    b[1] = c[3];
    b[2] = c[7];
    b[3] = c[11];
    b[4] = c[8];
    b[5] = c[4];
    b[6] = c[2];
    b[7] = c[10];
    b[8] = c[12];
    b[9] = c[1];
    b[10] = c[6];
    b[11] = c[9];
    b[12] = c[5];
}
int calc2()
{
    memset(used,false,sizeof(used));

    int ret = 0;
    for(int i = 1;i <= 12;i++)
        if(!used[i])
    {
        ret++;
        int tmp = i;
        while(!used[tmp])
        {
            used[tmp] = true;
            tmp = b[tmp];
        }
    }
    return ret;

}

void rr3()
{
    for(int i = 1;i <= 8;i++)
        c[i] = b[i];
        b[1] = c[4];
    for(int i = 2;i <= 4;i++)
        b[i] = c[i-1];
    b[5] = c[8];
    for(int i = 6;i <= 8;i++)
        b[i] = c[i-1];
}
void up3()
{
    for(int i = 1;i <= 8;i++)
        c[i] = b[i];
    b[1]=c[4];
    b[5]=c[1];
    b[8]=c[5];
    b[4]=c[8];
    b[2]=c[3];
    b[3]=c[7];
    b[7]=c[6];
    b[6]=c[2];
}
int calc3()
{
    memset(used,false,sizeof(used));

    int ret = 0;
    for(int i = 1;i <= 8;i++)
        if(!used[i])
    {
        ret++;
        int tmp = i;
        while(!used[tmp])
        {
            used[tmp] = true;
            tmp = b[tmp];
        }
    }
    return ret;

}
int num1[40];
int num2[40];
int num3[40];
int num[40];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int cnt = 0;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
    {
        for(int x = 1;x <= 54;x++)
            b[x] = x;
        for(int x = 0;x < i;x++)
            up();
        for(int x = 0;x < j;x++)
            rr();
        num1[cnt++]=calc();
    }
    for(int x = 1;x <= 54;x++)
        b[x] = x;
    rr();
    for(int i = 0;i < 4;i++)
    {
        num1[cnt++]=calc();
        up();
    }
    for(int x = 1;x <= 54;x++)
        b[x] = x;
    rr();
    rr();
    rr();
    for(int i = 0;i < 4;i++)
    {
        num1[cnt++]=calc();
        up();
    }
    cnt = 0;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
    {
        for(int x = 1;x <= 12;x++)
            b[x] = x;
        for(int x = 0;x < i;x++)
            up2();
        for(int x = 0;x < j;x++)
            rr2();
        num2[cnt++]=calc2();
        //printf("%d\n",calc2());
    }

    for(int x = 1;x <= 12;x++)
        b[x] = x;
    rr2();
    for(int i = 0;i < 4;i++)
    {
        num2[cnt++]=calc2();
        up2();
    }
    for(int x = 1;x <= 12;x++)
            b[x] = x;
    rr2();
    rr2();
    rr2();
    for(int i = 0;i < 4;i++)
    {
        num2[cnt++]=calc2();
        up2();
    }
    cnt = 0;
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++)
    {
        for(int x = 1;x <= 8;x++)
            b[x] = x;
        for(int x = 0;x < i;x++)
            up3();
        for(int x = 0;x < j;x++)
            rr3();
        num3[cnt++]=calc3();
        //printf("%d\n",calc3());
    }
    for(int x = 1;x <= 8;x++)
        b[x] = x;
    rr3();
    for(int i = 0;i < 4;i++)
    {
        num3[cnt++]=calc3();
        up3();
    }
    for(int x = 1;x <= 8;x++)
        b[x] = x;
    rr3();
    rr3();
    rr3();
    for(int i = 0;i < 4;i++)
    {
        num3[cnt++]=calc3();
        up3();
    }
    for(int i = 0;i < 24;i++)
        num[i] = num1[i]+num2[i]+num3[i];
    //for(int i = 0;i <24;i++)
   //     printf("%d\n",num[i]);
    int T;
    scanf("%d",&T);
    int n ;
    int iCase = 0;
    while(T--)
    {
        iCase++;
        scanf("%d",&n);
        int ans = 0;

        for(int i = 0;i < 24;i++)
        {
            ans += pow_m(n,num[i]);
            ans %=MOD;
        }
        ans *= inv(24,MOD);
        ans %=MOD;
        printf("Case %d: %d\n",iCase,ans);
    }
    return 0;
}

