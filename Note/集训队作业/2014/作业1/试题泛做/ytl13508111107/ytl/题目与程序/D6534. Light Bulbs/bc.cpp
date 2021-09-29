#include<iostream>
using namespace std;
#include<cstdio>
#include<cstdlib>
#include<cstring>

const int maxn = 500;
int moveto[maxn],ans[maxn],now[maxn];
int n;

namespace MaxInt{
    const int maxsize=1000/4+100,sizen=10000;
    typedef struct longnum{
        int size,data[maxsize];
        longnum(int x=0){
            if(!x){
                data[size=1]=0;
                return;
                }
            size=0;
            while(x){
                data[++size]=x%sizen;
                x/=sizen;
                }
            }
        longnum(char *s){
            int len=strlen(s);
            memset(data,0,sizeof(data));
            size=(len+3)/4;
            for(int i=0;i<len;i++)
                data[(len-i+3)/4]=data[(len-i+3)/4]*10+s[i]-'0';
            }
        void init(){
            size=0;
            memset(data,0,sizeof(data));
            }
        void out(){
            printf("%d",data[size]);
            for(int i=size-1;i>=1;i--)
                printf("%04d",data[i]);
            printf("\n");
            }
        };
    
    longnum operator +(const longnum&A,const longnum&B){
        static longnum ans;
        ans.init();
        int temp=0;
        for(int i=1;i<=A.size||i<=B.size;i++){
            if(i<=A.size)temp+=A.data[i];
            if(i<=B.size)temp+=B.data[i];
            ans.data[i]=temp%sizen;temp/=sizen;
            }
        ans.size=max(A.size,B.size);
        if(temp)ans.data[++ans.size]=temp;
        return ans;
        }
    longnum operator -(const longnum&A,const longnum&B){
        static longnum ans;
        ans.init();
        for(int i=1;i<=A.size;i++){
            int dec=0;
            if(i<=B.size)dec=B.data[i];
            ans.data[i]+=A.data[i]-dec;
            
            if(ans.data[i]<0){
                ans.data[i]+=sizen;
                ans.data[i+1]--;
                }
            }
        ans.size=A.size;
        while(!ans.data[ans.size] && ans.size>1)ans.size--;
        return ans;
        }
    longnum operator *(const longnum&A,const longnum&B){
        static longnum ans;
        ans.init();
        for(int i=1;i<=A.size;i++)
            for(int j=1;j<=B.size;j++){
                ans.data[i+j-1]+=A.data[i]*B.data[j];
                ans.data[i+j]+=ans.data[i+j-1]/sizen;
                ans.data[i+j-1]%=sizen;
                }
        ans.size=A.size+B.size;
        while(!ans.data[ans.size] && ans.size>1)ans.size--;
        return ans;
        }
    longnum operator /(const longnum&A,int p){
        static longnum ans;
        ans.init();
        int temp=0;
        for(int i=A.size;i>=1;i--){
            temp=temp*sizen+A.data[i];
            ans.data[i]=temp/p;temp%=p;
            }
        ans.size=A.size;
        while(!ans.data[ans.size] && ans.size>1)ans.size--;
        return ans;
        }
    int operator %(const longnum&A,int p){
        int ans = 0;
        for(int i=A.size;i>=1;i--)
            ans=(ans*sizen+A.data[i])%p;
        return ans;
        }
    bool operator <(const longnum&A,const longnum&B){
        if(A.size!=B.size)return A.size<B.size;
        for(int i=A.size;i>=1;i--)
            if(A.data[i]!=B.data[i])
                return A.data[i]<B.data[i];
        return 0;
        }
    bool operator >(const longnum&A,const longnum&B){
        return B<A;
        }
    bool operator <=(const longnum&A,const longnum&B){
        return !(A>B);
        }
    bool operator >=(const longnum&A,const longnum&B){
        return !(A<B);
        }
    bool operator ==(const longnum&A,const longnum&B){
        return A<=B&&A>=B;
        }
    bool operator !=(const longnum&A,const longnum&B){
        return !(A==B);
        }
    }
using namespace MaxInt;
int one_num;
longnum X;

int deal(longnum x){
    int len;
    if(x==0)return 1;
    else{
        len=0;
        while(x!=0){
            len++;moveto[len]^=(x%2);x=x/2;
            }
        return len;
        }
    return 0;
    }
void solve(){
    int q=0;
    for(int i=n;i>=1;i--)
        q+=ans[i];
    if(q>one_num)return;
    longnum temp=0;
    for(int i=n;i>=1;i--)
        temp=temp*2+ans[i];
    if(q<one_num){
        one_num=q;
        X=temp;
        }
    else X=min(X,temp);
    }
void dfs(int i){
    if(!i){
        if(now[1]==moveto[1])
            solve();
        return;
        }
    for(ans[i]=0;ans[i]<=1;ans[i]++){
        for(int q=1;q>=-1;q--)
            if(1<=i+q&&i+q<=n)
                now[i+q]^=ans[i];
        if(i==n || now[i+1]==moveto[i+1])
            dfs(i-1);
        for(int q=1;q>=-1;q--)
            if(1<=i+q&&i+q<=n)
                now[i+q]^=ans[i];
        }
    }

int main()
{
    freopen("light.in","r",stdin);
	freopen("bc.out","w",stdout);
	int kase = 0;
    char a[110],b[110];
    while(scanf("%s%s",a,b)==2){
        longnum x=a,y=b;
        if(x==0&&y==0)break;
        
        n=0;
        memset(moveto,0,sizeof(moveto));
        memset(now,0,sizeof(now));
        memset(ans,0,sizeof(ans));
        
        n=max(n,deal(a));
        n=max(n,deal(b));
        
        one_num=maxn;
        printf("Case Number %d: ",++kase);
        dfs(n);
        if(one_num==maxn)
            printf("impossible\n");
        else X.out();
        printf("\n");
        }
    
    return 0;   
}
