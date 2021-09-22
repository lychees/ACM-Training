#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<algorithm>

using namespace std;

const int N = 5000010;
const int maxn = 1000000;
const int INF = 1<<29;

bool isPrime[N];
int prime[N],pp;
int point[maxn+10];

void checkPrime()
{
    for(int i = 1;i<N;i++)
        isPrime[i]=true;
    isPrime[1]=false;
    for(int i=2;i<N;i++)
    {
        if(isPrime[i])
        {
            for(int j=i+i;j<N;j+=i)
            {
                isPrime[j]=false;
            }
        }
    }
    int pp = -1;
    for(int i=1;i<N;i++)
    {
        if(isPrime[i])
            prime[++pp]=i;
    }
}

bool ok1(int x)
{
    return isPrime[x];
}

bool ok2(int x)
{
    int cnt=1;
    for(int i=0;prime[i]*prime[i]<=x;i++)
    {
        int y=0;
        while(x%prime[i]==0)
        {
            x/=prime[i];
            y++;
        }
        cnt*=(y+1);
    }
    if(x!=1) cnt*=2;
    return isPrime[cnt];
}

bool ok3(int x)
{
    int cnt=1;
    for(int i=0;prime[i]*prime[i]<=x;i++)
    {
        if(x%prime[i]==0)
        {
            int y=0;
            while(x%prime[i]==0)
            {
                x/=prime[i];
                y++;
            }
            int sum=0,t=1;
            for(int j=0;j<=y;j++)
            {
                sum+=t;
                t*=prime[i];
            }
            cnt*=sum;
        }
    }
    if(x!=1) cnt *= (x+1);
    return isPrime[cnt];    
}

bool ok4(int x)
{
    if(x==1)
        return true;
    int pr[23],p=-1;
    
    for(int i=0;prime[i]*prime[i]<=x;i++)
    {
        if(x%prime[i]==0)
        {
            int count=0;
            while(x%prime[i]==0)
            {
                x/=prime[i];
                count++;
            }
            pr[++p]=count;
        }
    }
    if(x!=1) pr[++p]=1;
    for(int i=0;i<=p;i++)
    {
        if(pr[i]%4==1||pr[i]%4==2)
        {
            bool hasji = false;
            for(int j=0;j<=p;j++)
            {
                if(j!=i&&pr[j]%2==1)
                    hasji=true;
            }
            if(hasji==false)
                return false;
        }
    }
    return true;
}

int kind(int x)
{
    int y=0;
    if(ok1(x)) y|=1;
    if(ok2(x)) y|=2;
    if(ok3(x)) y|=4;
    if(ok4(x)) y|=8;
    return y;
}

struct Pri
{
    int sco,wh;
    bool friend operator < (const Pri &a,const Pri &b)
    {
        return a.sco>b.sco;
    }
};

int main()
{
    checkPrime();
    int sco[16];
    Pri pri[16];
    for(int i=0;i<16;i++)
    {
        sco[i]=0;
        pri[i].wh=i;
        for(int j=0;j<4;j++)
            if(i&1<<j)
                sco[i]++;
        pri[i].sco=sco[i];
    }
    sort(pri,pri+16);
    int csnum;
    cin>>csnum;
    for(int cs=1;cs<=csnum;cs++)
    {
        int n,k;
        cin>>n>>k;
        int num[16];
        memset(num,0,sizeof(num));
        for(int i=1;i<=n;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            int k = kind(a);
            printf("%d%c",sco[k],i==n?'\n':' ');
            num[k]+=b;        
        }
    //    puts("a");
        int pun[4];
        for(int i=0;i<4;i++)
        {
            cin>>pun[i];
        }
        int ans = -INF;
        int has=0;
        for(int i=0;i<16;i++)
        {
            if(num[i]!=0)
                has|=1<<i;
        }
    //    puts("b");
    //    printf("has = %d\n",has);
        for(int i=0;i<(1<<16);i++)
        {
            if(i==(i&has))
            {
        //        printf("i = %d\n",i);
                int ck=0,res=0,pval=0;
                for(int j=0;j<16;j++)
                    if(i&(1<<j))
                        ck++,res+=sco[j],pval=pval|j;
                if(ck>k) continue;
                for(int j=0;j<16;j++)
                {
                    int getn=num[pri[j].wh];
                    if(i&(1<<pri[j].wh))
                        getn--;
                    else 
                        continue;
                    getn=min(getn,k-ck);
                    ck+=getn;
                    res+=sco[pri[j].wh]*getn;
                }
                for(int j=0;j<4;j++)
                {
                    if(0==(1<<j&pval))
                        res+=pun[j];
                }
                if(ck==k)
                    ans = max(ans,res);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
