/**************************************************************
    Problem: 3610
    User: keavil
    Language: C++
    Result: Accepted
    Time:13908 ms
    Memory:48956 kb
****************************************************************/
 
#include<stdio.h>
#include<string.h>
int n,m,K,Q;
const long long mod = 1000000007;
struct matrix
{
    long long a[101][101];
    matrix(){memset(a,0,sizeof(a));}
    void setI(){for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=(i==j);}
    matrix operator * (const matrix &t)const
    {
        matrix ret;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    ret.a[i][j]=(ret.a[i][j]+a[i][k]*t.a[k][j])%mod;
        return ret;
    }
    matrix operator + (const matrix &t)const
    {
        matrix ret;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                ret.a[i][j]=(a[i][j]+t.a[i][j])%mod;
        return ret;
    }
    matrix operator * (long long t)const
    {
        matrix ret;t%=mod;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                ret.a[i][j]=a[i][j]*t%mod;
        return ret;
    }
    void operator +=(const matrix &t){*this=*this+t;}
    void operator *=(const matrix &t) {*this=*this*t;}
    void operator *=(long long &t){*this=*this*t;}
}trans,tmp,mat[3][40],mapnow,tmp1,tmp2;int tnow;
void work(int w,int deep)
{
    if(w==1)
    {
        mat[0][deep].setI();
        mapnow=trans;tnow=1;
        return ;
    }
    work(w>>1,deep+1);
    int d=w>>1;
    if(tnow==d-1)mapnow*=trans,tnow++;
    tmp1=mat[0][deep+1]*mapnow;
    tmp2=mat[1][deep+1]*mapnow;
    mat[0][deep]=tmp1;
    mat[0][deep]+=mat[0][deep+1];
    mat[1][deep]=tmp2;
    mat[1][deep]+=mat[1][deep+1];
    mat[1][deep]+=tmp1*(w>>1);
    mat[2][deep]=mat[2][deep+1]*mapnow;
    mat[2][deep]+=mat[2][deep+1];
    mat[2][deep]+=tmp1*((long long)d*d);
    mat[2][deep]+=tmp2*(d<<1);
    mapnow*=mapnow;tnow<<=1;
    if(w&1)
    {
        mat[0][deep]+=mapnow;
        mat[1][deep]+=mapnow*(w-1);
        mat[2][deep]+=mapnow*((long long)(w-1)*(w-1));
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&K,&Q);
    while(m--)
    {
        int x,y;scanf("%d%d",&x,&y);
        trans.a[x][y]++;
    }
    work(K+1,0);
    while(Q--)
    {
        int x,y;scanf("%d%d",&x,&y);
        printf("%lld\n",mat[2][0].a[x][y]);
    }
    return 0;
}