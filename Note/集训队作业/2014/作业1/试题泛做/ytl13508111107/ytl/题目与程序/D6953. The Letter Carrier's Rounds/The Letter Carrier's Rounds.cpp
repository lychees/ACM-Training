#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> STR;
typedef map<STR,set<STR> > MTA;//name user
typedef pair<STR,STR> Address;//mta name 

const int maxn = 1000010;
char str[10000],message[maxn][100];int n;
int trun[2000],to[2000],top;
MTA mta;

STR readstr(char *sp){
    LL a=0,b=0;
    int len=strlen(sp);
    LL mul = 1;
    while(len>8){
        a+=trun[(int)*sp]*mul;sp++;len--;
        mul*=top;
        }
    mul=1;
    while(*sp){
        b+=trun[(int)*sp]*mul;sp++;
        mul*=top;
        }
    return STR(a,b);
    }
STR readstr(){
    char str[20];
    scanf("%s",str);
    return readstr(str);
    }
void output(STR str){
    LL a=str.first,b=str.second;
    while(a){
        putchar(to[a%top]);
        a/=top;
        }
    while(b){
        putchar(to[b%top]);
        b/=top;
        }
    }
void readmta(){
    STR name=readstr();
    set<STR> S;
    int x;
    scanf("%d",&x);
    while(x--)
        S.insert(readstr());
    mta.insert(pair<STR,set<STR> >(name,S));
    }
Address dealAddress(char *str){
    int len=strlen(str);
    int pos;
    for(int i=0;i<len;i++)
        if(str[i]=='@')pos=i;
    str[pos]='\0';
    return Address(readstr(str+pos+1),readstr(str));
    }

int main(){
    freopen("letter.in","r",stdin);
    freopen("cy.out","w",stdout);
    
    top++;
    for(int i='0';i<='9';i++){
        trun[i]=top++;
        to[top-1]=i;
        }
    for(int i='a';i<='z';i++){
        trun[i]=top++;
        to[top-1]=i;
    }
    for(int i='A';i<='Z';i++){
        trun[i]=top++;
        to[top-1]=i;
    }
    
    //read MTA
    while(1){
        scanf("%s",str);
        if(str[0]=='*')break;
        readmta();
        }
    while(1){
        scanf("%s",str);
        if(str[0]=='*')break;
        Address sender = dealAddress(str);
        map<STR,vector<STR> > resiver;//mta user
        map<STR,set<STR> > multi;
        vector<STR> address;
        //read address
        while(1){
            scanf("%s",str);
            if(str[0]=='*')break;
            Address add = dealAddress(str);
            if(!resiver.count(add.first))
                address.push_back(add.first);
            if(multi[add.first].insert(add.second).second)
                resiver[add.first].push_back(add.second);
            }
        //read message
        char c;
        do c=getchar(); while(c!='\n');
        n=0;
        while(1){
            n++;
            gets(message[n]);
            if(message[n][0]=='*')break;
            }
        message[n][0]='.';message[n][1]='\0';
        
        //send
        for(int i=0;i<(int)address.size();i++){
            vector<STR> user = resiver[address[i]];
            printf("Connection between ");output(sender.first);printf(" and ");
            output(address[i]);printf("\n");
            
            printf("     HELO ");output(sender.first);printf("\n");
            printf("     250\n");
            printf("     MAIL FROM:<");output(sender.second);printf("@");output(sender.first);printf(">\n");
            printf("     250\n");
            bool ok=0;
            for(int j=0;j<(int)user.size();j++){
                printf("     RCPT TO:<");output(user[j]);printf("@");output(address[i]);printf(">\n");
                if(!mta[address[i]].count(user[j]))
                    printf("     550\n");
                else{
                    ok=1;
                    printf("     250\n");
                    }
                }
            if(ok){
                printf("     DATA\n     354\n");
                for(int i=1;i<=n;i++){
                    printf("     ");puts(message[i]);
                    }
                printf("     250\n");
                }
            printf("     QUIT\n     221\n");
            }
        }
    
    return 0;
}
