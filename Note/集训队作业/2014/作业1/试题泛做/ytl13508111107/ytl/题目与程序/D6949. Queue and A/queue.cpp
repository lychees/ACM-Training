#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;

const int maxn=30;

struct Event
{
    LL time,last,id;
    Event(){}
    Event(LL time,LL last,LL id):time(time),last(last),id(id){}
    bool operator <(const Event&B)const
    {
        return time<B.time;
    }
};
struct Peo
{
    LL time,value,no,id;
    Peo(){}
    Peo(LL time,LL value,LL no,LL id):time(time),value(value),no(no),id(id){}
    bool operator <(const Peo&B)const
    {
        //return time>B.time || (time==B.time && value>B.value) || (time==B.time && value==B.value && no>B.no);
        return time>B.time;
    }
};
bool cmp(const Peo&A,const Peo&B)
{
    return A.value<B.value || (A.value==B.value && A.no<B.no);
}
vector<Event> event;
queue<Event> needtodeal[maxn];
priority_queue<Peo> men;
vector<Peo> empty;
vector<int> like[maxn];
int map[maxn],value,n;
int findEventMap(int id)
{
    for(int i=1;i<=n;i++)
        if(map[i]==id)
            return i;
    return 0;
}
void solve()
{
    sort(event.begin(),event.end());
    vector<Peo> empty2;
    
    for(int e=0;e<(int)event.size();)
    {
        int t=event[e].time;
        if(men.empty() || men.top().time>=event[e].time)
        {
            while(e<(int)event.size() && event[e].time==t)
            {
                needtodeal[findEventMap(event[e].id)].push(event[e]);
                e++;
            }
        }
        if(!men.empty() && men.top().time <= t)
        {
            t=men.top().time;
            while(!men.empty())
            {
                if(men.top().time<=t)
                {
                empty.push_back(men.top());
                men.pop();
                }else break;
            }
        }
        sort(empty.begin(),empty.end(),cmp);
        empty2.clear();
        for(int i=0;i<(int)empty.size();i++)
        {
            Peo p=empty[i];
            int id=p.id,ok=0;
            for(int j=0;j<(int)like[id].size();j++)
            {
                int map=findEventMap(like[id][j]);
                if(!needtodeal[map].empty())
                {
                    p.time=t+needtodeal[map].front().last;
                    p.value=++value;
                    needtodeal[map].pop();
                    men.push(p);
                    ok=1;
                    break;
                }
            }
            if(!ok)empty2.push_back(p);
        }
        empty.clear();
        for(int i=0;i<(int)empty2.size();i++)
            empty.push_back(empty2[i]);
    }
    while(1)
    {
        bool haveEvent=0;
        for(int i=0;i<maxn;i++)
            if(!needtodeal[i].empty())
                haveEvent=1;
        if(!haveEvent)break;
        int t=men.top().time;
        while(!men.empty())
        {
            if(men.top().time<=t)
            {
            empty.push_back(men.top());
            men.pop();
            }else break;
        }
        sort(empty.begin(),empty.end(),cmp);
        empty2.clear();
        for(int i=0;i<(int)empty.size();i++)
        {
            Peo p=empty[i];
            int id=p.id,ok=0;
            for(int j=0;j<(int)like[id].size();j++)
            {
                int map=findEventMap(like[id][j]);
                if(!needtodeal[map].empty())
                {
                    p.time+=needtodeal[map].front().last;
                    p.value=++value;
                    needtodeal[map].pop();
                    men.push(p);
                    ok=1;
                    break;
                }
            }
            if(!ok)empty2.push_back(p);
        }
        empty.clear();
        for(int i=0;i<(int)empty2.size();i++)
            empty.push_back(empty2[i]);
    }
    
    LL ans=0;
    while(!men.empty())
    {
        ans=men.top().time;
        men.pop();
    }
    cout<<"All requests are serviced within "<<ans<<" minutes."<<endl;
}
int main()
{
    freopen("queue.in","r",stdin);
    freopen("queue.out","w",stdout);
    scanf("%d",&n);
    int a,b,c,d,e,f,g;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
        map[i]=a;
        for(int j=1;j<=b;j++)
            event.push_back(Event(LL(c)+LL(e)*LL(j)-LL(e),d,a));
    }
    int p,x;
    scanf("%d",&p);
    for(int i=1;i<=p;i++)
    {
        scanf("%d%d",&f,&g);
        empty.push_back(Peo(0,-1,f,i));
        while(g--)
        {
            scanf("%d",&x);
            like[i].push_back(x);
        }
    }
    solve();
    
    return 0;
}
