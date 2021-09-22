#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
const int MAXN = 1000010;
//素数筛选部分
bool notprime[MAXN];//值为false表示素数，值为true表示非素数
int prime[MAXN+1];
void getPrime()
{
    memset(notprime,false,sizeof(notprime));
    notprime[0]=notprime[1]=true;
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=MAXN;i++)
    {
        if(!notprime[i])prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++)
        {
            notprime[prime[j]*i]=true;
            if(i%prime[j]==0) break;
        }
    }
}
//合数分解
long long factor[100][2];
int fatCnt;
int getFactors(long long x)
{
    fatCnt=0;
    long long tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++)
    {
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0)
        {
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0)
            {
                factor[fatCnt][1]++;
                tmp/=prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp!=1)
    {
        factor[fatCnt][0]=tmp;
        factor[fatCnt++][1]=1;
    }
    return fatCnt;
}
struct Node
{
    int A,B;
    int score;
    int s;
}node[1010];
bool cmp(Node a,Node b)
{
    return a.score > b.score;
}
long long pow_m(long long a,long long n)
{
    long long ret = 1;
    long long tmp  = a;
    while(n)
    {
        if(n&1)ret*=tmp;
        tmp*=tmp;
        n>>=1;
    }
    return ret;
}
long long sum(long long p,long long n)//求1+p+p^2+p^3+..p^n
{
    if(p==0)return 0;
    if(n == 0)return 1;
    if(n&1)
        return (1+pow_m(p,n/2+1))*sum(p,n/2);
    else return (1+pow_m(p,n/2+1))*sum(p,n/2-1)+pow_m(p,n/2);
}
void check(int index)
{
    if(node[index].A == 1)
    {
        node[index].score = 1;
        node[index].s = (1<<3);
        return;
    }
    getFactors(node[index].A);
    node[index].s = 0;
    //第一个条件(是素数)
    if(fatCnt == 1 && factor[0][1] == 1)
        node[index].s |= (1<<0);
    //第二个条件
    if(fatCnt == 1 && notprime[factor[0][1]+1]==false)
        node[index].s |= (1<<1);
    //第三个条件
    if(fatCnt == 1 && notprime[sum(factor[0][0],factor[0][1])]==false)
        node[index].s |= (1<<2);
    //第四个条件
    bool flag = true;
    for(int i = 0;i < fatCnt;i++)
    {
        long long tmp = (factor[i][1]+1)*factor[i][1]/2;
        for(int j = 0;j < fatCnt;j++)
            if(i != j)
               tmp *= (factor[j][1]+1);
        if(tmp%2!=0)
        {
            flag = false;
            break;
        }
    }
    if(flag)node[index].s |= (1<<3);
    node[index].score = 0;
    for(int i = 0;i < 4;i++)
        if(node[index].s &(1<<i))
           node[index].score++;
}

int b[10];
int main()
{
    //freopen("1011.in","r",stdin);
    //freopen("out.txt","w",stdout);
    getPrime();
    int T;
    int N,K;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&K);
        for(int i = 0;i < N;i++)
        {
            scanf("%d%d",&node[i].A,&node[i].B);
            check(i);
        }
        for(int i = 0;i < N;i++)
        {
            printf("%d",node[i].score);
            if(i < N-1)printf(" ");
            else printf("\n");
        }
        for(int i = 0;i < 4;i++)
            scanf("%d",&b[i]);
        int ans = -10000000;
        sort(node,node+N,cmp);
        for(int k = 0;k <(1<<4);k++)
        {
            int tmp = 0;
            int temps = 0;
            int cc = K;
            for(int i = 0;i < N;i++)
                if((node[i].s & k)==0)
                {
                    if(cc == 0)break;
                    temps |= node[i].s;
                    tmp += node[i].score*min(cc,node[i].B);
                    cc -= min(cc,node[i].B);
                    if(cc == 0)break;
                }
            for(int i = 0;i < 4;i++)
                if((temps&(1<<i))==0)
                   tmp += b[i];
            if(cc!=0)continue;
            else ans = max(ans,tmp);
        }
        printf("%d\n",ans);
    }
    return 0;
}
