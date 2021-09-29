#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int,int> Chat;
typedef pair<int,int> Room;

const int maxn = 1010;
int w,r,used[maxn];
Chat chat[maxn];
Room room[maxn];
bool init(){
    if(scanf("%d",&w)!=1 || !w)
        return false;
    for(int i=1;i<=w;i++)
        scanf("%d%d",&chat[i].first,&chat[i].second);
    scanf("%d",&r);
    for(int i=1;i<=r;i++){
        int x;char str[20];
        scanf("%d%s",&x,str);
        room[i].first = ((str[0]-'0')*10+(str[1]-'0'))*60 + (str[3]-'0')*10+(str[4]-'0') - 14*60;
        room[i].second = x;
        }
    return true;
    }
void debug(){
    for(int i=1;i<=r;i++)
        printf("%d %d\n",room[i].first,room[i].second);
    }
int main()
{
    freopen("work.in","r",stdin);
    freopen("work.out","w",stdout);
    int kase = 0;
    while(init()){
        //debug();
        
        sort(room+1,room+1+r);
        for(int i=1;i<=w;i++)
            used[i]=0;
        for(int i=1;i<=r;i++){
            int pos = 0;
            for(int j=1;j<=w;j++)
                if(!used[j] && chat[j].second<=room[i].first && chat[j].first<=room[i].second
                     && (pos==0 || chat[j].first>=chat[pos].first))
                    pos = j;
            used[pos]=1;
            }
        int numc=0,numm=0;
        for(int i=1;i<=w;i++)
            if(!used[i]){
                numc++;
                numm+=chat[i].first;
                }
        printf("Trial %d: %d %d\n",++kase,numc,numm);
        }
    
    return 0;   
}
